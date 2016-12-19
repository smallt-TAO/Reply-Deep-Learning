#! /urs/bin/env python
# _*_ coding=UTF-8 _*_

"""
__author__ = 'Smalltao'
Usage example employing Lasagne for digit recognition using
the MNIST data.
"""
from __future__ import print_function

import sys
import os
import time

import numpy as np
import theano
import theano.tensor as T
import lasagne


def load_data_set():
    if sys.version_info[0] == 2:
        from urllib import urlretrieve
    else:
        from urllib.request import urlretrieve

    def download(filename, source='http://yann.lecun.com/exdb/mnist/'):
        print("Downloading %s" % filename)
        urlretrieve(source + filename, filename)

    import gzip

    def load_mnist_images(filename):
        if not os.path.exists(filename):
            download(filename)
        with gzip.open(filename, 'rb') as f:
            data = np.frombuffer(f.read(), np.uint8, offset=16)
        data = data.reshape(-1, 1, 28, 28)
        return data / np.float32(256)

    def load_mnist_labels(filename):
        if not os.path.exists(filename):
            download(filename)
        with gzip.open(filename, 'rb') as f:
            data = np.frombuffer(f.read(), np.uint8, offset=8)
        return data

    X_train = load_mnist_images('train-images-idx3-ubyte.gz')
    y_train = load_mnist_labels('train-labels-idx1-ubyte.gz')
    X_test = load_mnist_images('t10k-images-idx3-ubyte.gz')
    y_test = load_mnist_labels('t10k-labels-idx1-ubyte.gz')

    X_train, X_val = X_train[:-10000], X_train[-10000:]
    y_train, y_val = y_train[:-10000], y_train[-10000:]

    return X_train, y_train, X_val, y_val, X_test, y_test


def build_mlp(input_var=None):
    l_in = lasagne.layers.InputLayer(shape=(None, 1, 28, 28), input_var=input_var)
    print(lasagne.layers.get_output(l_in).eval({input_var: input_var}).shape)

    l_in_drop = lasagne.layers.DropoutLayer(l_in, p=0.2)
    print(lasagne.layers.get_output(l_in_drop).eval({input_var: input_var}).shape)

    l_hid1 = lasagne.layers.DenseLayer(
        l_in_drop,
        num_units=800,
        nonlinearity=lasagne.nonlinearities.rectify,
        w=lasagne.init.GlorotUniform()
    )
    print(lasagne.layers.get_output(l_hid1).eval({input: in}))

