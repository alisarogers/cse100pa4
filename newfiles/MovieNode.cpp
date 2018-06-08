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


	MovieNode::MovieNode(string movie, int yr)
	{
		name = movie;
		year = yr;
		movieAndYear = movie + "#@" + to_string(yr);
		weight = 1 + 2015 - year;
		// do we need to initialize actorBefore/actorAfter/cast?
	}	
	void MovieNode::setActorBefore(ActorNode* before){
		this->actorBefore = before;
	}
	
	void MovieNode::setActorAfter(ActorNode* after){
		this->actorAfter = after;
	}
	
	void MovieNode::addToCast (ActorNode* addActor)
	{
		this->castMembers.push_back(addActor);
	}

	vector<ActorNode*> MovieNode::getCast()
	{
		return this->castMembers;
	}

#endif //MOVIENODE_CPP
