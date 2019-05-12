#pragma once
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <queue>
#include <vector>
#include <map>
#include <iterator>
#include <stack>
#include "Automaton.h"

#define LAMBDA  '~'

using namespace std;

//Data types
typedef struct
{
	int next_state_id;
	char letter, stackTop;
	string stackAdd;
}tranzition;
typedef struct
{
	int state_id;

	vector<tranzition> tranz;
	int nr_tranz;
	bool f_state;
}state;
typedef struct check_word_params
{
	int cur_state_id;
	int wpoz;
	stack<char> s;
};

class PushdownAutomaton : public Automaton
{
	//Private variables
	vector<state> pstates;
	int initial_state_id;
	int nr_states, spacing;
	queue<check_word_params> q;
	vector<char> alphabet;

	//Private functions
	bool privCheckWord(char *word);
	static bool tranz_sort(tranzition a, tranzition b);

public:
	PushdownAutomaton();
	~PushdownAutomaton();

	void set_initial(int val);
	void toggle_final(int state, bool val);
	void add_tranzition(int from, int to, char letter,char topStack,string stackAdd);
	void add_state(int nr_states);
	void del_tranzition() {};
	int initialize(void);
	void display_alphabet(void);
	void display_automaton(void);
	//TODO
	bool check_word(char * word);
	bool check_nedet(void);
	
};

