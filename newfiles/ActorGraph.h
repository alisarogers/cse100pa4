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

using namespace std;


class ActorGraph {

private:
	vector<string> actors;
	vector<string> movies;
	vector<int> years;
	
	vector<ActorNode*> actorNodes;
	vector<MovieNode*> movieNodes;
	
public:
	vector<string> getActors();
	vector<string> getMovies();
	vector<int> getYears();
//	vector<movie_pair> getMoviesWithYears();
	bool loadFromFile(const char* in_filename, bool use_weighted_edges);
	ActorNode* findPath(string actor1, string actor2, vector<MovieNode*> movies, vector<ActorNode> actorVector, unordered_map<MovieNode*, vector<ActorNode*>> movieMap);
	ActorNode* createShortestPath(ActorNode* finalActor);
	ActorNode* printPath(ActorNode* firstActor);
	vector<ActorNode*> populateActorNodes(vector<string> actors, vector<string> movies, vector<int> years);

};

#endif //ACTORGRAPH_H
