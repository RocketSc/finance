#include <iostream>
#include <stdio.h>
#include <string.h>

#include "BanksController.h"

using namespace std;

void BanksController::printMenu()
{
    this->printList();
    
    for(int i = 0; i < this->menusize; i++) {
        std::cout << this->menu[i] << std::endl;
    }
}

void BanksController::printList()
{
    cout << "You have contracts in following banks:" << endl;
    ModelNode* current = this->list->getHead();
    
    while(current != 0) {
        cout << current->getNode().ptr()->getName() << endl;
             
        current = current->next;
    }
    
    cout << endl;
}



const char* BanksController::getName()
{
    return this->name;
}


Controller * BanksController::run(int option, ControllerStorage* cstorage)
{
   switch (option) {
            case 1:
                this->createBank();
                return this;
                break;
            case 2:
                this->deleteBank(cstorage);
                return this;
                break;
            case 3:
                return cstorage->getController("start");
                break;
            default:
                std::cout << "Incorrect" << std::endl;
                return this;
                break;
        }
}

BanksController::BanksController(ModelList* list) {
    this->list = list;
    this->name = "banks";
    this->loadMenu();
}

void BanksController::createBank()
{
    cout << "Creating bank.." << endl
         << "Enter bank name:" << endl;
         
    char input[21];

    fscanf(stdin, "%20s", input);

    
    ModelPointer temp = new Bank(input);
    
    this->list->add(temp);

    
}

void BanksController::deleteBank(ControllerStorage* cstorage)
{
    cout << "Deleting bank.." << endl
         << "Enter bank name:" << endl;
         
    char input[21];

    fscanf(stdin, "%20s", input);
    
    AccountsController* accountsC = (AccountsController*) cstorage->getController("accounts");
    
    if (accountsC->bankSearch(input)) {
        cout << "Delete Accounts in this bank first" << endl;
        return;
    }
    
    this->list->del(input);
}

void BanksController::loadMenu()
{
   this->menu[0] = "1. Add new Bank";
   this->menu[1] = "2. Delete Bank";
   this->menu[2] = "3. Back to main menu";
   this->menu[3] = "0. Exit";
   
   this->menusize = 4;
}

bool BanksController::searchBank(const char* bankName, ModelPointer& bank)
{
    ModelNode* current = this->list->getHead();
    
    bool found = false;
    
    while(1) {
        if( !strcmp(current->getNode().ptr()->getName(), bankName) ) {
            cout << "Bank has been found" << endl;
            bank = current->getNode();
            found = true;
            break;
        }
        
        if (current->next == 0) {
            cout << "Bank not found" << endl;
            break;
        }
        current = current->next;
    }
    
    return found;
}