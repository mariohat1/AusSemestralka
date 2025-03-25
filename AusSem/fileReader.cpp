#include "fileReader.h"

void fileReader::skipLines(int count)
{
    std::string line;
    for (size_t i = 0; i < count; i++)
    {
        std::getline(inputReader,line);
    }
}

commune* fileReader::containsCode(unsigned int code)
{
    for (auto& comm: this->data)
    {
        if (comm.getCode() == code)
        {
            return &comm;
        }
    }
    return nullptr;
}




std::vector<commune> fileReader::readFile()
{
    for (unsigned int currentYear = 2020; currentYear <= 2024; ++currentYear) {
        inputReader.open(std::to_string(currentYear) + ".csv");
        


        if (!inputReader.is_open()) {
            throw new std::runtime_error("Failed to open file");
        }

        skipLines(9);

        std::string line, temp, section;
        std::getline(inputReader, line, ';');
        int fileYear;
        std::stringstream ss(line);
        ss >> temp >> section;
        ss.clear();

        std::getline(inputReader, line, ';');
        ss.str(line);


        ss >> fileYear;
        if (fileYear != currentYear)
        {
            throw new std::runtime_error("Wrong file opened");
        }
        skipLines(3);
        std::string name;
        unsigned int male = 0, female = 0, code = 0;
        while (std::getline(inputReader, line))
        {

            std::stringstream ss(line);
            
            std::getline(ss, name, ';');
            std::getline(ss, line, '<');
            if (std::getline(ss, line, '>')) {
                std::stringstream(line) >> code;
            }
            std::getline(ss, line, ';');
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
            year yearToADD;
            yearToADD.female = female;
            yearToADD.male = male;
            yearToADD.year = currentYear;
            
            commune* comm = containsCode(code);

           
            if (comm == nullptr) {
                commune newComm(name.c_str(), code); 
                newComm.addYear(yearToADD);  
                data.push_back(newComm); 
            }
            else {
                
                comm->addYear(yearToADD);
            }
           

           
            
        }
        inputReader.close();
    }
	return data;
}

fileReader::~fileReader()
{
    if (inputReader.is_open())
    {
        inputReader.close();
    }
}
