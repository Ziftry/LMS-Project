#include <iostream>	// cout cin
#include <vector>	//vectors
#include <string>	//string variables used
#include <fstream>	// download and uploading files
#include <ctime>		// ctime used for clock and time functions
#include "book.h"
#include "student.h"
bool isValidID(int x);
void loadBooks();
void loadStudents();
void login();
void userInterface();		// All the functions created below main
void borrowBook();
void returnBook();
bool hasOverDue();
void printOverdue();
int getTime();
int adjustTime(int currentTime);
void suggestBook();
void uploadBooks();
void uploadStudents();

vector <book> books;	// This vector holds all the books loaded from book.txt
vector <student> students; // likewise students holds all the student accounts loaded from student.txt
int studentIndex=-1;  //This is the index in the vector student of the logged in student
					  // It doesn't need to be -1 but it made user authentication easier
int startTime = getTime();
							//startTime is the time the program started at   (time is kept in seconds since january 1, 2010)


int main() {
	cout << "Loading files from databases..." << endl;
	loadBooks();
	loadStudents();				// loads the data from book.txt and student.txt respectively

	userInterface();	// this opens the user interface which is closed when the student is logged out
	
	uploadBooks();			//these functions upload the changes made to book.txt and student.txt respectively
	uploadStudents();
	cout << endl << "Thank you for using the Library Management System!" << endl;
	cout << "Shutting Off!" << endl;													// sign off messages
}

bool hasOverDue() {		// this bool checks if the logged in student has an overdue book.

	for (int i = 0; i < students[studentIndex].getListSize(); i++) { //loops through all the books the logged in student has taken out

		for (int j = 0; j < books.size(); j++) { //This searches every book for the ID 

			if (students[studentIndex].getListValue(i) == books[j].getID()) { //Checks if this book has the matching ID

				if (adjustTime(getTime()) >= books[j].getExpDate()) { //Check if the expiration date is passed the current time

					return true;   // Returns true if they have an over due book

				}
				break; //break because each ID is unique and we dont need to keep searching for this book
			}

		}
	}
	return false;
}

void printOverdue() {			// This function is called to print which book the logged in student has which is overdue
	cout << "You have overdue books, return them before you can take out anymore:" << endl;
	for (int i = 0; i < students[studentIndex].getListSize(); i++) { //loops through all the books the logged in student has taken out

		for (int j = 0; j < books.size(); j++) { //This searches every book in the database for the ID 

			if (students[studentIndex].getListValue(i) == books[j].getID() && adjustTime(getTime()) >= books[j].getExpDate()) {
			//  ^^Checks if this book has the matching ID            			^^Check if the expiration date is passed the current time
				cout << "Book Title: " << books[j].getTitle() << "     Expiration Date was ";
				if ((adjustTime(getTime()) - books[j].getExpDate()) / (60 * 60 * 24) == 0) {	
					cout << "earlier today" << endl;								//I didnt like it to print 'expiration date was 0 days ago'
				}												//So it checks if expiration was today and will say 'was earlier today'
				else {
					cout << (adjustTime(getTime()) - books[j].getExpDate()) / (60 * 60 * 24) << " days ago." << endl; 
					//prints how many days have passed since expiration
				}
				cout << endl;
			}
			break; //break because each ID is unique and we dont need to keep searching for this book
		}
	}
}

