#include "state.h"
#include "q_learn.h"
#include <cstdio>
#include <map>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstring>

int main()
{
    char op[20];
    srand(1337);
    state cur(vector <pair <int,int> > {{1,2},{1,1}});
    while (1)
    {
        scanf("%s",op);
        if (strcmp(op,"exit")==0)
            return 0;
        if (strcmp(op,"play")==0)
        {
            int num,rt,shw;
            scanf("%d%d%d",&num,&rt,&shw);
            for (int i=1; i<=num; i++)
            {
                play_game(rt,shw);
                if (i%10000==0)
                    printf("%d/%d [%d]\n",i,num,Q_val.size());
            }
            printf("Done!\n");
        }
        if (strcmp(op,"load")==0)
        {
            char file[50];
            scanf("%s",file);
            load_from(string(file));
            printf("Done!\n");
        }
        if (strcmp(op,"save")==0)
        {
            char file[50];
            scanf("%s",file);
            store_to(string(file));
            printf("Done!\n");
        }
    }
}
