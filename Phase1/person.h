#ifndef PERSON_H
#define PERSON_H

#include "date.h"
#include "contact.h"
#include "fstream"
#include <vector>

class Person{
    // Its always OK to discuss your private issues with good friends, at least in C++! 
    friend class Network;
private:
	string f_name;
	string l_name;
    string friendCode;
	Date *birthdate;
    Phone *phone;
    Email *email;
    // the following two attributes are used in the linked list.
    Person* next;
    Person* prev;
    vector< Person* > myfriends;


public: 
    Person();
    ~Person();
    Person(string filename);
    Person(string f_name, string l_name, string bdate);
    Person(string f_name, string l_name, string bdate, string email, string phone);
    Person(string f_name, string l_name, string bdate, string email, string phone, string friendCode);
	void set_person();  
	void set_person(string filename);
    bool operator==(const Person& rhs);
    bool operator!=(const Person& rhs);
    string get_fname();
    string get_lname();
    Date get_bd();
    int makeFriend(Person* newFriend);

    void print_person();
};

#endif
