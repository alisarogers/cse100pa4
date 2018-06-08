
/* PA4: actorConnection.h
 * Authors: arogers/edscott
 * Date: 6/2/2018
 *
*/
#ifndef ACTORCONNECTIONS_H
#define ACTORCONNECTIONS_H

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <unordered_map>
#include "MovieNode.h"
#include "ActorNode.h"

using namespace std;


class ActorConnections {
public:
    ActorNode* connectActors(string actor1, string actor2, vector<ActorNode*> actorVector);
    int edgeWeight(ActorNode* actor1, ActorNode* actor2);
    ActorNode* findWeightedPath(string actor1, string actor2, vector<ActorNode*> actorVector);
    ActorNode* createShortestPath(ActorNode* actor2, string actor1);
    string printPath(ActorNode* firstActor, string actor2);
    void populateNodes(vector<string> actors, vector<string> movies, vector<int> years);

};


#endif //ACTORGRAPH_H
