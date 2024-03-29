﻿#include "Arifmetic_code.h"



Arifmetic_code::Arifmetic_code()
{
    this->zeros_in_the_initial_double = new int[zeros_in_the_initial_double_sz];
    this->frequency_relative_array = new double* [frequency_relative_array_rows];
    this->alphbt_array = new String[alphbt_arr_rows];
    this->frequency_relative_array[0] = nullptr;
    this->frequency = new double[1];
    this->frequency[0] = 0;
    this->intervals = new double[1];
    this->intervals[0] = 0;
    this->frequency_relative = new double[1];
    this->frequency_relative[0] = 0;
}

Arifmetic_code::~Arifmetic_code()
{
    if (this->frequency_relative_array != nullptr) {
        for (int i = 0; i < frequency_relative_array_rows; i++) {
            delete[] this->frequency_relative_array[i];
        }
    }
    else {
        std::cout << "The frequency_relative_array is already empty." << std::endl;
    }
    delete[] this->frequency_relative_array;
    if (this->frequency != nullptr) delete this->frequency;
    if (this->intervals != nullptr) delete this->intervals;
    for (int i = 0; i < this->alphbt_arr_rows; ++i) {
        alphbt_array[i].~String();
    }
    if (zeros_in_the_initial_double != nullptr) {
        delete[] zeros_in_the_initial_double;
    }
}

void Arifmetic_code::encode_text()
{
    int len_text = this->text.Get_length();
    double limit_l = 0;
    double limit_r = 1;

    make_frequency_relative();
    push_back_to_relative(frequency_relative);

    int k = 0;
    for (int i = 0; i < len_text; i++) {

        make_intervals(limit_l, limit_r, i);

        for (int j = 0; j < length_f; j++) {

            if (this->alphbt[j] == this->text[i]) {
                if (j != 0) {

                    limit_r = intervals[j];
                    limit_l = intervals[j - 1];
                }
                else {
                    limit_r = intervals[j];
                }
                break;
            }
        }
    }

    this->encoded = int_to_bin(choose_the_shortest_number_in_the_interval(limit_l, limit_r));
}

String Arifmetic_code::Get_encoded()
{
    return this->encoded;
}

void Arifmetic_code::encodeAndWriteToFile(const char* inputFile, const char* outputFile)
{

    std::ifstream input(inputFile);
    if (!input.is_open()) {
        std::cerr << "Failed to open input file" << std::endl;
        return;
    }

    std::ofstream output(outputFile, std::ios::binary);
    if (!output.is_open()) {
        std::cerr << "Failed to open output file" << std::endl;
        input.close();
        return;
    }

    String content;
    char ch;
    int iter_index = 0;

    while (input.get(ch)) {

        content.push_back(ch);

        if (content.Get_length() >= 9) {
            content.push_back('!');
            get_text(content, content.Get_length(), iter_index);

            encode_text();


            String encodedString = Get_encoded();

            for (int i = 0; i < encodedString.Get_length(); ++i) {
                output << encodedString[i];
            }

            output << ' ';

            content.make_zero();

            iter_index++;
            current_index++;
        }
    }

    if (content.Get_length() > 0) {
        this->last_length_symbols = content.Get_length();
        content.push_back('!');
        get_text(content, content.Get_length(), iter_index);
        encode_text();
        String encodedString = Get_encoded();

        for (int i = 0; i < encodedString.Get_length(); ++i) {
            output << encodedString[i];
        }
    }

    input.close();
    output.close();

}

void Arifmetic_code::decode_text(int len_symbols, int iter_index)
{

    double encoded_number = bin_to_double(this->text, this->text.Get_length());

    int amount_zeros = this->zeros_in_the_initial_double[iter_index];
    while (amount_zeros > 0) { 
        encoded_number /= 10; 
        amount_zeros--; 
    }

    int len_text = len_symbols;


    double limit_l = 0;
    double limit_r = 1;
    double last_one = 0;
    int k = 0;
    for (int i = 0; i < len_text; i++) {
        make_intervals(limit_l, limit_r, i);

        find_letter(encoded_number);

        for (int j = 0; j < length_f; j++) {
            if (this->alphbt[j] == this->decoded[i]) {

                if (j != 0) {
                    limit_r = intervals[j];
                    limit_l = intervals[j - 1];
                }
                else {
                    limit_r = intervals[j];
                }
                break;
            }
        }
    }


}

