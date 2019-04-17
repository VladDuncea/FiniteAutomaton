#include <iostream>
#include <cstdlib>
#include <string.h>
#include <queue>
#include "finiteautomaton.h"
#include "PushdownAutomaton.h"

using namespace std;

enum AutomatonType
{
	AUTOMATON_FINITE = 0,
	AUTOMATON_PUSHDOWN = 1
};

int main()
{
	int input;
	Automaton *fa;
	AutomatonType aType;
	//General information
	cout << "Duncea Vlad- Finite+Pushdown Automaton Aplication" << endl;
	cout << "You will first need to initialise the automaton with basic information." << endl;
	cout << "States and transitions can also be added later." << endl;
	cout << "0-Finite || 1-Pushdow" << endl;
	cout << "Automaton type: ";
	cin >> input;

	switch (input)
	{
	case AUTOMATON_FINITE:
		fa = new FiniteAutomaton;
		aType = AUTOMATON_FINITE;
		break;
	case AUTOMATON_PUSHDOWN:
		fa = new PushdownAutomaton;
		aType = AUTOMATON_PUSHDOWN;
		break;
	default:
		cout << "wrong input";
		return 0;
	}
	
	//Get critical data about automaton
	fa->initialize();

	//Start menu loop
	input = 0;
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
			if(aType == AUTOMATON_FINITE)
				cout << "7 - NFA to DFA" << endl;
			cout << endl << "0 - clear console and reshow menu" << endl;
			break;
		case 1:
			fa->display_automaton();
			break;
		case 2:
			fa->display_alphabet();
			break;
		case 3:
			cout << "Number of new states: ";
			cin >> info;
			fa->add_state(info);
			break;
		case 4:
			cout << "Number of tranzitions: ";
			cin >> info;
			cout << "'initial state' 'final state' 'letter'" << endl;
			cout << "EX: 0 1 a" << endl;
			for (int i = 0; i < info; i++)
			{
				int s1, s2;
				char l;
				cin >> s1 >> s2 >> l;
				((FiniteAutomaton*)fa)->add_tranzition(s1, s2, l);
			}

			break;
		case 5:
			char word[100];

			cout << "Insert word: ";
			cin >> word;
			fa->check_word(word);
			break;
		case 6:
			cout << (fa->check_nedet() ? "NFA !" : "DFA !") << endl;
			break;
		case 7:
			if(aType==AUTOMATON_FINITE)
				fa = ((FiniteAutomaton*)fa)->export_DFA();

			break;
		default:
			cout << "Invalid command type 0 for help" << endl;
			break;
		}
		cout << "Menu option: ";
		if (!(cin >> input))
		{
			input = 0;
			exit(-1);
			//cin.ignore(INT_MAX);

		}


	}


	return 0;
}
