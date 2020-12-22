// Copyright 2020 summersoul17 <17summersoul17@gmail.com>

#include <cache.hpp>
#include <random>

//512Kb<1Mb<2Mb<4Mb<8Mb<16Mb<18Mb
//vector<int> cache = {512, 1024, 2048, 5096, 10192};

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
    vector<NATURALS> straight_time;
    for(size_t j = 0; j < cache.size(); ++j){
        NATURALS cache_size = cache[j]*1024*1024/8;
        double* arr1 = new double[cache_size];
        [[maybe_unused]]double k;
        Cache::Cache_warming(cache_size, arr1);
        auto startTime = std::chrono::high_resolution_clock::now();
        for(NATURALS i = 0; i < cache_size*1000; i+=16){
            k = arr1[i%1000];
        }
        auto endTime = std::chrono::high_resolution_clock::now();
        straight_time.push_back(static_cast<NATURALS>(std::chrono::nanoseconds((endTime - startTime) / 1000).count()));
        delete[] arr1;
    }
    data_vector.emplace_back(straight_time, "straight");
}
void Cache::Back_experiment() {
    vector<NATURALS> back_time;
    for(size_t j = 0; j < cache.size(); ++j){
        NATURALS cache_size = cache[j]*1024*1024/8;
        double* arr1 = new double[cache_size];
        [[maybe_unused]]double k;
        Cache::Cache_warming(cache_size, arr1);
        auto startTime = std::chrono::high_resolution_clock::now();
        for(NATURALS i = cache_size*1000; i > 0; i-=16){
            k = arr1[i%1000];
        }
        auto endTime = std::chrono::high_resolution_clock::now();
        back_time.push_back(static_cast<NATURALS>(std::chrono::nanoseconds((endTime - startTime) / 1000).count()));
        delete[] arr1;
    }
    data_vector.emplace_back(back_time, "back");
}

void Cache::Random_experiment() {
    vector<NATURALS> random_time;
    for(size_t j = 0; j < cache.size(); ++j){
        vector<NATURALS> arr;
        vector<NATURALS>::iterator start, end;
        NATURALS cache_size = cache[j]*1024*1024/8;
        double* arr1 = new double[cache_size];
        [[maybe_unused]]double k;
        for(NATURALS i = 0; i < cache_size; i+=16) arr.emplace_back(i);
            start = arr.begin();
            end = arr.end();
            shuffle(start, end,std::mt19937(std::random_device()()));
        Cache::Cache_warming(cache_size, arr1);
        auto startTime = std::chrono::high_resolution_clock::now();
        for(NATURALS i = 0; i < cache_size*1000/16; ++i){
            k = arr1[arr[i%1000]];
        }
        auto endTime = std::chrono::high_resolution_clock::now();
        random_time.push_back(static_cast<NATURALS>(std::chrono::nanoseconds((endTime - startTime) / 1000).count()));
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
