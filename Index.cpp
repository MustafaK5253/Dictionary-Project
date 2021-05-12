#include "Index.h"
#include <iostream>
#include <queue>
using namespace std;

extern Book Dictionary;        // extern keyword tells that there is a Dictionary object in another module.
queue<Index*> Index::que;

Index::Index()	:	value(-1)	{}

/* 	Insert funtion is used to insert a word into the tree.
	val tells that the word is stored at val index in the dictionary.
	If word does not exist in dictionary than this word is inserted and val is returned.
	Otherwise some int other than val is returned where the word is actually present in dictoinary.
*/

int Index::insert (string s, int val)
{
	if(s.empty())
	{
		if(value == -1) value = val;
		return value;
	}
	char ch = s.back();
	s.pop_back();
	auto it = children.find(ch);
	if(it == children.end())
	{	
		children.insert({ch,new Index()});
		it = children.find(ch);
	}
	return it->second->insert(s,val);
}

/*
	Find funtion is used to find if a word is present in tree or not.
	If present than its index is returned.
	Otherwise -1 is returned.
*/

int Index::find(string s)
{
	if(s.empty())
	{
		return value;
	}
	char ch = s.back();
	s.pop_back();
	auto it = children.find(ch);
	if(it == children.end()) return -1;
	else return it->second->find(s);
}

/*
	Search funtion finds the node from where BFS should start.
	then it calls BFsearch funtion.
*/

void Index::search(string s)
{
	char ch;
	map<char,Index*>::iterator it;
	if(!s.empty())
	{
		ch = s.back();
		s.pop_back();
		it = children.find(ch);
		if(it != children.end()) return it->second->search(s);
	}
	que.push(this); 
	for(int i=0; i<12; i++) cout<<"----------";
	cout<<"\n\n";
	BFsearch();
}

/*
	BFsearch funtion performs Breadth first search in the tree.
*/

void Index::BFsearch()
{
	int val;
	Index* p;
	while(!que.empty())
	{
		p = que.front();
		val = p->value;
		if(val != -1) Dictionary.display(val);
		for(auto i = p->children.begin(); i != p->children.end(); i++)
		{
			que.push(i->second);
		}
		que.pop();
	}
}
