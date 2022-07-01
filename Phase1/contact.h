
#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>
// TODO: You may need to add other libraries here!

using namespace std;


class Contact {
    // TODO: private or protected? Look at your children!
protected:	
	string type;
public:
	virtual void print() = 0;   //This is a Pure virtual function.

    virtual string get_contact(string style="full") = 0;

	virtual void set_contact() = 0; //Base class having pure virtual function becomes abstract.
                                    // i.e. cannot be instantiated.
// A pure virtual function is a member function of base class whose only declaration is 
// provided in base class and should be defined in derived class otherwise derived class 
// also becomes abstract.
};


class Email: public Contact{
private:
    string email_addr;
public:
    Email();
    Email(string type, string email_addr);
    // TODO: Complete me!
	void print();
    string get_contact(string style);
	void set_contact();
};


class Phone: public Contact{
private:
    // TODO: modify dataType! Can int store 10 digit phone-number? 
	//dataType phone_num; 
    string phone_num;
public:
    Phone();
    Phone(string type, string phone_number);
    // TODO: Complete me!
    void print();
	void set_contact();
    string get_contact(string style);
};

#endif