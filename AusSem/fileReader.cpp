#include "FileReader.h"

void FileReader::skipLines(int count)
{
	std::string line;
	for (size_t i = 0; i < count; i++)
	{
		std::getline(inputReader, line);
	}
}

TerritorialUnit* FileReader::containsCode(unsigned int code, std::vector<TerritorialUnit*> data)
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

void FileReader::cumulateHierarchy()
{
	hierarchy.processPostOrder(hierarchy.accessRoot(), [&](CommuneBlock* node) {
		TerritorialUnit* comm = node->data_;
		TerritorialUnit* parentData = nullptr;

		if (node->parent_ != nullptr)
		{
			parentData = node->parent_->data_;
			if (parentData->getYears().empty())
			{
				for (size_t i = 0; i < comm->getYears().size(); i++)
				{
					Year years = {};
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

ds::amt::MultiWayExplicitHierarchy<TerritorialUnit*>& FileReader::loadHierarchy(std::vector<TerritorialUnit*>& data)
{
	hierarchy.emplaceRoot().data_ = new TerritorialUnit("rakusko", 1);
	inputReader.open("uzemie.csv");
	std::string line;
	int currentCodeProcessed = 11;
	int count = 0;
	CommuneBlock* currentParent = hierarchy.accessRoot();
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
			const char* nameToAdd = name.c_str();
			TerritorialUnit* comm = new TerritorialUnit(name.c_str(), code);
			UnitData data;
			data.single = comm;
			this->geoDivisionTable.insert(name, data, true);
			hierarchy.emplaceSon(*currentParent, static_cast<size_t>(code) - 1).data_ = comm;
			comm->setLevel(level);
		}
		if (level == 2)
		{
			TerritorialUnit* comm = new TerritorialUnit(name.c_str(), code);
			size_t parentIndex = (code / 10) - 1;
			size_t sonIndex = (code % 10) - 1;
			CommuneBlock* newParent = hierarchy.accessSon(*currentParent, parentIndex);
			hierarchy.emplaceSon(*newParent, sonIndex).data_ = comm;
			comm->setLevel(level);
			UnitData data;
			data.single = comm;
			this->federalRepublicTable.insert(name, data, true);
		}
		if (level == 3) {
			TerritorialUnit* comm = new TerritorialUnit(name.c_str(), code);
			size_t grandParentIndex = (code / 100) - 1;
			size_t parentIndex = ((code % 100) / 10) - 1;
			int sonIndex = (code % 10) - 1 > 0 ? (code % 10) - 1 : 0;
			CommuneBlock* grandParent = hierarchy.accessSon(*currentParent, grandParentIndex);
			CommuneBlock* newParent = hierarchy.accessSon(*grandParent, parentIndex);
			hierarchy.emplaceSon(*newParent, sonIndex).data_ = comm;
			comm->setLevel(level);
			UnitData data;
			data.single = comm;
			this->regionTable.insert(name, data, true);
		}
	}
	line = "";
	inputReader.close();
	inputReader.open("obce.csv");
	int i = 0;
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
		int sonIndex = (hierarchyOrder % 10) - 1 > 0 ? (hierarchyOrder % 10) - 1 : 0;
		CommuneBlock* grandParent = hierarchy.accessSon(*currentParent, grandParentIndex);
		CommuneBlock* Parent = hierarchy.accessSon(*grandParent, parentIndex);
		CommuneBlock* newParent = hierarchy.accessSon(*Parent, sonIndex);
		count = hierarchy.degree(*newParent);
		CommuneBlock* son = &hierarchy.emplaceSon(*newParent, count);
		size_t level = 4;
		TerritorialUnit* comm = data[i];
		son->data_ = comm;
		son->data_->setLevel(level);
		UnitData data;
		data.single = comm;
		this->communeTable.insert(name, data, true);
		i++;
	}
	inputReader.close();
	this->cumulateHierarchy();
	return this->hierarchy;
}



std::vector<TerritorialUnit*> FileReader::readFile()
{
	std::vector<TerritorialUnit*> data;
	int firstFile = false;

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
		unsigned int k = 0;
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
			Year yearToAdd;
			yearToAdd.female = female;
			yearToAdd.male = male;
			yearToAdd.year = currentYear;
			if (!firstFile) {
				TerritorialUnit* newComm = new TerritorialUnit(name.c_str(), code);
				newComm->addYear(yearToAdd);
				data.push_back(newComm);
			}
			else {
				data[k]->addYear(yearToAdd);
			}
			k++;
		}
		firstFile = true;
		inputReader.close();
	}
	return data;
}

FileReader::~FileReader()
{
	hierarchy.processPostOrder(hierarchy.accessRoot(), [](CommuneBlock* node) {
		delete node->data_;
		node->data_ = nullptr;
		});
	geoDivisionTable.clear();
	federalRepublicTable.clear();
	regionTable.clear();
	communeTable.clear();
	hierarchy.clear();
	if (inputReader.is_open())
	{
		inputReader.close();
	}
}
