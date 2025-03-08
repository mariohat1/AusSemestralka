#include "file_reader.h"

void file_reader::skip_lines(int count)
{
    std::string line;
    for (size_t i = 0; i < count; i++)
    {
        std::getline(input_reader,line);
    }
}




std::vector<commune>& file_reader::read_file(int year)
{
   
    input_reader.open(std::to_string(year) + ".csv");

   
    if (!input_reader.is_open()) {
        throw new std::runtime_error("Failed to open file");
    }

    skip_lines(9);

    std::string line,temp, section;
    std::getline(input_reader, line, ';');
    int file_year;
    std::stringstream ss(line);
    ss >> temp >> section;
    ss.clear();
    
    std::getline(input_reader, line, ';');
    ss.str(line);

    ss >>  file_year; 
    if (file_year != 2020)
    {
        throw new std::runtime_error("Wrong file opened");
    }
    skip_lines(3);
    std::string name, code;
        unsigned int male, female;
    while (std::getline(input_reader, line))
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
        const commune comm = commune(name.c_str(), code.c_str(), male, female);
        data.push_back(comm);

    }
	return data ;
}

file_reader::~file_reader()
{
    if (input_reader.is_open())
    {
        input_reader.close();
    }
}
