#ifndef _Q_LEARN
#define _Q_LEARN
#include "hash_state.h"
#include "state.h"
#include <map>
#include <unordered_map>

void play_game(int rate,int show);

void load_from(string f);
void store_to(string f);

extern unordered_map <pair <hash_state,int>,int,hash_state> Q_val;


#endif // _Q_LEARN
