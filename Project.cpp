#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct node {
    string party_request;
    string candidatename;
    string candidparty;
    string candidconst;
    string symbol_name;

    string voter_pass;
    long long voter_cnic;
    int votes;
    string consti;
    node* next;

    // Constructor and Destructor
    node() : next(nullptr) {}
    ~node() {
        if (next != nullptr) {
            delete next;
        }
    }
};

node* f = nullptr, *r = nullptr, *tp = nullptr, *prev = nullptr, *head = nullptr, *head2 = nullptr;
int exitOption = 0;  // Added variable to store exit option

void menu(node* head, node* head2);

void Election_login(node* head, node* head2)
{
	string a, b, user = "admin", pass = "admin";
	
	for(;;)
	{
	cout<<"\t\t\t\t\tWELCOME TO THE ELECTION MANGEMENT SYSTEM \n\n";
	cout<<"Enter User: ";
	cin>>a;
	cout<<"\nEnter Pass:  ";
	cin>>b;
	
    if(a != user && b!= pass)
    cout<<"\nWrong user or password, try again\n";
	
	else 
	break;
	
	int option;
	cout<<"Press any button to retry: ";
	cin>>option;
	system("CLS");
		
	}
	
	if(a == user && b == pass)
	{
	cout<<"Loggin in : ";
	menu(head, head2);
    }
	
	
}

void show_results()
{
	int option, count = 0, counter = 0;
	string consti, get_file, get_file1;
	
	cout<<"\n(1) See results for a particular constituency\n";
	cout<<"\n(2) See total election results \n";
	cin>>option;
	
	if(option == 1)
	{
	cout<<"\nEnter the constituency you want results of : ";
	cin>>consti;
	
	ifstream constituencies("constituencies.txt");
	while(getline(constituencies, get_file))
	{
	if(consti == get_file)
	break;
	else
	count = count + 1;
    }
    constituencies.close();
    
    ifstream voting_winner("voting_winner.txt");
    while(getline(voting_winner, get_file))
    {
    	if(counter == count)
    	{
		cout << consti << ":  " << get_file << endl;
		break;
	    }
	}
	voting_winner.close();
	}
	
	
	if(option == 2)
	{
	cout<<"\n\nThe Voting Process Has Commenced, Following Are The Results From The Respective Constituencies:\n";
	ifstream constituencies("constituencies.txt"); // DISPLAY OF VOTING RESULTS
	ifstream voting_winner("voting_winner.txt");
    fflush(stdin);
	while( getline (constituencies, get_file)  && getline(voting_winner, get_file1))
	{
	cout<<get_file<<":  "<< get_file1 << endl;
    }
	constituencies.close();
	voting_winner.close();
	cout<<endl<<endl;
	}
	
}


void registerConstituency()
{
	// Proccess for constituency
	string consti;
	cout << "\n\nEnter unique constituency\n";

	fflush(stdin);
	getline(cin, consti);

	string get_file;
	bool flag = false;
	ifstream constituencies("constituencies.txt");
	while (getline(constituencies, get_file))
	{
		if (get_file == consti)
		{
			flag = true;
			break;
		}
	}
	constituencies.close();

	if (flag == true)
	{
		cout << "\nConstituency already exists, try another one\n";
	}
	else
	{
		ofstream constituencies("constituencies.txt", ios::app);
		constituencies << consti << endl;
		cout << "Your Constituency has been registered\n";
		constituencies.close();
	}
}

void displayConstituency()
{
	ifstream constituencies("constituencies.txt");
	string file = "";

	constituencies.clear(); // this
	constituencies.seekg(0, ios::beg); // this

	while (getline(constituencies, file))
		cout << file << endl;
}

void updateOrDelete()
{
	fstream constituencies("constituencies.txt", ios::out | ios::in);
	fstream temp("temp.txt", ios::out | ios::in);
	string deleteline;
	string line;

	cout << "Which constituency do you want to remove? \n";
	cin >> deleteline;

	while (getline(constituencies, line))
	{
		if (line != deleteline)
		{
			ofstream temp("temp.txt", ios::app);
			temp << line << endl;
		}
	}

	constituencies.close();
	temp.close();

	remove("constituencies.txt");
	rename("temp.txt", "constituencies.txt");
}

