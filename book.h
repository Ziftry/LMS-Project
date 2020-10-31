	#pragma once
	#include <iostream>
	#include <vector>
	using namespace std;

	class book {
	private:
		int ISBN;
		string title;
		string author;
		string category;
		int ID;
		string readerName;
		string startDate;
		string expDate;

	public:
		book(int a, string b, string c, string d, int e);
		void takeout();

	
		void setISBN(int x);
		void setTitle(string x);
		void setAuthor(string x);
		void setCategory(string x);
		void setID(int x);
		void setName(string x);
		void setStartDate(string x);
		void setExpDate(string x);

		int getISBN();
		string getTitle();
		string getAuthor();
		string getCategory();
		int getID();
		string getName();
		string getStartDate();
		string getExpDate();
	};
