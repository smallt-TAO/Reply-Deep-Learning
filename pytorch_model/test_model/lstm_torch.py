from __future__ import print_function

import torch
import torch.nn as nn
from torch.autograd import Variable
import torch.optim as optim
import numpy as np

class Sequence(nn.Module):
    def __init__(self):
        super(Sequence, self).__init__()
        self.lstm1 = nn.LSTMCell(1, 50)
        self.lstm2 = nn.LSTMCell(50, 1)

    def forward(self, input, future=0):
        outputs = []
        h_t = Variable(torch.zeros(input.size(0), 50).double(), requires_grad=False)
        c_t = Variable(torch.zeros(input.size(0), 50).double(), requires_grad=False)
        h_t2 = Variable(torch.zeros(input.size(0), 1).double(), requires_grad=False)
        c_t2 = Variable(torch.zeros(input.size(0), 1).double(), requires_grad=False)

        for i, input_t in enumerate(input.chunk(input.size(1), dim=1)):
            h_t, c_t = self.lstm1(input_t, [h_t, c_t])
            h_t2, c_t2 = self.lstm2(h_t, [h_t2, c_t2])
            outputs += [h_t2]
        for i in range(future):
            h_t, c_t = self.lstm1(h_t2, [h_t, c_t])
            h_t2, c_t2 = self.lstm2(h_t, [h_t2, c_t2])
            outputs += [h_t2]
        outputs = torch.stack(outputs, 1).squeeze(2)
        return outputs

if __name__ == '__main__':
    # set random seed to 0
    np.random.seed(0)
    torch.manual_seed(0)
                
    # load data and make training set
    data = torch.load('traindata.pt')
    input = Variable(torch.from_numpy(data[3:, :-1]), requires_grad=False)
    target = Variable(torch.from_numpy(data[3:, 1:]), requires_grad=False)
    
    # build the model
    seq = Sequence()
    seq.double() 
    criterion = nn.MSELoss()
    optimizer = optim.LBFGS(seq.parameters(), lr=0.8)

    for i in range(15):
        def closure():
            optimizer.zero_grad()
            out = seq(input)
            loss = criterion(out, target)
            print('loss:', loss.data.numpy()[0])
            loss.backward()
            return loss
        optimizer.step(closure)



