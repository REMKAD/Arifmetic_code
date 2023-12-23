#include "Arifmetic_code.h"
#include <limits>


Arifmetic_code::Arifmetic_code()
{
    this->frequency = new double[1];
    this->frequency[0] = 0;
    this->intervals = new double[1];
    this->intervals[0] = 0;
    this->frequency_relative = new double[1];
    this->frequency_relative[0] = 0;
}

Arifmetic_code::~Arifmetic_code()
{
    if (this->frequency != nullptr) delete this->frequency;
}

void Arifmetic_code::encode_text()
{
    int len_text = this->text.Get_length();
    double limit_l = 0;
    double limit_r = 1;
    double last_one = 0;
    double last_limit_l = 0;
    double last_limit_r = 1;
    make_frequency_relative();
    // Add this loop to print the elements in frequency_relative
    std::cout << "Frequency Relative Elements:" << std::endl;
    for (int i = 0; i < length_f; ++i) {
        std::cout << "frequency_relative[" << i << "]: " << frequency_relative[i] << std::endl;
    }

    int k = 0;
    for (int i = 0; i < len_text; i++){
        make_intervals(limit_l, limit_r);
        std::cout << "" << std::endl;

        std::cout << "\tLimit_l: " << limit_l << "\tLimit_r: " << limit_r << std::endl;
        // Print intervals for debugging or observation
        std::cout << "Intervals: ";
        for (int j = 0; j < length_f; j++) {
            std::cout << intervals[j] << " ";
        }
        std::cout << std::endl;

        

        for (int j = 0; j < length_f; j++){

            if (this->alphbt[j] == this->text[i]){
                std::cout << "\t" << this->alphbt[j] << std::endl;
                if (j != 0) {

                    limit_r =  intervals[j];
                    limit_l =  intervals[j - 1];
                }
                else {
                    limit_r = intervals[j];
                }
                break;
            }
        }
        last_one = limit_l + (limit_r - limit_l) / 2; // why do you need last one?
        std::cout << "\t limit_l, limit_r: " << limit_l << " " << limit_r << std::endl;
        last_limit_l = limit_l;
        last_limit_r = limit_r;
    }
    this->encoded = int_to_bin(choose_the_shortest_number_in_the_interval(double_to_int(last_limit_l), double_to_int(last_limit_r)));
    std::cout << "Encoded: " << double_to_int(last_limit_l) << std::endl;
    std::cout << "Encoded: " << double_to_int(last_limit_r) << std::endl;
    std::cout << "result: " << choose_the_shortest_number_in_the_interval(double_to_int(last_limit_l), double_to_int(last_limit_r)) << std::endl;
}

String Arifmetic_code::Get_encoded()
{
    return this->encoded;
}


//���������� ������������� ������ ������

void Arifmetic_code::decode_text()
{
    double encoded_number = bin_to_double(this->text, this->text.Get_length());
    std::cout << "Encoded: " << encoded_number << std::endl;

    int len_text = 0;
    for (int j = 0; j < length_f - 1; j++) len_text += frequency[j];

    
    double limit_l = 0;
    double limit_r = 1;
    double last_one = 0;
    int k = 0;
    for (int i = 0; i < len_text; i++) {
        make_intervals(limit_l, limit_r);

        std::cout << "" << std::endl;

        std::cout << "\tLimit_l: " << limit_l << "\tLimit_r: " << limit_r << std::endl;
        // Print intervals for debugging or observation
        std::cout << "Intervals: ";
        for (int j = 0; j < length_f; j++) {
            std::cout << intervals[j] << " ";
        }
        std::cout << std::endl;

        find_letter(encoded_number);

        for (int j = 0; j < length_f; j++) {
            if (this->alphbt[j] == this->decoded[i]) {
                std::cout << "\t" << this->alphbt[j] << std::endl;
 
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

void Arifmetic_code::print_frequency()
{
    for (int i = 0; i < this->alphbt.Get_length(); i++) {
        std::cout << this->frequency[i]<< std::endl;
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

void Arifmetic_code::get_text(const String& text, int len, int& mode) 
{   
    if (mode == 0) {
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
            
        
        this->length_f = this->alphbt.Get_length();
        
        if (this->frequency_relative != nullptr) {  
            delete[] this->frequency_relative;
            this->frequency_relative = nullptr; // Reset the pointer after deletion
        } 
        if (this->frequency != nullptr) delete this->frequency;
    
        

        if (this->intervals != nullptr) delete this->intervals;
        intervals = new double[this->length_f];
        frequency = new double[this->length_f];
        frequency_relative = new double[this->length_f] ;
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
        for (int i = 0; i < this->length_f-1; i++) {
            for (int j = i+1; j < this->length_f; j++) {
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
    }
    else if (mode == 1) {
        this->text = text;
        if (this->intervals != nullptr) delete this->intervals;
        std::cout << this->text << std::endl;
    }
    std::cout << this->text << std::endl;
}

void Arifmetic_code::make_intervals(double lim_l, double lim_r)
{   
    if(lim_r == 1){
        for (int j = 0; j < length_f; j++) {
            if (j == 0) {
            intervals[j] = frequency_relative[j];
            } else {
                intervals[j] = intervals[j - 1] + frequency_relative[j];
            }
        }
    }
    else {
        intervals[0] = lim_l + (lim_r - lim_l) * frequency_relative[0];
        for (int j = 1; j < length_f-1; j++) {
            intervals[j] = intervals[j-1]+(lim_r - lim_l) *frequency_relative[j];
        }
        intervals[length_f - 1] = lim_r ;
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
            std::cout << intervals[i] << "=interval;  number=" << encoded_number << std::endl;
            decoded.push_back(this->alphbt[i]);

            break;
        }
    }
}

long long Arifmetic_code::choose_the_shortest_number_in_the_interval(long long lim_l, long long lim_r)
{   
    long long diff = lim_r - lim_l;
    long long divisor = 1;

    while (diff >= divisor) {
        divisor *= 10;
    }

    divisor /= 10;
    long long result = (lim_r - lim_r % divisor) / divisor; 

    return result;
    std::cout << "double to int finish" << std::endl;
}

String Arifmetic_code::int_to_bin(int num)
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
    int base = 1;
    int result = 0;
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
    //std::cout << digit << std::endl;
    digit %= 10;
    //std::cout << digit << "=digit" << std::endl;
    char char_digit='A';
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
            char_digit = '0';
            std::cout << "not binary output" << std::endl;
            break;
        case 0:
            char_digit = '0';
            std::cout << "not binary outputA" << std::endl;
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

long long Arifmetic_code::double_to_int(double num)
{
    long long result = 0;
    int help = 0;
    int k = 0;
    // std::cout << num << "  = num" << std::endl;
    while ((10 - num) != 10) {
        // std::cout << 10 - num << "  = 10-num" << std::endl;
        if ((10 - num) > 9) {
            if (k > 15) break;
            num *= 10;
          
            if (num < static_cast<double>(std::numeric_limits<int>::min()) || num > static_cast<double>(std::numeric_limits<int>::max())) {
                std::cout << "����� ��������� �� ��������� ��������� ����� �����" << std::endl;
            }
            else {
                help = static_cast<int>(num);
            }
            result *= 10;
            result += help;
            // std::cout << num << " -   " << help << "   = num - help" << std::endl;
            num -= help;
            // std::cout << num << " - \t\t\t" << help << "   = num - help" << std::endl;
            help = 0;
            // std::cout << "\n" << result << "\n" << std::endl;
            k++;
        }
        else {
            help = static_cast<int>(num);
            num -= help;
            help = 0;
        }
    }
    // std::cout << result << " result" << std::endl;
    return result;
}

int Arifmetic_code::get_freq_size()
{
    return this->length_f;
}