void display(node* head) // CANDIDATE DISPLAY BY PARTY 
{
	for (node* ptr = head->next; ptr->next != NULL; ptr = ptr->next)
	{
		cout << ptr->candidatename << "\t" << ptr->candidparty <<endl;
	}
}

void display1(node* head) // CANDIDATE DISPLAY BY SYMBOL
{
	
	for (node* ptr = head->next; ptr->next != NULL; ptr = ptr->next)
	{
		cout << ptr->candidatename << "\t" << ptr->symbol_name <<endl;
	}
}

int cnic_count(long long c) // FUNCTION OF RECURSION TO COUNT CNIC DIGITS
{
	if (c == 0)
		return 0;
	return 1 + cnic_count(c / 10);
}

void voter_registration()
{
	long long cnic, get_file;
	string password, consti;
	bool flag = true;
	cout << "Enter CNIC number without dashes: ";
	fflush(stdin);
	cin >> cnic;
	
	ifstream voter_cnic("voter_cnic.txt");
	while(voter_cnic>>get_file)
	{
	if(cnic == get_file)
	{
	flag = false;
	break;
    }
    }
    voter_cnic.close();
    
	if (cnic_count(cnic) == 13 && flag == true)
	{
		ofstream voter_cnic("voter_cnic.txt", ios::app);
		voter_cnic << cnic << endl;
		voter_cnic.close();

		cout << "Enter a unique password: ";
		cin >> password;
		ofstream voter_passwords("voter_passwords.txt", ios::app);
		voter_passwords << password << endl;
		voter_passwords.close();
		
		cout<< "Enter the constituency you want to be registered on: \n";
		displayConstituency();
		cin>>consti;
		ofstream voter_consti("voter_consti.txt", ios::app);
		voter_consti << consti << endl;
		voter_consti.close();
		
		cout << "You have been registered as a voter." << endl;
	}

	else
		cout << "INVALID CNIC, PLEASE TRY AGAIN AND USE YOUR OWN CNIC !\n";
}


void voterlogin(node* head, node* head2)
{
	string constit;
	string pass;
	long long cnic;
	bool flag = false;
	int option;
	string votingname;

	cout << "Enter cnic: ";
	cin >> cnic;

	for (node* ptr = head; ptr->next != NULL; ptr = ptr->next)
	{
		if (cnic == ptr->voter_cnic )
		{
			flag = true;
			break;
		}
	}

	if (flag == true)
	{
		flag = false;
		cout << "CNIC exists, Enter password: ";
		cin >> pass;
		for (node* ptr1 = head->next; ptr1->next != NULL; ptr1 = ptr1->next)
		{
			if (pass == ptr1->voter_pass)
			{
				flag = true;
				break;
			}
		}
		if (flag == true)
		{
			string a;
			cout << "You are logged in." << endl;
			cout << "Please Enter What You Want To Do :\n\n(1) Cast vote \n(2) Show Candidates With Respective Symbol Affiliation\n(3) Show Candidates With Respective Symbol " << endl;

			cin >> option;
			if (option == 1)
			{
				ifstream votes_casted("votes_casted.txt");
				long long get_file2;
				while(votes_casted>>get_file2)
				{
				if(cnic == get_file2)
				{
				cout<<"\nYou have already casted a vote\n";
				flag= false;
				break;
			    }
			    }
			    votes_casted.close();
			    
			    if(flag == true)
			    {
			    	cout << "\nEnter your constituency: ";
				cin >> constit;
				for (node* ptr2 = head2->next; ptr2->next != NULL; ptr2 = ptr2->next)
				{
					if (constit == ptr2->candidconst)
					{
						cout << ptr2->candidatename << "	" << ptr2->candidparty << "	" << ptr2->candidconst << endl;

					}
				}
				
				cout << "\nWho to vote, enter stated name:  ";
				fflush(stdin);
				getline(cin, votingname);
				for (node* ptr3 = head2; ptr3->next != NULL; ptr3 = ptr3->next)
				{
					if (votingname == ptr3->candidatename)
				{
						cout << "\n\nYou cast a vote to " << ptr3->candidatename << " from " << ptr3->candidparty << endl;
						ptr3->votes = ptr3->votes + 1;
						
						ofstream votes_casted("votes_casted.txt", ios::app);
						votes_casted << cnic <<endl;
						votes_casted.close();
						
				node* prev ;
				for (prev = head; prev->next != head->next; prev = prev->next)
				{
					if (prev->next == head)
					{
						prev->next = head->next;
						head->next = NULL;
						break;
					}
				}
				
				}
				
				}
			}
			
			if(option == 2)
			display(head2);
			
			if(option == 3)
			display1(head2);

		}
		else
		{
			cout << "Wrong password, OR you have already voted\n";
		}
		}
				

	}
	else
	{
		cout << "CNIC does not exist, OR you have alreday voted\n";
	}
}

