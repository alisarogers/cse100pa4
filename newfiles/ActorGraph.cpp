/* PA4 ActorGraph.cpp
 * Authors: arogers/edscott
 * Date: 6/2/2018
 *
*/
#ifndef ACTORGRAPH_CPP
#define ACTORGRAPH_CPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <unordered_map>
#include "MovieNode.h"
#include "ActorNode.h"
#include "ActorGraph.h"
#include <queue>
#include <algorithm>

using namespace std;



vector<string> ActorGraph::getActors()
{
	return this->actors;
}

vector<string> ActorGraph::getMovies()
{
	return this->movies;
}

vector<int> ActorGraph::getYears()
{
	return this->years;
}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges)
{
		
   	// Initialize the file stream
	ifstream infile(in_filename);

	bool have_header = false;

 	// keep reading lines until the end of file is reached
	while (infile) {
        	string s;

        	// get the next line
       		if (!getline( infile, s )) break;

        	if (!have_header) {
      			// skip the header
      		     	have_header = true;
       		     	continue;
        	}

      		istringstream ss( s );
  		vector <string> record;

      		while (ss) {
           		string next;

          		// get the next string before hitting a tab character and put it in 'next'
           		if (!getline( ss, next, '\t' )) break;

          		record.push_back( next );
        	}

    		if (record.size() != 3) {
        		// we should have exactly 3 columns
            		continue;
        	}

     		string actor_name(record[0]);
	        string movie_title(record[1]);
        	int movie_year = stoi(record[2]);

        	this->actors.push_back(actor_name);
      		this->movies.push_back(movie_title);
        	this->years.push_back(movie_year);
   	
	 
        // we have an actor/movie relationship, now what?
	}	

	if(!infile.eof()) {
		cerr << "Failed to read " << in_filename << "!\n";
		return false;
	}
	infile.close();
	
	return true;

}
	
ActorNode* ActorGraph::findPath(string actor1, string actor2, vector<ActorNode*> actorVector)
{
	queue<ActorNode*> actorQueue;
	ActorNode* actor1Node;
	ActorNode* actor2Node;

	for(int i = 0; i < actorVector.size(); i++)
	{
		vector<ActorNode*> emptyVector;
		actorVector[i]->path = "";
		actorVector[i]->actorPath = emptyVector;
	}
	

	/* find actor 1 and actor 2 nodes */
	for(int i = 0; i < actorVector.size(); i++) 
	{
		if(actorVector[i]->name == actor1)
		{
			actor1Node = actorVector[i];
		}
		
		if(actorVector[i]->name == actor2)
		{
			actor2Node = actorVector[i];
		}
	}

	actorQueue.push(actor1Node);
	ActorNode* currActor;
	vector<ActorNode*> costarsVector;
	string tempStr;
	vector<string> visitedMovies;
	vector<string> visitedActors;

	visitedActors.push_back(actor1Node->name);
	while(!actorQueue.empty())
	{
		currActor = actorQueue.front();		
		actorQueue.pop();

		/* if we found the one we're looking for*/
		if(currActor->name == actor2) {
			return currActor;
		} 
		else
		{
			/* iterate through the current Actor's movies and check to see if actor2 is in any of them*/
			for(int m = 0; m < currActor->starredIn.size(); m++) 
			{	

				/* if we've already visited this movie */
				if(!visitedMovies.empty()) {
					if(find(visitedMovies.begin(), visitedMovies.end(), currActor->starredIn[m]) != visitedMovies.end()) 
					{ continue; }
				}

				/* uses the map to get the actors who starred in the movie */
				costarsVector = map[currActor->starredIn[m]];

				/* add current move to the visited list so we don't look there again */
				visitedMovies.push_back(currActor->starredIn[m]);
				
				//double check our current actor is actually in this movie??
				if(find(costarsVector.begin(), costarsVector.end(), currActor) == costarsVector.end()) {
					continue;
				}

				/* if we found the actor we're looking for in this movie's stars */
				if(find(costarsVector.begin(), costarsVector.end(), actor2Node) != costarsVector.end())
				{
					actor2Node = *(find(costarsVector.begin(), costarsVector.end(), actor2Node));
					actor2Node->path = "--[" + currActor->starredIn[m] + "]-->(" + actor2 + ")";
					actor2Node->actorPath.push_back(currActor);
					return actor2Node;
				}
				else {
				/* add the costars to the queue so we can visit their costars*/
				for (int n = 0; n < costarsVector.size(); n++)
				{
					/* if we already visited this actor, we skip this iteration */
					if(!visitedActors.empty()) {
						if (find(visitedActors.begin(), visitedActors.end(), costarsVector[n]->name) != visitedActors.end())
						{ continue; } 
					}

					/* make sure we aren't pushing someone onto their own path */
					if(costarsVector[n] != currActor) {
						costarsVector[n]->actorPath.push_back(currActor);
						costarsVector[n]->path = "--[" + currActor->starredIn[m] + "]-->(" + costarsVector[n]->name + ")";
					
						visitedActors.push_back(costarsVector[n]->name);
						actorQueue.push(costarsVector[n]);
					}
				}
				}
			}
		}
	}


	
}


