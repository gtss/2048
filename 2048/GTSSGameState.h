//
//  GTSSGameState.h
//  2048
//
//  Created by yourname on 14-3-28.
//  Copyright (c) 2014年 gtss. All rights reserved.
//

#define GSize 4

struct Position {
    int x;
    int y;
};

struct GameState {
    int state[GSize][GSize];
};


