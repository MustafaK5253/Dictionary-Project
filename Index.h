#ifndef INDEX_H
#define INDEX_H

#include "Book.h"
#include <map>
#include <utility>
#include <queue>
#include <string>
using namespace std;

class Index
{
	int value;
	map<char,Index*> children;
	static queue<Index*> que;
	void BFsearch();
	
	public:
		Index();
		int insert(string,int);
		int find(string);
		void search(string);
};


#endif
