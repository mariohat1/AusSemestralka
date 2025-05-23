#pragma once
#include <iostream>
#include <libds/amt/explicit_hierarchy.h>
#include "commune.h"
#include "fileReader.h"
class hierarchyIterator
{
private:
	using CommuneBlock = ds::amt::MultiWayExplicitHierarchyBlock<commune*>;
	using iterator = ds::amt::MultiWayExplicitHierarchy<commune*>::PreOrderHierarchyIterator;
	CommuneBlock* currentPosition;
	ds::amt::MultiWayExplicitHierarchy<commune*>* hierarchy;
	
	int count = 0;


public:
	hierarchyIterator(ds::amt::MultiWayExplicitHierarchy<commune*>* hierarchy)
		: hierarchy(hierarchy), currentPosition(hierarchy->accessRoot()) {

	}
	


	CommuneBlock* run() {
		std::cout << this->hierarchy->size()  << std::endl;
		while(true) {
			std::string userInput;

			displayMenu();
			std::cin >> userInput;

			if (userInput == "s") {
				selectSon();
			}
			else if (userInput == "p") {
				return this->currentPosition;
			}
			else if (userInput == "u") {
				moveUp();
			}
			else if (userInput == "q") {
				return nullptr;

			}
		}
		
	}
	
	void selectSon() {

		if (!currentPosition->sons_->isEmpty())
		{

			int sonOrder;
			std::string sonOrderInput;
			std::cin >> sonOrderInput;
			sonOrder = stoi(sonOrderInput);

			if (sonOrder <= this->count)
			{
				currentPosition = hierarchy->accessSon(*currentPosition, sonOrder);
			}
			system("CLS");

		}
	}
	void moveUp() {
		system("CLS");
		if (currentPosition->parent_ != nullptr)
		{
			currentPosition = hierarchy->accessParent(*currentPosition);
		}
		else {
			std::cout << "Parent does not exist" << std::endl;
		}
		std::cout << std::endl;

	}



	void displayMenu() {
		std::cout << "s ---- select son at index -- next argument [index]" << std::endl;
		std::cout << "p ---- select predicate -- next argument [index] of predicate" << std::endl;
		std::cout << "u ---- back to parent --no next arguments" << std::endl;
		std::cout << "q ---- quit" << std::endl;
		std::cout << "current Parent: " << currentPosition->data_->getName() << std::endl;

		this->count= 0;
		if (!currentPosition->sons_->isEmpty())
		{
			for (auto it = currentPosition->sons_->begin(); it != currentPosition->sons_->end(); ++it)
			{
				CommuneBlock* comm = *it;
				std::cout << this->count << " " << comm->data_->getName() << std::endl;
				this->count++;
			}


		}
	}
	
};

