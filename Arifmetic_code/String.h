#pragma once

#include <iostream>
#include <fstream>

class String
{

private:

        //variables 

    int length;
    char* str = nullptr;
    int Strlen(const char* str);

public:

        //construct destruct

    String();//default constructor
    String(const String& other);//copy constructor
    String(String&& other) noexcept;//move constructor 
    String(const char* str);//constructor
    ~String();//destruct
        
        //operations
    String& operator= (const String& other);
    String& operator= (String&& other) noexcept;
    String& operator+= (const String& s);
    
        //help functions
    void make_zero();
    void push_before(char symb);
    void push_back(char symb);
    int Get_length();
    void writeToFile();
    void print();
    void set_length(int len);

        //operators
    char& operator[](int indx); //indexof string[10]=?
    char  operator[](int indx)const;

        //input and output
    friend std::istream& operator>>(std::istream& is, String& str);
    friend std::ostream& operator<<(std::ostream& stream, const String& string);

};