void borrowBook() {
	int bookID, bookIndex = -1;       //bookID is the ID of the book the user wants to take borrow   
									// bookIndex is the index of that book in the vector books
	bool allowed = true;	// this bool is false if the student is not allowed to take out another book

	if (students[studentIndex].getMaxAllowed() <= students[studentIndex].getListSize()) {	
		// First checks if the student has his maximum allowed number of books taken out

		cout << "You have already taken out your maximum amount of books. Please return a book to take one out." << endl;
		allowed = false;	// if so prints this msg and sets allowed = false
	}
	if (hasOverDue()) {	// calls the function to see if the student has an overdue book
		printOverdue();	// if so it prints what books the student has which are overdue
		allowed = false;
	}
	if (allowed) {				// if the student wasnt dissallowed for any reason
		cout << "Enter the ID of the book you would like to borrow:" << endl;
		cin >> bookID;				// takes in the book ID the student wants to borrow

		for (int i = 0; i < books.size(); i ++) {
			if (books[i].getID() == bookID) {
				bookIndex = i;		// This loop searches through all the books and checks each one if it has the same
				break;				// ID has the one the student wants to takeout, if so, the index in the vector books is remembered
			}
		}
		if (bookIndex == -1) {
			cout << "No book with this ID can be found." << endl;	//If that ID is not found bookIndex would remain unchanged and be -1
		}														
		else if (students[studentIndex].getUsername() == books[bookIndex].getName()) {  
			//This checks if the user has already taken out the book if so:

			cout << "You have already taken out this book." << endl;			
			if ((books[bookIndex].getExpDate() - adjustTime(getTime())) / 86400 > 1) {	//checks if the book is due after today
				cout << "The expiration date is in: ";
				cout << (books[bookIndex].getExpDate() - adjustTime(getTime())) / 86400 << " days." << endl;
														//If the book is due after today it reminds the student how long they have left
			}
			else {
				cout << "The expiration date is later today." << endl; // reminds the student if its due later today
			}
		}else if(books[bookIndex].getName().empty()){	// checks if that book is available

			students[studentIndex].borrowBook(books[bookIndex].getID()); // Adds the book ID to the student's borrowed list

			books[bookIndex].setName(students[studentIndex].getUsername());	// sets the booker borrowers name to the students name
			books[bookIndex].setStartDate(adjustTime(getTime()));			// sets the borrowing start time to now
			books[bookIndex].setExpDate(adjustTime(getTime()) + students[studentIndex].getMaxTime()*60*60*24);  
																// ^^^ sets the expiration date to the students max borrowing time
			cout << "You have taken out the book." << endl;				
			cout << "It must be returned within " << students[studentIndex].getMaxTime() << " days." << endl;
											// ^^ these tell the student he has successfully taken out the book and when he has to return it
		}
		else {			// if the book can not be taken out & the reason was not because the student already has taken it out
			cout << "This book is not available to be taken out." << endl;	
			if ((books[bookIndex].getExpDate() - adjustTime(getTime()))/86400 > 1) {	//This checks if the book is overdue and if not it gives the
				cout << "The book will likely be availble in: ";						//expiration date as an estimate to when it will be available
				cout << (books[bookIndex].getExpDate() - adjustTime(getTime())) / 86400 << " days." << endl;
			}
		}
	}
}

void returnBook() {		// Function called for when a student wants to return a book
	int returnID;	//ID of the book the student is returning
	cout << "What is the ID of the book you want to return?" << endl;
	cin >> returnID;							// Asks for the ID of the book and takes it in

	if (isValidID(returnID)) {				// calls isValidID to check if the ID the student input is the ID of a book in the system
		if (students[studentIndex].hasBook(returnID)) {	//Checks if the student has taken out this book
			students[studentIndex].returnBook(returnID);	//If he has then it returns the book on the students account

			for (int i = 0; i < books.size(); i++) {	//loops through all the books in the databse to find the index of the book
				if (books[i].getID() == returnID) {
					books[i].returnBook();				//and it resets the book's information so it can be taken out again
				}
			}
			cout << "You have successfully returned this book!" << endl << endl;
		}
		else {					
			cout << "You have not taken this book out !" << endl << endl;
		}																//these 3 messages tell the student what has happened
	}
	else {
		cout << "This is not a valid book ID." << endl << endl;
	}
}

void userInterface() {			
	char input;	// input holds the character the user inputs
	bool logout = false;	// logout is true when the student wants to log out and it breaks the loop when true
	login();    //Calls the login() function which is user authentication
	cout << "Welcome back, " << students[studentIndex].getUsername() << endl << endl;	//gives the user a welcome message
	while(!logout){
		cout << endl << "Please choose: " << endl;	
		cout << "        1 -- Borrow Books" << endl;			// Prints options for the user 
		cout << "        2 -- Return Books" << endl;	
		cout << "        3 -- Recieve a Book Suggestion" << endl;
		cout << "        0 -- Log Out" << endl;
		
		cin >> input;	//takes user input
		cout << endl;
	
		switch (input) {		// switch statment for each case of user input
		case '1':
			borrowBook();
			break;
		case '2':
			returnBook();		// Corrrosponding functions for the choice the user selected
			break;
		case '3':
			suggestBook();
			break;
		case '0':
			logout = true;	// logs the student out by breaking the loop
			break;
		default:
			cout << "Not a correct input, please try again:" << endl << endl;	// loops back to another input after the breaks
			break;
		}
	}
}

