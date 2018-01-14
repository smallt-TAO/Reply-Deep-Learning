from scipy.misc import imsave
import numpy as np
import algorithm01
import network
import random_walk_NV
import word2vec as word2vec


def test_alg(network_matrix):
    matrix_len = len(network_matrix)
    # Find the re array for restore
    _, re_array = algorithm01.matrix_change(network_matrix)
    # print(re_array)

    # Store the train set for Word2vec train.
    test = random_walk_NV.RandomWalk(net)
    test.store_file()

    # train the word2vec embedding.
    word2vec.train_model(size=3)
    color_matrix = word2vec.infer_model(matrix_size=matrix_len)

    # restore the color image.
    res_matrix = [[[255, 255, 255] for _ in range(matrix_len)] for si in range(matrix_len)]
    for i in range(matrix_len):
        for j in range(matrix_len):
            res_matrix[i][j] = color_matrix[re_array[i]][re_array[j]]

    imsave("../result/demo_color.png", np.array(res_matrix))


if __name__ == '__main__':
    # net = network.NetworkGene.scale_free(800, 20, 30)
    net = network.NetworkGene.small_word(800, 20, 0.12)
    test_alg(net)
