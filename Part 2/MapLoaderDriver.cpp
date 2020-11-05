#include <string>
#include "MapLoader.h"

using namespace std;

int main() {

    auto* m = new MapLoader("../part 2/mexico.map");
    auto* m1 = new MapLoader("../part 2/artic.map");
    auto* m2 = new MapLoader("../part 2/northern-europe.map");
    auto* m3 = new MapLoader("../part 2/swiss.map");

    if (m->getMap()->validate()) {
        cout << "PASS : " << m->getMapName() << " is a valid map" << endl;
    } else {
        cout << "FAIL : " << m->getMapName() << " is NOT a valid map" << endl;
    }

    cout << endl;

    if (m1->getMap()->validate()) {
        cout << "PASS : " << m1->getMapName() << " is a valid map" << endl;
    } else {
        cout << "FAIL : " << m1->getMapName() << " is NOT a valid map" << endl;
    }

    cout << endl;

    if (m2->getMap()->validate()) {
        cout << "PASS : " << m2->getMapName() << " is a valid map" << endl;
    } else {
        cout << "FAIL : " << m2->getMapName() << " is NOT a valid map" << endl;
    }

    cout << endl;

    if (m3->getMap()->validate()) {
        cout << "PASS : " << m3->getMapName() << " is a valid map" << endl;
    } else {
        cout << "FAIL : " << m3->getMapName() << " is NOT a valid map" << endl;
    }
}