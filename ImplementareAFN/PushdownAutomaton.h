#pragma once
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <queue>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

class PushdownAutomaton
{
	struct tranzition
	{
		int next_state_id;
		char letter,stackTop;
		vector<char> stackAdd;
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

public:
	PushdownAutomaton();
	~PushdownAutomaton();
};

