
#include <iostream>
#include "contact.h"
using namespace std;
// g++ -std=c++11 test_contact.cpp contact.cpp -o test

int main()
{
/*
// contact protected:	
	string type;
private:
    string email_addr;
public:
    Email(string type, string email_addr);
    // TODO: Complete me!
	void print();
    string get_contact(string style="full");
	void set_contact();
*/
    cout << "test 1------------------\n";
    Email e1("USC", "tommytrojan@usc.edu");
    cout << e1.get_contact("full") << endl;
    e1.print();
    cout << "test line 1------------------\n" << endl;
    e1.set_contact();
    e1.print();
    cout << "test 2------------------\n";
    Email e2;
    
    e2.print(); 
    cout << "test line 2------------------\n" << endl;

    cout << "test 3------------------\n";
    Phone p1;
    p1.print();
    cout << "test line 3------------------\n" << endl;

    cout << "test 4------------------\n";
    p1.set_contact();
    p1.print();
    cout << "test line 4------------------\n" << endl;

    cout << "test 5------------------\n";
    Phone p2("Office", "916-355-5358");
    p2.print();
    cout << "test line 5------------------\n" << endl;
    Phone p3("Cell", "9163555300");
    p2.print();
    //cout << "Is d3 not equal to d1? " << (d3!=d1) << endl;

    return 0;
}
