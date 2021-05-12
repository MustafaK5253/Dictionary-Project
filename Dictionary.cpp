#include <iostream>
#include <fstream> 
#include <sstream>
#include <algorithm>
#include "Index.h"
using namespace std;

Book Dictionary;
Index DictIndx;

void banner()
{
	system("cls");
	cout<<"\n\n\n\t\t.....DICTIONARY APPLICATION.....\n\n";
	cout<<"\tMade with love by Mustafa Kasarawala.....\n\n\n";
	for(int i=0; i<12; i++) cout<<"----------";
	cout<<"\n\n\n\n";
}

int main()
{
	string word, meaning, example, rev_word, temp;
	int syn, ant, tempInt, tempInt2;
	char input;
	bool flag, mainFlag;
	stringstream ss;
	
	// ------------------- LOADING DATA FROM FILE.. ------------------------------
	
	ifstream reader("DictData.txt");
	
	while( getline(reader,word) )
	{
		getline(reader,meaning);
		getline(reader,example);
		getline(reader,temp);
		ss.clear();
		ss.str(temp);
		ss>>syn>>ant;
		rev_word = word;
		reverse(rev_word.begin(),rev_word.end());
		DictIndx.insert(rev_word, Dictionary.getPos());
		Dictionary.insert(word,meaning,example,syn,ant);
	}
	reader.close();
	
	// ----LOADING COMPLETED..  ALL DATA IS STORED INTO DICTIONARY OBJECT. INDEX OBJECT CONTAINS INDEX NUMBERS OF WORDS IN DICTIONARY....
	
	ofstream writer("DictData.txt" , ios::app);
	
	mainFlag = true;
	while(mainFlag)
	{
		// -------------------- HOME PAGE ---------------------
		banner();
		cout<<"\tTo search, please enter\t1\n";
		cout<<"\tTo add, please enter\t2\n";
		cout<<"\tTo exit, please enter\t3\n\n\n";
		cout<<"\tPlease enter your choice -- ";
		cin>>input; cin.ignore();
		// ----------------------------------------------------
		
		switch(input)
		{
			case '1' :
				
				cout<<"\n\n\tType here -- ";
				cin>>word;
				rev_word = word;
				reverse(rev_word.begin(),rev_word.end());
				
				//-----SHOWING RESULTS PAGE---------
				banner();
				cout<<"Showing results for "<<word<<" ....\n\n";
				DictIndx.search(rev_word);
				cout<<"Enter any key to continue....  ";
				cin>>input; cin.ignore();
				break;
				
			case '2' :
				
				//------FORM PAGE----------------
				banner();
				cout<<"Please type the word here -- ";
				getline(cin,word);
				rev_word = word;
				reverse(rev_word.begin(),rev_word.end());
				
				tempInt = Dictionary.getPos();
				tempInt2 = DictIndx.insert(rev_word,tempInt);
				
				if( tempInt != tempInt2 )
				{
					cout<<"\n\n\a\tThe word already exists in dictionary...\n\n\n";
					for(int i=0; i<12; i++) cout<<"----------";
					cout<<'\n';
					Dictionary.display(tempInt2);
				}
				else
				{
					syn = tempInt; ant = -1;
					
					cout<<"\n\nPlease type its meaning here --  ";
					getline(cin,meaning);
					cout<<"\n\nPlease type an example here --  ";
					getline(cin,example);
					
					flag = false;
					while(1)
					{
						if(flag)	cout<<"\n\n\aoooppps, the word does not exist in dictionary !!!\n";
						cout<<"\n\nCan you a tell a synonymn? Enter 1 for yes and 0 for no :  ";
						cin>>input;
						if(input != '1') break;
						cout<<"\n\nPlease type the word here -- ";
						cin>>temp;
						reverse(temp.begin(),temp.end());
						tempInt = DictIndx.find(temp);
						if(tempInt == -1)
						{
							flag = true;
						}
						else
						{
							syn = tempInt;
							break;
						}
					}
					
					flag = false;
					while(1)
					{
						if(flag)	cout<<"\n\n\aoooppps, the word does not exist in dictionary !!!\n";
						cout<<"\n\nCan you tell an antonymn? Enter 1 for yes and 0 for no :  ";
						cin>>input;
						if(input != '1') break;
						cout<<"\n\nPlease type the word here -- ";
						cin>>temp;
						reverse(temp.begin(),temp.end());
						tempInt = DictIndx.find(temp);
						if(tempInt == -1)
						{
							flag = true;
						}
						else
						{
							ant = tempInt;
							break;
						}
					}
					
					Dictionary.insert(word,meaning,example,syn,ant);
					writer<<word<<'\n'<<meaning<<'\n'<<example<<'\n'<<syn<<' '<<ant<<'\n';					
				}
				
				cout<<"\n\nEnter any key to continue .... ";
				cin>>input;
				break;
				
			default:
				mainFlag = false;
		}
	}
	
	writer.close();
	return 0;
}
