#pragma once
#include "String.h"


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

        //decoding

    void decode_text();
    String Get_decoded();

        //text

    void get_text(const String& text, int len);
    int get_freq_size();


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
    void make_intervals(double lim_l, double lim_r);
    void make_frequency_relative();
    void find_letter(double encoded_number);
        //convertation

    String int_to_bin(int num);
    double bin_to_double(const String& text, int len);
    char Get_char_digit(int digit);
    int Get_int_digit(char digit);
    int double_to_int(double num);

};

