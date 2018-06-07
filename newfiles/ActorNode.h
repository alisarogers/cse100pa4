
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
using namespace std;


class MovieNode;

class ActorNode {
public:
    string name;
    MovieNode* movieBefore;
    MovieNode* movieAfter;
    vector<string> starredIn;

    vector<ActorNode*> actorPath;


	string path;

    ActorNode(string actor);
    void setMovieBefore(MovieNode* before);
    void setMovieAfter(MovieNode* after);
    void addToMovies (string addMovie);
    vector<string> getStarredIn();
};
#endif //ACTORNODE_H