void prepass(node* head, string voter_consti1, string voter_pass1, long long voter_cnic1) //PASSING CONTENT FROM FILE TO LINKED LIST OF VOTER
{
	node* ptr;
	for (ptr = head->next; ptr->next != NULL; ptr = ptr->next) {} // taking pointer to last position 
	
	ptr->consti = voter_consti1;
	ptr->voter_pass = voter_pass1;
	ptr->voter_cnic = voter_cnic1;

	node* ptr1 = new node; // new node
	ptr->next = ptr1; // new node is last node 
	ptr1->next = NULL; // 
}

void prepass2(node* head, string n, string c, string p) //PASSING CONTENT FROM FILE TO LINKED LIST OF CANDIDATE
{
	node* ptr;
	for (ptr = head->next; ptr->next != NULL; ptr = ptr->next) {} // taking pointer to last position 
	ptr->candidatename = n; // ID in node
	ptr->candidconst = c; // symbol in node
	ptr->candidparty = p;

	node* ptr1 = new node; // new node
	ptr->next = ptr1; // new node is last node 
	ptr1->next = NULL; // 
}

void register_party()
{
	static int party_count;
	string party_name;
	string party_symbol;
	string party_username;
	string party_password;
	string get_file;
	bool flag = false;

	// Proccess for party name

	cout << "\n\nEnter Unique Party Name\n";
	fflush(stdin);
	getline(cin, party_name);

	ifstream party_names("party_names.txt");
	while (getline(party_names, get_file)) // loop to check wether party name already exists or not in the party_names file
	{
		if (get_file == party_name)
		{
			flag = true;
			break;
		}
	}
	party_names.close();

	if (flag == true)
	{
		cout << "\nParty name already exists, try another one\n";
	}

	if (flag == false)
	{
		ofstream party_names("party_names.txt", ios::app);
		party_names << party_name << endl;
		cout << "Your Party Name Has Been Registered, ";
		party_names.close();

		ifstream party_symbols("party_symbols.txt");   //symbols file opened

		int counter = 0;
		while (counter <= party_count)  //skipping line to alotting corresponding symbol with count variable
		{
			getline(party_symbols, party_symbol);
			if (counter == party_count)
			{
				cout << "Your Party Symbol Is : " << party_symbol;
			}
			counter = counter + 1;
		}
		party_count = party_count + 1;
		party_symbols.close();



		// Proccess for username

		cout << "\n\nNow Enter a Unique Party Username\n";
		fflush(stdin);
		getline(cin, party_username);
		ofstream party_usernames("party_usernames.txt", ios::app);
		party_usernames << party_username << endl;
		party_usernames.close();


		// Proccess for password

		cout << "Enter unique party password\n";
		fflush(stdin);
		getline(cin, party_password);
		ofstream party_passwords("party_passwords.txt", ios::app);
		party_passwords << party_password << endl;
		party_passwords.close();

		cout << "\n Your Party Has Been Successfully Registered\n";
	}
}