String Arifmetic_code::Get_decoded()
{
    return this->decoded;
}

void Arifmetic_code::decodeAndWriteToFile(const char* inputFile, const char* outputFile) {
    std::ifstream input(inputFile, std::ios::binary);
    if (!input.is_open()) {
        std::cerr << "Failed to open input file" << std::endl;
        return;
    }

    std::ofstream output(outputFile);
    if (!output.is_open()) {
        std::cerr << "Failed to open output file" << std::endl;
        input.close();
        return;
    }
    String encodedContent;
    char ch;
    int iter_index = 0;

    while (input.get(ch)) {
        if (ch != ' ') {
            encodedContent.push_back(ch);
        }
        else {

            get_encoded_text(encodedContent, iter_index);
            decode_text(9, iter_index);
            String decodedString = Get_decoded();

            for (int i = 0; i < decodedString.Get_length(); ++i) {
                output << decodedString[i];
            }

            encodedContent = "";
            iter_index++;
        }
    }
    if (encodedContent.Get_length() != 0) {

        get_encoded_text(encodedContent, iter_index);

        decode_text(this->last_length_symbols, iter_index);
        String decodedString = Get_decoded();

        for (int i = 0; i < decodedString.Get_length(); ++i) {
            output << decodedString[i];
        }

        encodedContent = "";
    }

    input.close();
    output.close();
}

void Arifmetic_code::get_text(const String& text, int len, int iteration_index)
{
    this->text = text;
    int length = len;
    bool truth = true;


    this->alphbt.make_zero();
    for (int i = 0; i < length; i++) {
        int j = 0;
        while (this->alphbt[j] != '\0') {
            if (text[i] == this->alphbt[j]) {
                truth = false;

            }
            j++;
        }
        if (truth) {
            this->alphbt.push_back(this->text[i]);
        }
        truth = true;
    }


    if (this->frequency_relative != nullptr) {
        delete[] this->frequency_relative;
        this->frequency_relative = nullptr;
    }

    if (this->frequency != nullptr) {
        delete this->frequency;
    }

    this->length_f = this->alphbt.Get_length();




    if (this->intervals != nullptr) delete this->intervals;
    intervals = new double[this->length_f];
    frequency = new double[this->length_f];
    frequency_relative = new double[this->length_f];
    for (int i = 0; i < this->length_f; i++) {
        frequency[i] = 0;
    }
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < this->length_f; j++) {
            if (this->text[i] == this->alphbt[j]) {
                this->frequency[j] += 1;
            }
        }
    }
    for (int i = 0; i < this->length_f - 1; i++) {
        for (int j = i + 1; j < this->length_f; j++) {
            if (this->frequency[i] < this->frequency[j]) {
                int help = 0;
                char help_ch;
                help_ch = this->alphbt[i];
                help = this->frequency[i];
                this->alphbt[i] = this->alphbt[j];
                this->alphbt[j] = help_ch;
                this->frequency[i] = this->frequency[j];
                this->frequency[j] = help;
            }
            else if ((this->alphbt[i] > this->alphbt[j]) && (this->frequency[i] == this->frequency[j])) {
                int help = 0;
                char help_ch;
                help_ch = this->alphbt[i];
                help = this->frequency[i];
                this->alphbt[i] = this->alphbt[j];
                this->alphbt[j] = help_ch;
                this->frequency[i] = this->frequency[j];
                this->frequency[j] = help;
            }

        }
    }

    push_back_to_BString(this->alphbt);

}

int Arifmetic_code::get_freq_size()
{
    return this->length_f;
}

void Arifmetic_code::get_encoded_text(const String& text, int iteration_index)
{
    this->text = text;
    this->alphbt = alphbt_array[iteration_index];
    this->frequency_relative = frequency_relative_array[iteration_index];
    this->length_f = this->alphbt.Get_length();
    if (this->intervals != nullptr) delete this->intervals;
    intervals = new double[this->length_f];
    if (this->decoded.Get_length() != 0) this->decoded.make_zero();
}

void Arifmetic_code::print_frequency()
{
    for (int i = 0; i < this->alphbt.Get_length(); i++) {
        std::cout << this->frequency[i] << std::endl;
    }
}

void Arifmetic_code::print_alphbt()
{
    for (int i = 0; i < this->alphbt.Get_length(); i++) {
        std::cout << alphbt[i] << std::endl;
    }
}

