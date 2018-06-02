/*
 * ActorGraph.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.

	*** need to add a map as a protected  variable ** 

 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.h"
#include "ActorNode.h"
#include <queue>
#include <utility>
//#include "Edges.h"

using namespace std;
//typedef pair<int, ActorNode> lengthActor;
typedef map<movie_pair, vector<ActorNode>> map_type;

ActorGraph::ActorGraph(void) {}
vector<string> ActorGraph::getActors(void)
{ 
	return this->actors;
}
vector<string> ActorGraph::getMovies(void)
{
         return this->movies;
}
vector <int> ActorGraph::getYears(void)
{
         return this->years;
}

vector<movie_pair> ActorGraph::getMoviesAndYears(void)
{
	return this->movie_years;
}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
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
	movie_pair movieYear = make_pair(movie_title, movie_year);
	this->movie_years.push_back(movieYear); 
   	
	/* could initialize a pair each time and then push it onto 
	 * movieYears */
	 
        // we have an actor/movie relationship, now what?
    }


    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}



map_type ActorGraph::createAdList (vector<movie_pair> movieYears, vector<ActorNode> actors) {
		map_type AdjMap;
		for(int i = 0; i < actors.size(); i++)
		{
			if(AdjMap.find(movieYears.at(i)) == AdjMap.end()){
			//	AdjMap[movieYears.at(i)].push_back(actors.at(i));
			vector<ActorNode> actorVector;
			AdjMap.emplace(movieYears.at(i), actorVector);
			} 
	
			// how do we make this a new vector?
			AdjMap[movieYears.at(i)].push_back(actors.at(i));
			

	//	this->AdjMap = AdjMap;
		return AdjMap;
		}
}




vector<ActorNode> ActorGraph::populateNodes(vector<string> actors, vector<movie_pair> movie_years) {
	

	vector<ActorNode> condensedActors;
	bool existsAlready;
	
	//creates a vector of ActorNodes, with each actor only once
	for(int i = 0; i < actors.size(); i++) {
		existsAlready = false;
		for(int j = 0; j < condensedActors.size(); j++) {
			if(condensedActors.at(j).name == actors.at(i))
			{
				existsAlready = true;
				break;
			}
		}
		if(!existsAlready) 
		{
			ActorNode newActor = ActorNode(actors.at(i));
			condensedActors.push_back(newActor);
		}
	}	
	
	//adds the movies to the actor Nodes
	for (int k = 0; k < movie_years.size(); k++) {
		for(int l = 0; l < condensedActors.size(); l++) 
		{
			if (actors.at(k) == condensedActors.at(l).name) 
			{
				condensedActors.at(l).moviesIn.push_back(movie_years.at(k));
			} 
		}
	}


}


void ActorGraph::clearActorPaths(vector<ActorNode> actorVector) 
{
	for(int i = 0; i < actorVector.size(); i++)
	{
		actorVector[i].path.clear();
	}

}


vector<string> ActorGraph::findPath (ActorNode actor1, ActorNode actor2, int& length, vector<movie_pair> movie_years, vector<ActorNode> actorVector) {

	/* q = an empty queue
 		add (0,u) to q // (0, u) -> (length from u, current vertext)
	while q is not empty:
		(length, curr) = q.dequeue();
		if curr == v: // we found the one we're searching for
			return lenth
		for all outgoing edges (curr, wv) from curr: // otherwise explore all neighbors
			if w has not yet been visitied
				add (length + 1, w) to q
	return FAIL // if we reach here, it failed
	path exists from u to v
	*/

	/* sets all the paths back to null for all the actors*/
	clearActorPaths(actorVector);
	ActorNode currActor = actor1;
	pair<int, ActorNode> currCheck (0, currActor);

	/* creates  queue of ActorNodes + length of their path
	 * and pushes actor1 onto it 
         */		
	queue<pair<int, ActorNode>> actorQueue;
	actorQueue.push(currCheck);	
	vector<string> foundPath;

	/* creates the map */
	map_type costarMap = createAdList(movie_years, actorVector);
	vector<ActorNode> costars;
	
	vector<movie_pair> tempMovies;
	pair<int, ActorNode> tempPair;

	/* queue is FIFO*/
	while(!actorQueue.empty()) {
		currCheck = actorQueue.front();
		actorQueue.pop();
		if(currCheck.second.name == actor2.name) {
			length = currCheck.first;
			foundPath = currCheck.second.path;
			return foundPath;
		} else {
			for(int m = 0; m < currCheck.second.moviesIn.size(); m++)
			{
				// this inserts all of the current actor's costars from 
				// every one of their movies into the queue
				tempMovies = currCheck.second.moviesIn;
				movie_pair tempMov = tempMovies[m];
				costars = costarMap[tempMov];	
				for(int n = 0; n < costars.size(); n++) 
				{
					tempPair = make_pair((currCheck.first + 1), costars.at(n));
					tempPair.second.addToPath(tempMov.first);
					tempPair.second.addToPath(currCheck.second.name);
					string temp = "";
					temp += currCheck.first; 
					tempPair.second.addToPath(temp);
					actorQueue.push(tempPair);		
				}
			}
		}
		// use edges 
		// edges should return the actors with adjacency 1
		// we'll add these actors to the queue
		// continue through the queue until we find actor2
		// 

		// go to this actor's movies, use the AdjMap to return 		      // the list of people in each of their movies (all of their movies)		
		// helper method to compile all of their actors vectors


	return foundPath;

	}


}
