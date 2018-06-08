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
		actorVector[i]->path = "";
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
//	vector<MovieNode*> movieVector;
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
					}
					visitedActors.push_back(costarsVector[n]->name);
					actorQueue.push(costarsVector[n]);
				}
				}
			}
		}
	}
	
}


ActorNode* ActorGraph::findWeightedPath(string actor1, string actor2, vector<ActorNode*> actorVector)
{
	queue<ActorNode*> actorQueue;
	priority_queue <MovieNode, vector<MovieNode>, Comparator> weightedQueue;
	ActorNode* actor1Node;
	ActorNode* actor2Node;

	for(int i = 0; i < actorVector.size(); i++)
	{
		actorVector[i]->path = "";
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
//	vector<MovieNode*> movieVector;
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
					}
					visitedActors.push_back(costarsVector[n]->name);
					actorQueue.push(costarsVector[n]);
				}
				}
			}
		}
	}
	
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

	


	this->actorNodes = condensedActors;
}

#endif //ACTORGRAPH_H