void reg_independent_candid()
{
	static int candid_count;
	string candidatename;
	string party = "independent";
	string consti;
	string constituency;
	string symbol;
	int counter = 0;

	//Registering an independent candidate

// Proccess for independent candidate's name and enqueue his request

	cout << "\nEnter independent candidate's name : ";
	fflush(stdin);
	getline(cin, candidatename);

	//proccess for independent candidate's constituency

	cout << "\nWhich constituency would you like to register in ? :\n\n";
	ifstream constituencies("constituencies.txt");
	while (getline(constituencies, constituency))
	{
		cout << constituency << endl;
	}
	constituencies.close();
	cout << "\n";
	fflush(stdin);
	getline(cin, consti);
	cout << "\nYou have been successfully registered as a candidate\n ";

	ifstream indcandid_symbols("indcandidsymbols.txt");  //symbols file opened
	while (counter <= candid_count)  //skipping line to alotting corresponding symbol with count variable
	{
		fflush(stdin);
		getline(indcandid_symbols, symbol);
		if (counter == candid_count)
		{
		ofstream candid_symbols("candid_symbols.txt", ios::app);
		candid_symbols << symbol << endl;
		cout << "\n\nYour party symbol has been alloted, you can see it in the candidate display list from the main menu \n" << symbol;
		candid_symbols.close();
		}
		counter = counter + 1;
	}
	candid_count = candid_count + 1;
	indcandid_symbols.close();

	ofstream candid_names("candid_names.txt", ios::app);
	ofstream candid_party("candid_party.txt", ios::app);
	ofstream candid_consti("candid_constituency", ios::app);

	candid_names << candidatename << endl;
	candid_party << party << endl;
	candid_consti << consti << endl;
	candid_names.close();
	candid_party.close();
	candid_consti.close();

}


void reg_party_candid()
{
	string constituency;

	//Registering a party candidate


	// Proccess for party candidate's name and enqueue his request

	r = new node;
	cout << "\nEnter party candidate's name : ";
	fflush(stdin);
	getline(cin, r->candidatename);

	// proccess for party candidate's party

	cout << "Which party would you like to be registered on ? : \n";
	string line;
	ifstream party_names("party_names.txt");
	while (getline(party_names, line))
		cout << line << endl;
	party_names.close();
	cout << "\n";
	fflush(stdin);
	getline(cin, r->party_request);

	//proccess for party candidate's constituency

	cout << "\nWhich constituency would you like to register in ? :\n";
	ifstream constituencies("constituencies.txt");
	while (getline(constituencies, constituency))
	{
		cout << constituency << endl;
	}
	constituencies.close();
	
	cout << "\nYour party symbol will be alloted once your approved by the party, you will be able see it in the candidate display list from the main menu \n";
	cout << "\n";
	fflush(stdin);
	getline(cin, r->consti);
	f->next = r;
	r->next = NULL;
}


void requests(string match, string input)  //approve or disapprove requests as a queue
{
	int p, count, counter = 0;
	string party_name;

	if (match == input)
	{
		party_name = match;
		cout << "Remaining requests" << endl;
		for (tp = f; tp != NULL; tp = tp->next)
		{
			if (tp->party_request == party_name)
			{
				cout << "Candidate name : " << tp->candidatename << endl;
				cout << "press 1 to approve or press 2 to disapprove  : ";
				cin >> p;
				if (p == 1)
				{
					cout << "approved candidate is " << tp->candidatename << endl;
                    
                    ifstream party_names("party_names.txt");
                    while(getline(party_names, match))
                    {
                    	if(party_name == match)
                    	break;
                    	else
                    	count = count +1;
					}
					party_names.close();
					
					string symbol;
					ifstream party_symbols("party_symbols.txt");
					while(counter <= count)
					{
						
						getline(party_symbols, symbol);
						if(counter == count)
						break;
					}
					party_symbols.close();
                    
					// to be registered at the end, once party approves
                    if(1)
                    {
                    ofstream candid_names("candid_names.txt", ios::app);
					ofstream candid_party("candid_party.txt", ios::app);
					ofstream candid_consti("candid_constituency", ios::app);
					ofstream candid_symbols("candid_symbols.txt", ios::app);

					candid_names << tp->candidatename << endl;
					candid_party << tp->party_request << endl;
					candid_consti << tp->consti << endl;
					candid_symbols << symbol << endl;
					candid_names.close();
					candid_party.close();
					candid_consti.close();
					candid_symbols.close();	
					}
				}

				if (p == 2)
				cout << "disapproved candidate is " << tp->candidatename << endl;
				node* prev;
				for (prev = f; prev->next != tp->next; prev = prev->next)
				{
					if (prev->next == tp)
					{
						prev->next = tp->next;
						tp->next = NULL;
						break;
					}
				}
			}
		}
	}

	else
		cout << "You have entered a different party's name, we cannot provide you further access. Please try again\n";
}

