#pragma once
#include <iostream>
#include <vector>
using namespace std;

class student {
private:
	string username;	
	string password;
	int maxAllowed;
	int maxTime;
	vector <int> borrowedList;	// This is a list of the books the user has borrowed

public:
	student(string a, string b, int c, int d, vector <int> e);
	void printStudent();

	void setUsername(string x);
	void setPassword(string x);
	void setMaxAllowed(int x);		// Set functions
	void setMaxTime(int x);
	void setBorrowedList(vector <int> x);

	string getUsername();
	string getPassword();
	int getMaxAllowed();		// get functions
	int getMaxTime();
	int getListSize();
	int getListValue(int x);

	void returnBook(int x);	// used when a book is returned

	void printList();	// Prints the borrowedList

	bool hasBook(int x);	// Checks if the user has a book of ID 'x'
	void borrowBook(int x); // lets the user borrow a book of ID 'x'

							// Check the .cpp file for more details

};	
