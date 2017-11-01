#! /urs/bin/env python
# _*_ coding=UTF-8 _*_

"""
__author__ = 'Smalltao'
cnn rnn compel the structure.
"""
from __future__ import print_function
import numpy as np

import theano
import theano.tensor as T

import lasagne
from lasagne import layers
from lasagne.nonlinearities import rectify, softmax, sigmoid, tanh

floatX = theano.config.floatX
batch_size = 32


def build_network():
    batch_norm = False
    num_units = 500  # rnn hidden units number
    l2 = 0.0  # l2 regularization
    dropout = 0.5

    input_var = T.tensor4('input_var')
    answer_var = T.ivector('answer_var')

    print('==> building network')
    example = np.random.uniform(size=(batch_size, 1, 128, 858), low=0.0, high=1.0).astype(np.float32)
    answer = np.random.randint(low=0, high=176, size=(batch_size, ))

    network = layers.InputLayer(shape=(None, 1, 128, 858), input_var=input_var)
    print(layers.get_output(network).eval({input_var: example}).shape)

    # conv-relu-pool 1
    network = layers.Conv2DLayer(incoming=network, num_filters=16, filter_size=(7, 7),
                                 stride=1, nonlinearity=rectify)
    print(layers.get_output(network).eval({input_var: example}).shape)

    network = layers.MaxPool2DLayer(incoming=network, pool_size=(3, 3), stride=2, pad=2)
    print(layers.get_output(network).eval({input_var: example}).shape)
    if batch_norm:
        network = layers.BatchNormLayer(incoming=network)

    # conv-relu-pool 2
    network = layers.Conv2DLayer(incoming=network, num_filters=32, filter_size=(5, 5),
                                 stride=1, nonlinearity=rectify)
    print(layers.get_output(network).eval({input_var: example}).shape)

    network = layers.MaxPool2DLayer(incoming=network, pool_size=(3, 3), stride=2, pad=2)
    print(layers.get_output(network).eval({input_var: example}).shape)
    if batch_norm:
        network = layers.BatchNormLayer(incoming=network)

    # conv-relu-pool 3
    network = layers.Conv2DLayer(incoming=network, num_filters=32, filter_size=(5, 5),
                                 stride=1, nonlinearity=rectify)
    print(layers.get_output(network).eval({input_var: example}).shape)

    network = layers.MaxPool2DLayer(incoming=network, pool_size=(3, 3), stride=2, pad=2)
    print(layers.get_output(network).eval({input_var: example}).shape)
    if batch_norm:
        network = layers.BatchNormLayer(incoming=network)

    # conv-relu-pool 4
    network = layers.Conv2DLayer(incoming=network, num_filters=32, filter_size=(3, 3),
                                 stride=1, nonlinearity=rectify)
    print(layers.get_output(network).eval({input_var: example}).shape)

    network = layers.MaxPool2DLayer(incoming=network, pool_size=(3, 3), stride=2, pad=2)
    print(layers.get_output(network).eval({input_var: example}).shape)
    if batch_norm:
        network = layers.BatchNormLayer(incoming=network)

    params = layers.get_all_params(network, trainable=True)
    output = layers.get_output(network)
    output = output.transpose((0, 3, 1, 2))
    output = output.flatten(ndim=3)

    # This params is important
    num_channels = 32
    filter_w = 54
    filter_h = 8

    network = layers.InputLayer(shape=(None, filter_w, num_channels * filter_h), input_var=output)
    print(layers.get_output(network).eval({input_var: example}).shape)

    network = layers.GRULayer(incoming=network, num_units=num_units, only_return_final=True)
    print(layers.get_output(network).eval({input_var: example}).shape)
    if batch_norm:
        network = layers.BatchNormLayer(incoming=network)
    if dropout > 0:
        network = layers.dropout(network, dropout)

    # last layer: classification
    network = layers.DenseLayer(incoming=network, num_units=176, nonlinearity=softmax)
    print(layers.get_output(network).eval({input_var: example}).shape)

    params += layers.get_all_params(network, trainable=True)
    prediction = layers.get_output(network)

    print('==> param shapes', [x.eval().shape for x in params])

    loss_ce = lasagne.objectives.categorical_crossentropy(prediction, answer_var).mean()
    if l2 > 0:
        loss_l2 = l2 * lasagne.regularization.apply_penalty(params, lasagne.regularization.l2)
    else:
        loss_l2 = 0
    loss = loss_ce + loss_l2

    # updates = lasagne.updates.adadelta(loss, params)
    updates = lasagne.updates.momentum(loss, params, learning_rate=0.003)  # good one
    # updates = lasagne.updates.momentum(loss, params, learning_rate=0.0003)  # good one

    print('==> compiling train_fn')
    train_fn = theano.function(inputs=[input_var, answer_var],
                               outputs=[prediction, loss],
                               updates=updates)
    test_fn = theano.function(inputs=[input_var, answer_var],
                              outputs=[prediction, loss])

    return train_fn, test_fn


def load_data():
    data = np.zeros((batch_size, 1, 128, 858), dtype=np.float32)
    answers = []

    return data, answers
