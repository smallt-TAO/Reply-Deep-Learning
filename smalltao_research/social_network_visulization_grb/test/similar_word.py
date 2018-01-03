from gensim.models import word2vec


def similar_test():
    model_infer = word2vec.Word2Vec.load("data/lin.model")
    for i in range(40):
        print(str(i), model_infer.most_similar(str(i), topn=10)[0][0])


if __name__ == '__main__':
    similar_test()
