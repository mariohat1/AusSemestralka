#pragma once
#include "TableData.h"
class LevelThree
{
private:
    using UnitData = TableData<TerritorialUnit*>;
    using Table = ds::adt::Treap<std::string, UnitData>;
    Table& geoDivisionTable;
    Table& federalRepublicTable;
    Table& regionTable;
    Table& communeTable;

    void printInfo(Table& table) {
        std::string key;
        std::cout << "nazov?" << std::endl;
        std::cin.ignore();
        std::getline(std::cin, key);
        TableData<TerritorialUnit*>* data = nullptr;
        bool found = table.tryFind(key, data);
        if (found)
        {
            std::cout << "Found: ";
            if (data->duplicit != nullptr)
            {
                for (auto it = data->duplicit->begin(); it != data->duplicit->end(); ++it)
                {
                    TerritorialUnit& comm = **it;
                  
                    comm.printAll();
                }
            }
            else {
                data->single->printAll();
            }
        }
        else {
            std::cout << "Name not found" << std::endl;
        }



    };


         
public:
	LevelThree(ds::adt::Treap<std::string, UnitData>& geoDivision,
        ds::adt::Treap<std::string, UnitData>& federalRepublic,
        ds::adt::Treap<std::string, UnitData>& region,
        ds::adt::Treap<std::string, UnitData>& commune)
        : geoDivisionTable(geoDivision), federalRepublicTable(federalRepublic),
        regionTable(region), communeTable(commune) {
    }
    int run() {
        std::cout << "0 ---- geogreficke delenie" << std::endl;
        std::cout << "1 ---- spolkova republika" << std::endl;
        std::cout << "2 ---- region" << std::endl;
        std::cout << "3 ---- obec" << std::endl;
        std::cout << "q ---- quit" << std::endl;

        std::string input;
        std::cin >> input;
        
        
        if (input == "0")
        {

            this->printInfo(this->geoDivisionTable);
        }
        else if (input == "1") {
            this->printInfo(federalRepublicTable);
        }
        else if (input == "2") {
            this->printInfo(regionTable);
        }
        else if (input == "3") {
            this->printInfo(this->communeTable);
        }
        else if (input == "q") {
            return -1;
        }

    
    } 


   


	

};

