#include "state.h"
#include <vector>
#include <algorithm>

/*
bool state :: operator < (const state &cp) const
{
    auto tup1=make_tuple(length,head_i,head_j,apple_i,apple_j);
    auto tup2=make_tuple(cp.length,cp.head_i,cp.head_j,cp.apple_i,cp.apple_j);
    if (tup1!=tup2)
        return tup1<tup2;
    for (int i=0; i<HEIGHT; i++)
        for (int j=0; j<WIDTH; j++)
            if ((base[i][j]!=0)!=(cp.base[i][j]!=0))
                return (base[i][j]!=0)<(cp.base[i][j]!=0);
    return 0;
}
*/


hash_state state :: to_hash()
{
    long long brd=0;
    for (int i=0; i<HEIGHT; i++)
        for (int j=0; j<WIDTH; j++)
            if (base[i][j])
                brd|=1ll<<(i*WIDTH+j);
    return hash_state(brd,head_i,head_j,apple_i,apple_j);
}

int state ::  gen_apple ()
{
    std::vector <std::pair <int,int> > avl;
    for (int i=0; i<HEIGHT; i++)
        for (int j=0; j<WIDTH; j++)
            if (base[i][j]==0)
                avl.push_back(std::make_pair(i,j));
    if (avl.empty())
    {
        apple_i=-1;
        apple_j=-1;
        return 0;
    }
    std::random_shuffle(avl.begin(),avl.end());
    apple_i=avl[0].first;
    apple_j=avl[0].second;
    return 1;
}

int state :: make_move(int dir)
{
    int nxt_i,nxt_j;
    nxt_i=head_i+move_dif[dir][0];
    nxt_j=head_j+move_dif[dir][1];
    if (WARPING)
    {
        if (nxt_i<0)
            nxt_i+=HEIGHT;
        if (nxt_i>=HEIGHT)
            nxt_i-=HEIGHT;
        if (nxt_j<0)
            nxt_j+=WIDTH;
        if (nxt_j>=WIDTH)
            nxt_j-=WIDTH;
    }
    if (nxt_i<0 || nxt_i>=HEIGHT || nxt_j<0 || nxt_j>=WIDTH)
        return -1;
    if (base[nxt_i][nxt_j]>1)
        return -1;
    int has_eaten;
    if (nxt_i==apple_i && nxt_j==apple_j)
        has_eaten=1;
    else
        has_eaten=0;
    if (has_eaten)
        length++;
    head_i=nxt_i;
    head_j=nxt_j;
    if (!has_eaten)
    {
        for (int i=0; i<HEIGHT; i++)
            for (int j=0; j<WIDTH; j++)
                if (base[i][j]>0)
                    base[i][j]--;
    }
    base[nxt_i][nxt_j]=length;
    if (has_eaten)
    {
        int gend=gen_apple();
        if (gend==0)
        {
            for (int d=0; d<4; d++)
            {
                int x=nxt_i+move_dif[d][0];
                int y=nxt_j+move_dif[d][1];
                if (x>=0 && x<HEIGHT && y>=0 && y<WIDTH)
                    if (base[x][y]==1)
                        return 3;
            }
            return 2;
        }
        else
            return 1;
    }
    else
        return 0;
}

void state :: show ()
{
    for (int i=0; i<HEIGHT; i++)
    {
        for (int j=0; j<WIDTH; j++)
            if (i==apple_i && j==apple_j)
                printf("%3c",'a');
            else
                printf("%3d",base[i][j]);
        printf("\n");
    }
}

state :: state ( std::vector <std::pair <int,int> > l)
{
    for (int i=0; i<HEIGHT; i++)
        for (int j=0; j<WIDTH; j++)
            base[i][j]=0;
    for (int i=0; i<(int)l.size(); i++)
        base[l[i].first][l[i].second]=l.size()-i;
    head_i=l[0].first;
    head_j=l[0].second;
    length=l.size();
    gen_apple();
}
