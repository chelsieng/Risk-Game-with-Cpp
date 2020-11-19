
#pragma once

#include <iostream>

using namespace std;

class GameEngine;

class Observer {
public:
    Observer();
    ~Observer();
    // pure virtual function
    virtual void update() = 0;
};


class PhaseObserver : public Observer {
private:
    GameEngine* subject;

public:
    explicit PhaseObserver(GameEngine* subject);
    ~PhaseObserver();
    PhaseObserver(const PhaseObserver *phaseObserver);
    PhaseObserver& operator=(const PhaseObserver &p);
    virtual void update();
    void showInfo();

    friend ostream& operator << (ostream& ostream, const PhaseObserver &phaseObserver);
};

class StatisticsObserver : public Observer {
private:
    GameEngine* subject;

public:
    explicit StatisticsObserver(GameEngine* subject);
    ~StatisticsObserver();
    StatisticsObserver(const StatisticsObserver *StatisticsObserver);
    StatisticsObserver& operator=(const StatisticsObserver &s);
    virtual void update();
    void showInfo();

    friend ostream& operator << (ostream& ostream, const StatisticsObserver &statisticsObserver);

};

class Subject {
private:
    // subscribers to the subject
    vector<Observer*> observers;
public:
    Subject();
    ~Subject();
    Subject(const Subject &subject);
    Subject& operator=(const Subject &s);
    virtual void attach(Observer* o);
    virtual void detach(Observer* o);
    virtual void notify();

    friend ostream& operator << (ostream& ostream, const Subject &subject);
};


