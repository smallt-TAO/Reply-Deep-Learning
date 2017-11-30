""" 
Implementation of DDPG - Deep Deterministic Policy Gradient

Algorithm and hyperparameter details can be found here: 
    http://arxiv.org/pdf/1509.02971v2.pdf

The algorithm is tested on the Pendulum-v0 OpenAI gym task 
and developed with Tensorflow

Authors: 
Patrick Emami
Shusen Wang
"""
import tensorflow as tf
import numpy as np
import gym
from gym import wrappers
# from neural_network import NeuralNetworks
from neural_network_share_weight import NeuralNetworks
from replay_buffer import ReplayBuffer

# ==========================
#   Training Parameters
# ==========================
# Max training steps
MAX_EPISODES = 50000
# Max episode length
MAX_EP_STEPS = 1000
# Base learning rate for the Actor network
ACTOR_LEARNING_RATE = 0.0001
# Base learning rate for the Critic Network
CRITIC_LEARNING_RATE = 0.001
# Discount factor
GAMMA = 0.99
# Soft target update param
TAU = 0.001

# ===========================
#   Utility Parameters
# ===========================
# Render gym env during training
RENDER_ENV = True
# Use Gym Monitor
GYM_MONITOR_EN = True
# Gym environment
ENV_NAME = 'Pendulum-v0'
# Directory for storing gym results
MONITOR_DIR = './results/gym_ddpg'
# Directory for storing tensorboard summary results
SUMMARY_DIR = './results/tf_ddpg'
# File for saving reward and qmax
RESULTS_FILE = './results/rewards.npz'
RANDOM_SEED = 1234
# Size of replay buffer
BUFFER_SIZE = 10000
MINIBATCH_SIZE = 128



class Actor():
    
    def __init__(self, sess, network, learning_rate):
        self.sess = sess
        self.learning_rate = learning_rate
        _, self.a_dim, _ = network.get_const()
        
        self.inputs = network.get_input_state(is_target=False)
        self.out = network.get_actor_out(is_target=False)
        self.params = network.get_actor_params(is_target=False)
        
        # This gradient will be provided by the critic network
        self.critic_gradient = tf.placeholder(tf.float32, [None, self.a_dim])

        # Combine the gradients
        self.policy_gradient = tf.gradients(tf.multiply(self.out, -self.critic_gradient), self.params)
        
        # Optimization Op        
        self.optimize = tf.train.AdamOptimizer(self.learning_rate).\
            apply_gradients(zip(self.policy_gradient, self.params))
        
    def train(self, state, c_gradient):
        self.sess.run(self.optimize, feed_dict={
            self.inputs: state,
            self.critic_gradient: c_gradient
        })

    def predict(self, state):
        return self.sess.run(self.out, feed_dict={
            self.inputs: state
        })
    

class ActorTarget():
    
    def __init__(self, sess, network, tau):
        self.sess = sess
        self.tau = tau
        
        self.inputs = network.get_input_state(is_target=True)
        self.out = network.get_actor_out(is_target=True)
        self.params = network.get_actor_params(is_target=True)
        param_num = len(self.params)
        self.params_other = network.get_actor_params(is_target=False)
        assert(param_num == len(self.params_other))
        
        # update target network
        self.update_params = \
            [self.params[i].assign(tf.multiply(self.params_other[i], self.tau) +
                                                  tf.multiply(self.params[i], 1. - self.tau))
                for i in range(param_num)]
    
    def train(self):
        self.sess.run(self.update_params)

    def predict(self, state):
        return self.sess.run(self.out, feed_dict={self.inputs: state})
        
        
class Critic:
    def __init__(self, sess, network, learning_rate):
        self.sess = sess
        self.learning_rate = learning_rate

        # Create the critic network
        self.state, self.action = network.get_input_state_action(is_target=False)
        self.out = network.get_critic_out(is_target=False)
        self.params = network.get_critic_params(is_target=False)
        
        # Network target (y_i)
        self.predicted_q_value = tf.placeholder(tf.float32, [None, 1])

        # Define loss and optimization Op
        #self.loss = tflearn.mean_square(self.predicted_q_value, self.out)
        self.loss = tf.nn.l2_loss(self.predicted_q_value - self.out)
        self.optimize = tf.train.AdamOptimizer(self.learning_rate).minimize(self.loss)

        self.action_grads = tf.gradients(self.out, self.action)

    def train(self, state, action, predicted_q_value):
        return self.sess.run([self.out, self.optimize], feed_dict={
            self.state: state,
            self.action: action,
            self.predicted_q_value: predicted_q_value
        })

    def predict(self, state, action):
        return self.sess.run(self.out, feed_dict={
            self.state: state,
            self.action: action
        })
        
    def action_gradients(self, state, actions):
        return self.sess.run(self.action_grads, feed_dict={
            self.state: state,
            self.action: actions
        })
        
