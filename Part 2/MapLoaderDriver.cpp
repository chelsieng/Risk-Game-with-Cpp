#include <string>
#include "MapLoader.h"
#include "../Part 1/Map.h"

using namespace std;

int main() {

    MapLoader* m = new MapLoader("swiss.map");
    MapLoader* m2 = new MapLoader("mexico.map");
    MapLoader* m3 = new MapLoader("artic.map");
    MapLoader* m4 = new MapLoader("northern-europe.map");

    if(m->loadMap("../Part 2/swiss.map")->validate()){
        cout << "swiss passed" <<endl;
    }else{
        cout << "swiss fail" <<endl;
    }
    if(m2->loadMap("../Part 2/mexico.map")->validate()){
        cout << "mexico passed"<<endl;
    }else{
        cout << "mexico failed" <<endl;
    }
    if (m3->loadMap("../Part 2/artic.map")->validate()){
        cout << "artic passed" <<endl;
    }else{
        cout << "artic failed" <<endl;
    }
    if(m4->loadMap("../Part 2/northern-europe.map")->validate()){
        cout << "north europe passed" <<endl;
    }else{
        cout << "north europe failed" <<endl;
    }
}