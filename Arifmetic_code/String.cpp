#include "String.h"


String::String() {
    str = new char[1];
    str[0] = '\0';
    length = 0;
}

String::String(const String& other) {
    this->length = other.length;
    if (this->str != nullptr) delete this->str;
    str = new char[this->length + 1]; 

    for (size_t i = 0; i < this->length; i++) {
        this->str[i] = other.str[i];
    }
    str[this->length] = '\0'; 
}

String::String(String&& other) noexcept {
    this->length = other.length;
    this->str = other.str; 
    other.length = 0;
    other.str = nullptr; 
}

String::String(const char* str) {
    this->length = Strlen(str);
    this->str = new char[length + 1];
    for (int i = 0; i < length; i++) {
        this->str[i] = str[i];
    }
    this->str[length] = '\0';
}

String::~String() {
    delete[] this->str;
}

String& String::operator =(const String& other) {
    if (this->str != nullptr) {
        delete[] this->str;
    }
    int length = Strlen(other.str);
    this->length =  length;
    this->str = new char[length + 1];
    for (int i = 0; i < length; i++) {
        this->str[i] = other.str[i];
    }
    this->str[length] = '\0';
    return *this;
}

String& String::operator=(String&& other) noexcept {
    if (this != &other) {
        delete[] this->str; 
        this->str = other.str;
        this->length = other.length; 
        other.str = nullptr; 
        other.length = 0;
    }
    return *this;
}

String& String::operator+= (const String& s)
{
    int len_s = Strlen(s.str);
    int len = this->length + len_s;
    char* str = new char[len + 1];

    for (int j = 0; j < this->length; j++)
        str[j] = this->str[j];

    for (int i = 0; i < len_s; i++)
        str[this->length + i] = s[i];

    str[len] = '\0';
    delete this->str;
    this->length = len;
    this->str = str;
    return *this;
}

void String::make_zero() {
    if (this->str != nullptr) delete this->str;
    this->str = new char[1];
    this->str[0] = '\0';
    this->length = 0;
}

void String::push_before(char symb)
{
    int length = this->length;
    char* help = new char[length];
    this->length += 1;
    for (int i = 0; i < length; i++) {
        help[i] = str[i];
    }
    if (this->str != nullptr) delete this->str;
    this->str = new char[this->length + 1];
    this->str[0] = symb;
    for (int i = 0; i < length; ++i) {
        this->str[i + 1] = help[i];
    }
    this->str[this->length] = '\0';
    if (help != nullptr) delete[] help;
}

void String::push_back(char symb)
{
    int length = this->length;
    char* help = new char[length];
    this->length += 1;
    for (int i = 0; i < length; i++) {
        help[i] = str[i];
    }
    if (this->str != nullptr) delete this->str;
    this->str = new char[this->length + 1];
    for (int i = 0; i < length;++i) {
        this->str[i] = help[i];
    }
    this->str[this->length - 1] = symb;
    this->str[this->length] = '\0';
    if (help != nullptr) delete[] help;
    
}

int String::Get_length() {
    return length;
}

void String::writeToFile()
{
    std::ofstream outputFile("out.txt", 'w'); // Используем флаг ios::app
    if (outputFile.is_open()) {
        outputFile << this->str;
        outputFile.close();
    }
    else {
        std::cout << "Unable to open or create the file 'out.txt'" << std::endl;
    }
}

void String::print()
{
    for (int i = 0; i < length;i++) {
        std::cout << str[i];
    }
    std::cout << std::endl;
}

char& String::operator[](int indx)
{
    if (indx < 0 || indx > this->length)
    {
        throw std::out_of_range("there is no spot in string with this index bro\n");
    }
    return this->str[indx];
}

char String::operator[](int indx) const
{
    if (indx < 0 || indx >= this->length)
    {
        throw std::out_of_range("there is no spot in string wiz this index bro\n");
    }
    return this->str[indx];
}

std::istream& operator>>(std::istream& is, String& str)
{
    char sent[10000];
    is.get(sent, 10000);
    if (is)
        str = sent;
    while (is && is.get() != '\n')
        continue;
    return is;
}

std::ostream& operator<<(std::ostream& stream, const String& string)
{
    stream << string.str;
    return stream;
}


int String::Strlen(const char* str) {
    if ((str == nullptr) || (str[0] == '\0')) return 0;
    int i = 0;
    while (str[i] != '\0') i++;
    return i;
}




