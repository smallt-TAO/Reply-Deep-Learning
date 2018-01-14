import random

__author__ = 'Smalltao'


class NetworkGene(object):
    def __init__(self):
        pass

    @staticmethod
    def scale_free(size, num, m, key_p=0):
        """
        :param size: size of the matrix.
        :param num: size of the matrix begin.
        :param m: size of limit.
        :return: matrix_b
        """
        # init the matrix
        matrix_b = [([0] * size) for _ in range(size)]
        for i in range(num):
            for j in range(i):
                matrix_b[i][j], matrix_b[j][i] = 1, 1
        # init the degree of vector.
        degree_b = [0] * size
        for i in range(num):
            degree_b[i] = num - 1
        # add the vector
        for i in range(num, size):
            mm, dd = 0, degree_b[:i]
            while mm < m:
                mm += 1
                degree_n = 0
                for j in range(i):
                    degree_n += dd[j]
                p = [0] * i
                p[0] = dd[0] / (degree_n + 0.000001)
                for j in range(1, i):
                    p[j] = p[j - 1] + dd[j] / (degree_n + 0.000001)
                for j in range(i):
                    if random.random() < p[j]:
                        if random.random() > key_p:
                            matrix_b[i][j], matrix_b[j][i] = 1, 1
                            degree_b[i] += 1
                            degree_b[j] += 1
                            dd[j] = 0
                            break
        return matrix_b

    @staticmethod
    def normal_word(size, k):
        matrix_b = [([0] * size) for _ in range(size)]
        for i in range(size):
            for j in range(i + 1, i + k / 2 + 1):
                if j < size:
                    matrix_b[i][j] = 1
                    matrix_b[j][i] = 1
                else:
                    matrix_b[i][j - size] = 1
                    matrix_b[j - size][i] = 1

        return matrix_b

    @staticmethod
    def small_word(size, k, p):
        matrix_b = [([0] * size) for _ in range(size)]
        for i in range(size):
            for j in range(i + 1, int(i + k / 2 + 1)):
                if j < size:
                    matrix_b[i][j] = 1
                    matrix_b[j][i] = 1
                else:
                    matrix_b[i][j - size] = 1
                    matrix_b[j - size][i] = 1
        # create the small word
        for i in range(size):
            for j in range(i + 1, size):
                if matrix_b[i][j] != 0:
                    if random.random() < p:
                        matrix_b[i][j] = 0
                        matrix_b[j][i] = 0
                        s = random.randint(i + 1, size - 1)
                        matrix_b[i][s] = 1
                        matrix_b[s][i] = 1

        return matrix_b


