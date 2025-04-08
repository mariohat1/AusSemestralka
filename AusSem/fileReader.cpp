#include "fileReader.h"

void fileReader::skipLines(int count)
{
	std::string line;
	for (size_t i = 0; i < count; i++)
	{
		std::getline(inputReader, line);
	}
}

commune* fileReader::containsCode(unsigned int code, std::vector<commune*> data)
{
	for (auto& comm : data)
	{
		if (comm->getCode() == code)
		{
			return comm;
		}
	}
	return nullptr;
}

void fileReader::cumulateHierarchy()
{
	hierarchy.processPostOrder(hierarchy.accessRoot(), [&](CommuneBlock* node) {
		commune* comm = node->data_;
		commune* parentData = nullptr;

		if (node->parent_ != nullptr)
		{
			parentData = node->parent_->data_;
			if (parentData->getYears().empty())
			{
				for (size_t i = 0; i < comm->getYears().size(); i++)
				{
					year years = {};
					parentData->addYear(years);

				}
			}

			for (size_t i = 0; i < comm->getYears().size(); i++)
			{

				parentData->getYears()[i].female += comm->getYears()[i].female;
				parentData->getYears()[i].male += comm->getYears()[i].male;
				parentData->getYears()[i].year = comm->getYears()[i].year;
			}
		}




		});
}

ds::amt::MultiWayExplicitHierarchy<commune*>& fileReader::loadHierarchy(std::vector<commune*>& data)
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
			commune* comm = new commune(name.c_str(), code);
			hierarchy.emplaceSon(*currentParent, static_cast<size_t>(code) - 1).data_ = comm;
			comm->setLevel(level);
			


		}


		if (level == 2)
		{
			commune* comm = new commune(name.c_str(), code);
			size_t parentIndex = (code / 10) - 1;
			size_t sonIndex = (code % 10) - 1;
			CommuneBlock* newParent = hierarchy.accessSon(*currentParent, parentIndex);
			
			hierarchy.emplaceSon(*newParent, sonIndex).data_ = comm;
			comm->setLevel(level);

		}


		if (level == 3) {
			commune* comm = new commune(name.c_str(), code);
			size_t grandParentIndex = (code / 100) - 1;
			size_t parentIndex = ((code % 100) / 10) - 1;
			size_t sonIndex = (code % 10) - 1 > 0 ? (code % 10) - 1 : 0;
			CommuneBlock* grandParent = hierarchy.accessSon(*currentParent, grandParentIndex);
			CommuneBlock* newParent = hierarchy.accessSon(*grandParent, parentIndex);
			hierarchy.emplaceSon(*newParent, sonIndex).data_ = comm;
			comm->setLevel(level);

		}
	}
	line = "";
	inputReader.close();
	
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


		CommuneBlock* son = &hierarchy.emplaceSon(*newParent, count);
		size_t level = 4;
		commune* comm = containsCode(code, data);
		son->data_ = comm;
		son->data_->setLevel(level);
		count = hierarchy.degree(*newParent) - 1 == count ? count = 0 : count++;



	}
	
	inputReader.close();
	this->cumulateHierarchy();

	return this->hierarchy;
}







std::vector<commune*> fileReader::readFile()
{
	std::vector<commune*> data;
	
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

			 commune* comm = containsCode(code, data);

			 
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
