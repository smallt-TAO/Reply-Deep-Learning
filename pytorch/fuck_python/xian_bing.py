# Solve the question

dp_value = [[0 for i in range(11)] for _ in range(4)]

# init dp_value
dp_value[3][8] = 1
dp_value[2][7] = 2
dp_value[1][5] = 1
dp_value[1][4] = 1
dp_value[1][6] = 1

for i in range(3, 0, -1):
    for j in range(1, 10):
        temp = max(dp_value[i][j], dp_value[i][j - 1], dp_value[i][j + 1])
        dp_value[i - 1][j] += temp
        
print dp_value[0][5] 

