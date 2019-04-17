#pragma once
class Automaton
{

public:
	Automaton();
	virtual ~Automaton();

	virtual void set_initial(int state)=0;
	virtual void toggle_final(int state, bool val) = 0;
	virtual void add_state(int nr_states)=0;
	virtual void del_tranzition(void)=0;
	virtual int initialize(void)=0;
	virtual void display_alphabet(void)=0;
	virtual void display_automaton(void)=0;
	virtual bool check_word(char * word)=0;
	virtual bool check_nedet(void)=0;
};