void Arifmetic_code::print_freq_alphbt()
{
    for (int i = 0; i < this->alphbt.Get_length(); i++) {
        std::cout << alphbt[i] << "  " << this->frequency[i] << std::endl;
    }
}

void Arifmetic_code::make_intervals(double lim_l, double lim_r, int index)
{
    if ((lim_r == 1) & (index == 0)) {
        for (int j = 0; j < length_f; j++) {
            if (j == 0) {
                intervals[j] = frequency_relative[j];
            }
            else {
                intervals[j] = intervals[j - 1] + frequency_relative[j];
            }
        }
    }
    else {
        intervals[0] = lim_l + (lim_r - lim_l) * frequency_relative[0];
        for (int j = 1; j < length_f - 1; j++) {
            intervals[j] = intervals[j - 1] + (lim_r - lim_l) * frequency_relative[j];
        }
        intervals[length_f - 1] = lim_r;
    }

}

void Arifmetic_code::make_frequency_relative()
{
    for (int j = 0; j < length_f; j++) {
        frequency_relative[j] = frequency[j] / this->text.Get_length();
    }
}

void Arifmetic_code::find_letter(double encoded_number)
{
    for (int i = 0; i < length_f; i++) {
        if (intervals[i] > encoded_number)
        {
            decoded.push_back(this->alphbt[i]);

            break;
        }
    }
}

long long Arifmetic_code::choose_the_shortest_number_in_the_interval(double lim_l, double lim_r)
{
    long long result = 0;
    int help1 = 0;
    int help2 = 0;
    int k = 0;
    bool starts_with_zero = true;
    double num1 = lim_l;
    double num2 = lim_r;
    int zero_count = 0;


    while (((10 - num1) != 10) && ((10 - num2) != 10)) {
        if (((10 - num1) > 9) & ((10 - num2) > 9)) {
            if (k > 15) break;
            num1 *= 10;
            num2 *= 10;

            if (num1 < static_cast<double>(std::numeric_limits<int>::min()) || num1 > static_cast<double>(std::numeric_limits<int>::max())) {
                std::cout << "type conversion error" << std::endl;
            }
            else {
                help1 = static_cast<int>(num1);
            }

            if (num2 < static_cast<double>(std::numeric_limits<int>::min()) || num2 > static_cast<double>(std::numeric_limits<int>::max())) {
                std::cout << "type conversion error" << std::endl;
            }
            else {
                help2 = static_cast<int>(num2);
            }

            if (help1 == help2)
            {
                if (help1 == 0)
                {
                    if (starts_with_zero == true) { zero_count++; }
                    result *= 10;
                    result += help1;
                }
                else
                {
                    starts_with_zero = false;
                    result *= 10;
                    result += help1;
                }
            }
            else
            {
                result *= 10;
                result += help2;
                break;
            }

            num1 -= help1;
            num2 -= help2;
            help1 = 0;
            help2 = 0;
            k++;
        }
        else {
            help1 = static_cast<int>(num1);
            num1 -= help1;

            help2 = static_cast<int>(num2);
            num2 -= help2;

            help1 = 0;
            help2 = 0;
        }
    }

    push_back_to_zeros(zero_count);
    return result;
}

String Arifmetic_code::int_to_bin(long long num)
{
    String encoded = "\0";
    int digit = 0;
    char help;
    while (num != 0) {
        digit = num % 2;
        help = Get_char_digit(digit);
        encoded.push_before(help);
        num /= 2;
    }
    return encoded;
}

double Arifmetic_code::bin_to_double(const String& text, int len)
{
    double ten = 10;
    long long base = 1;
    long long result = 0;
    int help = 0;
    double result_to_return = 1;
    for (int i = len - 1; i >= 0; i--) {
        help = Get_int_digit(text[i]);
        result += help * base;
        base *= 2;
    }
    result_to_return = result / ten;
    while (result_to_return > 1) {
        result_to_return = result / ten;
        ten *= 10;
    }
    return result_to_return;
}

