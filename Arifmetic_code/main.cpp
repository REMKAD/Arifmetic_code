#include <iostream>
#include "String.h"
#include "Arifmetic_code.h"

int main() {

 
    std::ifstream f_1("in_1.txt");
    std::ifstream f_2("in_2.txt");
    String s_1, s_2;
    if (f_1.is_open() && f_2.is_open()) {
        f_1 >> s_1;
        f_2 >> s_2;
    }
    else {
        std::cerr << "Failed to open one or both files" << std::endl;
    }
    
    String S = "AAB";
    Arifmetic_code a;
    
    a.get_text(S, S.Get_length());
    a.encode_text();
    String b = a.Get_encoded();
    std::cout << b << std::endl;
   // a.decode_text();
    //String c = a.Get_decoded();
    //std::cout << c << std::endl;
    
 
    return 0;

}
//0110 0111 0100 1010 1011