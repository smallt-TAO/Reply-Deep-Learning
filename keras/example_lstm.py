#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
__author__ = 'Smalltao'
demo for the rnn lstm.
"""
from __future__ import print_function
import numpy as np
import matplotlib.pyplot as plt

from keras.models import Sequential
from keras.layers import LSTM, Dense, Activation


def load_data():
	train_x, train_y, test_x, test_y = 1, 1, 1, 1
	train_x = np.array((1, 2), dtype=np.int32)
	return train_x, train_y, test_x, test_y


def build_model():
	model = Sequential()
	model.add(LSTM(input_dim=1, output_dim=50, return_sequences=True))
	print(model.layers)
	model.add(LSTM(100, return_sequences=False))
	print(model.layers)
	model.add(Dense(output_dim=1))
	model.add(Activation('linear'))

	model.compile(loss='mse', optimizer='gsd')

	return model


def main():
	train_x, train_y, test_x, test_y = load_data()
	model = build_model()
	predict = []

	try:
		model.fit(train_x, train_y, batch_size=512, np_epoch=100, validation_split=0.1)
		predict = model.predict(test_x)
		predict = np.reshape(predict, (predict.size,))
	except KeyboardInterrupt:
		print(predict)
		print(test_y)
	print(predict)
	print(test_y)

	# plot the figure
	plt.figure(1)
	plt.plot(predict, 'r:')
	plt.plot(test_y, 'g-')
	plt.legend(['predict', 'true'])

	return predict, test_y


if __name__ == '__main__':
	Predict, Test_y = main()

	# some action for code.
	accuracy = 0.001

	# save the file
	f = open("demo.txt", 'a')
	f.write(str(accuracy))
	f.write('\n')
	f.close()
