#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include "book.h"
#include "student.h"
bool isValidID(int x);
void loadBooks();
void loadStudents();
void printAllStudents();
void login();
void userInterface();
void borrowBook();
void returnBook();
bool hasOverDue();
void printOverdue();
int getTime();
int adjustTime(int currentTime);
void uploadBooks();
void uploadStudents();

vector <book> books;
vector <student> students;
int studentIndex=-1;
int startTime = getTime();

int main() {
	cout << "Loading files from databases..." << endl << endl;
	loadBooks();
	loadStudents();

	userInterface();
	
	uploadBooks();
	uploadStudents();
	cout << endl << "Thank you for using the Library Management System!" << endl;
	cout << "Logging off!" << endl;
}

bool hasOverDue() {

	for (int i = 0; i < students[studentIndex].getListSize(); i++) { //loops through all the books the logged in student has taken out

		for (int j = 0; j < books.size(); j++) { //This searches every book for the ID 

			if (students[studentIndex].getListValue(i) == books[j].getID()) { //Checks if this book has the matching ID


				if (adjustTime(getTime()) >= books[j].getExpDate()) { //Check if the expiration date is passed the current time

					return true;
				}
				break; //break because each ID is unique and we dont need to keep searching for this book
			}

		}
	}
	return false;
}

