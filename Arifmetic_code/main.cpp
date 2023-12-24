#include <iostream>
#include "String.h"
#include "Arifmetic_code.h"
#include <vector>


int main() {

    const char* inputFile = "hey.txt"; // Change this to your input file name
    const char* encodedFile = "encoded.bin"; // Change this to your encoded file name
    const char* decodedFile = "decoded.txt"; // Change this to your decoded file name

    Arifmetic_code a;
    a.encodeAndWriteToFile(inputFile, encodedFile);

    

    a.decodeAndWriteToFile(encodedFile, decodedFile);
    

    return 0;
}

// int main() {

 
//     std::ifstream f_1("in_1.txt");
//     std::ifstream f_2("in_2.txt");
//     String s_1, s_2;
//     if (f_1.is_open() && f_2.is_open()) {
//         f_1 >> s_1;
//         f_2 >> s_2;
//     }
//     else {
//         std::cerr << "Failed to open one or both files" << std::endl;
//     }
    
//     String S = "ABAABAACA!";
//     Arifmetic_code a;
    
//     a.get_text(S, S.Get_length());
//     a.encode_text();
//     String b = a.Get_encoded();
//     std::cout << b << std::endl;

//     a.decode_text();
//     String c = a.Get_decoded();
//     std::cout << c << std::endl;
    
 
//     return 0;

// }
// //0110 0111 0100 1010 1011