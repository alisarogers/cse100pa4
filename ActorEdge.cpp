/* 
 * Edges.cpp
 * 

 */



#include "Edges.h"


// first we need to make a node for each movie, and then use that 
// to map
// 

// create the keys for movies with their years
// go through each actor and add their name to the vector list of each // movie they're in



//when we're adding the actors, check if the movie node already exists
// add to the existing movie node or create a new one

	map_type createAdList (vector<movie_pair> movieYears, vector<ActorNode> actors) {
		map_type AdjMap;
		for(int i = 0; i < actors.length(); i++)
		{
			if(AdjMap.find(movie_pair){
				AdjMap[movieYears.at(i)].push_back(actors.at(i));
			} else {
	
			// how do we make this a new vector?
			AdjMap[movieYears.at(i)].emplace(vector<ActorNode> actorVector);
			AdjMap[movieYears.at(i)].push_back(actors.at(i));
			
			}

		this->AdjMap = AdjMap;
		return AdjMap;
	}

