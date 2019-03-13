#include "finiteautomaton.h"

void FiniteAutomaton::add_tranzition(int s1,int s2,char l)
{
	int n = ++(pstates[s1].nr_tranz);
	tranzition toAdd;
	toAdd.letter = l;
	toAdd.next_state_id = s2;

	//Check if the letter is new to the alphabet
	if (alphabet.empty())
	{
		//First letter in alphabet
		alphabet.push_back(l);
	}
	else
	{
		//Place them in alphabetic order
		if(!binary_search(alphabet.begin(),alphabet.end(),l))
		alphabet.insert(upper_bound(alphabet.begin(), alphabet.end(),l),l);
	}

	
	if (n == 1)
	{
		//Add directly the first tranzition
		pstates[s1].tranz.push_back(toAdd);
	}
	else
	{ 
		//Keep the vector sorted
		pstates[s1].tranz.insert(upper_bound(pstates[s1].tranz.begin(), pstates[s1].tranz.end(), toAdd, tranz_sort), toAdd);
	}
}

void FiniteAutomaton::add_state(int states_to_add)
{
	//Get the last state id
	int last_state = -1;
	if (!pstates.empty())
		last_state = pstates.size() -1;

	//Create a new empty state
	state toAdd;
	toAdd.state_id = last_state+1;
	toAdd.nr_tranz = 0;
	toAdd.f_state = false;

	//Add nr_states of states to the array of current states
	for (int i = 0; i < states_to_add; i++)
	{
		pstates.push_back(toAdd);
		//Iterate the state id
		toAdd.state_id++;
		nr_states++;
	}
}

bool FiniteAutomaton::check_word(char *word)
{
	//Empty function queue and reset variables
	while (!q.empty())
		q.pop();
	spacing = 0;

	//Add initial state to queue and call check function
	check_word_params cwp{ pstates[initial_state_id].state_id,0 };
	q.push(cwp);
	bool result = priv_check_word(word);

	//Print acordingly
	cout << "The word : " << word << " is " << (result ? "correct" : "incorrect") << endl;
	return result;
}

bool FiniteAutomaton::check_nedet(void)
{
	for (int i = 0; i < nr_states; i++)
	{
		for (int j = 1; j < pstates[i].tranz.size() && !pstates[i].tranz.empty(); j++)
		{
			if (pstates[i].tranz[j-1].letter == pstates[i].tranz[j].letter)
				return true;
		}
	}
	return false;
}

