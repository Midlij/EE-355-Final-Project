
#include "contact.h"
// TODO: Add needed libraries! 

/*
// contact protected:	
	string type;
private:
    string email_addr;
public:
    Email(string type, string email_addr);
	void print();
    string get_contact(string style="full");
	void set_contact();
*/

Email::Email()
{
    //type = "Null";
    //email_addr = "NullAdd@gmail.com";
    set_contact();
}

Email::Email(string ty, string emailAd){                           
    // TODO: Complete me!
    this->type = ty;                            //type = ty;
    this->email_addr = emailAd;                // email_addr = emailAd;
}


void Email::set_contact(){
    // TODO: Do not change the prompts!
	
    cout << "Enter the type of email address: ";
    // some code here
    getline(cin, this->type);
    cout << "Enter email address: ";
    // some code here
    getline(cin, this->email_addr);
}


string Email::get_contact(string style){
    // Note: We have default argument in declaration and not in definition!
    //return style + " (" + this->type + "): " + this->email_addr;

    
    if (style=="full")
	    return "(" + this->type + ") " + this->email_addr;
    else 
        return this->email_addr; 
    
}


void Email::print(){
    // Note: get_contact is called with default argument
	cout << "Email: " << this->get_contact("full") << endl;
}


Phone::Phone()
{
    //type = "Work";
    //phone_num = "0000000000";
    set_contact();
}
Phone::Phone(string ty, string num){
    // TODO: It is possible that num includes "-" or not, manage it!
    // TODO: Complete this method!
    // Note: We don't want to use C++11! stol is not valid!
    // The code has been covered in the discussion session

    /* Note: Understand your own TA's bug!
     * This code has a bug, can you understand why? */
    this->type = ty;

    //long int area_code = atoi(num.substr(0, 3).c_str());
    //long int  number;
    //if (num.substr(3, 1) == "-")
        //number = atoi(num.substr(4).c_str());
    //else
        //number = atoi(num.substr(3).c_str()); 
     
    //this->phone_num = to_string(area_code*10000000 + number);
    //cout << "initial string: " << to_string(area_code) + to_string(number);
    //this->phone_num = to_string(area_code) + to_string(number); 
    if (num.length() == 10) {
        this->phone_num = num.substr(0, 3) + "-" + num.substr(3, 3) + "-" + num.substr(6, 4);
    }
    else if (num.length() == 12) {
        this->phone_num = num.substr(0, 3) + "-" + num.substr(4, 3) + "-" + num.substr(8, 12);
    }
    else  this->phone_num = num;
}


void Phone::set_contact(){
    // TODO: Complete this method
    // Use the same prompts as given!
    string num, ty;
    bool checkNum = false;
	cout <<"Enter the type of phone number: ";
    std::getline(std::cin, ty);
    type = ty;
    cout << "Enter the phone number (acceptable formats (1234567890), (123 456 7890) or (123-456-7890): ";
    //cout << "Enter the phone number: ";
    std::getline(std::cin, num);
    while (!checkNum) {
      
        if ((num.length() == 10) || (num.length() == 12)) {
            checkNum = true;
        }
        else {
            cout << "Error number!. Please make sure that number is follows the format (123456790), (123 456 7890), or (123-456-7890)." << endl << "Enter the phone number: ";
            std::getline(std::cin, num);
        }
    }
    
    if (num.length() == 10) {
        this->phone_num = num.substr(0, 3) + "-" + num.substr(3, 3) + "-" + num.substr(6, 4);
    }
    else if (num.length() == 12) {
        this->phone_num = num.substr(0, 3) + "-" + num.substr(4, 3) + "-" + num.substr(8, 12);
    }

}


string Phone::get_contact(string style){
    // TODO: Complete this method, get hint from Email 
    // The code has been covered in discussion session 

    /* Note: Understand your own TA's bug!
     * This code has a bug, can you understand it!
    int x1 = (phone_num/10000000);
	int x2 = ((phone_num)/10000)%1000;
	int x3 = phone_num%10000;

    */ 
    if (style=="full")

	   //return "(" + type + "): " + phone_num.substr(0, 3) + "-" + phone_num.substr(3, 3) + "-" + phone_num.substr(6);
    //else 
        //return phone_num.substr(0, 3) + "-" + phone_num.substr(3, 3) + "-" + phone_num.substr(6);

        return "(" + this->type + ") " + this->phone_num;
    else 
        return this->phone_num;
//    return style + " (" + this->type + "): " + this->phone_num;
}


void Phone::print(){
    // Note: get_contact is called with default argument
	cout <<"Phone: " << get_contact("full") << endl;
}

