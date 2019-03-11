#include <iostream>
#include <cstdlib>
#include <string.h>
#include <queue>
#include "finiteautomaton.h"

using namespace std;

int main()
{
	FiniteAutomaton fa;
	cout << "Duncea Vlad- Finite Automaton Aplication"<<endl;
	cout << "You will first need to initialise the automaton with basic information." << endl;
	cout << "States and transitions can be also added later."<<endl;
	fa.initialize();
	int input = 0;
	while (true)
	{
		int info;
		switch (input)
		{
		case 0:
		
			system("CLS");
			cout << "Options: " << endl;
			cout << "1 - display automaton" << endl;
			cout << "2 - display alphabet" << endl;
			cout << "3 - add states" << endl;
			cout << "4 - add tranzitions" << endl;
			cout << "5 - test word" << endl;
			cout << "6 - check if the automaton is nedeterministic" << endl;
			cout <<endl<< "0 - clear console and reshow menu" << endl;
			break;
		case 1:
			fa.display_automaton();
			break;
		case 2:
			fa.display_alphabet();
			break;
		case 3:
			cout << "Number of new states: ";
			cin >> info;
			fa.add_state(info);
			break;
		case 4:
			cout << "Number of tranzitions: ";
			cin >> info;
			cout << "'initial state' 'final state' 'letter'" << endl;
			cout << "EX: 0 1 a" << endl;
			for (int i = 0; i < info; i++) 
				fa.add_tranzition();
			break;
		case 5:
			char word[100];
			
			cout << "Insert word: ";
			cin >> word;
			fa.check_word(word);
			break;
		case 6:
			cout << (fa.check_nedet() ? "AFN !" : "AFD !")<<endl;
			break;
		default:
			cout << "Invalid command type 0 for help"<<endl;
			break;
		}
		cout << "Menu option: ";
		cin >> input;
	} 


	return 0;
}
