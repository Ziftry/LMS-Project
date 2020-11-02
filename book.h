	#pragma once
	#include <iostream>
	#include <vector>
	using namespace std;

	class book {
	private:
		long long ISBN;    // long long  must be used as ISBN are 13 digits
		string title;
		string author;
		string category;
		int ID;
		string readerName;
		int startDate;
		int expDate;

	public:
		// constructors:
		book(long long a, string b, string c, string d, int e, string f, int g, int h);
		book(long long a, string b, string c, string d, int e);// the readerName, startDate, and expDate is only
		//														  needed when the book has been borrowed
		void returnBook();

		void setISBN(long long x);
		void setTitle(string x);
		void setAuthor(string x);
		void setCategory(string x);
		void setID(int x);				// set functions
		void setName(string x);
		void setStartDate(int x);
		void setExpDate(int x);

		long long getISBN();
		string getTitle();
		string getAuthor();
		string getCategory();			// get functions
		int getID();
		string getName();
		int getStartDate();
		int getExpDate();
	};