void login() {	// user authentication function
	while (1) {
		string user = "", pass = "";	// strings holding the username and password
		bool found = false;			// bool if a matching account is found
		cout << "Please login: " << endl;
		cout << "Username:" << endl;
		cin >> user;
		cout << "Password:" << endl;		// takes in username and password
		cin >> pass;

		for (int i = 0; i <= students.size()-1 || found; i++) {			// This searches every student in the vector students
			if (students[i].getUsername() == user && students[i].getPassword() == pass) {
				found = true;						//If the username and password match then the index of the student is remembered
				studentIndex = i;					//and found is set to true
				break;	
			}
		}
		if (!found) {
			cout << "No user with this password found" << endl << endl;	// if not found
		}
		else {
			break;		//breaks the infinite while loop 
		}
	}
}

void loadBooks() {    //Reads the data from book.txt
	int ID, takeOutDate, returnDate;					
	long long ISBN;							// these are the holder variables to transfer file contents to vector books
	string title, author, category, name;

	ifstream data_in;
	data_in.open("book.txt");				//opens book.txt as data_in and if fails returns an error
	if (data_in.fail()) {				
		cerr << "Error: Failed to open 'book.txt'." ;
		exit(1);
	}
	while (!data_in.eof()) {			// loops until end of file
		int borrowed;		// indicates if the book is being borrowed 1==yes   0 is no
		data_in >> ISBN >> title >> author >> category >> ID >> borrowed;	// the book.txt file holds information in this order
		if (borrowed == 0) {
			books.push_back(book(ISBN, title, author, category, ID));		//creates a book in the vector with the information
		}
		else if (borrowed == 1) {							//If the book is borrowed
			data_in >> name >> takeOutDate >> returnDate;			//3 more variables will have to be recorded
			books.push_back(book(ISBN, title, author, category, ID, name, takeOutDate, returnDate));// A book with these 3 variables is 
		}																							// Constructed
		else {
			cerr << "Error in 'book.txt'. " << "   ID- " << ID << endl << "Borrowed Value not 0 or 1" << endl;
			exit(1);			//This error is given if someone tampered with book.txt and the format is not correct
		}
	}
	data_in.close();
	cout << "Successfully loaded book data" << endl;	// closes book.txt and gives a msg
}

void loadStudents() { //reads the data from students.txt
	string username, password;
	int maxAllowed, maxTime, listSize, ID;		//creates 6 variables corrosponding to the information in student.txt	

	ifstream data_in;
	data_in.open("student.txt");			//opens student.txt as data_in
	if (data_in.fail()) {
		cerr << "Error: Failed to open 'student.txt'.";	//gives an error if it cant open student.txt
		exit(1);
	}

	while (!data_in.eof()) {			//loop until at end of file for student.txt 
		vector <int> borrowed;	// This vector is going to hold the borrowed book ID's for the student before construction for that student
		data_in >> username >> password >> maxAllowed >> maxTime >> listSize;	//takes in the information for a student
		for (listSize; listSize > 0; listSize--) {		//the last variable: listSize will indicate how many book ID's the student
			data_in >> ID;								//has taken out. So, it will tell the code how many more integers to scan
			borrowed.push_back(ID);
		}
		students.push_back(student(username, password, maxAllowed, maxTime, borrowed));	// Constructs the student
	}
	data_in.close();	//closes student.txt
	cout << "Successfully loaded student data" << endl << endl << endl;	//gives a success message
}

void uploadBooks() {	// This function is to upload all the book information to the database incase there are changes
	ofstream data_out;
	data_out.open("book.txt");		//opens book.txt as data_out
	if (data_out.fail()) {
		cerr << "Error: Failed to upload to 'book.txt'."; //returns an error if failed to open book.txt
		exit(1);
	}
	for (int i = 0; i < books.size(); i++) {		// This loops through all the books in the vector books
		data_out << books[i].getISBN() << " " << books[i].getTitle() << " " << books[i].getAuthor() << " ";
		data_out << books[i].getCategory() << " " << books[i].getID() << " ";			// These two lines send the information of the book to the file
		if (!books[i].getName().empty()) {
			data_out << 1 << " " << books[i].getName() << " " << books[i].getStartDate() << " " << books[i].getExpDate();
		}								//^^^ If the book is taken out then it will send the name of the borrower the start and expiration dates 							
		else {
			data_out << 0;		//Other wise it will send a 0
		}
		if(i+1<books.size())		// This if statment sends a new line unless it is the last student
			data_out << endl;
	}
	data_out.close();							// closes student.txt
	cout << "Updated 'book.txt'" << endl;		// sends a successs message
}

