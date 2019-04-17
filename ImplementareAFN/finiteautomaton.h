#pragma once
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <queue>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include "Automaton.h"

using namespace std;



class FiniteAutomaton : public Automaton
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
	int initial_state_id;
	int nr_states, spacing;
	queue<check_word_params> q;
	vector<char> alphabet;

	bool priv_check_word(char *);
	static bool tranz_sort(tranzition, tranzition);

public:
	FiniteAutomaton()
	{
		initial_state_id =0;
		spacing = 0;
		nr_states = 0;
	}
	
	~FiniteAutomaton();

	void set_initial(int state);
	void toggle_final(int state,bool val);
	void add_tranzition(int,int,char);
	void add_state(int nr_states);
	void del_tranzition(){}
	int initialize(void);
	void display_alphabet(void);
	void display_automaton(void);
	bool check_word(char * word);
	bool check_nedet(void);
	FiniteAutomaton * export_DFA(void);
};

