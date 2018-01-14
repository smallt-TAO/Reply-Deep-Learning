# !/usr/bin/env python
# -*- coding: utf-8 -*-

"""
本段代码为了将VRAA处理前后的顶点对应关系求出。
由于后面并没有使用，所以搁置这里。
"""

from numpy import *
import copy


def matrix_change(matrix):
    m = len(matrix)
    matrix_d = [0] * m
    for i in range(m):
        for j in range(m):
            if matrix[i][j] == 1:
                matrix_d[i] += 1
    dict_d = {}
    for i in range(m):
        dict_d[i] = matrix_d[i]
    max_d = max(matrix_d)
    matrix_d_new = []
    for num_v in range(max_d, 0, -1):
        for (k, v) in dict_d.items():
            if v == num_v:
                matrix_d_new.append(k)
    array_new = matrix_alter0(matrix, max_d, matrix_d)
    matrix_new, matrix_new_array = matrix_alter(array_new, matrix)

    return matrix_new, matrix_new_array


def matrix_random(matrix):
    m = len(matrix)
    array = [i for i in range(m)]
    random.shuffle(array)
    matrix_new = [([0] * m) for si in range(m)]
    for i in range(m):
        for j in range(m):
            matrix_new[i][j] = matrix[array[i]][array[j]]

    return matrix_new, array


def matrix_alter(array_d, matrix):
    m = len(matrix)
    matrix_v = [array_d[0]]
    flag = True
    for i in range(1, m):
        if flag:
            matrix_v.append(array_d[i])
            flag = False
        else:
            matrix_v.insert(0, array_d[i])
            flag = True

    matrix_new = [([0] * m) for si in range(m)]
    for i in range(m):
        for j in range(m):
            matrix_new[i][j] = matrix[matrix_v[i]][matrix_v[j]]

    return matrix_new, matrix_v


def matrix_alter0(matrix, max_num, matrix_d):
    m = len(matrix)
    matrix_d_new = []

    for i in range(max_num, -1, -1):
        array_new = []
        size_new = len(matrix_d_new)
        loss_array = [0] * m
        loss = m
        for j in range(size_new):
            loss_array[matrix_d_new[j]] = loss
            loss -= 1
        for j in range(m):
            if matrix_d[j] == i:
                array_new.append(j)
        if len(array_new) != 0 and i != max_num:
            iter_num = len(array_new)
            iter_array = []
            iter_flag = [True] * iter_num
            for kk in range(iter_num):
                mat_1 = matrix[array_new[kk]]
                sum_num = 0
                for run in range(size_new):
                    sum_num += mat_1[matrix_d_new[run]] * loss_array[matrix_d_new[run]]
                iter_array.append(sum_num)
            iter_array_or = copy.deepcopy(iter_array)
            iter_array.sort()
            iter_array.reverse()
            for k in iter_array:
                for l in range(iter_num):
                    if iter_array_or[l] == k and iter_flag[l] is True:
                        matrix_d_new.append(array_new[l])
                        iter_flag[l] = False
                        break
        if i == max_num:
            matrix_d_new.extend(array_new)

    return matrix_d_new
