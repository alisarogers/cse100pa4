
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
#include "ActorGraph.h"
#include <algorithm>
#include <queue>
using namespace std;

int edgeWeight(ActorNode* actor1, ActorNode* actor2) {
	
	string foundMovie;
	for(int i = 0; i < actor1->weightedStarredIn.size(); i++)
	{
		/* find the movie that immediately connects them with least weight*/
		if(find(actor2->weightedStarredIn.begin(), actor2->weightedStarredIn.end(), actor1->weightedStarredIn[i]) != actor2->weightedStarredIn.end()) {
			foundMovie = actor1->weightedStarredIn[i];
			break;
		}
	}
	string movieYear;
	movieYear = foundMovie.substr(foundMovie.length() - 4, foundMovie.length());
	int toReturn = stoi(movieYear);

}


   /* before we call this function, we will have to create the graph
    * and call populateNodes, then use the graph's map*/
ActorNode* connectActors(string actor1, string actor2, vector<ActorNode*> actorVector)
{
	priority_queue<ActorNode*, vector<ActorNode*>, bandComparator> bandQueue;
	ActorNode* actor1Node;
	ActorNode* actor2Node;

	/* initialize all bands to 0, plus find actor1Node*/
	for (int i = 0; i < actorVector.size(); i ++)
	{
		if (actorVector[i]->name == actor1) 
		{ actor1Node = actorVector[i]; }
		
		if (actorVector[i]->name == actor2)
		{ actor2Node = actorVector[i]; }
		
		actorVector[i]->band = 0;
	}
	
	int c;
	ActorNode* v;
	ActorNode* w;
	bandQueue.push(actor1Node);
	while(!bandQueue.empty()) {		
		
		/* get first value in the PQ*/
		v = bandQueue.top();
		bandQueue.pop();

		/* check if we found it? */
		if (v == actor2Node)
		{
			return v;
		}
	
	
		/* get a list of all the neighbors*/
		vector<ActorNode*> cycleActors;
		string currMovie;
		vector<ActorNode*> costars;
		for(int j = 0; j < v->weightedStarredIn.size(); j++)
		{
			currMovie = v->weightedStarredIn[j];
			costars = giveUsMap->map[currMovie];
			for (int k = 0; k < costars.size(); k++)
			{
				cycleActors.push_back(costars[k]);
			}
		}

		for(int l = 0; l < cycleActors.size(); l++)
		{
			w = cycleActors[l];
			c = min(v->band, edgeWeight(v, w));
			if (c > w->band)
			{
				w->actorPath = v->actorPath;
				w->actorPath.push_back(v);
				w->band = c;
				bandQueue.push(w);
			}
		}
/* initialize band field to "0" 
for each of v neihgbors w:
	c = min(v.band, edgeWeight(v, w))
	if c is "more" than w.band"
		w.prev = v
		w.band = c
		enqueue {w, c} into the PQ
*/
	}


}

    void populateNodes(vector<string> actors, vector<string> movies, vector<int> years);


#endif //ACTORGRAPH_H
