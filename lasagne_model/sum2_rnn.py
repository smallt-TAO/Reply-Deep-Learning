#! /urs/bin/env python
# _*_ coding=UTF-8 _*_

"""
__author__ = 'Smalltao'
Usage example employing Lasagne for two sum add.
"""
from __future__ import print_function

import numpy as np
import theano
import theano.tensor as T
import lasagne

MIN_LENGTH = 50
MAX_LENGTH = 55
N_HIDDEN = 100
N_BATCH = 100
LEARNING_RATE = 0.001
GRAD_CLIP = 100
EPOCH_SIZE = 100
NUM_EPOCHS = 10


def gen_data(min_length=MIN_LENGTH, max_length=MAX_LENGTH, n_batch=N_BATCH):
    """
    Generate a batch of sequences for the "add" task.
    :param min_length:
    :param max_length:
    :param n_batch:
    :return:
    """
    X = np.concatenate([np.random.uniform(size=(n_batch, max_length, 1)),
                        np.zeros((n_batch, max_length, 1))], axis=-1)
    mask = np.zeros((n_batch, max_length))
    y = np.zeros((n_batch, ))
    for n in range(n_batch):
        length = np.random.randint(min_length, max_length)
        mask[n, : length] = 1
        X[n, length:, 0] = 0
        X[n, np.random.randint(length / 10), 1] = 1
        X[n, np.random.randint(length / 2, length), 1] = 1
        y[n] = np.sum(X[n, :, 0] * X[n, :, 1])
    X -= X.reshape(-1, 2).mean(axis=0)
    y -= y.mean()
    return (X.astype(theano.config.floatX), y.astype(theano.config.floatX),
            mask.astype(theano.config.floatX))


def main(num_epochs=NUM_EPOCHS):
    print("Building network ...")
    l_in = lasagne.layers.InputLayer(shape=(N_BATCH, MAX_LENGTH, 2))
    l_mask = lasagne.layers.InputLayer(shape=(N_BATCH, MAX_LENGTH))

    l_forward = lasagne.layers.RecurrentLayer(l_in, N_HIDDEN, mask_input=l_mask,
                                              grad_clipping=GRAD_CLIP,
                                              W_in_to_hid=lasagne.init.HeUniform(),
                                              W_hid_to_hid=lasagne.nonlinearities.tanh,
                                              only_return_final=True)
    l_backward = lasagne.layers.RecurrentLayer(l_in, N_HIDDEN, mask_input=l_mask,
                                               grad_clipping=GRAD_CLIP,
                                               W_in_to_hid=lasagne.init.HeUniform(),
                                               W_hid_to_hid=lasagne.nonlinearities.tanh,
                                               only_return_final=True, backwards=True)

    l_concat = lasagne.layers.ConcatLayer([l_forward, l_backward])
    l_out = lasagne.layers.DenseLayer(l_concat, num_units=1, nonlinearity=lasagne.nonlinearities.tanh)

    target_values = T.vector('target_output')

    network_output = lasagne.layers.get_output(l_out)
    predicted_values = network_output.flatten()
    cost = T.mean(0.5 * (predicted_values - target_values) ** 2)
    all_params = lasagne.layers.get_all_params(l_out)

    print("Computing updates ...")
    updates = lasagne.updates.adagrad(cost, all_params, LEARNING_RATE)
    print("Computing functions ...")
    train = theano.function([l_in.input_var, target_values, l_mask.input_var],
                            cost, updates=updates)
    compute_cost = theano.function([l_in.input_var, target_values, l_mask.input_var], cost)

    X_val, y_val, mask_val = gen_data()

    print("Training...")
    try:
        for epoch in range(num_epochs):
            for _ in range(EPOCH_SIZE):
                X, y, m = gen_data()
                train(X, y, m)
            cost_val = compute_cost(X_val, y_val, mask_val)
            print("Epoch {} validation cost = {}".format(epoch, cost_val))
    except KeyboardInterrupt:
        pass

if __name__ == '__main__':
    main()
