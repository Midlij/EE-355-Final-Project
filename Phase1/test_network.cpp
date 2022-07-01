
#include "network.h"
#include "Person.h"
#include "Contact.h"

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
using namespace std;

// g++ -std=c++11 test_network.cpp network.cpp misc.cpp Person.cpp date.cpp contact.cpp -o test_network

int main(){

    Network myNet("networkDB.db");
    
    myNet.printDB();

    Person p1("Burbank", "Truman", "1/17/1962");
    p1.print_person();

    
    cout << endl;

    myNet.remove("Burbank", "Truman");
    myNet.printDB();

    myNet.showMenu(); 

    return 0;
} 
