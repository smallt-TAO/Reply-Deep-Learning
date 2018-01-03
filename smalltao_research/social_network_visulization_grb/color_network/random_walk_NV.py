# smalltao
# 20171229

from random import choice
import network


class RandomWalk(object):
    def __init__(self, matrix):
        self.back_able = True
        self.matrix = matrix

    @staticmethod
    def matrix_dict(adjacency_matrix):
        adj_dict = dict()

        assert len(adjacency_matrix) == len(adjacency_matrix[0])
        for vertex in range(len(adjacency_matrix)):
            temp = list()
            for col in range(len(adjacency_matrix)):
                if adjacency_matrix[vertex][col] == 1:
                    temp.append(str(col))
            adj_dict[str(vertex)] = temp

        return adj_dict

    @staticmethod
    def edge_cnt(adjacency_matrix):
        e_cnt = 0
        for i in range(len(adjacency_matrix)):
            for j in range(len(adjacency_matrix)):
                if adjacency_matrix[i][j] == 1:
                    e_cnt += 1
        return e_cnt

    @staticmethod
    def dict_path(adjacency_dict, step=5):
        root_path = [i for i in range(len(adjacency_dict))]
        root_vertex = list()
        root_vertex.append(str(choice(root_path)))

        while step:
            step_temp = root_vertex[-1]
            step_next_temp = choice(adjacency_dict[step_temp])
            root_vertex.append(step_temp + '->' + step_next_temp)
            root_vertex.append(step_next_temp)
            step -= 1

        return root_vertex

    def store_file(self, loop=100, file_name='../data/lin'):
        # store the origin
        for i in range(len(self.matrix)):
            tem = [str(v) for v in self.matrix[i]]
            with open(file_name + '-origin', 'a') as fl:
                print(' '.join(tem), sep=' ', end='\n', file=fl)

        # store the train files
        edge_cnt = self.edge_cnt(self.matrix)
        mtr_dict = self.matrix_dict(self.matrix)
        for i in range(loop):
            tex = self.dict_path(mtr_dict, step=edge_cnt)
            with open(file_name, 'a') as fl:
                print(' '.join(tex) + ' ', sep=' ', end='', file=fl)
        pass


if __name__ == '__main__':
    net = network.NetworkGene.scale_free(400, 3, 50)

    test = RandomWalk(net)
    test.store_file()






