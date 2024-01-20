#pragma once
#include "String.h"

class Arrays
{
    Arrays();
    ~Arrays();
public:
    double** frequency_relative_array = nullptr;
    String* alphbt_array = nullptr;
    int* zeros_in_the_initial_double = nullptr;
    int frequency_relative_array_size;
    void push_back(int new_elem);
    void push_back(double new_elem);
};

