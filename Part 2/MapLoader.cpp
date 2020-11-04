//
// Created by Raffi Alan Bezirjian on 2020-10-16.
//

#include "MapLoader.h"

#define MAX_BUFFER_SIZE 1000

#define READ_STATE_UNKNOWN		0
#define READ_STATE_FILE			1
#define READ_STATE_CONTINENT	2
#define READ_STATE_COUNTRY		3
#define READ_STATE_BORDER		4

#include <stdio.h>
int MapLoader::m_read_state = READ_STATE_UNKNOWN;

/* This is a function that compares characters of two strings 
This function starts comparing the first character of each string. 
If they are equal to each other, it continues with the following pairs until the characters differ, 
until a terminating null-character is reached, or until num characters match in both strings, whichever happens first.*/

int strncmp(const char* s1, const char* s2, size_t n)
{
    unsigned char a, b;
    const char* last = s1 + n;

    do {
        a = (unsigned char)*s1++;
        b = (unsigned char)*s2++;
    } while (s1 < last && a && a == b);

    return a - b;
}

// Default Constructor
MapLoader::MapLoader()
{
    m_file_name = "";
};

//Constructor to read a domination file
MapLoader::MapLoader(string fileName)
{
    m_file_name = fileName;
}

//Copy constructor
MapLoader::MapLoader(MapLoader& tmp)
{
    m_file_name = tmp.m_file_name;
}

//Destructor
MapLoader::~MapLoader() {

};


//Assignment operator
MapLoader& MapLoader::operator=(const MapLoader& tmp)
{
    if (this != &tmp)
    {
        m_file_name = tmp.m_file_name;
    }
    return *this;
}

Map* MapLoader::load()
{
    return MapLoader::load_map_d(m_file_name);
}

ostream& operator<<(ostream& ostream, const MapLoader& mapLoader)
{
    return (ostream << mapLoader.m_file_name);
}

char* MapLoader::get_atom(char** str)
{
    char* start = *str;
    char* end = *str;
    /*find white space*/
    while (*end != ' ' && *end != '\n' && *end != '\r' && *end != '\0')
    {
        end++;
    }
    *end = '\0';
    *str = end + 1;

    return start;
}


char* MapLoader::read_line(char** p_line_start)
{
    char* line_start = *p_line_start;
    char* line_end;

    /*find the valid first char*/
    while (1) {
        if ((*line_start == '\r') || (*line_start == '\n'))
            ++line_start;
        else if (line_start[0] == '\xef' && line_start[1] == '\xbb' && line_start[2] == '\xbf')
            line_start += 3;         // U+FFFE (BOM)
        else
            break;
    }
    /*find the valid end char*/
    for (line_end = line_start; ((*line_end != '\0') && (*line_end != '\r') && (*line_end != '\n')); ++line_end) {
    };


    if (line_end == line_start)
    {
        return 0;
    }
    if(*line_end != '\0')
    {
        *(line_end++) = '\0';
    }

    *p_line_start = line_start;

    return line_end;
}

bool MapLoader::check_read_state(char* line_start)
{
    /*check the line header*/
    if (!strncmp(line_start, "[files]", 7))
    {

        m_read_state = READ_STATE_FILE;
    }
    else if (!strncmp(line_start, "[continents]", 12))
    {
        m_read_state = READ_STATE_CONTINENT;
    }
    else if (!strncmp(line_start, "[countries]", 11))
    {
        m_read_state = READ_STATE_COUNTRY;
    }
    else if (!strncmp(line_start, "[borders]", 9))
    {
        m_read_state = READ_STATE_BORDER;
    }
    else
    {
        return false;
    }
    return true;
}

char* MapLoader::read_file(char* file_name,size_t* bufsize)
{
    int res;
    long sz;
    long bytes_read;
    char* buf;
    /*create file pointer*/
    FILE* fp;
#ifdef WIN32
    fopen_s(&fp, file_name, "rb");
#else
    fp = fopen(file_name, "rb");
#endif
    if (!fp)
    {
        return 0;
    }
    res = fseek(fp, 0, SEEK_END);
    if (res == -1) {
        fclose(fp);
        return 0;
    }
    /*get file size*/
    sz = ftell(fp);
    rewind(fp);


    buf = sz < SIZE_MAX ? (char*)malloc(sz + 1) : NULL;
    if (!buf)
    {
        fclose(fp);
        return NULL;
    }
    /*read all bytes*/
    bytes_read = 0;
    do {
        res = fread(buf + bytes_read, 1, sz - bytes_read, fp);
        if (res <= 0)
        {	fclose(fp);
            free(buf);
            return 0;
        }
        bytes_read += res;
    } while (sz - bytes_read > 0);

    /*put the ending character*/
    buf[sz] = '\0';
    fclose(fp);

    if (bufsize)
    {
        *bufsize = sz;
    }

    return buf;
}

