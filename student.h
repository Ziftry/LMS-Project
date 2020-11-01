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
	vector <int> borrowedList;

public:
	student(string a, string b, int c, int d, vector <int> e);
	void printStudent();

	void setUsername(string x);
	void setPassword(string x);
	void setMaxAllowed(int x);
	void setMaxTime(int x);
	void setBorrowedList(vector <int> x);

	string getUsername();
	string getPassword();
	int getMaxAllowed();
	int getMaxTime();
	int getListSize();
	int getListValue(int x);

	void returnBook(int x);

	void printList();

	bool hasBook(int x);
	void borrowBook(int x);

};
