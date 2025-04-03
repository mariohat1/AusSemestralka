#include "fileReader.h"

void fileReader::skipLines(int count)
{
	std::string line;
	for (size_t i = 0; i < count; i++)
	{
		std::getline(inputReader, line);
	}
}

commune* fileReader::containsCode(unsigned int code)
{
	for (auto& comm : this->data)
	{
		if (comm->getCode() == code)
		{
			return comm;
		}
	}
	return nullptr;
}

ds::amt::MultiWayExplicitHierarchy<commune*>& fileReader::loadHierarchy()
{
	hierarchy.emplaceRoot().data_ = new commune("rakusko", 1);
	inputReader.open("uzemie.csv");
	std::string line;
	int currentCodeProcessed = 11;
	int count = 0;
	CommuneBlock* currentParent = hierarchy.accessRoot();
	if (currentParent == nullptr) {
		std::cout << "asd";
	}

	while (std::getline(inputReader, line)) {



		std::string name;
		int code = 0;
		if (line.empty()) {
			break;
		}
		std::stringstream ss(line);
		std::getline(ss, name, ';');
		std::getline(ss, line, '<');

		std::getline(ss, line, '>');
		code = stoi(line.substr(2));
		int level = std::to_string(code).size();

		if (level == 1)
		{

			hierarchy.emplaceSon(*currentParent, code - 1).data_ = new commune(name.c_str(), code);


		}


		if (level == 2)
		{

			size_t parentIndex = (code / 10) - 1;
			size_t sonIndex = (code % 10) - 1;
			CommuneBlock* newParent = hierarchy.accessSon(*currentParent, parentIndex);
			hierarchy.emplaceSon(*newParent, sonIndex).data_ = new commune(name.c_str(), code);

		}


		if (level == 3) {
			size_t grandParentIndex = (code / 100) - 1;
			size_t parentIndex = ((code % 100) / 10) - 1;
			size_t sonIndex = (code % 10) - 1 > 0 ? (code % 10) - 1 : 0;
			CommuneBlock* grandParent = hierarchy.accessSon(*currentParent, grandParentIndex);
			CommuneBlock* newParent = hierarchy.accessSon(*grandParent, parentIndex);
			hierarchy.emplaceSon(*newParent, sonIndex).data_ = new commune(name.c_str(), code);


		}
	}
	line = "";
	inputReader.close();
	this->data = this->readFile();
	inputReader.open("obce.csv");

	while (std::getline(inputReader, line)) {
		std::string name, hierarchyCode;
		int code = 0;
		if (line.empty()) {
			break;
		}
		std::stringstream ss(line);
		std::getline(ss, name, ';');
		std::getline(ss, line, '<');
		if (std::getline(ss, line, '>')) {
			std::stringstream(line) >> code;
		}
		ss >> hierarchyCode;
		int hierarchyOrder = stoi(hierarchyCode.substr(3));


		size_t grandParentIndex = (hierarchyOrder / 100) - 1;
		size_t parentIndex = ((hierarchyOrder % 100) / 10) - 1;
		size_t sonIndex = (hierarchyOrder % 10) - 1 > 0 ? (hierarchyOrder % 10) - 1 : 0;
		CommuneBlock* grandParent = hierarchy.accessSon(*currentParent, grandParentIndex);
		CommuneBlock* Parent = hierarchy.accessSon(*grandParent, parentIndex);
		CommuneBlock* newParent = hierarchy.accessSon(*Parent, sonIndex);
		
		if (name == "Weppersdorf")
		{
			std::cout << "go";
		}
		CommuneBlock* son = &hierarchy.emplaceSon(*newParent, count);
		
		son->data_ =  containsCode(code);
		
		count = hierarchy.degree(*newParent) - 1 == count ? count = 0 : count++;



	}

	inputReader.close();

	return this->hierarchy;
}







std::vector<commune*>& fileReader::readFile()
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
			year yearToAdd;
			yearToAdd.female = female;
			yearToAdd.male = male;
			yearToAdd.year = currentYear;

			commune* comm = containsCode(code);


			if (comm == nullptr) {
				commune* newComm = new commune(name.c_str(), code);
				newComm->addYear(yearToAdd);
				data.push_back(newComm);
			}
			else {

				comm->addYear(yearToAdd);
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
