#ifndef _STATE_H
#define _STATE_H

#define HEIGHT (4)
#define WIDTH (4)
#define WARPING (false)
#include <vector>
#include "hash_state.h"

using namespace std;

class state
{
    int move_dif[4][2]=
    {
        { 0,-1},
        {-1, 0},
        { 0, 1},
        { 1, 0}
    };
    int base[HEIGHT][WIDTH];
    int offset;
    int length;
    int head_i,head_j;
    int apple_i,apple_j;
    int tail_i,tail_j;
public:
    long long board_hash;

    int gen_apple(void); //attempts to place an apple in a random place
    void clear_offset();

public :
    int make_move(int dir); //makes a move in a direction
    //(left, up, right, down)
    void show (void);
    state (void);
    //bool operator < (const state &cp) const;
    state (std::vector <pair <int,int> > val);

    hash_state to_hash();

};

#endif // _STATE_H
