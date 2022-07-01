#include <iostream>
#include "Person.h"
#include "Contact.h"

#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
using namespace std;

// g++ -std=c++11 test_person.cpp Person.cpp Date.cpp contact.cpp -o test_person

int main(){

    cout << "Creat a person through entering:----------\n";
    Person c1;

    cout << "Print out information of C1:" << endl;
    c1.print_person();
    cout << "C1----------------\n";

    //c1.print_person();
    cout << "----------------\n";

    Person c2("person_template.txt");
    c2.print_person();
    cout << "----------------\n";

    cout << "Is c1 equal to c2: " << (c1 == c2) << endl;
    cout << "Is c1 not equal to c2: " << (c1 != c2) << endl;

    cout << endl << endl;

    cout << "Creat a person through parameters:----------\n";
    Person c3("Max", "Chen", "1/1/1970", "(USC) xchen355@usc.edu", "(Office) 9162427579");
    cout << "Print out information of C2:" << endl;
    c3.print_person();
    cout << "----------------\n";
    cout << endl << endl;

    return 0;
}
