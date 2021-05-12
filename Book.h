#ifndef BOOK_H
#define BOOK_H

#include <vector>
#include <list>
#include <string>
using namespace std;

class Book
{
	vector<string> word;
	vector<string> meaning;
	vector<string> example;
	vector<int> syn;
	vector<int> ant;
	int pos;
	list<int> graph[1000];
	
	public:
		Book();
		void insert(string, string, string, int, int);
		void display(int);
		int getPos();
};

#endif
