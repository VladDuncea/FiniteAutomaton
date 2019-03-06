#include <iostream>
#include <cstdlib>
#include <string.h>
#include <queue>
#include "finiteautomaton.h"

using namespace std;

int main()
{
	FiniteAutomaton fa;
	fa.initialize();
	fa.display_automaton();
	cout << (fa.check_nedet() ? "AFN !" : "AFD !");
	cout << endl;
	//Read words
	while (true)
	{
		char word[100];
		cout << "Try word ?(y,n)";
		cin >> word;

		if (word[0] == 'n')
			return 0;

		cout << "Insert word: ";
		cin >> word;
		fa.check_word(word);
		
	} 


	return 0;
}
