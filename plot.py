import matplotlib.pyplot as plt
import numpy as np

def convert_time_helper(t_str):
    return np.array([float(time[:-2]) for time in t_str], dtype = float)

def convert_time(tms, pos=0):
    if pos == len(tms):
        return tms

    if isinstance(tms[pos], list):
        tms[pos] = convert_time_helper(tms[pos])
        return convert_time(tms, pos+1)
    else:
        return convert_time_helper(tms)


if __name__ == "__main__":
    
    with open('output/rbt_runtime.txt', 'r') as rbt_file:
        rbt_rt = rbt_file.read().split(',')
    with open("output/bst_runtime.txt", 'r') as bst_file:
        bst_rt = bst_file.read().split(',')

    with open('output/rbt_sim.txt', 'r') as rbt_file_sim:
        rbt_sim = rbt_file_sim.read().splitlines()

    with open('output/bst_sim.txt', 'r') as bst_file_sim:
        bst_sim = bst_file_sim.read().splitlines()


    rbt_rt = convert_time(rbt_rt)
    bst_rt = convert_time(bst_rt)

    rbt_sim = convert_time([s.split(',') for s in rbt_sim])
    bst_sim = convert_time([s.split(',') for s in bst_sim])

    
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

    num_sim = len(rbt_sim)
    sim_i = [f"sim-{i}" for i in range(len(rbt_sim))]
    rbt_sim_means = np.mean(rbt_sim, axis=1)
    bst_sim_means = np.mean(bst_sim, axis=1)
    alg_means = {
        "Red-Black" : rbt_sim_means,
        "Binary-Search" : bst_sim_means
    }

    x = np.arange(len(rbt_sim_means))
    width = 0.25
    multiplier = 0

    fig, ax = plt.subplots(layout='constrained')

    for alg, avg_time in alg_means.items():
        offset = width * multiplier
        rects = ax.bar(x + offset, avg_time, width, label=alg)
        ax.bar_label(rects, padding=3)
        multiplier += 1

    ax.set_ylabel('μs')
    ax.set_title('Fig 3: Average insertion speed\nby search algorithm per simulation')
    ax.set_xticks(x + 0.125, sim_i)
    ax.legend(loc='upper left', ncols=2)
    ax.set_ylim(0, 0.7)
    plt.savefig('./plots/Sim-Avg.jpg')


    plt.show()

    



