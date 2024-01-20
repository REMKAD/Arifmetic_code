#include "Arrays.h"

Arrays::Arrays()
{


}

Arrays::~Arrays()
{
    if (frequency_relative_array != nullptr) {
        for (size_t i = 0; i < frequency_relative_array_size; i++) {
            delete[] frequency_relative_array[i];
            frequency_relative_array[i] = nullptr;
        }
        delete[] frequency_relative_array;
        frequency_relative_array = nullptr;
    }
    // Освобождение памяти для alphbt_array
    if (alphbt_array != nullptr) {
        delete alphbt_array;
        alphbt_array = nullptr;
    }

    // Освобождение памяти для zeros_in_the_initial_double
    if (zeros_in_the_initial_double != nullptr) {
        delete zeros_in_the_initial_double;
        zeros_in_the_initial_double = nullptr;
    }

}

void Arrays::push_back(int new_elem)
{
    
}

void Arrays::push_back(double new_elem)
{
}
