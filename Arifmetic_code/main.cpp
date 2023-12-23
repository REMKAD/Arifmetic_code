#include <iostream>
#include "String.h"
#include "Arifmetic_code.h"

void encodeAndWriteToFile(const char* inputFile, const char* outputFile, Arifmetic_code& a) {
    int mode = 0; // 0 - encode, 1 - decode
    std::ifstream input(inputFile);
    if (!input.is_open()) {
        std::cerr << "Failed to open input file" << std::endl;
        return;
    }

    String content;
    char ch;
    while (input.get(ch)) {
        content.push_back(ch);
        if (content.Get_length() >= 15) // Stop reading after 15 characters
            break;
    }
    input.close();

    content.push_back('!'); // Append '!' to the content

    a.get_text(content, content.Get_length(), mode);
    a.encode_text();
    String encodedString = a.Get_encoded();
    std::ofstream output(outputFile, std::ios::binary);
    if (!output.is_open()) {
        std::cerr << "Failed to open output file" << std::endl;
        return;
    }

    for (int i = 0; i < encodedString.Get_length(); ++i) {
        output << encodedString[i];
    }
    output.close();
}

void decodeAndWriteToFile(const char* inputFile, const char* outputFile, Arifmetic_code& a) {
    int mode = 1; // 0 - encode, 1 - decode
    std::ifstream input(inputFile, std::ios::binary);
    if (!input.is_open()) {
        std::cerr << "Failed to open input file" << std::endl;
        return;
    }

    String encodedContent;
    char ch;
    while (input.get(ch)) {
        encodedContent.push_back(ch);
    }
    input.close();
    a.get_text(encodedContent, encodedContent.Get_length(), mode);
    a.decode_text();
    String decodedString = a.Get_decoded();
    std::cout << decodedString << std::endl;
    std::cout << decodedString << std::endl;
    std::ofstream output(outputFile);
    if (!output.is_open()) {
        std::cerr << "Failed to open output file" << std::endl;
        return;
    }

    for (int i = 0; i < decodedString.Get_length(); ++i) {
        output << decodedString[i];
    }
    output.close();
}


int main() {

    const char* inputFile = "hey.txt"; // Change this to your input file name
    const char* encodedFile = "encoded.bin"; // Change this to your encoded file name
    const char* decodedFile = "decoded.txt"; // Change this to your decoded file name

    Arifmetic_code a;
    encodeAndWriteToFile(inputFile, encodedFile, a);
    decodeAndWriteToFile(encodedFile, decodedFile, a);


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