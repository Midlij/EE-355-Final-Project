
#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <string.h>
#include <dirent.h> // directory+entry

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName){
    // TODO: complete this method!
    // Implement it in one single line!
    // You may need to implement the load method before this!
    setnetwork(fileName);
}

Network::~Network(){ 
    cout << "***Deleteing Network object" << endl;
    while( count != 0 ){
        pop_front();
    }
}

/*
void Network::setnetwork(string filename) {

    head = NULL;
    tail = NULL;
    count = 0;
    int cnt = 0;
    string f_name, l_name, b_date, f_ph, f_email, line;
    std::ifstream inFile;
    inFile.open(filename);
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            if ((line.substr(0, 1) != " ") && (line.substr(0, 1) != "-")) {
                cnt += 1;
                //cout << "Reading Entry N "<< cnt << endl;
                // Line #1: first name (can have spaces!) + "," + " " + last name (can have spaces!)
                f_name = line.substr(0, line.find(',')).c_str();
                l_name = line.substr(line.find(',') + 2).c_str();

                // Line #2: birthdate: M/D/YYYY
                getline(inFile, line);
                b_date = line;

                // Line #3: full email type + email like: (Gmail) something@email.com
                getline(inFile, line);
                f_email = line;

                // Line #4: full phone number type + phone: (Home) 224432587
                getline(inFile, line);
                f_ph = line;

                Person* newNode = new Person(f_name, l_name, b_date, f_email, f_ph);
                push_back(newNode);

                if (getline(inFile, line))
            }

        }

        inFile.close();
    }
    //else cout << "File FILENAME does not exist!" << endl;
}
*/
void Network::setnetwork(string filename){
    // Loads the netwrok from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.txt as a template
    // Phone number can be with dashes or without them
    // TODO: Now you will notice you need to go back and make a new constructor to the Connection class,  
    // Connection::Connection(fname, lname, bdate, email, phone)
    // TODO: Update this method with new requirements 
    
    Person* ptr = head;
    vector < vector<string> > friends;
    vector <string> temp;
    //vector <string> userCode;
    while(head != NULL){
        ptr = head->next;
        delete head;
        head = ptr;
        count--;
    }
    head = NULL;
    tail = NULL;
    ifstream infile;
    infile.open(filename.c_str());

    string line, fname, lname, bdate, email, phone, friendCode;

    while(getline(infile, line)){
        lname = line.substr(0, line.find(','));
        fname = line.substr(line.find(',')+2);
        getline(infile, bdate);
        getline(infile, email);
        getline(infile, phone);
        friendCode = (codeName(fname, lname));
        getline(infile, line);
        while(line.compare(0,5, "-----")!= 0){
        	temp.push_back(line);
        	getline(infile, line);
        }
        friends.push_back(temp);
        temp.clear();
        Person* newEntry = new Person(fname, lname, bdate, email, phone, friendCode);
        this->push_back(newEntry);
        cout << "Read one ... with friendCode ..." << friendCode << endl;
        newEntry->print_person();
    }

    cout << endl;
    cout << "Makefriends Processing -----------------------------------" << endl;
    cout << endl;

    Person* temp1 = head;
    int i=0;
    while(temp1 != NULL){
    	if(friends[i].size() != 0){
	    	for(int j=0; j <friends[i].size(); j++){
                    cout << "Possible temp2 name_string: " << friends[i][j] << endl;
	    			Person* temp2 = search(friends[i][j]);
                    cout << "Find one pair friend ... " << endl;
                    cout << "Person temp1: " << endl;
                    temp1->print_person();
                    if (temp2 == NULL) {
                        cout << "Null temp2......" << endl;
                    }
                    else if (temp2 == temp1){
                        cout << "temp2 and temp1 are the same person. " << endl;
                    }
                    else {
                        cout << "Person temp2: " << endl;
                        temp2->print_person();
	    			    temp1->makeFriend(temp2);
                        cout << "Makefriend step2...Success " << endl;
	    			    temp2->makeFriend(temp1); 
                    }
                    cout << "End of one forLoop ... " << endl;
	    	}
	    }
        cout << "Find one more ? ... " << endl;
    	temp1=temp1->next;
        //cout << "Find one more ? ... " << endl;
    	i++;
   
    }
}

void Network::push_front(Person* newEntry)
{
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;

    head = newEntry;
    count++;
}

void Network::push_back(Person* newEntry)
{
    newEntry->next = NULL;
    newEntry->prev = tail;
    if (tail != NULL)
        tail->next = newEntry;
    else
        head = newEntry;
    
    tail = newEntry;
    count++;
}



Person* Network::search(Person* searchEntry){
    // Searches the Network for searchEntry
    // if found, returns a pointer to it, else returns NULL

    Person* ptr = head;
    int cnt = 0;
    cout << "Searching : " << endl;
    searchEntry->print_person();

    while(ptr != NULL ){
        cnt +=1;
        //ptr->print_person();
        if (*ptr == *searchEntry) {
            cout << "Find the same person at position " << cnt << " of the DLL." << endl;
            return ptr;
        }
        ptr = ptr->next;
        //if (cnt == 2) { return ptr;}
    }
    cout << "Did not find a same perons in the DLL." << endl;
    return NULL;   
}


