/* PA4 ActorNode.cpp
 * Authors: arogers/edscott
 * Date: 6/2/2018
 *
*/
#ifndef ACTORNODE_CPP
#define ACTORNODE_CPP

#include <string>
#include <vector>
#include "MovieNode.h"
#include "ActorNode.h"

using namespace std;

	ActorNode::ActorNode(string actor)
	{
		this->name = actor;
		this->weight = 0;
	}

	void ActorNode::setMovieBefore(MovieNode* before)
	{	
		this->movieBefore = before;
	}

	void ActorNode::setMovieAfter(MovieNode* after) 
	{
		this->movieAfter = after;
	}

	void ActorNode::addToMovies (string addMovie)
	{
		this->starredIn.push_back(addMovie);
	}

	vector<string> ActorNode::getStarredIn()
	{
		return this->starredIn;
	}

class actorComparator {
public:
	bool operator() (ActorNode &a, ActorNode &b)
	{
		return a.weight < b.weight;
	}
};


#endif //ACTORNODE_H
