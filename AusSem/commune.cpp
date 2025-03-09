#include "commune.h"

commune::commune(const  char* name, const  char* code, unsigned int male, unsigned int female)
{
    this->male = male;
    this->female = female;

    std::string name_utf8 = convert_utf8(name); 
    size_t length = name_utf8.length() + 1;    
    this->name = new char[length];

    strcpy_s(this->name, length, name_utf8.c_str());
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
    
    std::cout << this->name << std::endl;
    
}

std::string commune::convert_utf8(const char* name)
{
    std::string name_str(name);  

    std::string result;
    size_t len = name_str.length();

    for (size_t i = 0; i < len; ++i) {
        unsigned char first_byte = name_str[i];

        if (first_byte <= 127) {
            
            result += first_byte;
        }
        else { // ak je prvy bajt vacsi ako 128  kontrolujeme ci dalsi bajt je vacsi ako 128, co vlastne je utf code pre 2 bajty (co nam staci kontrolovat, lebo chcem eu jazyky)
            
            if (i + 1 < len) {
                unsigned char second_bye = name_str[i + 1];
                             
                if (second_bye >= 128) {     
                    unsigned char lower_bits = (second_bye & 0b00111111); // dolne bity 

                    unsigned char first_byte_shift = (first_byte & 0b00011111); // spravenie miesta pre dolne(tych, ktore dostaneme z second_byte_shiftu.
                    unsigned char higher_bits = first_byte_shift << 6;
                    
                    unsigned char combinedByte = higher_bits | lower_bits; // or aby sme ich skombinovali a neprisli o ziadne cisla
                    result += combinedByte;
                    i++;  
                }                
            }           
        }
    }

    return result;
}

   



