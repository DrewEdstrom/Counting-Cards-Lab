#ifndef SHUFFLEALGORITHMS_H_INC
#define SHUFFLEALGORITHMS_H_INC

#include <cmath>
#include <vector>

//shuffles a vector by picking a random index of vec and attempting to copy
//that element to the vector copy, repeating this process until there are
//no more elements to pick from vec
template<typename T>
std::vector<T> slow_shuffle(std::vector<T> vec)
{
    //the shuffled copy of vec
    std::vector<T> copy;
    //the randomly selected index
    size_t i;
    //the size of vec prior to removal of elements
    int original_size{static_cast<int>(vec.size())};

    //execute until all elements in vec have been shuffled
    while(vec.size() > 0)
    {
        //pick some index of an element in vec
        i = static_cast<size_t>(floor(rand() % original_size));

        //execute if the element has not yet been shuffled
        if(i < vec.size())
        {
            copy.push_back(vec[i]);
            //to avoid having to shift all vector elements left, move
            //chosen element to back and then remove
            vec[i] = std::move(vec.back());
            vec.pop_back();
        }
    }

    return copy;
}

//like slowest_shuffle() except now indexes are picked at random from a
//range only containing remaining indexes in vec
template<typename T>
std::vector<T> moderate_shuffle(std::vector<T> vec)
{
    //the shuffled copy of vec
    std::vector<T> copy;
    //the randomly selected index
    size_t i;

    //execute until all elements in vec have been shuffled
    while(vec.size() > 0)
    {
        //pick some remaining element in vec
        i = static_cast<size_t>(floor(rand() % static_cast<int>(vec.size())));

        //move picked element to new vector and remove from old
        copy.push_back(vec[i]);
        vec.erase(vec.begin() + i);
    }

    return copy;
}

//like moderate_shuffle() except we avoid both having to copy the contents 
//of vec to a new vector and resizing any vectors
template<typename T>
std::vector<T> fisher_yates_shuffle(std::vector<T> vec)
{
    //where elements of vec can be temporarily stored while moving elements
    //between indexes
    T temp;
    size_t m {vec.size()},
           i;

    //executes until all of vec has been rearranged
    while(m > 0)
    {
        i = static_cast<size_t>(floor(rand() % static_cast<int>(m--)));

        temp = vec[m];
        vec[m] = vec[i];
        vec[i] = temp;
    }

    return vec;
}

#endif
