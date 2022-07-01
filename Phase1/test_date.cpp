
#include <iostream>
#include "date.h"
using namespace std;
// g++ -std=c++11 test_date.cpp Date.cpp -o test

int main(){

    Date d1(12, 2, 1990);                   // input date format D, M, YYYY
    d1.print_date("Month D, YYYY");
    d1.print_date("M/D/YYYY");
    d1.print_date("D-Month-YYYY");
    cout << "------------------\n";

    Date d2(13, 13, 1968);                   // input date format  D, M, YYYY 
    d2.print_date("Month D, YYYY");
    cout << "------------------\n";

    Date d3("2/11/1990");                   // input date M, D, YYYY
    d3.print_date("Month D, YYYY");
    cout << "------------------\n";

    cout << "Is d3 equal to d1? " << (d3==d1) << endl;
    cout << "Is d3 not equal to d1? " << (d3!=d1) << endl;

    // Test Phase1.
    Date d4;
    d4.set_date(12,12,2121);
    d4.print_date("Month D, YYYY");
    cout << "Is d4 a leap year? " << d4.check_leap_date() << endl;
    cout << "Is d4 a Pal format (MDY)? " << d4.check_pal_date() << endl;
    Date d5;
    d5.set_date(12,12,2000);
    d5.print_date("Month D, YYYY");
    cout << "Is d5 a leap year? " << d5.check_leap_date() << endl;
    cout << "Is d5 a Pal format (MDY)? " << d5.check_pal_date() << endl;
    // End test Phase1.

    return 0;
}

