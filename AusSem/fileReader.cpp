#include "fileReader.h"

void fileReader::skipLines(int count)
{
    std::string line;
    for (size_t i = 0; i < count; i++)
    {
        std::getline(inputReader,line);
    }
}




std::vector<commune>& fileReader::readFile(int year)
{
   
    inputReader.open(std::to_string(year) + ".csv");

   
    if (!inputReader.is_open()) {
        throw new std::runtime_error("Failed to open file");
    }

    skipLines(9);

    std::string line,temp, section;
    std::getline(inputReader, line, ';');
    int fileYear;
    std::stringstream ss(line);
    ss >> temp >> section;
    ss.clear();
    
    std::getline(inputReader, line, ';');
    ss.str(line);

    ss >>  fileYear; 
    if (fileYear != 2020)
    {
        throw new std::runtime_error("Wrong file opened");
    }
    skipLines(3);
    std::string name, code;
        unsigned int male, female = 0;
    while (std::getline(inputReader, line))
    {
        
        std::stringstream ss(line);
        std::getline(ss, name, ';');
        std::getline(ss, code, ';');
        if (std::getline(ss, line, ';')) {
            std::stringstream(line) >> male;
        }       
        std::getline(ss, line, ';'); 

       
        if (std::getline(ss, line, ';')) {
            std::stringstream(line) >> female;
        }
        
        if (name == "Nicht klassifizierbar")
        {
            break;
        }    
        commune comm = commune(name.c_str(), code.c_str(), male, female);
        
        data.push_back(comm);

    }
	return data ;
}

fileReader::~fileReader()
{
    if (inputReader.is_open())
    {
        inputReader.close();
    }
}
