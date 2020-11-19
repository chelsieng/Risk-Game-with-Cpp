
#include <vector>
#include "GameEngine.h"
#include "GameObservers.h"

using namespace std;

Observer::Observer() {

}

// Destructor
Observer::~Observer() {

}

// ====================================== Phase Observer =======================================

// Constructor
PhaseObserver::PhaseObserver(GameEngine *subject) {
    subject->attach(this);
    this->subject = subject;
}

// Destructor
PhaseObserver::~PhaseObserver() {
    subject->detach(this);
    delete this->subject;
    this->subject = nullptr;
}

// Copy Constructor
PhaseObserver::PhaseObserver(const PhaseObserver *p) {
    delete this->subject;
    this->subject = nullptr;
    this->subject = new GameEngine(*p->subject);
}

// Assignment Operator
PhaseObserver& PhaseObserver::operator=(const PhaseObserver& p) {
    if (this == &p) {
        return *this;
    }

    delete this->subject;
    this->subject = nullptr;
    this->subject = new GameEngine(*p.subject);

    return *this;
}

// Insertion stream operator
std::ostream &operator<<(ostream &out, const PhaseObserver &phaseObserver) {
    return out << "Phase Observer" << endl;
}

// ====================================== Statistics Observer =======================================

// Constructor
StatisticsObserver::StatisticsObserver(GameEngine *subject) {
    subject->attach(this);
    this->subject = subject;
}

// Destructor
StatisticsObserver::~StatisticsObserver() {
    subject->detach(this);
    delete this->subject;
    this->subject = nullptr;
}

// Copy Constructor
StatisticsObserver::StatisticsObserver(const StatisticsObserver *s) {
    delete this->subject;
    this->subject = nullptr;
    this->subject = new GameEngine(*s->subject);
}

// Assignment Operator
StatisticsObserver& StatisticsObserver::operator=(const StatisticsObserver& s) {
    if (this == &s) {
        return *this;
    }

    delete this->subject;
    this->subject = nullptr;
    this->subject = new GameEngine(*s.subject);

    return *this;
}

// Insertion stream operator
std::ostream &operator<<(ostream &out, const StatisticsObserver &statisticsObserver) {
    return out << "Statistics Observer" << endl;
}

// ====================================== Subject Observer =======================================

Subject::Subject() {}

// Destructor
Subject::~Subject() {
    for (Observer *o : this->observers) {
        delete o;
        o = nullptr;
    }
}

// Copy Constructor
Subject::Subject(const Subject &subject) {
    for (auto *o : this->observers) {
        delete o;
        o = nullptr;
    }

    for (auto o : subject.observers) {
        this->observers.push_back(o);
    }
}

// Assignment Operator
Subject& Subject::operator=(const Subject& subject) {
    // Checking for self assignment
    if (this == &subject) {
        return *this;
    }

    for (auto *o : this->observers) {
        delete o;
        o = nullptr;
    }

    for (auto *o : subject.observers) {
        this->observers.push_back(o);
    }
    return *this;
}

// Insertion stream operator
std::ostream &operator<<(ostream &out, const Subject &subject) {
    return out << "This Subject has " << subject.observers.size() << " observers subscribed" << endl;
}

// ------------------------------------------------------ PATTERN METHODS --------------------------------

// subscribe to subject
void Subject::attach(Observer *o) {
    this->observers.push_back(o);
}

// unsubscribe
void Subject::detach(Observer *o) {
    int counter = 0;
    for (int i = 0; i < this->observers.size(); i++) {
        if (o == this->observers[i]){
            break;
        }
        counter++;
    }
    this->observers.erase(this->observers.begin() + counter);
}

// notify all observers
void Subject::notify() {
    for (Observer* o : this->observers) {
        o->update();
    }
}

void StatisticsObserver::update() {
    showInfo();
}

