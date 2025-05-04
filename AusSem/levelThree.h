#pragma once
#include "DuplicitTreap.h"

class levelThree
{
private:
    using Table = ds::adt::Treap<std::string, CommuneData>;
    Table geoDivisionTable;
    Table federalRepublicTable;
    Table regionTable;
    Table communeTable;
         
public:
	levelThree(ds::adt::Treap<std::string, CommuneData>& geoDivision,
        ds::adt::Treap<std::string, CommuneData>& federalRepublic,
        ds::adt::Treap<std::string, CommuneData>& region,
        ds::adt::Treap<std::string, CommuneData>& commune)
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

            this->printInfo(geoDivisionTable);
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


    void printInfo(Table& table) {
        std::string key;
        std::cout << "nazov?" << std::endl;
        std::getline(std::cin, key);

        CommuneData* data = nullptr;
        bool found = table.tryFind(key,data);
        if (found)
        {
            if (data->duplicit != nullptr)
            {
                for (auto it = data->duplicit->begin(); it != data->duplicit->end(); ++it)
                {
                    commune& comm = **it;
                    std::cout << "Najdene ";
                    comm.print();
                }
            }
            else {
                data->single->print();
            
            }

        }
        else {
            std::cout << "nazov sa nenasiel" << std::endl;
        }
    
    
    
    };


	

};