ActorNode* ActorGraph::findWeightedPath(string actor1, string actor2, vector<ActorNode*> actorVector)
{
	priority_queue <ActorNode*, vector<ActorNode*>, actorComparator> weightedQueue;
	ActorNode* actor1Node;
	ActorNode* actor2Node;
	vector<ActorNode*> orderOfQueue;

	for(int i = 0; i < actorVector.size(); i++)
	{
		vector<ActorNode*> emptyVector;
		actorVector[i]->path = "";
		actorVector[i]->actorPath = emptyVector;
		actorVector[i]->weight = -1; 
		actorVector[i]->pathWeight = 0;
	}
	
	/* find actor 1 and actor 2 nodes */
	for(int i = 0; i < actorVector.size(); i++) 
	{
		if(actorVector[i]->name == actor1)
		{
			actor1Node = actorVector[i];
		}
		
		if(actorVector[i]->name == actor2)
		{
			actor2Node = actorVector[i];
		}
	}

	weightedQueue.push(actor1Node);
	ActorNode* currActor;
	vector<ActorNode*> costarsVector;
	string tempStr;
	vector<string> visitedMovies;
	vector<string> visitedActors;

	visitedActors.push_back(actor1Node->name);
	while(!weightedQueue.empty())
	{
		currActor = weightedQueue.top();		
		weightedQueue.pop();


		/* if we found the one we're looking for*/
		if(currActor->name == actor2) {
			return currActor;
		} 
		else
		{
			vector<ActorNode*> visitedThisLoop;
			/* iterate through the current Actor's movies and check to see if actor2 is in any of them*/
			for(int m = 0; m < currActor->weightedStarredIn.size(); m++) 
			{	
				/* if we've already visited this movie */
				if(!visitedMovies.empty()) {
					if(find(visitedMovies.begin(), visitedMovies.end(), currActor->weightedStarredIn[m]) != visitedMovies.end()) 
					{ continue; }
				}

				/* uses the map to get the actors who starred in the movie */
				costarsVector = map[currActor->weightedStarredIn[m]];

				/* add current move to the visited list so we don't look there again */
				visitedMovies.push_back(currActor->weightedStarredIn[m]);

				//double check our current actor is actually in this movie??
				if(find(costarsVector.begin(), costarsVector.end(), currActor) == costarsVector.end()) {
					continue;
				}
				
				/* add the costars to the queue so we can visit their costars*/
				for (int n = 0; n < costarsVector.size(); n++)
				{
					/* if we already visited this actor, we skip this iteration */
			/*		if(!visitedActors.empty()) {
						if (find(visitedActors.begin(), visitedActors.end(), costarsVector[n]->name) != visitedActors.end())
						{ continue; } 
					}
		*/
					/* make sure we aren't pushing someone onto their own path */
					if(costarsVector[n] != currActor) {
						string movieString = currActor->weightedStarredIn[m];
						int movieYear = stoi(movieString.substr((movieString.length() - 4), movieString.length()));
						int newWeight = 1 + 2015 - movieYear;
						if ((costarsVector[n]->weight > newWeight) || (costarsVector[n]->weight == -1)) {
							costarsVector[n]->weight = 1 + 2015 - movieYear;
							costarsVector[n]->path = "--[" + currActor->weightedStarredIn[m] + "]-->(" + costarsVector[n]->name + ")";
						} 
				
						costarsVector[n]->actorPath = currActor->actorPath;
						costarsVector[n]->actorPath.push_back(currActor);
						
						costarsVector[n]->pathWeight = costarsVector[n]->weight;
						costarsVector[n]->pathWeight += currActor->pathWeight;
						
						if (find(visitedActors.begin(), visitedActors.end(), costarsVector[n]->name) == visitedActors.end())
						{ weightedQueue.push(costarsVector[n]); 


						orderOfQueue.push_back(costarsVector[n]);
						}
					
						visitedActors.push_back(costarsVector[n]->name);
					}
				}
			}
		}
	}
int QueueSize = orderOfQueue.size();
	
}




string ActorGraph::printPath(ActorNode* secondActor, string actor1) 
{		
	string returnPath = "(" + actor1 + ")";

	for(int i = 0; i < secondActor->actorPath.size(); i++)
	{
		returnPath.append(secondActor->actorPath[i]->path);
	}

	returnPath.append(secondActor->path);	
	
	return returnPath;

}

