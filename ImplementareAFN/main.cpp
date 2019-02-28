#include <iostream>
#include <cstdlib>
#include <string.h>

using namespace std;

class FiniteAutomaton
{
	struct state;

	struct tranzition
	{
		struct state *next_state;
		char letter;
	};

	struct state
	{
		int state_id;
		//Maybe use vectors
		tranzition *tranz;
		int nr_tranz;
		bool f_state;
	};

	state * pstates, *initial;
	int nr_states;

	bool priv_check_word(state *cur_state, char word[], int wpoz)
	{
		int len;
		len = strlen(word);
		bool ok = false;

		//Lambda word
		if (wpoz == len)
		{
			if (cur_state->f_state)
				return true;
			return false;
		}

		//Check if a tranzition is available
		for (int i = 0; i < cur_state->nr_tranz; i++)
		{
			if (cur_state->tranz[i].letter == word[wpoz])
			{
				cur_state = cur_state->tranz[i].next_state;
				ok = true;
			}
		}

		if (ok)
			return priv_check_word(cur_state, word, wpoz + 1);

		return false;
	}

public:
	FiniteAutomaton()
	{
		pstates = initial = NULL;
	}

	int initialize()
	{
		if (pstates != NULL)
		{
			cout << "Machine already initialized!";
			return -1;
		}

		cout << "Numar de stari: ";
		cin >> nr_states;
		pstates = new state[nr_states];
		if (pstates == NULL)
			return -1;
		for (int i = 0; i < nr_states; i++)
		{
			pstates[i].state_id = i;
			pstates[i].nr_tranz = 0;
			pstates[i].tranz = NULL;
			pstates[i].f_state = false;
		}

		//Initial state
		int x;
		cout << "Starea initiala (0-" << nr_states - 1 << "): ";
		cin >> x;
		initial = &pstates[x];

		//Final states
		cout << "Number of final states: ";
		cin >> x;
		for (int i = 0; i < x; i++)
		{
			int fs;
			cin >> fs;
			pstates[fs].f_state = true;
		}

		//Tranzitions
		cout << "Numar tranzitii: ";
		cin >> x;
		cout << "Tranzitii 'stare 1' 'stare 2' 'litera'\n";

		for (int i = 0; i < x; i++)
		{
			int s1, s2;
			char l;
			cin >> s1 >> s2 >> l;
			int n = ++(pstates[s1].nr_tranz);
			tranzition * aux = (tranzition *)realloc(pstates[s1].tranz, n);
			if (aux == NULL)
				return 0;
			pstates[s1].tranz = aux;
			pstates[s1].tranz[n - 1].letter = l;
			pstates[s1].tranz[n - 1].next_state = &pstates[s2];
		}
		cout << "Initial state: " << initial->state_id << endl << endl;
	}

	void display_automaton()
	{
		if (pstates == NULL)
		{
			return;
		}

		for (int i = 0; i < nr_states; i++)
		{
			cout << "State: " << i << endl;
			cout << "Final state: ";
			if (pstates[i].f_state)
				cout << "YES";
			else
				cout << "NO";
			cout << endl;

			for (int j = 0; j < pstates[i].nr_tranz; j++)
			{
				cout << "On letter: " << pstates[i].tranz[j].letter << " go to " << pstates[i].tranz[j].next_state->state_id << endl;
			}
			cout << endl;
		}
	}

	bool check_word(char word[])
	{
		return priv_check_word(initial, word, 0);
	}
};


int main()
{
	FiniteAutomaton fa;
	fa.initialize();

	fa.display_automaton();
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
		cout << "The word : " << word << " is " << (fa.check_word(word) ? "correct" : "incorrect" ) << endl;
	}


	return 0;
}
