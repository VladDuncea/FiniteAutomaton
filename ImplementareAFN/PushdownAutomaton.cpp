#include "PushdownAutomaton.h"



bool PushdownAutomaton::tranz_sort(tranzition a, tranzition b)
{
	//Sort by tranzitions letter
	if (a.letter == b.letter)
	{	//Sort by state id
		if (a.next_state_id == b.next_state_id)
		{
			//Sort by top of stack
			return a.stackTop < b.stackTop;
		}
		return a.next_state_id < b.next_state_id;
	}
	return (a.letter < b.letter);
}

PushdownAutomaton::PushdownAutomaton()
{
	initial_state_id = 0;
	spacing = 0;
	nr_states = 0;
}


PushdownAutomaton::~PushdownAutomaton()
{
}

void PushdownAutomaton::set_initial(int val)
{
	//Check if state exists
	if (val < 0 || val >= nr_states)
		exit(-1);

	initial_state_id = val;
}

void PushdownAutomaton::toggle_final(int state, bool val)
{
	if (state >= 0 && state < nr_states)
		pstates[state].f_state = val;
}

void PushdownAutomaton::add_tranzition(int s1, int s2, char letter, char stackTop, string stackAdd)
{
	tranzition t;
	t.letter = letter;
	t.next_state_id = s2;
	t.stackAdd = stackAdd;
	t.stackTop = stackTop;

	//keep track of states
	int n = ++(pstates[s1].nr_tranz);

	//Check if the letter is new to the alphabet
	if (alphabet.empty())
	{
		//First letter in alphabet
		alphabet.push_back(letter);
	}
	else
	{
		//Place them in alphabetic order
		if (!binary_search(alphabet.begin(), alphabet.end(), letter))
			alphabet.insert(upper_bound(alphabet.begin(), alphabet.end(), letter), letter);
	}


	if (n == 1)
	{
		//Add directly the first tranzition
		pstates[s1].tranz.push_back(t);
	}
	else
	{
		//Keep the vector sorted
		pstates[s1].tranz.insert(upper_bound(pstates[s1].tranz.begin(), pstates[s1].tranz.end(), t, tranz_sort), t);
	}
}

void PushdownAutomaton::add_state(int f_nr_states)
{
	//Get the last state id
	int last_state = -1;
	if (!pstates.empty())
		last_state = pstates.size() - 1;

	//Create a new empty state
	state toAdd;
	toAdd.state_id = last_state + 1;
	toAdd.nr_tranz = 0;
	toAdd.f_state = false;

	//Add nr_states of states to the array of current states
	for (int i = 0; i < f_nr_states; i++)
	{
		pstates.push_back(toAdd);
		//Iterate the state id
		toAdd.state_id++;
		nr_states++;
	}
}

int PushdownAutomaton::initialize(void)
{
	if (!pstates.empty())
	{
		cout << "Machine already initialized!";
		return -1;
	}

	int x, y;

	//Read the number of states and allocate them
	cout << "Number of states: ";
	cin >> x;
	add_state(x);

	//Set initial state

	cout << "Initial state (0-" << nr_states - 1 << "): ";
	cin >> x;
	set_initial(x);

	//Final states
	cout << "Number of final states: ";
	cin >> x;
	for (int i = 0; i < x; i++)
	{
		cin >> y;
		toggle_final(y, true);
	}

	//Tranzitions
	cout << "Number of tranzitions: ";
	cin >> x;
	cout << "Tranzitions 'state 1' 'state 2' 'letter' 'TOS' 'addToStack\n";

	for (int i = 0; i < x; i++)
	{
		int s1, s2;
		char l,tos;
		char stackAdd[100];
		cin >> s1 >> s2 >> l >> tos;
		cin >> stackAdd;
		add_tranzition(s1, s2, l,tos,stackAdd);
	}
	return 0;
}

void PushdownAutomaton::display_alphabet(void)
{
	cout << "Used alphabet: ";
	for (const auto &x : alphabet)
	{
		cout << x << " ";
	}
	cout << endl;
}

void PushdownAutomaton::display_automaton(void)
{
	//Verifiy that the machine is initialized
	if (pstates.empty())
	{
		return;
	}

	//Show initial state id
	cout << "Initial state: " << pstates[initial_state_id].state_id << endl;

	for (int i = 0; i < nr_states; i++)
	{
		cout << "State: " << i << endl;
		cout << "Final state: ";
		if (pstates[i].f_state)
			cout << "YES";
		else
			cout << "NO";
		cout << endl;

		//Show all the tranzitions available from this node
		for (int j = 0; j < pstates[i].nr_tranz; j++)
		{
			tranzition &tr = pstates[i].tranz[j];
			cout << "On letter: " << tr.letter <<" with TOS="<< tr.stackTop << " go to " << tr.next_state_id<<" and add "<<tr.stackAdd.data() <<endl;
		}
		cout << endl;
	}
}

bool PushdownAutomaton::check_word(char * word)
{
	return false;
}

bool PushdownAutomaton::check_nedet(void)
{
	return false;
}
