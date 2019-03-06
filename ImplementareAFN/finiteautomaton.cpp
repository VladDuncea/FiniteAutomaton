#include "finiteautomaton.h"

struct FiniteAutomaton::tranzition
{
	struct state *next_state;
	char letter;
};

struct FiniteAutomaton::state
{
	int state_id;
	//Maybe use vectors

	vector<tranzition> tranz;
	int nr_tranz;
	bool f_state;
};

void FiniteAutomaton::add_tranzition()
{
	int s1, s2;
	char l;
	cin >> s1 >> s2 >> l;
	int n = ++(pstates[s1].nr_tranz);
	tranzition toAdd;
	toAdd.letter = l;
	toAdd.next_state = &pstates[s2];

	//Add directly the first tranzition
	if (n == 1)
	{
		pstates[s1].tranz.push_back(toAdd);
	}
	else
	{
		pstates[s1].tranz.insert(upper_bound(pstates[s1].tranz.begin(), pstates[s1].tranz.end(), toAdd, tranz_sort), toAdd);
	}
}

bool FiniteAutomaton::check_word(char *word)
{
	//Empty function queue
	while (!q.empty())
		q.pop();

	//Add initial state to queue and call check function
	check_word_params cwp{ initial,0 };
	q.push(cwp);
	bool result = priv_check_word(word);
	cout << "The word : " << word << " is " << (result ? "correct" : "incorrect") << endl;
	return result;
}

bool FiniteAutomaton::check_nedet(void)
{
	for (int j = 0; j < nr_states; j++)
	{
		for (int i=0;i<pstates[j].tranz.size()-1;i++)
		{
			if (pstates[j].tranz[i].letter == pstates[j].tranz[i+1].letter)
				return true;
		}
	}
	return false;
}

void FiniteAutomaton::display_automaton()
{
	//Verifiy that the machine is initialized
	if (pstates == NULL)
	{
		return;
	}

	//Show initial state id
	cout << "Initial state: " << initial->state_id << endl;

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
			cout << "On letter: " << pstates[i].tranz[j].letter << " go to " << pstates[i].tranz[j].next_state->state_id << endl;
		}
		cout << endl;
	}

}

int FiniteAutomaton::initialize()
{
	if (pstates != NULL)
	{
		cout << "Machine already initialized!";
		return -1;
	}

	//Read the number of states and allocate them
	cout << "Numar de stari: ";
	cin >> nr_states;
	pstates = new state[nr_states];
	
	if (pstates == NULL)
		return -1;
		//Initialise every node vith default values
	for (int i = 0; i < nr_states; i++)
	{
		pstates[i].state_id = i;
		pstates[i].nr_tranz = 0;
		pstates[i].f_state = false;
	}

	//Set initial state
	set_initial();

	//Final states
	int x;
	cout << "Number of final states: ";
	cin >> x;
	for (int i = 0; i < x; i++)
	{
		toggle_final();
	}

	//Tranzitions
	cout << "Numar tranzitii: ";
	cin >> x;
	cout << "Tranzitii 'stare 1' 'stare 2' 'litera'\n";

	for (int i = 0; i < x; i++)
	{
		add_tranzition();
	}
	return 0;
}

bool FiniteAutomaton::priv_check_word(char * word)
{
	//If queue is empty there is nothing left to check
	if (q.empty())
		return false;

	//Read front of queue
	check_word_params cwp = q.front();
	q.pop();

	//Take the needed parameters
	state *cur_state = cwp.cur_state;
	int wpoz = cwp.wpoz;
	int len = strlen(word);

	//When al the cases for a letter are done send newline
	if (spacing != wpoz)
	{
		spacing++;
		cout << endl;
	}

	//Lambda word
	if (wpoz == len)
	{
		cout << "State: " << cur_state->state_id << "| Word: 'lambda'" << endl;
		if (cur_state->f_state)
			return true;
		return priv_check_word(word);
	}

	//Show the current run data
	cout << "State: " << cur_state->state_id << "| Word: " << word + wpoz << endl;

	//Check if a tranzition is available
	for (int i = 0; i < cur_state->nr_tranz; i++)
	{

		if (cur_state->tranz[i].letter == word[wpoz])
		{
			//Available tranzition
			//Add data to struct then to the queue
			cwp.cur_state = cur_state->tranz[i].next_state;
			cwp.wpoz = wpoz + 1;
			q.push(cwp);
		}
	}

	//Cicle until queue is empty
	return priv_check_word(word);
}

bool FiniteAutomaton::tranz_sort(tranzition a, tranzition b)
{
	if (a.letter < b.letter)
		return true;
	return false;
}

void FiniteAutomaton::set_initial()
{
	int x;
	cout << "Starea initiala (0-" << nr_states - 1 << "): ";
	cin >> x;
	while (x < 0 || x >= nr_states)
	{
		cout << "Starea initiala (0-" << nr_states - 1 << "): ";
		cin >> x;
	}
	initial = &pstates[x];
}

void FiniteAutomaton::toggle_final()
{
	int fs;
	cin >> fs;
	if (fs >= 0 && fs < nr_states)
		pstates[fs].f_state = !pstates[fs].f_state;
}

