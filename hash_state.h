#ifndef _HASH_STATE
#define _HASH_STATE

#include <tuple>
#include <cstdio>

class hash_state
{
    long long board;
    int head_i,head_j;
    int apple_i,apple_j;
public:
    bool operator == (const hash_state &cp) const;
    hash_state (long long board,int h_i,int h_j,int a_i,int a_j);
    hash_state ();
    std::size_t operator () (const std::pair<hash_state,int> &cp) const;
    void init_from (FILE *f);
    void save_to (FILE *f) const;
};

#endif // _HASH_STATE
