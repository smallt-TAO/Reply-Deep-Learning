import matplotlib.pyplot as plt


def read_text(text_path, size=1000):
    res = list()
    avg_res = list()
    with open(text_path, "r") as f:
        text_list = f.readlines()
        for text in text_list:
            res.append(float(text.split(",")[2].split(":")[1].lstrip()))
            avg_res.append(float(text.split(",")[3].split(":")[1].lstrip()))
    return res[:1000], avg_res[:1000]


def plot_res(size):
    x_input = range(size)
    y1, y1_avg = read_text("NAF.txt", size)
    y2, y2_avg = read_text("DDPG.txt", size)
    y3, y3_avg = read_text("DDPG_N.txt", size)
    plt.ylabel(u'Reward Loss')  # fill the meaning of X axis
    plt.xlabel(u'Train Step')  # fill the meaning of Y axis
    plt.plot(x_input, y1_avg, color='r', linestyle='-', label='NAF')
    plt.plot(x_input, y2_avg, color='g', linestyle='--', label='DDPG')
    plt.plot(x_input, y3_avg, color='b', linestyle='-.', label='DDPG_N')
    plt.legend()
    plt.savefig("result.png")
    plt.show()


if __name__ == "__main__":
    plot_res(1000)