void uploadStudents() {     // This function is to upload all the student information to the database incase there are changes
	ofstream data_out;
	data_out.open("student.txt");	//opens student.txt as data_out
	if (data_out.fail()) {
		cerr << "Error: Failed to upload to 'student.txt'.";		//returns an error if student.txt fails to open
		exit(1);
	}
	for (int i = 0; i < students.size(); i++) {			//loops through all the students in the vector students
		data_out << students[i].getUsername() << " " << students[i].getPassword() << " ";
		data_out << students[i].getMaxAllowed() << " " << students[i].getMaxTime() << " ";	// sends out the information to student.txt

		if (students[i].getListSize() > 0) {				// if the student has books taken out
			data_out << students[i].getListSize() << " ";	//sends the amount of borrowed books the student has
			for (int j = 0; j < students[i].getListSize(); j++) {	//the for loop sends the ID's of the books the student has borrowed
				data_out << students[i].getListValue(j);
				if (j + 1 < students[i].getListSize()) {	// the if statement makes sure a space is printed between the ID's
					data_out << " ";						// it does not print a space after the last ID
				}
			}
		}
		else {	
			data_out << 0;		//if the student has taken out no books a 0 is sent to the end of their row
		}
		if (i + 1 < students.size())	// The if statment makes sure to send a new line after every student except the last one
			data_out << endl;			
	}
	data_out.close();						// closes student.txt and returns a success msg
	cout << "Updated 'student.txt'" << endl;
}

bool isValidID(int x) {			//This function checks if the book ID inputted is a book in memory

	for (int i = 0; i < books.size(); i++) { //loops through all the books in vector books
		if (books[i].getID() == x) {
			return(true);					// returns true if one of the books has a matching ID
		}
	}
	return (false);					// Otherwise returns false
}	 

void suggestBook() {			// This function suggests a book for the user to takeout 
	srand(time(NULL));		// randomises to random seed
	int x = books.size()-1;			//we want a random number on a range from 1 to how many books there are
									// so x will be the max number in the range
	int randomBook = rand() % x + 1;	//this gets a random number
	while (1) {										// Keeps looping until a book is suggested
		randomBook = rand() % x + 1;	//gets a random number
		if(books[randomBook].getName() == ""){		// Makes sure that the book is available before suggesting it
			cout << "Why not read " << books[randomBook].getTitle() << "?" << endl;
			cout << "The genre is " << books[randomBook].getCategory() << "."<< endl;	//prints the books title, genre, and ID
			cout << "The book ID is: " << books[randomBook].getID() << endl;
			break;
		}
	}
}

int getTime() {	// This function gets the current time
	time_t timer;			// Time is counted in seconds since January 1, 2010
	struct tm y2k = { 0 };
	double seconds;
															// ********I did not write this
	y2k.tm_hour = -1;   y2k.tm_min = 0; y2k.tm_sec = 0;		// This code is from the <ctime> library reference : time
	y2k.tm_year = 110; y2k.tm_mon = 0; y2k.tm_mday = 2;		// The link to the page is:
																					// http://www.cplusplus.com/reference/ctime/time/
	time(&timer);  /* get current time; same as: timer = time(NULL)  */

	seconds = difftime(timer, mktime(&y2k));
	return seconds;
}

int adjustTime(int currentTime) { // This takes in the current time which will be gotton with the function getTime()
								  //It then adjusts the time so every X amount of seconds in real life while using this program
									// will have a day pass inside the program
	int time_difference = currentTime - startTime;
	int time = currentTime + time_difference * (864 * 10); // <--- The number being multipled with 864 is how many seconds while the program is openned will count a day	
	return time;											// At the time of writing this it is currently 10: So every 10 seconds the program is open 1 day will pass

	// This function takes the difference from the start time of the program and the current time
	// and skews it so every 10 seconds the program was open a day passed
}