void ActorGraph::populateNodes(vector<string> actors, vector<string> movies, vector<int> years) 
{
	vector<ActorNode*> condensedActors;
	bool existsAlready;
	string movieAndYear;
	
	for(int i = 0; i < movies.size(); i++) 
	{
		vector<ActorNode*> emptyVector;
		movieAndYear = movies[i] + "#@" + to_string(years[i]);
		map[movieAndYear] = emptyVector;
	} 


	for(int i = 0; i < actors.size(); i++) 
	{
		existsAlready = false;
		for(int j = 0; j < condensedActors.size(); j++)	
		{
			if(condensedActors[j]->name == actors[i])
			{
				movieAndYear = movies[i] + "#@" + to_string(years[i]);
				map[movieAndYear].push_back(condensedActors[j]);
				condensedActors[j]->starredIn.push_back(movieAndYear);
				existsAlready = true;
				break;
			}
		}

		if(!existsAlready)
		{
			ActorNode* newActor = new ActorNode(actors[i]);
			condensedActors.push_back(newActor);
			movieAndYear = movies[i] + "#@" + to_string(years[i]);
			map[movieAndYear].push_back(newActor);
			newActor->starredIn.push_back(movieAndYear);
		}
	}


	
	for (int i = 0; i < condensedActors.size(); i++)
	{
		
		priority_queue<string, vector<string>, MovieComparator> weightedMovies;
		for (int j = 0; j < condensedActors[i]->starredIn.size(); j++) 
		{
			weightedMovies.push(condensedActors[i]->starredIn[j]);
		}
		for (int k = 0; k < condensedActors[i]->starredIn.size(); k++)
		{
			condensedActors[i]->weightedStarredIn.push_back(weightedMovies.top());
			weightedMovies.pop();
		}
	}


	this->actorNodes = condensedActors;
}

int ActorGraph::edgeWeight(ActorNode* actor1, ActorNode* actor2) {
	
	string foundMovie;

	/* if they're the same person */
	if(actor1 == actor2)
	{ return 0; }

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
	return 1 + 2015 - toReturn;
}

string ActorGraph::edgeMovie(ActorNode* actor1, ActorNode* actor2) {
	
	string foundMovie;

	/* if they're the same person */
	if(actor1 == actor2)
	{ return 0; }

	for(int i = 0; i < actor1->weightedStarredIn.size(); i++)
	{
		/* find the movie that immediately connects them with least weight*/
		if(find(actor2->weightedStarredIn.begin(), actor2->weightedStarredIn.end(), actor1->weightedStarredIn[i]) != actor2->weightedStarredIn.end()) {
			foundMovie = actor1->weightedStarredIn[i];
			break;
		}
	}
	return foundMovie;
}

int ActorGraph::connectActors(string actor1, string actor2, vector<ActorNode*> actorVector)
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
	vector<ActorNode*> visitedActors;
	bandQueue.push(actor1Node);
	actor1Node->band = 9999;
	while(!bandQueue.empty()) {		
		
		/* get first value in the PQ*/
		v = bandQueue.top();
		bandQueue.pop();

		/* check if we found it? */
		if (v == actor2Node)
		{
			return v->band;
		}
	
	
		/* get a list of all the neighbors*/
		vector<ActorNode*> cycleActors;
		string currMovie;
		vector<ActorNode*> costars;
		for(int j = 0; j < v->weightedStarredIn.size(); j++)
		{
			currMovie = v->weightedStarredIn[j];
			costars = map[currMovie];
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
				/* if we haven't already visited this actor, enqueue */
				if (find(visitedActors.begin(), visitedActors.end(), w) == visitedActors.end()) {
					visitedActors.push_back(w);
					bandQueue.push(w);
				} 
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

ActorNode* ActorGraph::findWeightedPath2(string actor1, string actor2, vector<ActorNode*> actorVector)
{
	priority_queue<ActorNode*, vector<ActorNode*>, bandComparator> bandQueue;
	ActorNode* actor1Node;
	ActorNode* actor2Node;

	/* initialize all weights to 0, plus find actor1Node*/
	for (int i = 0; i < actorVector.size(); i ++)
	{
		if (actorVector[i]->name == actor1) 
		{ actor1Node = actorVector[i]; }
		
		if (actorVector[i]->name == actor2)
		{ actor2Node = actorVector[i]; }
		
		actorVector[i]->weight = 0;
	}
	
	int c;
	ActorNode* v;
	ActorNode* w;
	vector<ActorNode*> visitedActors;
	bandQueue.push(actor1Node);
	actor1Node->weight = 0;
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
			costars = map[currMovie];
			for (int k = 0; k < costars.size(); k++)
			{
				if(costars[k] != v) {
					cycleActors.push_back(costars[k]);
				}
			}
		}

		for(int l = 0; l < cycleActors.size(); l++)
		{
			w = cycleActors[l];
			c = v->weight + edgeWeight(v, w);
			if (c < w->weight || (w->weight == 0))
			{
			
				if(w != actor1Node) {
					w->path = "--[" + edgeMovie(v, w) + "]-->(" + w->name + ")";
				}
				if(find(w->actorPath.begin(), w->actorPath.end(), v) == w->actorPath.end()) {
					w->actorPath = v->actorPath;
					w->actorPath.push_back(v);
				}
		
				w->weight = c;
				/* if we haven't already visited this actor, enqueue */
				if (find(visitedActors.begin(), visitedActors.end(), w) == visitedActors.end()) {
					visitedActors.push_back(w);
					bandQueue.push(w);
				} 
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

#endif //ACTORGRAPH_H
