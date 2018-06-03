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
using namespace std;

class MovieNode;

class ActorNode {

private:
	string name;
	MovieNode* movieBefore;
	MovieNode* movieAfter;
	vector<MovieNode*> starredIn;

public:
	ActorNode(string actor);
	void setMovieBefore(MovieNode* before);
	void setMovieAfter(MovieNode* after);
	void addToMovies (MovieNode* addMovie);
	vector<MovieNode*> getStarredIn();
};
#endif //ACTORNODE_H
