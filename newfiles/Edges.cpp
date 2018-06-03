/* PA4 Edges.cpp
 * Authors: arogers/edscott
 * Date: 6/3/2018
 */

#ifndef EDGES_CPP
#define EDGES_CPP
#include <unordered_map>
#include "Actor.h"
#include "Movie.h"
#include <vector>


Edges(vector<MovieNode*> movies) 
{
	unordered_map<MovieNode*, vector<ActorNode*>> map;
	for(int i = 0; i < movies.size(); i++)
	{
		map[movies[i]->movieAndYear] = movies.castMembers;
	}
	this->edgeMap = map;:
}
#endif //EDGES_CPP
