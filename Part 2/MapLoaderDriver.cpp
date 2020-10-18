//
// Created by Raffi Alan Bezirjian on 2020-10-16.
//

#include <string>
#include "MapLoader.h"
#include "Map.h"

using namespace std;

int main() {



    MapLoader* m = new MapLoader("../artic.map");
    //MapLoader* m2 = new MapLoader("../mexico.map");
    // MapLoader* m3 = new MapLoader("../swiss.map");
    // MapLoader* m4 = new MapLoader("../northern-europe.map");
    //MapLoader* m5 = new MapLoader("../canada.map");

    cout << *m << *(m->load());

    return 0;



/*Testing Invalid Mexico Maps*/

/**


     int k;
    vector<string> file_vec = {"../mexico_err1.map", "../mexico_err2.map"};


    for(auto file_name:file_vec)
    {
        MapLoader* m = new MapLoader(file_name);


        cout<<"\nReading map file :" <<*m <<endl;

        Map* map = m->load();

        if(map)
        {
            cout <<  "Writing map data" <<endl;
            cout << *map;
        }
        else{
            cout <<  "Error: Cannot Read Map File" <<endl;
        }

    }

    return 0;


*/

}
