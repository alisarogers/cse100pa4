/* PA4 MovieNode.h
 * Authors: arogers/edscott
 * Date: 6/2/2018
 *
*/
#ifndef MOVIENODE_CPP
#define MOVIENODE_CPP

#include <string>
#include <vector>
#include "ActorNode.h"
#include "MovieNode.h"

using namespace std;


	MovieNode* MovieNode::MovieNode(string movie, int yr)
	{
		this->name = movie;
		this->year = yr;
		this->movieAndYear = movie + "#@" + to_string(yr);
		// do we need to initialize actorBefore/actorAfter/cast?
		return this;
	}	
	void MovieNode::setActorBefore(ActorNode* before){
		this->actorBefore = before;
	}
	
	void MovieNode::setActorAfter(ActorNode* after){
		this->actorAfter = after;
	}
	
	void MovieNode::addToCast (ActorNode* addActor)
	{
		this->cast.push_back(addActor);
	}

	vector<ActorNode*> MovieNode::getCast()
	{
		return this->cast;
	}

#endif //MOVIENODE_CPP
