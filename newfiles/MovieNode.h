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
using namespace std;
class ActorNode;

class MovieNode {
public:
	string name;
	string movieAndYear;
	int year;
	ActorNode* actorBefore;
	ActorNode* actorAfter;
	vector<ActorNode*> castMembers;

	MovieNode();
	MovieNode* MovieNode(string movie, int yr);
	void setActorBefore(ActorNode* before);
	void setActorAfter(ActorNode* after);
	void addToCast (ActorNode* addActor);
	vector<ActorNode*> getCast();
};

#endif //MOVIENODE_H
