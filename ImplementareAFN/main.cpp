#include <iostream>
#include <cstdlib>

using namespace std;

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

void afisare(int n, state states[])
{
	for (int i = 0; i < n; i++)
	{
		cout << "State: " << i << endl;
		cout << "Final state: ";
		if (states[i].f_state)
			cout << "YES";
		else
			cout << "NO";
		cout << endl;

		for (int j = 0; j < states[i].nr_tranz; j++)
		{
			cout << "On letter: " << states[i].tranz[j].letter << " go to " << states[i].tranz[j].next_state->state_id << endl;
		}
		cout << endl;
	}
}

int main()
{
	state * pstates, *initial;
	int n;
	//the number of states and initialization
	cout << "Numar de stari: ";
	cin >> n;
	pstates = new state[n];
	if (pstates == NULL)
		return -1;
	for (int i = 0; i < n; i++)
	{
		pstates[i].state_id = i;
		pstates[i].nr_tranz = 0;
		pstates[i].tranz = NULL;
		pstates[i].f_state = false;
	}

	//Initial state
	int x;
	cout << "Starea initiala (0-" << n - 1 << "): ";
	cin >> x;
	initial = &pstates[x];
	//Final states
	cout << "Number of final states: ";
	cin >> x;
	for (int i = 0; i < x; i++)
	{
		int fs;
		cin >> fs;
		pstates[i].f_state = true;
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
	cout << "Initial state: " << initial->state_id << endl<<endl;
	afisare(n, pstates);

	return 0;
}