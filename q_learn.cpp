#include "q_learn.h"
#include <algorithm>

unordered_map <pair <hash_state,int>,int,hash_state> Q_val;

int get_Q_val(hash_state x,int mov)
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

int propose_move(hash_state cur)
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
        int op=propose_move(cur.to_hash());
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
        hash_state nxt_hsh=nxt.to_hash();
        int mxnxt=get_Q_val(nxt_hsh,0);
        for (int i=1; i<4; i++)
            mxnxt=max(mxnxt,get_Q_val(nxt_hsh,i));
        hash_state cur_hsh=cur.to_hash();
        Q_val[std::make_pair(cur_hsh,op)]=((100-rate)*get_Q_val(cur_hsh,op)+rate*(reward+90*(alive?mxnxt:-3)/100))/100;
        if (show)
        {
            for (int i=0; i<4; i++)
                printf("[%d] ",get_Q_val(cur_hsh,i));
            printf("%d %d %d\n",op,reward,Q_val.size());
            cur.show();
        }
        cur=nxt;
    }
}

void load_from(string f)
{
    Q_val.clear();
    FILE *fl=fopen(f.c_str(),"r");
    int n;
    fscanf(fl,"%d",&n);
    int mov;
    int val;
    hash_state sta;
    while (n--)
    {
        sta.init_from(fl);
        fscanf(fl,"%d",&mov);
        fscanf(fl,"%d",&val);
        Q_val[make_pair(sta,mov)]=val;
    }
    fclose(fl);
}

void store_to(string f)
{
    FILE *fl=fopen(f.c_str(),"w");
    fprintf(fl,"%d\n",Q_val.size());
    for (auto it:Q_val)
    {
        it.first.first.save_to(fl);
        fprintf(fl,"%d ",it.first.second);
        fprintf(fl,"%d ",it.second);
        fprintf(fl,"\n");
    }
}
