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
	vector <string> borrowedList;

public:
	student(string a, string b, int c, int d, vector <string> e);
	void printStudent();

	void setUsername(string x);
	void setPassword(string x);
	void setMaxAllowed(int x);
	void setMaxTime(int x);
	void setBorrowedList(vector <string> x);

	string getUsername();
	string getPassword();
	int getMaxAllowed();
	int getMaxTime();

};