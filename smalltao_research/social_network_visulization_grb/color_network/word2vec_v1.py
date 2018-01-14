from scipy.misc import imsave
from gensim.models import word2vec
import numpy as np


def train_model(size=3):
    sentences = word2vec.Text8Corpus(u'../data/lin')
    print("Train the model.")
    model = word2vec.Word2Vec(sentences, size)
    print("Save the model.")
    model.save(u"../model/lin.model")


def max_min_normalization(x, x_max, x_min):
    return (x - x_min) / (x_max - x_min)


def sigmoid(input_x):
        return 1.0 / (1 + np.exp(-float(input_x)))


def infer_model(matrix_size=400):
    model_infer = word2vec.Word2Vec.load("../model/lin.model")

    # matrix_size = 400
    pix = list()
    grb_matrix = [[[255, 255, 255] for _ in range(matrix_size)] for si in range(matrix_size)]
    for i in range(matrix_size):
        for j in range(matrix_size):
            try:
                edge_vector = model_infer[str(i) + '->' + str(j)]
                edge_temp = list()
                for e in edge_vector:
                    edge_temp.append(e)
                    pix.append(e)
                grb_matrix[i][j] = edge_temp
            except:
                node_1, node_2 = model_infer[str(i)], model_infer[str(j)]
                edge_temp = list()
                for ran in range(3):
                    gap = (node_1[ran] - node_2[ran]) / 2
                    edge_temp.append(gap)
                    pix.append(gap)
                grb_matrix[i][j] = edge_temp

    grb_matrix = np.array(grb_matrix)
    # print(grb_matrix[:, :, 0])

    matrix_max, matrix_min = max(pix), min(pix)
    for i in range(matrix_size):
        for j in range(matrix_size):
            try:
                edge_vector = model_infer[str(i) + '->' + str(j)]
                edge_temp = list()
                for e in edge_vector:
                    # edge_temp.append(max_min_normalization(e, matrix_max, matrix_min))
                    edge_temp.append(sigmoid(e))
                grb_matrix[i][j] = edge_temp
            except:
                node_1, node_2 = model_infer[str(i)], model_infer[str(j)]
                edge_temp = list()
                for ran in range(3):
                    gap = (node_1[ran] - node_2[ran]) / 2
                    edge_temp.append(sigmoid(gap))
                    pix.append(sigmoid(gap))
                grb_matrix[i][j] = edge_temp

    # imsave("../result/demo_color.png", np.array(grb_matrix))
    return np.array(grb_matrix)


if __name__ == '__main__':
    # train_model()
    infer_model()
