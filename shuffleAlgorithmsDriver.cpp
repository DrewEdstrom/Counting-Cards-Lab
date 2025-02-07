#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include "functionBenchmarking.h"
#include "shuffleAlgorithms.h"

using namespace std;

//converts the contents of a vector to a string
template<typename T>
string vec_to_str(vector<T> vec);

//commences the process of benchmarking for a set of arrays
template<typename T>
void run_benchmark(ostream & ostr, vector<vector<T>> arrays, int trials);

int main()
{
    //the arrays for shuffling
    vector<vector<int>> num_arrays{{1,2},
                                   {1,2,3},
                                   {1,2,3,4},
                                   {1,2,3,4,5,6},
                                   {1,2,3,4,5,6,7,8,9},
                                   {1,2,3,4,5,6,7,8,9,10,11,12},
                                   {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}};
    vector<vector<string>> str_arrays{{"the","quick"},
                                      {"the","quick","brown"},
                                      {"the","quick","brown","fox"},
                                      {"the","quick","brown","fox","jumped"},
                                      {"the","quick","brown","fox","jumped", "over"}};
    vector<vector<char>> char_arrays{{'a','b'},
                                     {'a','b','c'},
                                     {'a','b','c','d'},
                                     {'a','b','c','d','e','f'},
                                     {'a','b','c','d','e','f','g'},
                                     {'a','b','c','d','e','f','g','h'}};
    int trials = 100000;
    ofstream output_file{"shuffle_benchmark_results.txt", ios_base::app};
    string file_name;

    while(!output_file)
    {
        cout << "\n\nCannot access benchmark results output file! Enter a "
                << "new file to output to.\n";
        cin >> file_name;
        output_file.open(file_name, ios_base::app);
    }

    //seeding the random number generation
    srand(static_cast<unsigned>(time(nullptr)));

    cout << "\n\nWelcome to the Shuffle Algorithms driver!"
            << "\nNote that all times listed are for " << trials << " trials."
            << "\n\nRunning benchmark...";
    output_file << "\n\nAverage runtimes are calculated from " << trials << " trials.";
    run_benchmark(output_file, num_arrays, trials);
    run_benchmark(output_file, str_arrays, trials);
    run_benchmark(output_file, char_arrays, trials);
    output_file << "\n\n\n\n" << string(50, '-');
    output_file.close();
    output_file.clear();
    cout << "\n\nBenchmarking finished. Check output file for results.\n\n";

    return 0;
}

//converts the contents of a vector to a string
template<typename T>
string vec_to_str(vector<T> vec)
{
    ostringstream ostr;

    ostr << "[";

    for(size_t i = 0; i < vec.size(); i++)
    {
        if(i == vec.size() - 1)
        {
            ostr << vec[i] << "]";
        }
        else
        {
            ostr << vec[i] << ", ";
        }
    }

    string str{ostr.str()};

    return str;
}

//commences the process of benchmarking for a set of arrays
template<typename T>
void run_benchmark(ostream & ostr, vector<vector<T>> arrays, int trials)
{
    //quick test to verify shuffling is successful for each algorithm
    ostr << "\n\nTest of functionality of algorithms:"
            << "\nSlowest shuffle: " 
            << vec_to_str(slow_shuffle<T>(arrays[arrays.size()-1]))
            << "\nModerate shuffle: " 
            << vec_to_str(moderate_shuffle<T>(arrays[arrays.size()-1]))
            << "\nBest shuffle: " 
            << vec_to_str(fisher_yates_shuffle<T>(arrays[arrays.size()-1]));

    //output runtimes for the shuffle functions for comparison
    ostr << "\n\nElements" << setw(21) 
            << "\"Slow\" Times (ns)" << setw(26) 
            << "\"Moderate\"  Times (ns)" << setw(28) 
            << "\"Fisher\"  Times (ns)";

    for(size_t i = 0; i < arrays.size(); i++)
    {
        ostr << "\n" << arrays[i].size() << setw(15)
                << compute_avg_runtime(slow_shuffle<T>, arrays[i], trials)
                << setw(21)
                << compute_avg_runtime(moderate_shuffle<T>, arrays[i], trials)
                << setw(30)
                << compute_avg_runtime(fisher_yates_shuffle<T>, arrays[i], trials);
    }
}
