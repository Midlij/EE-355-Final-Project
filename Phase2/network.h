
#ifndef NETWORK_H
#define NETWORK_H

#include "person.h"
#include "date.h"
// You may need to add more libraries 
#include <stdlib.h>
class Network{

    private:
        Person* head;
        Person* tail;
        int count; 
        Person* search(Person* searchEntry);
        Person* search(string fname, string lname);
        Person* search(string friendCode);
        
    public:
        Network();
        Network(string fileName);
        ~Network();
        void pop_front();
        void push_front(Person* newEntry);
        void push_back(Person* newEntry);
        bool remove(string fname, string lname);
        void printDB();
        void setnetwork(string fileName);
        void saveDB(string filename);
        void showMenu();
        
};

#endif