char Arifmetic_code::Get_char_digit(int digit)
{
    digit %= 10;
    char char_digit = 'A';
    switch (digit) {
    case 1:
        char_digit = '1';
        break;
    case 2:
        char_digit = '2';
        std::cout << "not binary output" << std::endl;
        break;
    case 3:
        char_digit = '3';
        std::cout << "not binary output" << std::endl;
        break;
    case 4:
        char_digit = '4';
        std::cout << "not binary output" << std::endl;
        break;
    case 5:
        char_digit = '5';
        std::cout << "not binary output" << std::endl;
        break;
    case 6:
        char_digit = '6';
        std::cout << "not binary output" << std::endl;
        break;
    case 7:
        char_digit = '7';
        std::cout << "not binary output" << std::endl;
        break;
    case 8:
        char_digit = '8';
        std::cout << "not binary output" << std::endl;
        break;
    case 9:
        char_digit = '9';
        std::cout << "not binary output" << std::endl;
        break;
    case 0:
        char_digit = '0';
        break;

    deafault:
        std::cout << "Get_digit function error" << std::endl;
        break;

    }
    return char_digit;
}

int Arifmetic_code::Get_int_digit(char digit)
{
    int result = 0;
    if ((digit > '9') || (digit < '0')) {
        std::cout << "Wrong argument at Get_int_digit" << std::endl;
        return 11;
    }
    if (digit == '1') result = 1;
    else if (digit == '2') result = 2;
    else if (digit == '3') result = 3;
    else if (digit == '4') result = 4;
    else if (digit == '5') result = 5;
    else if (digit == '6') result = 6;
    else if (digit == '7') result = 7;
    else if (digit == '8') result = 8;
    else if (digit == '9') result = 9;
    else  result = 0;
    return result;
}


void Arifmetic_code::push_back_to_relative(const double* newRow) {
    if (this->frequency_relative_array[0] != nullptr) {
        int cols = alphbt_array[current_index].Get_length();
        double** newData = new double* [this->frequency_relative_array_rows + 1];
        for (int i = 0; i < this->frequency_relative_array_rows; ++i) {
            cols = alphbt_array[i].Get_length();
            newData[i] = new double[cols];
            for (int j = 0; j < cols; ++j) {
                newData[i][j] = this->frequency_relative_array[i][j];

            }
            delete[] this->frequency_relative_array[i];
        }
        cols = alphbt_array[current_index].Get_length();

        newData[this->frequency_relative_array_rows] = new double[cols];

        for (int i = 0; i < cols; ++i) {
            newData[this->frequency_relative_array_rows][i] = newRow[i];
        }

        delete[] this->frequency_relative_array;

        this->frequency_relative_array_rows += 1;
        this->frequency_relative_array = new double* [this->frequency_relative_array_rows];


        for (int i = 0; i < this->frequency_relative_array_rows; ++i) {
            cols = alphbt_array[i].Get_length();
            this->frequency_relative_array[i] = new double[cols];
            for (int j = 0; j < cols; ++j) {
                this->frequency_relative_array[i][j] = newData[i][j];
             
            }
        }

    }
    else {
        int cols = alphbt_array[current_index].Get_length();
        this->frequency_relative_array[0] = new double[cols];
        for (int i = 0; i < cols; ++i) {
            this->frequency_relative_array[0][i] = newRow[i];
        }


    }
}

void Arifmetic_code::push_back_to_zeros(int new_num)
{
    int* newData = new int[this->zeros_in_the_initial_double_sz + 1];
    for (int i = 0; i < this->zeros_in_the_initial_double_sz; ++i) {
        newData[i] = this->zeros_in_the_initial_double[i];
    }
    delete[] this->zeros_in_the_initial_double;
    newData[this->zeros_in_the_initial_double_sz] = new_num;
    this->zeros_in_the_initial_double_sz += 1;
    this->zeros_in_the_initial_double = new int[this->zeros_in_the_initial_double_sz];
    for (int i = 0; i < this->zeros_in_the_initial_double_sz; ++i) {
        this->zeros_in_the_initial_double[i] = newData[i];
    }
    delete[] newData;
}

void Arifmetic_code::push_back_to_BString(const String newRow)
{
    if (this->alphbt_array[0].Get_length() != 0) {
        int cols = alphbt_array[current_index].Get_length(); 
        String* newData = new String[this->alphbt_arr_rows + 1];
        for (int i = 0; i < this->alphbt_arr_rows; ++i) {
            newData[i] = alphbt_array[i];
            alphbt_array[i].~String();
        }

        newData[this->alphbt_arr_rows] = newRow;


        this->alphbt_arr_rows += 1;
        this->alphbt_array = new String[this->alphbt_arr_rows];

        for (int i = 0; i < this->alphbt_arr_rows; ++i) {
            alphbt_array[i] = newData[i]; 
        }
    }
    else {
        this->alphbt_array[0] = newRow;
        this->alphbt_arr_rows += 1;
    }
}

