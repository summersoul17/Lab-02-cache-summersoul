// Copyright 2020 summersoul17 <17summersoul17@gmail.com>

#include <cache.hpp>
#include <random>

void Cache::Cache_back(){
    cache.push_back(caches[0]*0.5);
    double n = 1;
    while(n < caches[2] * 1.5) {
        cache.push_back(n);
        n *= 2;
    }
    cache.push_back(caches[2]*1.5);
}

void Cache::Straight_experiment() {
    vector<unsigned> straight_time;
    for(size_t j = 0; j < cache.size(); ++j){
        unsigned cache_size = cache[j]*count_of_ints; //count of ints in all cache lines
        double* arr1 = new double[cache_size];
        [[maybe_unused]]double k;
        Cache::Cache_warming(cache_size, arr1);
        auto startTime = std::chrono::high_resolution_clock::now();
        for(unsigned i = 0; i < cache_size*count_of_travels; i+=16){
            k = arr1[i%1000];
        }
        auto endTime = std::chrono::high_resolution_clock::now();
        straight_time.push_back(static_cast<unsigned>(std::chrono::nanoseconds((endTime - startTime) / 1000).count()));
        delete[] arr1;
    }
    data_vector.emplace_back(straight_time, "straight");
}
void Cache::Back_experiment() {
    vector<unsigned> back_time;
    for(size_t j = 0; j < cache.size(); ++j){
        unsigned cache_size = cache[j]*count_of_ints;
        double* arr1 = new double[cache_size];
        [[maybe_unused]]double k;
        Cache::Cache_warming(cache_size, arr1);
        auto startTime = std::chrono::high_resolution_clock::now();
        for(unsigned i = cache_size*count_of_travels; i > 0; i-=16){
            k = arr1[i%1000];
        }
        auto endTime = std::chrono::high_resolution_clock::now();
        back_time.push_back(static_cast<unsigned>(std::chrono::nanoseconds((endTime - startTime) / 1000).count()));
        delete[] arr1;
    }
    data_vector.emplace_back(back_time, "back");
}

void Cache::Random_experiment() {
    vector<unsigned> random_time;
    for(size_t j = 0; j < cache.size(); ++j){
        vector<unsigned> arr;
        vector<unsigned>::iterator start, end;
        unsigned cache_size = cache[j]*count_of_ints;
        double* arr1 = new double[cache_size];
        [[maybe_unused]]double k;
        for(unsigned i = 0; i < cache_size; i+=16) arr.emplace_back(i);
            start = arr.begin();
            end = arr.end();
            shuffle(start, end,std::mt19937(std::random_device()()));
        Cache::Cache_warming(cache_size, arr1);
        auto startTime = std::chrono::high_resolution_clock::now();
        for(unsigned i = 0; i < cache_size*count_of_travels/16; ++i){
            k = arr1[arr[i%1000]];
        }
        auto endTime = std::chrono::high_resolution_clock::now();
        random_time.push_back(static_cast<unsigned>(std::chrono::nanoseconds((endTime - startTime) / 1000).count()));
        delete[] arr1;
    }
    data_vector.emplace_back(random_time, "random");
}

ostream &operator<<(ostream &os, Cache object) {
    for (size_t i = 0; i < object.data_vector.size(); ++i) {
        os << R"(Invistigations: )" << endl <<
    R"(     travel_variant: )" << object.data_vector[i].travel << endl <<
    R"(     experiments: )" << endl;
        for (size_t j = 0; j < object.cache.size(); ++j) {
            os << R"(           -experiment:
            number: )" << j+1 << endl <<
    R"(             input_data:
                buffer_size: )" << object.cache[j] << " mb" << endl <<
    R"(             results:
                duration: )" << object.data_vector[i].time_vector[j] << " nanoseconds" << endl << endl;
        }
    }
    return os;
}
