#pragma once
#ifndef A1_MAP_H
#define A1_MAP_H

#include <vector>
#include <string>
#include "../Part 4/Player.h"
#include <map>

using namespace std;

class Map {
public:
    class Army {
    private:
        int *id = new int(0);
        Player *owner;

    public:
        Army(Player *); //Army constructor for player

        int getId() const;

        void print() const;
    };

    class Territory {
    private:
        static int counter;
        int *id = new int(0);
        Player *owner;
        vector<Army *> *armies;

    public:
        Territory(); // Default Territory constructor with no armies present
        Territory(Player *); // Constructor for 1 player starting with 5 armies

        int getId() const;

        void print() const;
    };

};


#endif //A1_MAP_H