void printOverdue() {
	cout << "You have overdue books, return them before you can take out anymore:" << endl;
	for (int i = 0; i < students[studentIndex].getListSize(); i++) { //loops through all the books the logged in student has taken out

		for (int j = 0; j < books.size(); j++) { //This searches every book for the ID 

			if (students[studentIndex].getListValue(i) == books[j].getID() && adjustTime(getTime()) >= books[j].getExpDate()) {
			//  ^^Checks if this book has the matching ID            			^^Check if the expiration date is passed the current time
				cout << "Book Title: " << books[j].getTitle() << "     Expiration Date was ";
				if ((adjustTime(getTime()) - books[j].getExpDate()) / (60 * 60 * 24) == 0) {
					cout << "today" << endl;
				}
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
	int bookID, bookIndex = -1;
	bool allowed = true;

	if (students[studentIndex].getMaxAllowed() <= students[studentIndex].getListSize()) {

		cout << "You have already taken out your maximum amount of books. Please return a book to take one out." << endl;
		allowed = false;
	}
	if (hasOverDue()) {
		printOverdue();
		allowed = false;
	}
	if (allowed) {
		cout << "Enter the ID of the book you would like to borrow:" << endl;
		cin >> bookID;

		for (int i = 0; i < books.size(); i ++) {
			if (books[i].getID() == bookID) {
				bookIndex = i;
				break;
			}
		}
		if (bookIndex == -1) {
			cout << "No book with this ID can be found." << endl;
		}
		else if (students[studentIndex].getUsername() == books[bookIndex].getName()) {

			cout << "You have already taken out this book." << endl;
			if ((books[bookIndex].getExpDate() - adjustTime(getTime())) / 86400 > 1) {
				cout << "The expiration date is in: ";
				cout << (books[bookIndex].getExpDate() - adjustTime(getTime())) / 86400 << " days." << endl;
			}
		}else if(books[bookIndex].getName().empty()){

			students[studentIndex].borrowBook(books[bookIndex].getID()); // Adds the book ID to the student's borrowed list

			books[bookIndex].setName(students[studentIndex].getUsername());
			books[bookIndex].setStartDate(adjustTime(getTime()));
			books[bookIndex].setExpDate(adjustTime(getTime()) + students[studentIndex].getMaxTime()*60*60*24);
			
			cout << "You have taken out the book." << endl;
			cout << "It must be returned within " << students[studentIndex].getMaxTime() << " days." << endl;
		}
		else {
			cout << "This book is not available to be taken out." << endl;
			if ((books[bookIndex].getExpDate() - adjustTime(getTime()))/86400 > 1) {
				cout << "The book will likely be availble in: ";
				cout << (books[bookIndex].getExpDate() - adjustTime(getTime())) / 86400 << " days." << endl;
			}
		}
	}
}

void returnBook() {
	int returnID;
	cout << "What is the ID of the book you want to return?" << endl;
	cin >> returnID;

	if (isValidID(returnID)) {
		if (students[studentIndex].hasBook(returnID)) {
			students[studentIndex].returnBook(returnID);
			cout << "You have successfully returned this book!" << endl << endl;
		}
		else {
			cout << "You have not taken this book out !" << endl << endl;
		}
	}
	else {
		cout << "This is not a valid book ID." << endl << endl;
	}
}

void userInterface() {
	char input;
	bool logout = false;
	login();    //Calls the login() function which is user authentication
	cout << "Welcome back, " << students[studentIndex].getUsername() << endl << endl;
	while(!logout){
		cout << endl << "Please choose: " << endl;
		cout << "        1 -- Borrow Books" << endl;
		cout << "        2 -- Return Books" << endl;	
		cout << "        0 -- Log Out" << endl;
		
		cin >> input;
	
		switch (input) {
		case '1':
			borrowBook();
			break;
		case '2':
			returnBook();
			break;
		case 'q':
			students[studentIndex].printStudent();
			break;
		case '0':
			logout = true;
			break;
		default:
			cout << "Not a correct input, please try again:" << endl << endl;
			break;
		}
	}
}

void login() {
	while (1) {
		string user = "", pass = "";
		bool found = false;
		cout << "Username:" << endl;
		cin >> user;
		cout << "Password:" << endl;
		cin >> pass;

		for (int i = 0; i <= students.size()-1 || found; i++) {
			if (students[i].getUsername() == user && students[i].getPassword() == pass) {
				found = true;
				studentIndex = i;
				break;
			}
		}
		if (!found) {
			cout << "No user with this password found" << endl << endl;
		}
		else {
			break;
		}
	}
}

void loadBooks() {    //Reads the data from book.txt
	int ISBN, ID, takeOutDate, returnDate;
	string title, author, category, name;

	ifstream data_in;
	data_in.open("book.txt");
	if (data_in.fail()) {
		cerr << "Error: Failed to open 'book.txt'." ;
	}
	cout << "Book Data found." << endl;

	while (!data_in.eof()) {
		int test;
		data_in >> ISBN >> title >> author >> category >> ID >> test;
		if (test == 0) {
			books.push_back(book(ISBN, title, author, category, ID));
		}
		else if (test == 1) {
			data_in >> name >> takeOutDate >> returnDate;
			books.push_back(book(ISBN, title, author, category, ID, name, takeOutDate, returnDate));
		}
		else {
			cerr << "Error in 'book.txt'. Book: " << "Title- " << title << " ID- " << ID << endl << "Takeout Value not 0 or 1" << endl;
		}
	}
	data_in.close();
	cout << "Successfully loaded book data" << endl << endl;
}

void loadStudents() { //reads the data from students.txt
	string username, password;
	int maxAllowed, maxTime, listSize, ID;

	ifstream data_in;
	data_in.open("student.txt");
	if (data_in.fail()) {
		cerr << "Error: Failed to open 'student.txt'.";
	}
	cout << "Student Data found." << endl;


	while (!data_in.eof()) {
		vector <int> borrowed;
		data_in >> username >> password >> maxAllowed >> maxTime >> listSize;
		for (listSize; listSize > 0; listSize--) {
			data_in >> ID;
			borrowed.push_back(ID);
		}
		students.push_back(student(username, password, maxAllowed, maxTime, borrowed));
	}
	data_in.close();
	cout << "Successfully loaded student data" << endl << endl;
}

void uploadBooks() {
	ofstream data_out;
	data_out.open("book.txt");
	if (data_out.fail()) {
		cerr << "Error: Failed to upload to 'book.txt'.";
	}
	for (int i = 0; i < books.size(); i++) {
		data_out << books[i].getISBN() << " " << books[i].getTitle() << " " << books[i].getAuthor() << " ";
		data_out << books[i].getCategory() << " " << books[i].getID() << " ";
		if (!books[i].getName().empty()) {
			data_out << 1 << " " << books[i].getName() << " " << books[i].getStartDate() << " " << books[i].getExpDate();
		}
		else {
			data_out << 0;
		}
		if(i+1<books.size())
			data_out << endl;
	}
	data_out.close();
	cout << "Updated 'book.txt'" << endl;
}

void uploadStudents() {
	ofstream data_out;
	data_out.open("student.txt");
	if (data_out.fail()) {
		cerr << "Error: Failed to upload to 'student.txt'.";
	}
	for (int i = 0; i < students.size(); i++) {
		data_out << students[i].getUsername() << " " << students[i].getPassword() << " ";
		data_out << students[i].getMaxAllowed() << " " << students[i].getMaxTime() << " ";

		if (students[i].getListSize() > 0) {
			data_out << students[i].getListSize() << " ";
			for (int j = 0; j < students[i].getListSize(); j++) {
				data_out << students[i].getListValue(j);
				if (j + 1 < students[i].getListSize()) {
					data_out << " ";
				}
			}
		}
		else {
			data_out << 0;
		}
		if (i + 1 < students.size())
			data_out << endl;
	}
	data_out.close();
	cout << "Updated 'student.txt'" << endl;
}

void printAllStudents() {
	for (int i = 0; i < students.size(); i++) {
		cout << "Student " << i << ":" << endl;
		students[i].printStudent();
		cout << endl;
	}
}

bool isValidID(int x) {

	for (int i = 0; i < books.size(); i++) {
		if (books[i].getID() == x) {
			return(true);
		}
	}
	return (false);
}	 

int getTime() {
	time_t timer;
	struct tm y2k = { 0 };
	double seconds;

	y2k.tm_hour = -1;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 110; y2k.tm_mon = 0; y2k.tm_mday = 2;

	time(&timer);  /* get current time; same as: timer = time(NULL)  */

	seconds = difftime(timer, mktime(&y2k));
	return seconds;
}

int adjustTime(int currentTime) {

	int time_difference = currentTime - startTime;
	int time = currentTime + time_difference * 8640;
	return time;
}

