#include "commune.h"

commune::commune(const  char* name, const  char* code, unsigned int male, unsigned int female)
{
    this->male = male;
    this->female = female;
    size_t length = strlen(name) + 1;
    this->name = new char[length];
    strcpy_s(this->name, length, name);
    size_t length_code = strlen(code) + 1;
    this->code = new char[length_code];
    strcpy_s(this->code, length_code, code);
}

commune::commune(const commune& other)
{
    if (other.name && *other.name)
    {
        size_t length = strlen(other.name) + 1;
        name = new char[length];
        strcpy_s(name,length, other.name);

    }
      
    if (other.code && *other.code)
       {
           size_t length = strlen(other.code) + 1;
           code = new char[length];
           strcpy_s(code,length, other.code);

       }
    
    this->male = other.male;
    this->female = other.female;
    

}

commune& commune::operator=(const commune& other)
{
    if (this != &other)
    {
        if (other.name && *other.name)
        {
            size_t length = strlen(other.name) + 1;
            name = new char[length];
            strcpy_s(name, length, other.name);

        }

        if (other.code && *other.code)
        {
            size_t length = strlen(other.code) + 1;
            code = new char[length];
            strcpy_s(code, length, other.code);

        }
        this->female = other.female;
        this->male = other.male;
    }
    return *this;
}

commune::~commune()
{
    
        delete[] name;
        name = nullptr; 
   
   
        delete[] code;
        code = nullptr; 
        
}

unsigned int commune::getPopulation()
{
    return this->male + this->female;
}

void commune::print()
{
    
    std::cout << convert_utf8() << std::endl;
    
}

std::string commune::convert_utf8()
{
    std::string name_str(name);  // Convert char* to std::string

    std::string result;
    size_t len = name_str.length();

    for (size_t i = 0; i < len; ++i) {
        unsigned char firstByte = name_str[i];

        if (firstByte <= 127) {
            // Single-byte ASCII characters (0 to 127)
            result += firstByte;
        }
        else {
            // Multi-byte UTF-8 characters
            if (i + 1 < len) {
                unsigned char secondByte = name_str[i + 1];

                // Check if it's a valid continuation byte
                if ((secondByte & 0xC0) == 0x80) {
                    // Valid two-byte character
                    // Combine the first and second byte (don't add them, shift them properly)
                    unsigned char combinedByte = ((firstByte & 0x1F) << 6) | (secondByte & 0x3F);
                    result += combinedByte;
                    i++;  // Skip the second byte
                }
                else {
                    result += '?';  // Invalid sequence, replace with '?'
                }
            }
            else {
                result += '?';  // Single invalid byte, handle as error
            }
        }
    }

    return result;
}

   



