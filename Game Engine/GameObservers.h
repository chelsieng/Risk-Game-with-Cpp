
#pragma once

#include <iostream>

using namespace std;

class GameEngine;

class Observer {
public:
    // pure virtual function
    virtual void update() = 0;
};


class PhaseObserver : public Observer {
private:
    GameEngine* subject;

public:
    PhaseObserver(GameEngine* subject);
    ~PhaseObserver();

    virtual void update();
};

class StatisticsObserver : public Observer {
private:
    GameEngine* subject;

public:
    StatisticsObserver(GameEngine* subject);
    ~StatisticsObserver();


    virtual void update();

};

class Subject {
private:
    // subscribers to the subject
    vector<Observer*> observers;
public:
    virtual void attach(Observer* o);
    virtual void detach(Observer* o);
    virtual void notify();
};



