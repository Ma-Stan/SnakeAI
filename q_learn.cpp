#include "q_learn.h"
#include <algorithm>

map <pair <state,int>,int> Q_val;

int get_Q_val(state x,int mov)
{
    auto it=Q_val.find(std::make_pair(x,mov));
    if (it==Q_val.end())
    {
        Q_val[std::make_pair(x,mov)]=0;
        return 0;
    }
    else
        return it->second;
}

int propose_move(state cur)
{
    int val=rand()&127;
    if (val<10)
    {
        int pick=rand()&3;
        if (get_Q_val(cur,pick)<0)
        {
            val=rand()&127;
            if (val<3)
                return rand()&3;
            else
                goto safe;
        }
        return rand()&3;
    }
    else
    {
        safe:
        int mov,val;
        mov=0;
        val=get_Q_val(cur,0);
        for (int i=1; i<4; i++)
        {
            int nv=get_Q_val(cur,i);
            if (nv>val)
            {
                val=nv;
                mov=i;
            }
        }
        return mov;
    }
}


void play_game(int rate,int show)
{
    state cur(vector <pair <int,int> > {{1,2},{1,1}});
    int alive=1;
    while (alive)
    {
        int op=propose_move(cur);
        state nxt=cur;
        int code=nxt.make_move(op);
        int reward;
        if (code==0)
            reward=-1;
        else
            if (code==1)
                reward=200;
            else
                if (code<0)
                {
                    alive=0;
                    reward=-10;
                }
                else
                {
                    alive=0;
                    if (code==2)
                        reward=150;
                    else
                        reward=500;
                }
        reward*=100;
        int mxnxt=get_Q_val(nxt,0);
        for (int i=1; i<4; i++)
            mxnxt=max(mxnxt,get_Q_val(nxt,i));
        Q_val[std::make_pair(cur,op)]=((100-rate)*get_Q_val(cur,op)+rate*(reward+90*(alive?mxnxt:-3)/100))/100;
        if (show)
        {
            for (int i=0; i<4; i++)
                printf("[%d] ",get_Q_val(cur,i));
            printf("%d %d %d\n",op,reward,Q_val.size());
            cur.show();
        }
        cur=nxt;
    }
}
