
/* PA4 ActorNode.h
 * Authors: arogers/edscott
 * Date: 6/2/2018
 *
*/
#ifndef ACTORNODE_H
#define ACTORNODE_H

#include <string>
#include <vector>
#include "MovieNode.h"
#include <queue>
#include "UnionFind.h"

using namespace std;

class UnionFind;
class MovieNode;

class ActorNode {
public:
    string name;
    UnionFind* set;
    MovieNode* movieBefore;
    MovieNode* movieAfter;
    vector<string> starredIn;
    vector<string> weightedStarredIn;
    vector<ActorNode*> actorPath;
	int band;
	int weight;
	int pathWeight;
	string path;

    ActorNode(string actor);
    void setMovieBefore(MovieNode* before);
    void setMovieAfter(MovieNode* after);
    void addToMovies (string addMovie);
    vector<string> getStarredIn();
};

class actorComparator {
public:
	bool operator() (ActorNode* a, ActorNode* b) {
		return a->pathWeight > b->pathWeight;
	}
};

class MovieComparator {
public:
	bool operator() (string a, string b) {
	int weightA;
	int weightB;
	a = a.substr(a.length()-4, a.length());
	b = b.substr(b.length()-4, b.length());
	weightA = stoi(a);
	weightB = stoi(b);
	
	return weightA < weightB;

	}
};
class bandComparator {
public:
	bool operator() (ActorNode* a, ActorNode*b) {
		return a->band < b->band;
	}
};
#endif //ACTORNODE_H
