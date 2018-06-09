/* PA4 UnionFind.h
 * Authors: arogers/edscott
 * Date: 6/9/2018
 *
*/
#ifndef UNIONFIND_CPP
#define UNIONFIND_CPP

#include <string>
#include <vector>
#include "MovieNode.h"
#include "ActorNode.h"
#include <queue>
#include "UnionFind.h"
#include <unordered_map>
using namespace std;

	UnionFind::UnionFind(void) {
	}

	UnionFind::UnionFind(string movieName) 
	{
		sentinel = movieName;
	}

	//for each movie, union all the actors
	//break out of the for loop if the given actors are connected
	int UnionFind::unionAll (priority_queue<string, vector<string>, MovieComparator> movies, unordered_map<string, vector<ActorNode*>> map, vector<ActorNode*> actorNodes, string actor1, string actor2) {

		string movieString;	
		vector<ActorNode*> castVector;

		ActorNode* actor1Node;
		ActorNode* actor2Node;

		for(int i = 0; i < actorNodes.size(); i++)
		{
			if(actorNodes[i]->name == actor1)
			{
				actor1Node = actorNodes[i];
			}
			if(actorNodes[i]->name == actor2)
			{
				actor2Node = actorNodes[i];
			}
		}


		for (int i = 0; i < movies.size(); i++)
		{
			/* get the first movie */
			movieString = movies.top();
			movies.pop();
			
			/* get the cast*/
			castVector = map[movieString];
			if(!find(castVector[0]))
			{
				UnionFind * newSet = new UnionFind(movieString);
				castVector[0]->set = newSet;
				newSet->size++;
			}
			for(int j = 1; j < castVector.size(); j++)
			{
				unionTwo(castVector[j-1], castVector[j]);			
			}			

			if(find(actor1Node) == find(actor2Node))
			{
				break;
			}
			

		}
		
		movieString = find(actor1Node)->sentinel;
		movieString = movieString.substr(movieString.length()-4, movieString.length());
		return stoi(movieString);	

	}


	//given two elements u and v, merge the sets to which they belong
	//union
	void UnionFind::unionTwo(ActorNode* u, ActorNode* v)
	{
	
		/* find u set */
		UnionFind * firstSet = find(u);	
		UnionFind * secondSet = find(v);

		if(!firstSet)
		{
			u->set = secondSet;
			secondSet->size++;
		} else if(!secondSet)
		{	
			v->set = firstSet;
			firstSet->size++;
		}  else	if (firstSet->size < secondSet->size) {
			u->set = secondSet;
			secondSet->size++;
		} else {
			v->set = firstSet;
			firstSet->size++;		
		}
		
	}	

	//given an element e, return the set to which it belongs
	UnionFind* UnionFind::find(ActorNode* e)
	{
		if(!e) { return NULL; }
		return e->set;
	}
	
#endif //ACTORNODE_H
