#ifndef FUNCTIONBENCHMARKING_H_INC
#define FUNCTIONBENCHMARKING_H_INC

#include <chrono>

//determines how long it took for a function call (with one argument) to
//execute
template<typename Func, typename Arg>
long long int compute_runtime(Func func, Arg &arg)
{
    //the time at which a given algorithm was executed
    std::chrono::system_clock::time_point start;
    //the time at which a given algorithm finished running
    std::chrono::system_clock::time_point stop;
    //how long the algorithm ran for, in miliseconds
    long long int runtime;

    start = std::chrono::high_resolution_clock::now();
    //the function call
    func(arg);
    stop = std::chrono::high_resolution_clock::now();
    runtime = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();

    return runtime;
}

//computes the average runtime of a function (in miliseconds) for some
//given number of trials
template<typename Func, typename Arg>
long long int compute_avg_runtime(Func func, Arg &arg, int trials)
{
    //the sum of all runtimes
    long long int runtime_sum{0};

    //sum the runtimes from each function call
    for(int i = 0; i < trials; i++)
    {
        runtime_sum += compute_runtime(func, arg);
    }

    //return the average runtime
    return runtime_sum / trials;
}

#endif
