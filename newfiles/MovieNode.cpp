/* PA4 MovieNode.h
 * Authors: arogers/edscott
 * Date: 6/2/2018
 *
*/
#ifndef MOVIENODE_H
#define MOVIENODE_H

#include <string>
#include <vector>
#include "ActorNode.h"
#include "MovieNode.h"

using namespace std;


	MovieNode::MovieNode(string movie, int yr)
	{
		this->name = movie;
		this->year = yr;
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
		this->cast.push_back(addActor);
	}

	vector<ActorNode*> MovieNode::getCast()
	{
		return this->cast;
	}

#endif //MOVIENODE_H
