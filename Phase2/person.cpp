#include "person.h"
#include "misc.h"
#include <string.h>

Person::Person(){
    set_person();
}

Person::Person(string f_name, string l_name, string bdate, string email, string phone)
{
    string type;

    this->f_name = f_name;
    this->l_name = l_name;
    this->birthdate = new Date(bdate);

    type = email.substr(1, email.find(')') - 1);
    email = email.substr(email.find(')') + 2);
    this->email = new Email(type, email);

    type = phone.substr(1, phone.find(')') - 1);
    phone = phone.substr(phone.find(')') + 2);

    this->phone = new Phone(type, phone);

}

Person::Person(string f_name, string l_name, string bdate, string email, string phone, string friendCode)
{
    string type;

    this->f_name = f_name;
    this->l_name = l_name;
    this->birthdate = new Date(bdate);

    type = email.substr(1, email.find(')') - 1);
    email = email.substr(email.find(')') + 2);
    this->email = new Email(type, email);

    type = phone.substr(1, phone.find(')') - 1);
    phone = phone.substr(phone.find(')') + 2);

    this->phone = new Phone(type, phone);

    this-> friendCode = friendCode;

}

Person::Person(string filename){
    // TODO: Complete this method!
    set_person(filename);
}

Person::Person(string f_name, string l_name, string bdate)
{
    this->f_name = f_name;
    this->l_name = l_name;
    this->birthdate = new Date(bdate);
    this->email = new Email("empty", "no email");
    this->phone = new Phone("empty", "0000000000");
    this->next = NULL;
    this->prev = NULL;
}

Person::~Person(){
    delete birthdate;
    delete email;
    delete phone;    
}

void Person::set_person(){
    // prompts for the information of the user
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    string temp;
    string type;
    
	cout << "First Name: ";
    // TODO: pay attention to how we read first name, as it can have spaces!   
    std::getline(std::cin, f_name);

	cout << "Last Name: ";
    std::getline(std::cin, l_name);

    cout << "Birthdate (M/D/YYYY): ";
    std::getline(std::cin,temp);
    // TODO: pay attention to how we passed argument to the constructor of a 
    //       new object created dynamically using new command
    birthdate = new Date(temp); 
    email = new Email();
    phone = new Phone();

}


void Person::set_person(string filename) {
    // TODO: Complete this method!

    // Open the file <filename>
    // Look at person_template.txt 
    // Line #1: first name (can have spaces!)
    // Line #2: last name (can have spaces!)
    // Line #3: date of birth in string format 

    ifstream inputFile; // Declare fstream object.
    string temp, type;
    string style = "full";

    //Open files for reading.
    //inputFile.open(filename.c_str(),ios::in);
    inputFile.open(filename);
    getline(inputFile, temp);
    l_name = temp;
    getline(inputFile, temp);
    f_name = temp;// 

    getline(inputFile, temp);
    birthdate = new Date(temp);

    getline(inputFile, temp);
    type = temp.substr(1, temp.find(')') - 1);
    temp = temp.substr(temp.find(')') + 2);
    phone = new Phone(type, temp);

    getline(inputFile, temp);
    type = temp.substr(1, temp.find(')') - 1);
    temp = temp.substr(temp.find(')') + 2);
    email = new Email(type, temp);

    // close file.
    inputFile.close();
}
   
bool Person::operator==(const Person& rhs){
    // TODO: Complete this method!
    // Hint: Look at how we overloaded equality in Date
    // Two connection are equal only if they have the same first name, last name and date of birth!
    if ( (this->f_name == rhs.f_name) && (l_name == rhs.l_name) && (*birthdate == *rhs.birthdate))
          return true;
    else
        return false;
}

bool Person::operator!=(const Person& rhs){ 
    // TODO: Complete this method!
    // Hint: again, look at how we did this for Date
    return !(*this == rhs);
}

void Person::print_person(){
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
    //cout << "Phone " << phone->get_contact("full") << endl;
    //cout << "Email " << email->get_contact("full") << endl;
    phone->print();
    email->print();
    for(int i = 0; i < myFriends.size(); i++){
        cout << codeName(myFriends[i]->f_name, myFriends[i]->l_name) << endl;
    }
}

void Person::write_person(ofstream& os) {
    os << l_name << ", " << f_name << endl;
    os << birthdate->get_date() << endl;
    os << email->get_contact("full") << endl;
    os << phone->get_contact("full") << endl;
    for (int i = 0; i < myFriends.size(); i++) {
        os << codeName(myFriends[i]->f_name, myFriends[i]->l_name) << endl;
    }
    os << "------------------------------" << endl;
}

string Person::get_fname()
{
    return f_name;
}

string Person::get_lname()
{
    return l_name;
}

Date Person::get_bd()
{
    return *birthdate;
}

int Person::makeFriend(Person* newFriend){
    int flag = 0;
    if(myFriends.size() != 0){                      //The vector of myfriends is not empty.
        for(int i = 0; i < myFriends.size(); i++){
            if(myFriends[i] == newFriend){
                flag = 1;
                break;
            }
            else
                flag = 0;    
        }
        if(flag==0){
            myFriends.push_back(newFriend);
            return 1;
        }
        else
            return 0;
     }
     else {
         myFriends.push_back(newFriend);
        return 1;
     }

}
