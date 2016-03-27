#include "hash_state.h"
#define INT64SPECIFIER "%I64d "

hash_state :: hash_state (long long brd,int h_i,int h_j,int a_i,int a_j)
{
    board=brd;
    head_i=h_i;
    head_j=h_j;
    apple_i=a_i;
    apple_j=a_j;
}

hash_state :: hash_state ()
{
}

bool hash_state :: operator == (hash_state const &cp) const
{
    return std::make_tuple(board,head_i,head_j,apple_i,apple_j)==std::make_tuple(cp.board,cp.head_i,cp.head_j,cp.apple_i,cp.apple_j);
}
inline size_t hh (int val,int id)
{
    return (std::hash <int> ()(val))<<id;
}

size_t hash_state :: operator () (const std::pair <hash_state,int> &cp) const
{
    return (std::hash <long long> ()(cp.first.board))^hh(cp.first.head_i,1)^hh(cp.first.head_j,2)^hh(cp.first.apple_i,3)^hh(cp.first.apple_j,4);
}

void hash_state :: save_to (FILE *f) const
{
    fprintf(f,INT64SPECIFIER,board);
    fprintf(f,"%d %d %d %d ",head_i,head_j,apple_i,apple_j);
}

void hash_state :: init_from (FILE *f)
{
    fscanf(f,INT64SPECIFIER,&board);
    fscanf(f,"%d %d %d %d",&head_i,&head_j,&apple_i,&apple_j);
}


