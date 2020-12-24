// Copyright 2020 summersoul17 <17summersoul17@gmail.com>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <algorithm>

using std::vector;
using std::cout;
using std::cin;
using std::string;
using std::stringstream;
using std::endl;
using std::ostream;

struct Data;

class Cache{
public:
    void Cache_back();
    void Straight_experiment();
    void Back_experiment();
    void Random_experiment();
    static void inline Cache_warming(const unsigned & cache_size, const double* arr1){
        [[maybe_unused]]double  k = 0;
        for(unsigned i = 0; i < cache_size; i+=16){
            k = arr1[i];
        }
    };
    const vector<double>& get_cache(){
        return cache;
    };
    friend ostream& operator <<(ostream& os, const Cache object);

private:
    vector<double> cache;
    const vector<double> caches = {1, 4, 12};
    vector<Data> data_vector;
    const int count_of_ints = 131072;
    const int count_of_travels = 1000;
    const int step = 16;
};
struct Data{
    vector<unsigned> time_vector;
    string travel;
    Data(vector<unsigned> time_vector_, string travel_)
        : time_vector(time_vector_), travel(travel_){};
};
#endif // INCLUDE_HEADER_HPP_
