#include <string>
#include "MapLoader.h"
#include "Map.h"

using namespace std;

int main() {

    MapLoader* m = new MapLoader("swiss.map");
    MapLoader* m2 = new MapLoader("mexico.map");
    MapLoader* m3 = new MapLoader("artic.map");
    MapLoader* m4 = new MapLoader("northern-europe.map");
    MapLoader* m5 = new MapLoader("newworld.map");

    m->loadMap("/Users/jacobguirguis/Documents/Concordia/7_Fall_2020/COMP_345/Project/COMP-345/Part 2/swiss.map")->validate();
    m2->loadMap("/Users/jacobguirguis/Documents/Concordia/7_Fall_2020/COMP_345/Project/COMP-345/Part 2/mexico.map")->validate();
    m3->loadMap("/Users/jacobguirguis/Documents/Concordia/7_Fall_2020/COMP_345/Project/COMP-345/Part 2/artic.map")->validate();
    m4->loadMap("/Users/jacobguirguis/Documents/Concordia/7_Fall_2020/COMP_345/Project/COMP-345/Part 2/northern-europe.map")->validate();
}