FiniteAutomaton * FiniteAutomaton::export_DFA(void)
{
	//check if the automaton is nedeterministic
	if (!check_nedet())
	{
		//if not print acordingly and stop
		cout << "this finiteautomaton is not nedeterminisitc !";
		return NULL;
	}

	typedef map<char, vector<int>> nfa_state;
	map<int, nfa_state>  nfa_table;

	for (int i = 0; i < nr_states; i++)
	{
		nfa_state x;
		//Jump over states with no tranzitions
		int nr_tranz = pstates[i].nr_tranz;
		if (nr_tranz == 0)
			continue;
		//Current letter
		char letter = pstates[i].tranz[0].letter;
		vector<int> to_states;

		for (int j = 0; j < nr_tranz; j++)
		{
			//We hit a new letter
			if (pstates[i].tranz[j].letter != letter)
			{	
				//Add states that go to the letter
				x[letter] = to_states;
				//Clear states
				to_states.clear();
				//Update current letter
				letter = pstates[i].tranz[j].letter;
			}
			to_states.push_back(pstates[i].tranz[j].next_state_id);
		}
		//Add the last letter
		x[letter] = to_states;
		nfa_table[i] = x;
		
	}

	cout << nfa_table[0].size()<<endl;
	for (auto &iterator : nfa_table)
	{
		cout << iterator.first << " "<<endl;
		
		for (auto &iterator2 : iterator.second)
		{
			cout << " "<< iterator2.first<<endl;
			
			for (auto &iterator3 : iterator2.second)
			{
				cout << "  "<< iterator3<<endl;
			}
			cout << endl;
		}
		cout << endl;
	}

	//Create dfa state_list and temp vect<int>
	vector<vector<int>> dfa_states;
	vector<int> concat_state;

	//Add initial node
	concat_state.push_back(pstates[initial_state_id].state_id);
	dfa_states.push_back(concat_state);

	//Create the deterministic automaton
	FiniteAutomaton *dfa;
	dfa = new FiniteAutomaton;
	//Set initial state
	dfa->add_state(1);
	dfa->set_initial(0);

	//Go over dfa states until no more are added
	for (int i = 0; i < dfa_states.size(); i++)
	{
		for (auto &letter : alphabet)
		{
			//Var to check if one of the states inside this is final
			bool f_state = false;
			//Empty concatenated state id
			concat_state.clear();
			for (auto &cur_state_id : dfa_states[i])
			{
				//Check if this state is final
				if (pstates[cur_state_id].f_state == true)
					f_state = true;
				for (auto &next_state_id : nfa_table[cur_state_id][letter])
				{
					//Add first index, sort the other ones
					if (concat_state.empty())
						concat_state.push_back(next_state_id);
					else
					{
						//Add only once
						if (!binary_search(concat_state.begin(), concat_state.end(), next_state_id))
							concat_state.insert(upper_bound(concat_state.begin(), concat_state.end(), next_state_id), next_state_id);
					}
				}
			}
			//Set if final state
			if (f_state)
				dfa->pstates[i].f_state = f_state;

			//Create necessary tranzition
			if (!concat_state.empty())
			{
				//Add the new state if it doesnt exist
				if (find(dfa_states.begin(), dfa_states.end(), concat_state) == dfa_states.end())
				{
					dfa_states.push_back(concat_state);
					dfa->add_state(1);
				}
				//Create a tranzition from current state to the just found one
				dfa->add_tranzition(i, find(dfa_states.begin(), dfa_states.end(), concat_state) - dfa_states.begin(), letter);

			}
		}
	}

	return dfa;
}

void FiniteAutomaton::display_automaton()
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
			cout << "On letter: " << pstates[i].tranz[j].letter << " go to " << pstates[pstates[i].tranz[j].next_state_id].state_id << endl;
		}
		cout << endl;
	}

}

int FiniteAutomaton::initialize()
{
	if (!pstates.empty())
	{
		cout << "Machine already initialized!";
		return -1;
	}

	int x;

	//Read the number of states and allocate them
	cout << "Number of states: ";
	cin >> x;
	add_state(x);

	//Set initial state
	
	cout << "Starea initiala (0-" << nr_states - 1 << "): ";
	cin >> x;
	set_initial(x);

	//Final states
	cout << "Number of final states: ";
	cin >> x;
	for (int i = 0; i < x; i++)
	{
		toggle_final();
	}

	//Tranzitions
	cout << "Number of tranzitions: ";
	cin >> x;
	cout << "Tranzitii 'stare 1' 'stare 2' 'litera'\n";

	for (int i = 0; i < x; i++)
	{
		int s1, s2;
		char l;
		cin >> s1 >> s2 >> l;
		add_tranzition(s1,s2,l);
	}
	return 0;
}

void FiniteAutomaton::display_alphabet(void)
{

	cout<< "Used alphabet: ";
	for (const auto &x : alphabet)
	{
		cout << x << " ";
	}
	cout << endl;
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
	state *cur_state = &pstates[cwp.cur_state_id];
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
			cwp.cur_state_id = cur_state->tranz[i].next_state_id;
			cwp.wpoz = wpoz + 1;
			q.push(cwp);
		}
	}

	//Cicle until queue is empty
	return priv_check_word(word);
}

bool FiniteAutomaton::tranz_sort(tranzition a, tranzition b)
{
	if (a.letter == b.letter)
		return a.next_state_id < b.next_state_id;

	return (a.letter < b.letter);
}

void FiniteAutomaton::set_initial(int val)
{
	//Check if state exists
	if (val < 0 || val >= nr_states)
		exit(-1);

	initial_state_id = val;
}

void FiniteAutomaton::toggle_final()
{
	int fs;
	cin >> fs;
	if (fs >= 0 && fs < nr_states)
		pstates[fs].f_state = !pstates[fs].f_state;
}

