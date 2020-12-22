// Copyright 2020 Your Name <your_email>
#include <cache.hpp>
#include <gtest/gtest.h>

TEST(Example, Pushing_back) {
    Cache example;
    example.Cache_back();
    stringstream ss;
    for(const auto& size: example.get_cache()){
        ss << size << " ";
    }
    string ref_string = "0.5 1 2 4 8 16 18 ";
    EXPECT_EQ(ss.str(), ref_string);
}
TEST(Example, Experiments){
    Cache example;
    example.Cache_back();
    example.Straight_experiment();
    example.Back_experiment();
    example.Random_experiment();
    cout << example;
}
