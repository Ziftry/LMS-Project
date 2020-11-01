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
		int startDate;
		int expDate;

	public:
		book(int a, string b, string c, string d, int e, string f, int g, int h);
		book(int a, string b, string c, string d, int e);

		void returnBook();

		void setISBN(int x);
		void setTitle(string x);
		void setAuthor(string x);
		void setCategory(string x);
		void setID(int x);
		void setName(string x);
		void setStartDate(int x);
		void setExpDate(int x);

		int getISBN();
		string getTitle();
		string getAuthor();
		string getCategory();
		int getID();
		string getName();
		int getStartDate();
		int getExpDate();
	};
