//
//  GameState.c
//  2048
//
//  Created by yourname on 14-3-28.
//  Copyright (c) 2014年 gtss. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "GTSSGameState.h"

struct GameState * up(struct GameState *gs){
    for (int y=0; y<GSize; ++y) {
        for (int x=0,prev=-1,prevValue=-1,merged = 0; x<GSize; ++x) {
            if(gs->state[x][y] == 0){
                continue;
            }
            if(!merged && prevValue == gs->state[x][y]){
                prevValue *= 2;
                printf("%i\n",prevValue);
                gs->state[prev][y] = prevValue;
                gs->state[x][y] = 0;
                merged = 1;
                continue;
            }
            prevValue = gs->state[x][y];
            if(++prev != x){
                gs->state[prev][y]=prevValue;
                gs->state[x][y] = 0;
            }
            merged = 0;
        }
    }
    
    return gs;
}

struct GameState * down(struct GameState *gs){
    for (int y=GSize-1; y>=0; --y) {
        for (int x=GSize-1,prev=GSize,prevValue=-1,merged = 0; x>=0; --x) {
            if(gs->state[x][y] == 0){
                continue;
            }
            if(!merged && prevValue == gs->state[x][y]){
                prevValue *= 2;
                printf("%i\n",prevValue);

                gs->state[prev][y] = prevValue;
                gs->state[x][y] = 0;
                merged = 1;
                continue;
            }
            prevValue = gs->state[x][y];
            if(--prev != x){
                gs->state[prev][y]=prevValue;
                gs->state[x][y] = 0;
            }
            merged = 0;
        }
    }

    return gs;
}

struct GameState * left(struct GameState *gs){
    for (int x=0; x<GSize; ++x) {
        for (int y=0,prev=-1,prevValue=-1,merged = 0; y<GSize; ++y) {
            if(gs->state[x][y] == 0){
                continue;
            }
            if(!merged && prevValue == gs->state[x][y]){
                prevValue *= 2;
                printf("%i\n",prevValue);

                gs->state[x][prev] = prevValue;
                gs->state[x][y] = 0;
                merged = 1;
                continue;
            }
            prevValue = gs->state[x][y];
            if(++prev != y){
                gs->state[x][prev]=prevValue;
                gs->state[x][y] = 0;
            }
            merged = 0;
        }
    }

    return gs;
}

struct GameState * right(struct GameState *gs){
    for (int x=GSize-1; x>=0; --x) {
        for (int y=GSize-1,prev=GSize,prevValue=-1,merged = 0; y>=0; --y) {
            if(gs->state[x][y] == 0){
                continue;
            }
            if(!merged && prevValue == gs->state[x][y]){
                prevValue *= 2;
                printf("%i\n",prevValue);

                gs->state[x][prev] = prevValue;
                gs->state[x][y] = 0;
                merged = 1;
                continue;
            }
            prevValue = gs->state[x][y];
            if(--prev != y){
                gs->state[x][prev]=prevValue;
                gs->state[x][y] = 0;
            }
            merged = 0;
        }
    }

    return gs;
}

int nextValue(int randN){
    return randN % 10 != 0 ? 2 : 4;
}

struct GameState * put(struct GameState *gs, struct Position *p, int v){
    gs->state[p->x][p->y]=v;
    return gs;
}

struct GameState * next(struct GameState *gs, int randN1, int randN2){
    static struct Position tmp = {-1,-1};
    struct Position availables[GSize*GSize]={tmp,tmp,tmp,tmp,tmp,tmp,tmp,tmp,tmp,tmp,tmp,tmp,tmp,tmp,tmp,tmp};
    int i=0;
    for (int x=0 ; x< GSize; ++x) {
        for (int y=0;y< GSize;++y){
            if(gs->state[x][y] == 0){
                struct Position a;
                a.x = x;
                a.y = y;
                availables[i++] = a;
            }
        }
    }
    return put(gs, &availables[randN1 % i], nextValue(randN2));
}

void printGameState(struct GameState *gs){
    for (int x=0 ; x< GSize; ++x) {
        for (int y=0;y< GSize;++y){
            printf("%i ",gs->state[x][y]);
        }
        printf("\n");
    }
}

int main2(int argc, char * argv[]){
    struct GameState gs;
    for (int x=0 ; x< GSize; ++x) {
        for (int y=0;y< GSize;++y){
            gs.state[x][y] = 0;
        }
    }
    printGameState(next(next(&gs, rand(), rand()),rand(),rand()));
    int c;
    while ((c = getchar()) != EOF){
        switch (c) {
            case 'w':
                printGameState(next(up(&gs),rand(),rand()));
                break;
                
            case 's':
                printGameState(next(down(&gs),rand(),rand()));
                break;
            
            case 'a':
                printGameState(next(left(&gs),rand(),rand()));
                break;
                
            case 'd':
                printGameState(next(right(&gs),rand(),rand()));
                break;
        }
    }
    return 0;
}