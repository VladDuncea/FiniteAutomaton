#pragma once
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <queue>
#include <vector>
#include <map>
#include <iterator>

using namespace std;



class FiniteAutomaton
{
	struct tranzition
	{
		int next_state_id;
		char letter;
	};
	struct state
	{
		int state_id;

		vector<tranzition> tranz;
		int nr_tranz;
		bool f_state;
	};
	struct check_word_params
	{
		int cur_state_id;
		int wpoz;
	};

	vector<state> pstates;
	state *initial;
	int nr_states, spacing;
	queue<check_word_params> q;
	vector<char> alphabet;
	bool priv_check_word(char *);
	static bool tranz_sort(tranzition, tranzition);

public:
	FiniteAutomaton()
	{
		initial = NULL;
		spacing = 0;
	}
	~FiniteAutomaton() {
		//if (pstates != NULL)
			//delete[] pstates;
	}

	void set_initial(void);
	void toggle_final(void);
	void add_tranzition(void);
	void add_state(int nr_states);
	void del_tranzition(){}
	int initialize(void);
	void display_alphabet(void);
	void display_automaton(void);
	bool check_word(char * word);
	bool check_nedet(void);
	FiniteAutomaton * export_DFA(void);
};

