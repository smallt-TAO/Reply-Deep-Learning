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
