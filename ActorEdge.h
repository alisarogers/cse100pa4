/*
 * Edges.h
 * Author: arogers & edscott
 * Date: 5/31/2018
 * This file is going to be used to create an adjacency table for the
 * edges 
 */

#ifndef ACTOREDGE_H
#define ACTOREDGE_H
#include <vector>
#include <string>
#include <map>

using namespace std;

typedef map<movie_pair, vector<ActorNode>> map_type;


class Edges {
protected:
	map_type AdjMap;	

public:
	// need methods to read in the entire adjacency list	
	map_type createAdList (vector<movie_pair> movieYears, vector<ActorNode> actors);


};

#endif // ACTOREDGE_H
