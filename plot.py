import matplotlib.pyplot as plt
import numpy as np

def convert_to_time(t_str):
    t_num = np.zeros(len(t_str))
    for idx, time in enumerate(t_str):
        t_num[idx] = float(time[:-2])
    return t_num

if __name__ == "__main__":
    
    with open('output/rbt_runtime.txt', 'r') as rbt_file:
        rbt_rt = rbt_file.read().split(',')
    with open("output/bst_runtime.txt", 'r') as bst_file:
        bst_rt = bst_file.read().split(',')

    with open('output/rbt_sim.txt', 'r') as rbt_file:
        rbt_sim = rbt_file.read().splitlines()

    with open('output/rbt_sim.txt', 'r') as bst_file:
        bst_sim = bst_file.read().splitlines()

    rbt_sim_rf = []
    for idx, s in enumerate(rbt_sim):
        rbt_sim_rf.append(s.split(','))

    rbt_rt = convert_to_time(rbt_rt)
    bst_rt = convert_to_time(bst_rt)

    plt.figure(1)
    plt.plot(rbt_rt, color = 'r')
    plt.title('Fig 1: Plot of Red-Black Insertion Speed')
    plt.xlabel('Insertion')
    plt.ylabel('μs')
    plt.savefig('./plots/Red_Black_time.jpg')

    plt.figure(2)
    plt.plot(bst_rt, color = 'b')
    plt.title('Fig 2: Plot of Binary-Search Insertion Speed')
    plt.xlabel('Insertion')
    plt.ylabel('μs')
    plt.savefig('./plots/Binary_Search_time.jpg')

    plt.show()

    