class CriticTarget:
    def __init__(self, sess, network, tau):
        self.sess = sess
        self.tau = tau

        # Create the critic network
        self.state, self.action = network.get_input_state_action(is_target=True)
        self.out = network.get_critic_out(is_target=True)
        
        # update target network
        self.params = network.get_critic_params(is_target=True)
        param_num = len(self.params)
        self.params_other = network.get_critic_params(is_target=False)
        assert(param_num == len(self.params_other))
        self.update_params = \
            [self.params[i].assign(tf.multiply(self.params_other[i], self.tau) + tf.multiply(self.params[i], 1. - self.tau))
                for i in range(param_num)]
            
    def predict(self, state, action):
        return self.sess.run(self.out, feed_dict={
            self.state: state,
            self.action: action
        })

    def train(self):
        self.sess.run(self.update_params)
        

# ===========================
#   Tensorflow Summary Ops
# ===========================


def build_summaries():
    episode_reward = tf.Variable(0.)
    tf.summary.scalar("Reward", episode_reward)
    episode_ave_max_q = tf.Variable(0.)
    tf.summary.scalar("Qmax Value", episode_ave_max_q)

    summary_vars = [episode_reward, episode_ave_max_q]
    summary_ops = tf.summary.merge_all()

    return summary_ops, summary_vars

# ===========================
#   Agent Training
# ===========================


def train(sess, env, network):
    arr_reward = np.zeros(MAX_EPISODES)
    arr_qmax = np.zeros(MAX_EPISODES)

    actor = Actor(sess, network, ACTOR_LEARNING_RATE)
    actor_target = ActorTarget(sess, network, TAU)
    critic = Critic(sess, network, CRITIC_LEARNING_RATE)
    critic_target = CriticTarget(sess, network, TAU)
    
    s_dim, a_dim, _ = network.get_const()

    # Set up summary Ops
    summary_ops, summary_vars = build_summaries()

    sess.run(tf.global_variables_initializer())
    writer = tf.summary.FileWriter(SUMMARY_DIR, sess.graph)

    actor_target.train()
    critic_target.train()

    # Initialize replay memory
    replay_buffer = ReplayBuffer(BUFFER_SIZE, RANDOM_SEED)

    for i in range(MAX_EPISODES):

        s = env.reset()

        ep_reward = 0
        ep_ave_max_q = 0

        for j in range(MAX_EP_STEPS):

            if RENDER_ENV:
                env.render()

            # Added exploration noise
            a = actor.predict(np.reshape(s, (1, s_dim))) + (1. / (1. + i))

            s2, r, terminal, info = env.step(a[0])

            replay_buffer.add(np.reshape(s, (s_dim,)), np.reshape(a, (a_dim,)), r,
                              terminal, np.reshape(s2, (s_dim,)))

            # Keep adding experience to the memory until
            # there are at least minibatch size samples
            if replay_buffer.size() > MINIBATCH_SIZE:
                s_batch, a_batch, r_batch, t_batch, s2_batch = \
                    replay_buffer.sample_batch(MINIBATCH_SIZE)

                # Calculate targets
                target_q = critic_target.predict(s2_batch, actor_target.predict(s2_batch))

                y_i = []
                for k in range(MINIBATCH_SIZE):
                    if t_batch[k]:
                        y_i.append(r_batch[k])
                    else:
                        y_i.append(r_batch[k] + GAMMA * target_q[k])

                # Update the critic given the targets
                predicted_q_value, _ = critic.train(s_batch, a_batch, np.reshape(y_i, (MINIBATCH_SIZE, 1)))

                #ep_ave_max_q += np.amax(predicted_q_value)
                ep_ave_max_q += np.mean(predicted_q_value)

                # Update the actor policy using the sampled gradient
                a_outs = actor.predict(s_batch)
                grads = critic.action_gradients(s_batch, a_outs)
                actor.train(s_batch, grads[0])

                # Update target networks
                actor_target.train()
                critic_target.train()

            s = s2
            ep_reward += r

            if terminal:

                summary_str = sess.run(summary_ops, feed_dict={
                    summary_vars[0]: ep_reward,
                    summary_vars[1]: ep_ave_max_q / float(j)
                })

                writer.add_summary(summary_str, i)
                writer.flush()

                print('Reward: ' + str(ep_reward) + ',   Episode: ' + str(i) + ',    Qmax: ' +  str(ep_ave_max_q / float(j)))
                arr_reward[i] = ep_reward
                arr_qmax[i] = ep_ave_max_q / float(j)
                
                if i % 100 == 99:
                    np.savez(RESULTS_FILE, arr_reward[0:i], arr_qmax[0:i])

                break


def main(_):
    with tf.Session() as sess:

        env = gym.make(ENV_NAME)
        np.random.seed(RANDOM_SEED)
        tf.set_random_seed(RANDOM_SEED)
        env.seed(RANDOM_SEED)

        state_dim = env.observation_space.shape[0]
        action_dim = env.action_space.shape[0]
        action_bound = env.action_space.high
        # Ensure action bound is symmetric
        assert (env.action_space.high == -env.action_space.low)

        network = NeuralNetworks(state_dim, action_dim, action_bound)
        

        if GYM_MONITOR_EN:
            if not RENDER_ENV:
                env = wrappers.Monitor(
                    env, MONITOR_DIR, video_callable=False, force=True)
            else:
                env = wrappers.Monitor(env, MONITOR_DIR, force=True)

        train(sess, env, network)

        if GYM_MONITOR_EN:
            env.monitor.close()

if __name__ == '__main__':
    tf.app.run()
