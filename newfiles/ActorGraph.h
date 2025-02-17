
/* PA4 ActorGraph.h
 * Authors: arogers/edscott
 * Date: 6/2/2018
 *
*/
#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <unordered_map>
#include "MovieNode.h"
#include "ActorNode.h"
#include <queue>
using namespace std;


class ActorGraph {
public:
    vector<string> actors;
    vector<string> movies;
    vector<int> years;

    unordered_map<string, vector<ActorNode*>> map;   
    vector<ActorNode*> actorNodes;
    vector<MovieNode*> movieNodes;

    priority_queue<string, vector<string>, MovieComparator> moviesByYear;
    
    int connectActors(string actor1, string actor2, vector<ActorNode*> actorVector);
    int edgeWeight(ActorNode* actor1, ActorNode* actor2);
    string edgeMovie(ActorNode* actor1, ActorNode* actor2);
    vector<string> getActors();
    vector<string> getMovies();
    vector<int> getYears();
    
	bool loadFromFile(const char* in_filename, bool use_weighted_edges);
    ActorNode* findPath(string actor1, string actor2, vector<ActorNode*> actorVector);
    ActorNode* findWeightedPath(string actor1, string actor2, vector<ActorNode*> actorVector);
    ActorNode* findWeightedPath2(string actor1, string actor2, vector<ActorNode*> actorVector);
    ActorNode* createShortestPath(ActorNode* actor2, string actor1);
    string printPath(ActorNode* firstActor, string actor2);
    void populateNodes(vector<string> actors, vector<string> movies, vector<int> years);

};

#endif //ACTORGRAPH_H
