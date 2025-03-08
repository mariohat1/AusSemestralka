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
    std::string s(this->name);
    std::cout << s << std::endl;
    
}


