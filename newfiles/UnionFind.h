/* PA4 UnionFind.h
 * Authors: arogers/edscott
 * Date: 6/9/2018
 *
*/
#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <string>
#include <vector>
#include "MovieNode.h"
#include "ActorNode.h"
#include <queue>
#include <unordered_map>
using namespace std;


class MovieNode;
class ActorNode;
class MovieComparator;
class UnionFind {
public:
	string sentinel;
	int size;
	int height;
	UnionFind();
	UnionFind(string movieName);

	int unionAll (priority_queue<string, vector<string>, MovieComparator> movies, unordered_map<string, vector<ActorNode*>> map, vector<ActorNode*> actorNodes, string actor1, string actor2);

	//given two elements u and v, merge the sets to which they belong
	//union
	void unionTwo(ActorNode* u, ActorNode* v);
	
	UnionFind* find(ActorNode* e);
	//given an element e, return the set to which it belongs
	//find
	
};
#endif //ACTORNODE_H
