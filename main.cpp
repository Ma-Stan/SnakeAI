#include "state.h"
#include "q_learn.h"
#include <cstdio>
#include <map>
#include <vector>
#include <ctime>
#include <algorithm>

//std::map <std::pair <state,int>,int> Q_val;

int fn(vector <int> val)
{
    return 0;

}

int main()
{
    state cur(vector <pair <int,int> > {{1,2},{1,1}});
    srand(time(0));
    while (1)
    {
        int num,rt,shw;
        scanf("%d%d%d",&num,&rt,&shw);
        for (int i=0; i<num; i++)
        {
            play_game(rt,shw);
            if (i%10000==0)
                printf("DONE %d\n",i);
        }
    }
}
