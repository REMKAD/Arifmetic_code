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

    std::ofstream output(outputFile, std::ios::binary);
    if (!output.is_open()) {
        std::cerr << "Failed to open output file" << std::endl;
        input.close();
        return;
    }

    String content;
    char ch;

    while (input.get(ch)) {
        content.push_back(ch);

        if (content.Get_length() >= 5) {
            content.push_back('!'); // Append '!' to the content
            a.get_text(content, content.Get_length(), mode);
            a.encode_text();
            String encodedString = a.Get_encoded();

            for (int i = 0; i < encodedString.Get_length(); ++i) {
                output << encodedString[i];
            }

            output << ' '; // Separator between encoded segments

            content = "";
        }
    }

    // Encode the remaining content
    if (content.Get_length() > 0) {
        content.push_back('!');
        a.get_text(content, content.Get_length(), mode);
        a.encode_text();
        String encodedString = a.Get_encoded();

        for (int i = 0; i < encodedString.Get_length(); ++i) {
            output << encodedString[i];
        }
    }

    input.close();
    output.close();
    std::cout << "Done" << std::endl;
}

void decodeAndWriteToFile(const char* inputFile, const char* outputFile, Arifmetic_code& a) {
    int mode = 1; // 0 - encode, 1 - decode
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

    while (input.get(ch)) {
        if (ch != ' ') {
            encodedContent.push_back(ch);
        } else {
            a.get_text(encodedContent, encodedContent.Get_length(), mode);
            a.decode_text();
            String decodedString = a.Get_decoded();

            for (int i = 0; i < decodedString.Get_length(); ++i) {
                output << decodedString[i];
            }

            encodedContent = "";
        }
    }
    if (encodedContent.Get_length() != 0) {
            a.get_text(encodedContent, encodedContent.Get_length(), mode);
            a.decode_text();
            String decodedString = a.Get_decoded();

            for (int i = 0; i < decodedString.Get_length(); ++i) {
                output << decodedString[i];
            }

            encodedContent = "";
            }

    input.close();
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