void party_login()
{
	static int count = 0;
	int option;
	string  get_file, username, password, party_name;
	bool flag = false;
	cout << "\nWhat is your party name ?\n";

	fflush(stdin);
	getline(cin, party_name);

	ifstream party_names("party_names.txt");
	while (getline(party_names, get_file)) // loop to check wether party name already exists or not in the party_names file
	{
		if (get_file == party_name)
		{
			flag = true;
			break;
		}
		count = count + 1;
	}


	// When party name is checked that it exits, time to enter the username and password
	if (flag == true)
	{
		cout << "\nParty name exists, please enter username\n";
		fflush(stdin);
		cin >> username;

		int counter = 0; flag = false;
		ifstream party_usernames("party_usernames.txt");
		while (counter <= count)  //skipping lines to check username
		{
			getline(party_usernames, get_file);
			if (counter == count)
			{
				if (username == get_file)
					flag = true;
				break;
			}
			counter = counter + 1;
		}
		party_usernames.close();

		// When username is approved then time for the password
		if (flag == true)
		{
			cout << "\nNow please enter the password for the username\n";
			cin >> password;

			counter = 0; flag = false;
			ifstream party_passwords("party_passwords.txt");
			while (counter <= count)  //skipping lines to check username
			{
				getline(party_passwords, get_file);
				if (counter == count)
				{
					if (password == get_file)
						flag = true;
				}
				counter = counter + 1;
			}
			party_passwords.close();

			if (flag == true)
			{
				cout << "\nWhat would you like to do ?\n";
				cout << "(1) Approve/reject request of ticket \n(2)Check results of voting \n";
				cin >> option;

				if (option == 1)
				{
					string party_input;
					cout << "Please once again enter your party's name to procceed\n";
					fflush(stdin);
					getline(cin, party_input);
					requests(party_name, party_input);
				}
				
				if (option ==2)
				{
                 show_results();
				}
				
				
			}

		}
	}

	else if (flag == false)
	{
		cout << "Party does not exist, redirecting you to the main menu\n";
	}
}

void results(node* head, node* head2)
{
	static int max = 0;
	string get_file, get_file1;
	
	ifstream constituencies("constituencies.txt");
	while(getline(constituencies, get_file))
		{
		
	    for (node* ptr1 = head2; ptr1->next != NULL; ptr1 = ptr1->next)
	    {
		if(get_file == ptr1->candidconst)
		{
		if (max < ptr1->votes)
		max = ptr1->votes;
		}
	    }
	    
	    for (node* ptr2 = head2; ptr2->next != NULL; ptr2 = ptr2->next)
	    {
	    if(get_file == ptr2->candidconst)
	    {
	    	ofstream voting_winner("voting_winner.txt", ios::app);
        if (max == ptr2->votes && max>0)
		{
        voting_winner << ptr2->candidatename << "\t" << ptr2->candidparty << "\t" << ptr2->votes << " votes." << endl;
		}
		else if (max == ptr2->votes && max==0)
		voting_winner << "Nobody\t" << "None" << "\t" << ptr2->votes << " votes." << endl;
        voting_winner.close();  	    	
		}
        }
		}
		constituencies.close();
	
	if(1)
	{
	cout<<"\n\nThe Voting Process Has Commenced, Following Are The Results From The Respective Constituencies:\n";
	ifstream constituencies("constituencies.txt"); // DISPLAY OF VOTING RESULTS
	ifstream voting_winner("voting_winner.txt");
    fflush(stdin);
	while( getline (constituencies, get_file)  && getline(voting_winner, get_file1))
	{
	cout<<get_file<<":  "<< get_file1 << endl;
    }
	constituencies.close();
	voting_winner.close();
	cout<<endl<<endl;
	
	cout<<"\n\nENTER ANY NUMBER TO BE REDIRECTED TO THE MAIN MENU\n";
	cin>>get_file;
	system("CLS");
	menu (head, head2);	
	}
	
}

