import matplotlib.pyplot as plt
import numpy as np

def convert_time_helper(t_str):
    """
    Called by convert_time() to reformat text strings to float

    Parameters
    ----------
        t_str: str, list
               A list containing strings of times in microseconds
    Returns:
    -------
        np.array, float
               The transformed list with type as float

    """
    return np.array([float(time[:-2]) for time in t_str], dtype = float)

def convert_time(tms, pos=0):
    """
    Recursively converts lists of miscroseconds from string to float.
    
    Parameters
    ----------
        tms : str, list
              A list or list of lists containing strings of times in microseconds
        pos : int
              Position within a nested list. Disregarded if tms is just a list.
    Returns:
    -------
        np.array, float
              The transformed list or list of lists with type as float.
    """
    # base case
    if pos == len(tms):
        return tms
    # check for nested list
    if isinstance(tms[pos], list):
        tms[pos] = convert_time_helper(tms[pos]) # call helper function with one list
        return convert_time(tms, pos+1) # resursive call to next list
    else:
        return convert_time_helper(tms) # otherwise, return single list (1 simulation)

if __name__ == "__main__":
    
    # ====== READ IN FILES FROM OUTPUT ====== #
    with open('output/rbt_runtime.txt', 'r') as rbt_file:
        rbt_rt = rbt_file.read().split(',')
    with open("output/bst_runtime.txt", 'r') as bst_file:
        bst_rt = bst_file.read().split(',')

    with open('output/rbt_sim.txt', 'r') as rbt_file_sim:
        rbt_sim = rbt_file_sim.read().splitlines()

    with open('output/bst_sim.txt', 'r') as bst_file_sim:
        bst_sim = bst_file_sim.read().splitlines()

    num_sim = len(rbt_sim) # number of simulations 
                           # num_sim = len(bst_sim) also acceptable

    # ======= CONVERT STRING TIME TO FLOAT ======= # 
    rbt_rt = convert_time(rbt_rt)
    bst_rt = convert_time(bst_rt)

    rbt_sim = convert_time([s.split(',') for s in rbt_sim])
    bst_sim = convert_time([s.split(',') for s in bst_sim])

    # ========= Fig 1: Plot of Red-Black Insertion Speed ========= # 
    plt.figure(1, figsize=(num_sim/1.5,5), layout='constrained')
    plt.plot(np.log(rbt_rt), color = 'r')
    plt.title('Fig 1: Plot of Red-Black Insertion Speed')
    plt.xlabel('Insertion')
    plt.ylabel('log μs')
    plt.savefig('./plots/Red_Black_log-time.jpg')

    # ======= Fig 2: Plot of Binary-Search Insertion Speed ======= # 
    plt.figure(2, figsize=(num_sim/1.5,5), layout='constrained')
    plt.plot(np.log(bst_rt), color = 'b')
    plt.title('Fig 2: Plot of Binary-Search Insertion Speed')
    plt.xlabel('Insertion')
    plt.ylabel('log μs')
    plt.savefig('./plots/Binary_Search_log-time.jpg')

    # ======= PLOTTING BY SIMULATION ======= # 
    sim_i = [f"sim-{i+1}" for i in range(num_sim)] 
    rbt_sim_means = np.mean(rbt_sim, axis=1)
    bst_sim_means = np.mean(bst_sim, axis=1)
    # create a dictionary of mean simulation insert times 
    alg_means = {
        "Red-Black" : rbt_sim_means,
        "Binary-Search" : bst_sim_means
    }

    # ======= Fig 3: Average insertion speed by search algorithm (grouped bar) ======= # 
    x = np.arange(len(rbt_sim_means)) # the label locations
    width = 0.25 # the width of the bars
    multiplier = 0
    fig, ax = plt.subplots(figsize=(num_sim/1.5,5),layout='constrained')

    for alg, avg_time in alg_means.items():
        offset = width * multiplier
        if alg == 'Red-Black':
            color='r'
        else:
            color='b'
        rects = ax.bar(x + offset, avg_time, width, color=color, label=alg)
        multiplier += 1
    # Add some text for labels, title and custom x-axis tick labels, etc.
    ax.set_ylabel('μs')
    ax.set_title('Fig 3: Average insertion speed by search algorithm')
    ax.set_xticks(x + 0.125, sim_i)
    ax.legend(loc='upper left', ncols=2)
    plt.savefig('./plots/Sim_Avg_group.jpg')

    # ======= Fig 4: Average insertion speed by search algorithm (grouped line) ======= # 
    plt.figure(4, figsize=(num_sim/1.5,5), layout = 'constrained')
    for alg, avg_time in alg_means.items():
        if alg == 'Red-Black':
            color='r'
        else:
            color='b'
        plt.plot(avg_time, color=color, label = alg)
    plt.title('Fig 4: Average insertion speed by search algorithm')
    plt.xticks(np.arange(num_sim), sim_i)
    plt.legend(loc='upper left')
    plt.ylabel('μs')
    plt.savefig('./plots/Sim_Avg_line.jpg')

    plt.show() # show all plots

    



