//
// Created by Raffi Alan Bezirjian on 2020-10-16.
//

#pragma once
#include "Map.h"
#include <iostream>
using namespace graph;
using namespace std;

/*///////////////////////////////////////////////////
//--------------Load Map from file ----------------//
//Load Continent ,Countries, and their link infos  //
///////////////////////////////////////////////////*/

class MapLoader
{
    static int m_read_state;    //stream reading state
/*
	read all file data into a buffer;
	returns buffer pointer;
*/

    static char* read_file(char* file_name, size_t* bufsize);

/*
* read line from buffer;
* returns new line pointer;
*/

    static char* read_line(char** line_start);
	
    /*get atom from line*/
    static char* get_atom(char** str);
    /*check line header and change read state*/
    static bool	 check_read_state(char* line_start);

    /*read Map from file*/
    static Map* load_map_d(char* file_name);

    /*input file name*/
    char *m_file_name;

public:

    // Default Constructor
    MapLoader();
	
    //Constructor to read a domination file
    MapLoader(char* fileName);
	
    //Copy constructor
    MapLoader(MapLoader&);

    //Destructor
    ~MapLoader();

    //Assignment operator
    MapLoader& operator=(const MapLoader&);

    // Loading input file
    Map* load();

    // Insertion stream
    friend ostream& operator<<(ostream&, const MapLoader&);

};

