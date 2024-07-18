import matplotlib.pyplot as plt
import numpy as np

def convert_to_time(t_str, pos=0):
    if pos == len(t_str):
        return np.array(t_str, dtype = float)

    if not isinstance(t_str[pos], list):
        t_num = [float(time[:-2]) for time in t_str]
        return np.array(t_num, dtype = float)

    else:
        t_str[pos] = [float(time[:-2]) for time in t_str[pos]]
        return convert_to_time(t_str, pos+1)

if __name__ == "__main__":
    
    with open('output/rbt_runtime.txt', 'r') as rbt_file:
        rbt_rt = rbt_file.read().split(',')
    with open("output/bst_runtime.txt", 'r') as bst_file:
        bst_rt = bst_file.read().split(',')

    with open('output/rbt_sim.txt', 'r') as rbt_file_sim:
        rbt_sim = rbt_file_sim.read().splitlines()

    with open('output/bst_sim.txt', 'r') as bst_file_sim:
        bst_sim = bst_file_sim.read().splitlines()


    rbt_rt = convert_to_time(rbt_rt)
    bst_rt = convert_to_time(bst_rt)

    rbt_sim = convert_to_time([s.split(',') for s in rbt_sim])
    bst_sim = convert_to_time([s.split(',') for s in bst_sim])

    print(np.mean(rbt_sim, axis=1))
    print(np.mean(bst_sim, axis=1))


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

    



