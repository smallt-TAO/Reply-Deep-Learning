from scipy.misc import imsave
from gensim.models import word2vec
import numpy as np


def train_model():
    sentences = word2vec.Text8Corpus(u'../data/lin')
    print("Train the model.")
    model = word2vec.Word2Vec(sentences, size=3)
    print("Save the model.")
    model.save(u"../model/lin.model")


def infer_model():
    model_infer = word2vec.Word2Vec.load("../model/lin.model")

    matrix_size = 400
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
                grb_matrix[i][j] = [0, 0, 0]

    print(grb_matrix[:][:][0])

    matrix_max, matrix_min = max(pix), min(pix)
    gap = matrix_max - matrix_min
    for i in range(matrix_size):
        for j in range(matrix_size):
            try:
                edge_vector = model_infer[str(i) + '->' + str(j)]
                edge_temp = list()
                for e in edge_vector:
                    edge_temp.append((e - matrix_min) / gap * 255)
                grb_matrix[i][j] = edge_temp
            except:
                grb_matrix[i][j] = [0, 0, 0]

    imsave("../result/demo_color.png", np.array(grb_matrix))


if __name__ == '__main__':
    # train_model()
    infer_model()
