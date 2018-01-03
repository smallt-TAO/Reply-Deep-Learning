# !/usr/bin/env python
# -*- coding: utf-8 -*-
"""
This code for algorithm.
这段代码就是VRAA算法的核心代码。

"""

from numpy import *
import copy


def pre_handle(matrix):
    """
    For the nn networks better work.
    该函数为了处理网络替代后违背无向图对应的amb图像性质。
    :param matrix:
    :return:
    """
    iter_num, m = 0, len(matrix)
    matrix_d = [0] * m
    for i in range(m):
        for j in range(m):
            if matrix[i][j] == 1:
                matrix_d[i] += 1
    dict_d = dict()
    for i in range(m):
        dict_d[i] = matrix_d[i]
    if max(matrix_d) == min(matrix_d):
        for i in range(m):
            for j in range(m):
                if matrix[i][j] == 0:
                    matrix[i][i] = 1
                    matrix[j][i] = 1
                    return matrix
    return matrix


def matrix_change(matrix):
    # 该函数是算法的核心函数。
    m = len(matrix)
    matrix_d = [0] * m
    for i in range(m):
        for j in range(m):
            if matrix[i][j] == 1:
                matrix_d[i] += 1
    dict_d = dict()
    for i in range(m):
        dict_d[i] = matrix_d[i]
    max_d = max(matrix_d)
    matrix_d_new = list()
    for num_v in range(max_d, 0, -1):
        for (k, v) in dict_d.items():
            if v == num_v:
                matrix_d_new.append(k)
    array_new = matrix_alter1(matrix, max_d, matrix_d)
    matrix_new = matrix_alter(array_new, matrix)

    return matrix_new


def matrix_random(matrix):
    # 该函数是将网络顶点编号更加的随机。
    m = len(matrix)
    array = [i for i in range(m)]
    random.shuffle(array)
    matrix_new = [([0] * m) for si in range(m)]
    for i in range(m):
        for j in range(m):
            matrix_new[i][j] = matrix[array[i]][array[j]]

    return matrix_new


def matrix_alter(array_d, matrix):
    # 放置环节
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

    return matrix_new


def matrix_alter0(matrix, max_num, matrix_d):
    # 重新排序的简单版
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


def matrix_alter1(matrix, max_num, matrix_d):
    # 重新排序的豪华版
    m = len(matrix)
    matrix_d_new = []
    # behind the Point we talked.
    array_behind = [0 for si in range(m)]
    for behind_j in range(1, max_num + 1):
        for i in range(m):
            for j in range(m):
                if matrix_d[i] == behind_j and matrix[i][j] == 1 and matrix_d[j] == behind_j + 1:
                    array_behind[j] += 1

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
                sum_num += array_behind[array_new[kk]]
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
        if i == max_num:  # handle the same d.
            new_s = array_new[0]
            for start_i in range(len(array_new) - 1):
                matrix_d_new.append(new_s)
                array_new.remove(new_s)
                for start_j in range(m):
                    if matrix[new_s][start_j] == 1 and (start_j in array_new):
                        new_s = start_j
                        break
                    if matrix[new_s][start_j] == 0 and (start_j in array_new):
                        new_s = start_j
                        break

            matrix_d_new.extend(array_new)

    return matrix_d_new
