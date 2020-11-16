#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#pragma once

#include <iostream>
#include <vector>
#include <time.h>
#include <iomanip>
#include <unistd.h>
#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"


using namespace std;


// this is the GameEngine class, it will have number of players who will have armies. Also, territories assigned to only and only one player.


class GameEngine {
public:

    static void startupPhase(vector<Player *> *, vector<Territory *> *);
    static void reinforcementPhase(vector<Player *> *, vector<Territory *> *, vector<Continent *>);

}
;

#endif




