#pragma once
#include "String.h"
#include "vector"


class Arifmetic_code
{
    //17743265
    //177433
public:

        //constr and destruct

    Arifmetic_code();
    ~Arifmetic_code();
        
        //encoding

    void encode_text();
    String Get_encoded();

    void encodeAndWriteToFile(const char* inputFile, const char* outputFile);

        //decoding

    void decode_text(int len_symbols, int iter_index);
    String Get_decoded();
    void decodeAndWriteToFile(const char* inputFile, const char* outputFile);

        //text

    void get_text(const String& text, int len, int iteration_index);
    int get_freq_size();

    void get_encoded_text(const String& text, int iteration_index);

        //print variables 

    void print_frequency();
    void print_alphbt();
    void print_freq_alphbt();
    
private:

        //variables

    int length_f = 0;
    String alphbt = "\0";
    String text = "\0";
    String encoded = "\0";
    String decoded = "\0";
    double* frequency = nullptr;
    double* frequency_relative = nullptr;
    double* intervals = nullptr;

    std::vector<double*> frequency_relative_array;
    std::vector<String> alphbt_array;
    std::vector<int> zeros_in_the_initial_double; // !!!!!!!!!!! in deconstructor nothing is done for memory allocation !!!!!!!!!!!!!!
    int last_length_symbols = 0;

    void make_intervals(double lim_l, double lim_r, int index);
    void make_frequency_relative();
    void find_letter(double encoded_number);
    long long choose_the_shortest_number_in_the_interval(double lim_l, double lim_r);
        //convertation

    String int_to_bin(long long num);
    double bin_to_double(const String& text, int len);
    char Get_char_digit(int digit);
    int Get_int_digit(char digit);
    long long double_to_int(double num);

};

