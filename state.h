#ifndef _STATE_H
#define _STATE_H

#define HEIGHT (4)
#define WIDTH (4)
#define WARPING (false)
#include <vector>

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
    int length;
    int head_i,head_j;
    int apple_i,apple_j;

    int gen_apple(void); //attempts to place an apple in a random place

public :
    int make_move(int dir); //makes a move in a direction
    //(left, up, right, down)
    bool operator < (const state &cp) const;
    void show (void);
    state (void)
    {
    }

    state (std::vector <pair <int,int> > val);

};

#endif // _STATE_H
