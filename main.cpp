#include "rbt.hpp"
#include "Timer.h"
#include <cstdlib>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <map>
#include <Python.h>


auto totalTime(auto tms){ 
	auto total = simple_timer::timer<'u'>::interval{0.0};

	for(size_t i = 0; i < tms.size(); ++i)
	{
		total += tms[i];
	}
	return total;
}

auto avgTime(auto sum, auto tms)
{
	return sum/tms.size(); 
}

void showStats(auto tms)
{
	std::cout << "total dur: " << totalTime(tms) << '\n';
	std::cout << "avg insert: " << avgTime(totalTime(tms),tms) << '\n';
}


int main(int argc, const char* argv[]){
	
	std::cout << ">";
	Py_Initialize();

	srand(4);
	int total_argc = argc - 1;

	if (total_argc == 2)
	{
		if(argv[1][0] == '-' && argv[1][1] == 'v'){ 
			Tree::verbose = true; 
		}
	}
	else{ Tree::verbose = false; }
	
	Tree rb_tr; 
	Tree bs_tr;

 
	std::vector<Tree> rbt_trees;
	std::string tree_input;

	std::vector<simple_timer::timer<'u'>::interval> rbt_times;
	std::vector<simple_timer::timer<'u'>::interval> bst_times;

	std::map<int, std::vector<simple_timer::timer<'u'>::interval>> sim_rbt_times;
	std::map<int, std::vector<simple_timer::timer<'u'>::interval>> sim_bst_times;
	int key = 0; 
 	
	bool quit = false; 

	simple_timer::timer<'u'> tm; 
	while(!quit)
	{
		while(true)
		{
			std::string action;
			std::getline(std::cin, action);

			if (action == ".exit")
			{
				quit = true;
				break; 
			}
			if (action == ".print")
			{
				Tree::rbt = true;
				rb_tr.print();
				std::cout << ">";
			}
			if (action == ".print -bst")
			{
				Tree::rbt = false;
				bs_tr.print();
				std::cout << ">";
			}
			if (action == ".insert")
			{
				std::string list; 
				std::cout << "insert list: ";

				std::getline(std::cin, list); 

				std::stringstream ss(list);
				std::vector<int> data; 

				for (int i; ss >> i;) {
			    	data.push_back(i);    
			    	if (ss.peek() == ',') { 
			        	ss.ignore();
			    	}
				}

				for(size_t i = 0; i < data.size(); ++i)
				{

					Tree::rbt = true;
					tm.tick();
					rb_tr.insert(data[i]); 
					rbt_times.push_back(tm.tock());
					rbt_trees.push_back(rb_tr);

					Tree::rbt = false;
					tm.tick();
					bs_tr.insert(data[i]);
					bst_times.push_back(tm.tock());
				}
				std::cout << ">";
				break; 
			}
			if (action == ".erase")
			{
				int val;
				std::cin >> val;
				Tree::rbt = true;
				tm.tick();
				rb_tr.erase(rb_tr.find(val));
				tm.tock();
				std::cout << ">";
			}
			if (action == ".avg")
			{
				std::cout << avgTime(totalTime(rbt_times), rbt_times) << '\n';
				std::cout << ">";
			}
			if (action == ".time")
			{
				for(size_t i = 0; i < rbt_times.size(); ++i)
				{
					std::cout << rbt_times[i] << ' ';
				}
				std::cout << '\n';
				std::cout << ">";
			}
			
			if (action == ".compare")
			{
				std::cout << "=======rbt stats=======" << '\n';
				showStats(rbt_times);
				std::cout << "=======bst stats=======" << '\n';
				showStats(bst_times);
				std::cout << ">";
			}
			
			if (action == ".hist")
			{
				Tree::rbt = true;
				for(size_t i = 0; i < rbt_trees.size(); ++i)
				{
					rbt_trees[i].print();
				}
				std::cout << ">";
			}

			if (action == ".sim")
			{
				key += 1;
				std::vector<simple_timer::timer<'u'>::interval> temp_rbt_times; 
				std::vector<simple_timer::timer<'u'>::interval> temp_bst_times; 
				for(int i = 0; i < 1000; ++i)
				{
					int rand_num = rand() % 100000;
					
					Tree::rbt = true;
					tm.tick();
					rb_tr.insert(rand_num);
					auto tm_intrvl = tm.tock();
					rbt_times.push_back(tm_intrvl);
					temp_rbt_times.push_back(tm_intrvl);
					rbt_trees.push_back(rb_tr);

					Tree::rbt = false;
					tm.tick();
					bs_tr.insert(rand_num);
					tm_intrvl = tm.tock(); 
					bst_times.push_back(tm_intrvl);
					temp_bst_times.push_back(tm_intrvl);
				}
				sim_rbt_times.insert({key, temp_rbt_times});
				sim_bst_times.insert({key, temp_bst_times});
				std::cout << ">";
			}
			if (action == ".write")
			{
				std::ofstream rbtFile_rt;
				rbtFile_rt.open ("output/rbt_runtime.txt");
				for(size_t i = 0; i < rbt_times.size(); ++i)
				{
					rbtFile_rt << rbt_times[i];
					if(i != rbt_times.size() - 1)
					{
						rbtFile_rt << ',';
					}
				}
				rbtFile_rt.close();

				std::ofstream rbtFile_sim;
				rbtFile_sim.open ("output/rbt_sim.txt");

				for(auto m = sim_rbt_times.begin(); m != sim_rbt_times.end(); ++m)
				{
					auto temp = m->second;
					for(size_t i = 0; i < temp.size(); ++i)
					{
						rbtFile_sim << temp[i];

						if(i != temp.size() - 1)
						{
							rbtFile_sim << ',';
						}

						if(i == temp.size() - 1)
						{
							rbtFile_sim << '\n';
						}
					}
			
				}
				rbtFile_sim.close();

				std::ofstream bstFile_rt;
				bstFile_rt.open ("output/bst_runtime.txt");
				for(size_t i = 0; i < bst_times.size(); ++i)
				{
					bstFile_rt << bst_times[i];
					if(i != bst_times.size() - 1)
					{
						bstFile_rt << ',';
					}
				}
				bstFile_rt.close();

				std::ofstream bstFile_sim;
				bstFile_sim.open ("output/bst_sim.txt");

				for(auto m = sim_bst_times.begin(); m != sim_bst_times.end(); ++m)
				{
					auto temp = m->second;
					for(size_t i = 0; i < temp.size(); ++i)
					{
						bstFile_sim << temp[i];

						if(i != temp.size() - 1)
						{
							bstFile_sim << ',';
						}

						if(i == temp.size() - 1)
						{
							bstFile_sim << '\n';
						}
					}
			
				}
				bstFile_sim.close();

				std::cout << ">";
			}
			if (action == ".plot")
			{
				PyObject * obj = Py_BuildValue("s", "plot.py");
				FILE * fp = _Py_fopen_obj(obj,"r+");
				if(fp != NULL)
				{
					PyRun_SimpleFile(fp, "plot.py");
				}
				std::cout << ">";
			}

		}



	}

	Py_Finalize();


	return 0;
}