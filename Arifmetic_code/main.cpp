#include <iostream>
#include <chrono>
#include "String.h"
#include "Arifmetic_code.h"


int main() {

    const char* inputFile = "hey.txt"; 
    const char* encodedFile = "encode.bin";
    const char* decodedFile = "decoded.txt";

    Arifmetic_code a;

    auto start = std::chrono::high_resolution_clock::now();

    a.encodeAndWriteToFile(inputFile, encodedFile);

    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> duration = end - start;
    std::cout << "Duration of encoding: " << duration.count() << "seconds" << std::endl;

    auto start_1 = std::chrono::high_resolution_clock::now();

    a.decodeAndWriteToFile(encodedFile, decodedFile);
    
    auto end_1 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration_1 = end_1 - start_1;
    std::cout << "Duration of decoding: " << duration_1.count() << "seconds" << std::endl;
    return 0;
}