void voting_process(node* head, node* head2)
{
	// FIRST INPUT ALL THE CANDIDATES AND VOTERS INFO INTO A SEPERATE LINKED LIST EACH
	
	string voter_pass1, voter_consti1, candid_name1, candid_party1, candid_consti1, candid_symbol1;
	int count = 0;
	long long voter_cnic1;
	
    fstream voting_winner( "voting_winner.txt", ios::in );
    if (voting_winner)
      {
      
      voting_winner.open( "voting_winner", ios::out | ios::trunc );
      }
	voting_winner.close();
	
	ifstream voter_cnic("voter_cnic.txt");
	ifstream voter_passwords("voter_passwords.txt");
    ifstream voter_consti("voter_consti.txt");
    
	ifstream candid_names("candid_names.txt");
	ifstream candid_party("candid_party.txt");
	ifstream candid_consti("candid_constituency");
	ifstream candid_symbols("candid_symbols.txt");

	while(voter_cnic >> voter_cnic1)
	{

		getline(voter_passwords, voter_pass1 );

		getline(voter_consti, voter_consti1 );

		prepass(head, voter_consti1, voter_pass1, voter_cnic1);//copy name and ID together from string to linked list

	}
	
	while(getline(candid_names, candid_name1 ))
	{
		getline(candid_party, candid_party1);

		getline(candid_consti, candid_consti1 );

		getline(candid_symbols, candid_symbol1 );
		  

		prepass2(head2, candid_name1, candid_consti1, candid_party1);//copy name and ID together from string to linked list
	}
	
	voter_cnic.close();
	voter_passwords.close();
	voter_consti.close();
	candid_names.close();
	candid_party.close();
	candid_consti.close();
	candid_symbols.close();
	
	// NOW TO ASK THE VOTER WHAT DO THEY PREFER TO DO AT THE MOMENT
	for(;;)
	{
	int option;
	system("CLS");
	cout<<"What would you like to do ?\n\n";
	cout<<"(1) Voter Login\n";
	cout<<"(2) Finalize voting and see results\n\noption: ";
	cin>>option;
	
	if(option==1)
	voterlogin(head, head2); // WHERE VOTERS CAN SEE CANDIDATES AND CAST THEIR VOTE
	
	if(option==2) // END THE VOTING PROCESS AND FINALIZE THE VOTING RESULTS
	{
	results(head,head2);	
    break;
	}
	
	cout<<"\nENTER ANY NUMBER TO BE REDIRECTED TO THE VOTING MENU\n";
	cin>>option;

	}

}


void menu(node* head, node* head2)
{
	cout << "Select an option:" << endl << endl;
	cout << "1) Register a National Assembly Constituency (e.g. NA-1)\n";
	cout << "2) List all Constituencies\n";
	cout << "3) Update/Delete Constituencies \n";
	cout << "4) Register a Political Party \n";
	cout << "5) Register an Independent Candidate \n";
	cout << "6) Register a  Party Candidate\n";
	cout << "7) Party Login \n";
	cout << "8) Voter Registration \n";
	cout << "9) Commence Voting \n";
	cout << "10) Show Results of Voting\n";
	

	int option;
	cout << "option: "; cin >> option;

	switch (option) {
	case 1:
		registerConstituency();
		break;

	case 2:
		displayConstituency();
		break;

	case 3:
		updateOrDelete();
		break;

	case 4:
		register_party();
		break;

	case 5:
		reg_independent_candid();
		break;

	case 6:
		reg_party_candid();
		break;

	case 7:
		party_login();
		break;
	
	case 8:
		voter_registration();
			break;

	case 9:
		voting_process(head, head2);
		break;
		
	case 10:
	    show_results()	;

	}
}


int main() {
    f = new node;
    f->next = nullptr;

    node* prev = new node;
    prev->next = nullptr;

    head = new node;
    head->next = nullptr;

    head2 = new node;
    head2->next = nullptr;

    Election_login(head, head2);

    int exitOption;
    cout << "\nPRESS ANY NUMBER TO EXIT\n";
    cin >> exitOption;
    system("CLS");

    for (;;) {
        menu(head, head2);
        cout << "\nPRESS ANY NUMBER TO EXIT\n";
        cin >> exitOption;
        system("CLS");
    }

    // Release memory allocated for nodes
    delete f;
    delete prev;
    delete head;
    delete head2;

    return 0;
}

