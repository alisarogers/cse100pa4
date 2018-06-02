/*
 * ActorGraph.h
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H
#include "ActorNode.h"
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <map> 
//#include "Edges.h"


using namespace std;

typedef pair<string, int> movie_pair;

typedef map<movie_pair, vector<ActorNode>> map_type;

// Maybe include some data structures here


class ActorGraph {
    protected:
        vector <string> actors;
	vector <string> movies;
	vector <int> years;
	
	vector<movie_pair> movie_years;

	vector <ActorNode> actorNodes;
	
	map_type costarMap;

        // Maybe add class data structure(s) here

    public:
        ActorGraph(void);

        // Maybe add some more methods here

	map_type createAdList (vector<movie_pair> movieYears, vector<ActorNode> actors);
        /** You can modify this method definition as you wish
         *
         * Load the graph from a tab-delimited file of actor->movie relationships.
         *
         * in_filename - input filename
         * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
         *
         * return true if file was loaded sucessfully, false otherwise
         */
        //returns a vector containing the actors from the loaded file
        vector<string> getActors(void);
        //returns a vector containing the movies from the loaded file
        vector<string> getMovies(void);
        //returns a vector containing the years from the loaded file
        vector<int> getYears(void);
	vector<movie_pair> getMoviesAndYears(void);
        bool loadFromFile(const char* in_filename, bool use_weighted_edges);

	vector<string> findPath (ActorNode actor1, ActorNode actor2, int& length, vector<movie_pair> movie_years, vector<ActorNode> actors);
	
	vector<ActorNode> populateNodes (vector<string> actors, vector<movie_pair> movie_years);

	void clearActorPaths (vector<ActorNode> actorVector);	

	map_type createCostarMap(vector<string> actors); 

};


#endif // ACTORGRAPH_H