Person* Network::search(string fname, string lname){
    // New == for Person, only based on fname and lname
    // if found, returns a pointer to it, else returns NULL
    // TODO: Complete this method
    // Note: two ways to implement this, 1st making a new Person with fname and lname and and using search(Person*), 2nd using fname and lname directly. 
    Person* ptr = head;
    while (ptr != NULL) {
        if ((ptr->f_name == fname) && (ptr->l_name == lname))
            break;
        else
            ptr = ptr->next;
    }
    return ptr;
}

Person* Network::search(string friendCode){
	Person* ptr = head;
	while(ptr!=NULL){
		if(ptr->friendCode == friendCode)
			break;
		else
			ptr=ptr->next;
	}
	return ptr;
}

// Modified for Phase 1
void Network::printDB(){
    // Leave me alone! I know how to print! 
    // Note: Notice that we don't need to update this even after adding to Personattributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of connections: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while(ptr != NULL){
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}

/*
bool Network::remove(string fname, string lname){
    // We modified the definition of == for Person in Person definition itself, 
    // So we should not be worried about changes we made in Person to modify this method!
    Person* removee = head;

    removee = this->search(fname, lname);

    //cout << "Searching first name and last : " <<  fname << "+" << lname << endl;
    //cout << endl;

    if (removee != NULL) {
        if (this->count == 1) {
            head = NULL;
            tail = NULL;
            cout << "Removed the only one node from the DLL." << endl;
        }
        else if (removee == head) {
            head = removee->next;
            removee->next->prev = NULL;
            cout << "Removed the 1st node from the DLL." << endl;
        }
        else if (removee == tail) {
            tail = removee->prev;
            removee->prev->next = NULL;
            cout << "Removed the last node from the DLL." << endl;
        }
        else {
            removee->next->prev = removee->prev;
            removee->prev->next = removee->next;
            cout << "Removed one middle node from the DLL." << endl;
        }

        delete removee;
        this->count--;
        cout << "The DLL has " << this->count << " connections left" << endl;
        return true;

    }
    cout << "Did not remove any node from the DLL." << endl;
    return false;
}
*/

bool Network::remove(string fname, string lname){
    // We modified the definition of == for Connection in Connection definition itself, 
    // So we should not be worried about changes we made in Connection to modify this method!
    // Copy from lab5
    Person* temp = head;
    Person* ptr = search(fname, lname);
    string res;
    if(!ptr){
        delete ptr;
        return false;
    }
    else{
    	res = codeName(fname, lname);
        if(ptr->prev == NULL && ptr->next != NULL){
            Person* ptr2 = ptr->next;
            ptr2->prev = NULL;
            head = ptr2;
            count--;
        }
        else if(ptr->next == NULL && ptr->prev !=NULL){
            Person* ptr1 = ptr->prev;
            ptr1->next = NULL;
            tail = ptr1;
            count--;
        }
        else if(ptr->prev == NULL && ptr->next == NULL){
            Person* ptr1 = ptr->prev;
            Person* ptr2 = ptr->next;   
            ptr1->next = NULL;
            ptr2->prev = NULL;
            count--;
        }
        else{
            Person* ptr1 = ptr->prev;
            Person* ptr2 = ptr->next;
            ptr2->prev = ptr1;
            ptr1->next = ptr2;
            count--;
        }
        // delete ptr;
        Person* temp2 = head;
        while(temp2!=NULL){
        	for(int i = 0; i < temp2->myfriends.size(); i++)
	        	if(temp2->myfriends[i] == ptr){
	        		temp2->myfriends.erase(temp2->myfriends.begin() + i); 
	        		break;
	        	}
        	temp2 = temp2->next;
        }
        delete ptr;
        delete temp2;
        return true;
    }
}

// Phase 1 added:
void Network::pop_front()
{
    if( this->count != 0){
        cout << "pop front node begin:......" << endl;
        Person* temp = head;
        if ( tail == head) {
            tail = NULL;
            head = NULL;
        }
        else {
            head = temp->next;
            head->prev = NULL;
        }
        
        this->count--;
        delete temp;
        cout << "pop front end." << endl;
  }
}

void Network::pop_back(){
    //placeholder 
}
Person* Network::front(){
    // Placeholder
}
// End of Phase 1 added. 


//void Network::sendEmail(string addr, string subject, string content, string attachment=""){
    // Sending a command looks like:
    // echo "content" | mailx -s "subject" -a "attachment" addr;
    // TODO: Search how you can run a unix command in C++
    // TODO: You need to add double quotation character (") to both sides of strings for this command. Adding other characters (like ? in code below) should be easy, but double quotation says: I'm a character but not a typical character! 
    // string new_str = '?' + old_str + '?'
    // TODO: Complete this method
//}


