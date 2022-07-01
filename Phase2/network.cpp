
#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <string.h>
#include <dirent.h> // directory

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

void Network::setnetwork(string filename){
   
    // Loads the netwrok from file <filename>
    vector < vector<string> > friends;   //  info +ID )2D
    vector <string> temp;               //temp 1D
    
    cout << "Deleting everything before loading new data" << endl;
    while(count != 0){
        pop_front();
    }
    head = NULL;
    tail = NULL;
   
    ifstream inFile;
    inFile.open(filename.c_str());

    string line, fname, lname, bdate, email, phone, friendCode;

    while(getline(inFile, line)){
        lname = line.substr(0, line.find(','));
        line = line.substr(line.find(',')+2);
        fname = line.substr(0, line.find('\n'));   // deleting the last space
        getline(inFile, bdate);
        getline(inFile, email);
        getline(inFile, phone);
        friendCode = (codeName(fname, lname));
        getline(inFile, line);
        while(line.compare(0,5, "-----")!= 0){
        	temp.push_back(line);
        	getline(inFile, line);
        }
        friends.push_back(temp);
        temp.clear();
        Person* newEntry = new Person(fname, lname, bdate, email, phone, friendCode);
        this->push_back(newEntry);

        cout << endl;
    }
    inFile.close();
    cout << endl;

    Person* temp1 = head;
    int i=0;
    while(temp1 != NULL){
    	if(friends[i].size() != 0){
            //cout << "For the #" << i+1 << "th person, " << temp1->l_name << "  " << temp1->l_name << ", has following friends: ------" << endl;
	    	for(int j=0; j <friends[i].size(); j++){ // the i th person has friends[i].size() friends. 
                    //cout << "Possible temp2 name_string: " << friends[i][j] << endl;
	    			Person* temp2 = search(friends[i][j]);
                    //cout << "Find one friend ... " << endl;
                    if (temp2 == NULL) {
                        //cout << "Null temp2......" << endl;
                    }
                    else if (temp2 == temp1){
                        //cout << "temp2 and temp1 are the same person. " << endl;
                    }
                    else {
                        //cout << "Person temp2: " << endl;
                        //temp2->print_person();
	    			    temp1->makeFriend(temp2);
                        //cout << "Makefriend step2...Success " << endl;
	    			    temp2->makeFriend(temp1); 
                        cout << endl;
                    }
                    //cout << "End of one forLoop ... " << endl << endl;
	    	}
	    }
    	temp1=temp1->next;
    	i++;
   
    }
}

void Network::saveDB(string filename)
{
    ofstream outPut(filename.c_str());
    Person* ptr = head;
    if (!outPut.is_open()) {
        cout << " the file open fail" << endl;
    }
    else{
        while (ptr != NULL) {
            outPut << ptr->l_name << ", " << ptr->f_name << endl;
            outPut << ptr->birthdate->get_date() << endl;
            outPut << ptr->email->get_contact("full") << endl;
            outPut << ptr->phone->get_contact("full") << endl;
            for (int i = 0; i < ptr->myFriends.size(); i++) {
                //cout << "Write...: " << codeName(ptr->myfriends[i]->f_name, ptr->myfriends[i]->l_name) << endl;
                outPut << codeName(ptr->myFriends[i]->f_name, ptr->myFriends[i]->l_name) << endl; 
            };                
            outPut << "------------------------------" << endl;
            ptr = ptr->next;
        }
        outPut.close();  //close the file
    }
    delete ptr;
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

bool Network::remove(string fname, string lname){
// Remove node that has fname and lname.

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
        	for(int i = 0; i < temp2->myFriends.size(); i++)
	        	if(temp2->myFriends[i] == ptr){
	        		temp2->myFriends.erase(temp2->myFriends.begin() + i); 
	        		break;
	        	}
        	temp2 = temp2->next;
        }
        delete ptr;
        delete temp2;
        return true;
    }
}

void Network::pop_front()
{
    if( this->count != 0){
        //cout << "pop front node begin:......" << endl;
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
        //cout << "pop front end." << endl;
  }
}


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
            getline(std::cin, fname);
            cout << "Last Name: ";
            getline(std::cin, lname);
            cout << "Birthdate: ";
            getline(std::cin, bdate);
            // if found: print connection
            // if not, cout << "Not found! \n";
            Person* newperson = new Person(fname, lname, bdate);
            // search by using search(Person*) (we first name, last name and birthdate for this search)
            if (search(newperson) == NULL) {  // Also, we can use search(fname, lname) if we don't care about birth date
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
        else if (opt==9){
        	cout << "Make friends... \n";
        	cout << "First Name: ";
        	std::getline(std::cin, fname);
        	cout << "Last Name: ";
        	std::getline(std::cin, lname);
        	Person* c1 = search(fname, lname); // search by using first name and last name
            if(c1 != NULL){
	        	cout << "First Name of 2nd connection: ";
	        	getline(cin, fname);
	        	cout << "Last Name of 2nd connection: ";
	        	getline(cin, lname);
	        	Person* c2 = search(fname, lname);
                if ((c2 != NULL) && (c2 != c1)) {    // check if 2nd person existe but not same as the 1st one 
                    if (c1->makeFriend(c2) == 1) {
                        c2->makeFriend(c1);
                        cout << "These two persons are now friends!\n\n";
                        c1->print_person();
                        cout << "-----------------------------------" << endl;
                        c2->print_person();
                        cout << "-----------------------------------" << endl;
                    }
                    else
                        cout << "Already friends!\n";
                }
                else if (c2 == NULL)
                    cout << "2nd Connection not found\n";
                else cout << "Person can not make friend with it self\n";

            }
            else
                cout << "Connection not found!\n";
        }
        else if (opt == 0) {
            break;
        }
        else {
        cout << "Nothing matched!\n";

        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to the main menu ... ";
        string temp;
        std::getline(std::cin, temp);
        cout << "\033[2J\033[1;1H";
        }
    }
}