void StatisticsObserver::showInfo() {
    string currPhase = subject->getPhase();

    if (currPhase == "Statistics") {
        map<int, int> hash = {};
        int total = 0;
        cout << "Let's see everyone's current standings:" << endl;
        cout << "" << endl;
        cout << "|---------------------------------------------------------------|" << endl;
        cout << "|    Player   |    Percent of Map Owned   |   Number of Cards   |" << endl;

        for (auto t : *subject->getMap()->getTerritories()) {
            total++;
            hash[t->getOwner()->getId()]++;
        }
        for (Player *p : *subject->getTotalPlayers()) {
            cout << "|---------------------------------------------------------------|" << endl;
            cout << "|      " << p->getId() << "      |             " << ((double)hash[p->getId()] / (double)total ) * 100 << "            |          " << p->getHand()->getSize() << "          |" << endl;
        }
            cout << "|---------------------------------------------------------------|" << endl;
        cout << endl;
    }

    if (currPhase == "Conquered") {
        cout << "********************UPDATE : Territory Conquered********************" << endl;
        cout << "Player " << subject->getPlayerTurn() << " conquered territory " << subject->getConqTerr() << endl;
        cout << "********************************************************************" << endl;
    }

    if (currPhase == "Player Eliminated") {
        cout << "********************UPDATE : Player Eliminated********************" << endl;
        cout << "Player " << subject->getEliminatedPLayer() << " owns no territories - they have been removed from the game!" << endl;
        cout << "******************************************************************" << endl;
    }
    if (currPhase == "Game Over") {
        cout << endl;
        cout << endl;
        cout << "\t \t Game Over" << endl;
        cout << "*****************************************************" << endl;
        cout << "*****************************************************" << endl;
        cout << "** Congratulations Player " << subject->getPlayerTurn() << ", you've won the game! **" << endl;
        cout << "*****************************************************" << endl;
        cout << "*****************************************************" << endl;
        cout << endl;
    }
}

void PhaseObserver::update() {
    showInfo();
}

void PhaseObserver::showInfo() {
    string currentPhase = subject->getPhase();

    if (currentPhase == "Map Selection") {
        // Displaying welcome message
        cout << endl;
        cout << "==========================================================" << endl;
        cout << ">>>>>>>>>>>>>>>>>>>>MAP SELECTION PHASE<<<<<<<<<<<<<<<<<<<" << endl;
        cout << "==========================================================" << endl;
        cout << endl;
    }
    if (currentPhase == "Player and Deck Creation") {
        cout << endl;
        cout << "==========================================================" << endl;
        cout << ">>>>>>>>>>>>>>PLAYER AND DECK CREATION PHASE<<<<<<<<<<<<<<" << endl;
        cout << "==========================================================" << endl;
        cout << endl;
    }
    if (currentPhase == "Startup Phase") {
        cout << endl;
        cout << "==========================================================" << endl;
        cout << ">>>>>>>>>>>>>>>>>>>>>>STARTUP PHASE<<<<<<<<<<<<<<<<<<<<<<<" << endl;
        cout << "==========================================================" << endl;
    }
    if (currentPhase == "Reinforcement Phase") {
        cout << endl;
        cout << "==========================================================" << endl;
        cout << ">>>>>>>>>>>>>>>>>>>>>REINFORCEMENT PHASE<<<<<<<<<<<<<<<<<<" << endl;
        cout << "==========================================================" << endl;
    }
    if (currentPhase == "Player Reinforcement") {
        cout << endl;
        cout << "----------------------------------------------------------" << endl;
        cout << "-------------------Player " << subject->getPlayerTurn() << ": Reinforcement----------------" << endl;
        cout << "----------------------------------------------------------" << endl;
        cout << endl;
    }
    if (currentPhase == "Order Issuing Phase") {
        cout << endl;
        cout << endl;
        cout << "==========================================================" << endl;
        cout << ">>>>>>>>>>>>>>>>>>>>>ORDER ISSUING PHASE<<<<<<<<<<<<<<<<<<" << endl;
        cout << "==========================================================" << endl;
    }
    if (currentPhase == "Player Issuing") {
        cout << endl;
        cout << "----------------------------------------------------------" << endl;
        cout << "--------------Player " << subject->getPlayerTurn() << ": ORDER ISSUING PHASE---------------" << endl;
        cout << "----------------------------------------------------------" << endl;
    }
    if (currentPhase == "Order Execution Phase") {
        cout << endl;
        cout << endl;
        cout << "==========================================================" << endl;
        cout << ">>>>>>>>>>>>>>>>>>>>>ORDER EXECUTION PHASE<<<<<<<<<<<<<<<<" << endl;
        cout << "==========================================================" << endl;
        cout << endl;
    }
    if (currentPhase == "Player Execution") {
        cout << "----------------------------------------------------------" << endl;
        cout << "---------------Player " << subject->getPlayerTurn() << ": ORDER EXECUTION PHASE------------" << endl;
        cout << "----------------------------------------------------------" << endl;
    }
}