void Network::showMenu(){
    // TODO: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!

    int opt= 2;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library
        cout << "Last Menu Option is: " << opt << endl;

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new connection \n";
        cout << "4. Remove a connection \n";
        cout << "5. Search \n";
        cout << "6. Print \n";
        cout << "9. Connect \n";
        cout << "0. Quit \n";
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            // TODO: Complete me!
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            cin >> fileName;
            this->saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt==2){
            // TODO: Complete me!
            cout << "Loading network database \n";
            // TODO: print all the files in this same directory that have ".db" format
            // Take a look into sample_files.cpp 
            DIR *dir;
            struct dirent *ent;
            char targetFolderAddr[] = "./";
            string extension = "db";
            if ((dir = opendir ("./")) != NULL) { 
                while ((ent = readdir (dir)) != NULL) {
                    string fname = ent->d_name;
                    string extensionchk = fname.substr(fname.find('.')+1);
                    if (extensionchk == extension)
                    cout << fname << endl;
                }
                closedir (dir);
            } else {
            /* could not open directory */
                perror ("No directory!");
                //break;
            }

            cout << "Enter the name of the load file in the listed (with .db): "; 
            cin >> fileName;
            std::ifstream inFile;
            inFile.open(fileName.c_str(), ios::in);
            if (inFile.fail()) {
                // If file with name FILENAME does not exist: 
                cout << "File FILENAME does not exist!" << endl;
            }
            else {
                // If file is loaded successfully, also print the count of connections in it: 
                cout << "File Exist and is loading..." << endl;
                setnetwork(fileName);
                printDB();
                cout << "File is loaded successfully" << endl;
                cout << "Network loaded from " << fileName << " with " << count << " connections \n";
            }
        }
        else if (opt == 3){
            // TODO: Complete me!
            // TODO: use push_front, and not push_back 
            // Add a new Connection ONLY if it does not exists!
            cout << "Adding a new connection \n";
                cout << "Enter a new connection: " << endl;
            Person* newperson = new Person();

            if (search(newperson) == NULL) {
                cout << "Adding a new connection (push front)\n";
                push_front(newperson);
            }
            else {
                cout << "Connection already exist! " << endl;
            }
        }
        else if (opt == 4){
            // TODO: Complete me!
            cout << "Searching and Removing a connection \n";
            cout << "First name: ";
            getline(cin, fname);
            cout << "Last name: ";
            getline(cin, lname);
            // if found, cout << "Remove Successful! \n"
            if (remove(fname, lname)) {
                cout << "Remove successfully!" << endl;
            }
            // if not found: cout << "Person not found! \n";
            else {
                cout << "Person not found!" << endl;
            }
        }
        else if (opt == 5) {
            // TODO: Complete me!
            cout << "Searching: \n";
            cout << "First Name: ";
            getline(cin, fname);
            cout << "Last Name: ";
            getline(cin, lname);
            cout << "Birthdate: ";
            getline(cin, bdate);
            // if found: print connection
            // if not, cout << "Not found! \n";
            Person* newperson = new Person(fname, lname, bdate);

            if (search(newperson) == NULL) {                   // Also, we can use search(fname, lname) if we dont care about birth date
                cout << "Not found!" << endl;
            }
            else {
            cout << "Connection exist!" << endl;
            }
        }
        else if (opt== 6) {
            cout << "Printing ......" << endl;
            this->printDB();
        }
/*        else if (opt==6){
            this->printDB();
        }
*/
        else if (opt==9){
        	cout << "Make friends... \n";
        	cout << "First Name: ";
        	getline(cin, fname);
        	cout << "Last Name: ";
        	getline(cin, lname);
        	Person* c1 = search(fname, lname);
            if(c1 != NULL){
	        	cout << "First Name of 2nd connection: ";
	        	getline(cin, fname);
	        	cout << "Last Name of 2nd connection: ";
	        	getline(cin, lname);
	        	Person* c2 = search(fname, lname);
	        	if(c2 != NULL){
	        		if(c1->makeFriend(c2) == 1) {
	        			c2->makeFriend(c1);
	        			cout << "These two persons are now friends!\n";
                        c1->print_person();
                        cout << endl;
                        c2->print_person();
	        		}
	        		else
	        			cout << "Already friends!\n";
	        	}
	        	else
	        		cout << "Not found\n";

            }
            else
                cout << "Not found!\n";
        }
        else if (opt == 0) {
            break;
        }
        else {
            cout << "Nothing matched!\n";

            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "\n\nPress Enter key to go back to main menu ... ";
            string temp;
            std::getline(std::cin, temp);
            cout << "\033[2J\033[1;1H";
        }
    }
}

void Network::saveDB(string filename)
{
    ofstream output(filename.c_str());
    Person* ptr = head;
    if (!output.is_open()) {
        cout << " the file open fail" << endl;
    }
    else{
        while (ptr != NULL) {
            output << ptr->l_name << ", " << ptr->f_name << endl;
            output << ptr->birthdate->get_date() << endl;
            output << ptr->email->get_contact("full") << endl;
            output << ptr->phone->get_contact("full") << endl;
            output << "------------------------------" << endl;
            ptr = ptr->next;
        }
    }
    delete ptr;
}

