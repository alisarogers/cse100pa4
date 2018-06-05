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

	while(!actorQueue.empty())
	{
		currActor = actorQueue.front();		
		actorQueue.pop();
		if(currActor->name == actor2Node->name) {
			return currActor;
		} else
		{
			for(int m = 0; m < currActor->starredIn.size(); m++) 
			{
				currActor->starredIn[m]->actorBefore = currActor;
				costarsVector = currActor->starredIn[m]->castMembers;
				for (int n = 0; n < costarsVector.size(); n++)
				{
					costarsVector[n]->movieBefore = currActor->starredIn[m];
					actorQueue.push(costarsVector[n]);
				}
			}
		}
	}
	
}


ActorNode* ActorGraph::createShortestPath(ActorNode* actor2, string actor1)
{
	ActorNode* currActor = actor2;
	currActor->movieBefore->actorAfter = currActor;
	currActor->movieBefore->actorBefore->movieAfter = currActor->movieBefore;
	while(currActor->movieBefore->actorBefore->name != actor1)
	{
		currActor = currActor->movieBefore->actorBefore;
		currActor->movieBefore->actorAfter = currActor;
			
		currActor->movieBefore->actorBefore->movieAfter = currActor->movieBefore;
	}

	return currActor->movieBefore->actorBefore;
}

string ActorGraph::printPath(ActorNode* firstActor, string actor2) 
{
	string toReturn;
	ActorNode* currActor = firstActor;
	while(currActor->name != actor2) 
	{
		toReturn.append("(" + currActor->name + ")--");
		toReturn.append("[" + currActor->movieAfter->movieAndYear + "]-->");
		currActor = currActor->movieAfter->actorAfter;
	}		
	toReturn += actor2;
	return toReturn;

}

void ActorGraph::populateNodes(vector<string> actors, vector<string> movies, vector<int> years) 
{
	vector<ActorNode*> condensedActors;
	bool existsAlready;
	for(int i = 0; i < actors.size(); i++) 
	{
		existsAlready = false;
		for(int j = 0; j < condensedActors.size(); j++)	
		{
			if(condensedActors[j]->name == actors[i])
			{
				existsAlready = true;
				break;
			}
		}

		if(!existsAlready)
		{
			ActorNode* newActor = new ActorNode(actors[i]);
			condensedActors.push_back(newActor);
		}
	}
	
	vector<MovieNode*> condensedMovies;
	MovieNode * newMovie;
	for(int i = 0; i < movies.size(); i++) 
	{
		existsAlready = false;
		for(int j = 0; j < condensedMovies.size(); j++)	
		{
			if((condensedMovies[j]->name == movies[i]) && (condensedMovies[j]->year == years[i]))
			{
				existsAlready = true;
				break;
			}
		}

		if(!existsAlready)
		{
			newMovie = MovieNode(movies[i], years[i]);
			condensedMovies.push_back(newMovie);
		}
	}

	for (int i = 0; i < actors.size(); i++)
	{
		// find the actor in the actor vector
		// add in movies[i] to the actos' starredIn
		// find the movie in the movie vector
		// add actors[i] to the movies' castMembers
		for(int j = 0; j < condensedActors.size(); j++)
		{
			if (condensedActors[j]->name == actors[i])
			{
				for(int k = 0; k < condensedMovies.size(); k ++)
				{
					if (condensedMovies[k]->name == movies[i])
					{
						condensedActors[j]->starredIn.push_back(condensedMovies[k]);
						condensedMovies[k]->castMembers.push_back(condensedActors[j]);
					}
				}
			}
		}

	}

	this->actorNodes = condensedActors;
	this->movieNodes = condensedMovies;		
}

#endif //ACTORGRAPH_H
