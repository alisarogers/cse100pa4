
#ifndef ACTORNODE_CPP
#define ACTORNODE_CPP

#include "ActorGraph.h"
#include "ActorNode.h"
#include <string>
#include <vector>


using namespace std;

void ActorNode::addMovies(movie_pair movie)
{
	this->moviesIn.push_back(movie);
}



#endif