Map* MapLoader::load_map_d(string file_name)
{

///////read file into buffer////////////////////
    size_t buffer_size = 0;
    char* buffer = read_file((char*)file_name.c_str(), &buffer_size);

    if(buffer == 0)
    {
        return 0;
    }

    m_read_state = READ_STATE_UNKNOWN;

    char* line_start = buffer;
///////////Data from file///////////
    vector<string>	cont_name_vec;
    vector<string>	country_vec;
    vector<int>		cont_id_for_ter_vec;

    vector<vector<int>> ter_id_list_in_cont_vec;
    vector<vector<int>> all_ter_link_info;

///////////Read Buffer to Text/////////////

    while (1)
    {
        /*read line from buffer*/
        char* line_end;
        line_end = read_line(&line_start);
        if(line_end == 0)
        {
            break;
        }
        /*compare line header*/
        if(check_read_state(line_start) == false)
        {
            /*read line data*/
            if (m_read_state == READ_STATE_FILE)
            {
//				continue;
            }
                /*reading continent info*/
            else if (m_read_state == READ_STATE_CONTINENT)
            {
                string str_name = get_atom(&line_start);

                if (str_name.length() > 0)
                {
                    cont_name_vec.push_back(str_name);
                    ter_id_list_in_cont_vec.push_back(vector<int>());
                }
            }
                /*reading county info*/
            else if (m_read_state == READ_STATE_COUNTRY)
            {
                int no;
                string name;
                int cont_id;

                no = atoi(get_atom(&line_start));
                name = get_atom(&line_start);
                cont_id = atoi(get_atom(&line_start));

                country_vec.push_back(string(name));
                ter_id_list_in_cont_vec[cont_id - 1].push_back(no - 1);
                cont_id_for_ter_vec.push_back(cont_id - 1);
            }
                /*reading link info*/
            else if (m_read_state == READ_STATE_BORDER)
            {
                int id;
                all_ter_link_info.push_back(vector<int>());
                while (line_start < line_end - 1)
                {
                    id = atoi(get_atom(&line_start));
                    all_ter_link_info[all_ter_link_info.size() - 1].push_back(id - 1);
                }
            }
        }

        if (*line_end == '\0')
            break;
        line_start = line_end;
    }

    vector<Graph<int>*>* graph_vec = new vector<Graph<int>*>;
    vector<Continent*>* continents = new vector<Continent*>;

/////////////Create All Territories///////////////////
    vector <Territory*> all_ter_vec;
    for (auto country : country_vec)
    {
        all_ter_vec.push_back(new Territory(new string(country)));
    }

/////////// Create All Continents///////////////
    vector< vector<Territory*>*>	ter_list_each_cont_vec;
    int tmp_cont_id = 0;
    for (auto ter_id_vec_in_cont : ter_id_list_in_cont_vec)
    {
        vector<Territory*>* ter_in_cont = new vector<Territory*>();
        Graph<int>* ter_graph = new Graph<int>;

        /*create territories graphs in the same continent*/
        for (auto cur_ter_id : ter_id_vec_in_cont)
        {
            ter_graph->add_vertex(all_ter_vec[cur_ter_id]->getId());
            ter_in_cont->push_back(all_ter_vec[cur_ter_id]);

            /*find linked territories in the same continent*/
            for (auto linked_ter_id : all_ter_link_info[cur_ter_id])
            {

                /*link territories in single direction*/
                if (linked_ter_id > cur_ter_id &&
                    cont_id_for_ter_vec[linked_ter_id] == tmp_cont_id)
                {

                    ter_graph->add_edge(all_ter_vec[cur_ter_id]->getId(), all_ter_vec[linked_ter_id]->getId());
                }
            }
        }
        /*add continents*/
        continents->push_back(new Continent(new string(cont_name_vec[tmp_cont_id]), ter_graph, ter_in_cont));
        tmp_cont_id++;
    }
    /*create continents graph*/
    Graph<int>* cont_graph = new Graph<int>;

    bool cont_link_info[100][100];//link info of all continents


    /*create continents link info*/
    for(unsigned int i = 0; i < all_ter_link_info.size(); i ++)
    {
        for(int j = 0; j < continents->size(); j ++)
        {
            cont_link_info[i][j] = false;
        }

        for(unsigned int j  = 1;j < all_ter_link_info[i].size(); j ++)
        {

            int src = cont_id_for_ter_vec[i];
            int dst = cont_id_for_ter_vec[all_ter_link_info[i][j]];

            /*create a single link between two continents*/
            if (src < dst && cont_link_info[src][dst] == false)
            {
                cont_link_info[src][dst] = true;
                cont_graph->add_edge((*continents)[src]->getId(),
                                     (*continents)[dst]->getId());
            }
        }
    }

    graph_vec->push_back(cont_graph);


    return new Map(cont_graph, continents);
}
