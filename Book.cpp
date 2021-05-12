#include "Book.h"
#include <iostream>
using namespace std;

Book::Book() : pos(0)	{}

int Book::getPos()
{
	return pos;
}

void Book::insert(string wd, string mg, string ex, int sy, int an)
{
	int ant1, ant2;
	if(sy != pos)
	{
		sy = syn[sy];
	}
	if(an != -1)
	{
		ant1 = an;
		ant2 = syn[an];
		if(ant[ant1] == -1) ant[ant1] = sy;
		if(ant[ant2] == -1) ant[ant2] = sy;
		an = ant2;
		if( sy != pos && ant[sy] == -1)
		{
			ant[sy] = an;
		}
	}
	else
	{
		if( sy != pos && ant[sy] != -1)
		{
			an = ant[sy];
		}
	}
	word.push_back(wd);
	meaning.push_back(mg);
	example.push_back(ex);
	syn.push_back(sy);
	ant.push_back(an);
	graph[sy].push_back(pos);
	pos++;
}

void Book::display(int value)
{
	int cntr;
	cout<<"\n==>  "<<word[value]<<" :- "<<meaning[value]<<"\n\n";
	cout<<"( Ex -- "<<example[value]<<" )\n\n";
	cntr = graph[syn[value]].size() - 2;
	if(cntr != -1)
	{
		cout<<"Synonymns --\t";
		for(list<int>::iterator i = graph[syn[value]].begin(); i != graph[syn[value]].end(); i++)
		{
			if(*i != value)
			{
				cout<<word[*i];
				if(cntr > 0)
				{
					cout<<", ";
					cntr--;
				}
				else cout<<'.';
			}
		}
		cout<<'\n';	
	}
	if(ant[value] == -1)
	{
		ant[value] = ant[syn[value]];
	}
	if(ant[value] != -1)
	{
		cntr = graph[ant[value]].size() - 1;
		cout<<"Antonymns --\t";
		for(list<int>::iterator i = graph[ant[value]].begin(); i != graph[ant[value]].end(); i++)
		{
			cout<<word[*i];
			if(cntr > 0)
			{
				cout<<", ";
				cntr--;
			}
			else cout<<'.';
		}
		cout<<'\n';
	}
	cout<<'\n';
	for(int i=0; i<12; i++) cout<<"----------";
	cout<<"\n\n";
}
