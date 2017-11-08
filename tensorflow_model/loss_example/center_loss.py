#  -*- coding: utf-8 -*-

def get_center_loss(features, labels, alpha, num_classes):
    len_features = features.get_shape()[1]
    centers = tf.get_variable('centers', [num_classes, len_features], dtype=tf.float32,
        initializer=tf.constant_initializer(0), trainable=False)
    labels = tf.reshape(labels, [-1])

    centers_batch = tf.gather(centers, labels)
    loss = tf.div(tf.nn.l2_loss(features - centers_batch),int(len_features))
    diff = centers_batch - features
    unique_label, unique_idx, unique_count = tf.unique_with_counts(labels)
    appear_times = tf.gather(unique_count, unique_idx)
    appear_times = tf.reshape(appear_times, [-1, 1])

    diff = diff / tf.cast((1 + appear_times), tf.float32)
    diff = alpha * diff

    centers_update_op = tf.scatter_sub(centers, labels, diff)
    return loss, centers_update_op

with tf.variable_scope('loss_scope'):
    self.centerloss,self.centers_update_op = get_center_loss(self.features,
                        self.y,
                        0.5,
                        self.CLASSNUM)
    #self.loss = tf.losses.softmax_cross_entropy(onehot_labels=util.makeonehot(self.y, self.CLASSNUM), logits=self.score)
    self.loss = tf.losses.sparse_softmax_cross_entropy(
                                                    labels=self.y, 
                                                    logits=self.score)
                + 0.05 * self.centerloss
    # tf.summary.scalar('loss',self.loss)

with tf.control_dependencies([self.centers_update_op]):
     self.train_op = tf.train.MomentumOptimizer(0.001, 0.9).minimize(self.loss)

