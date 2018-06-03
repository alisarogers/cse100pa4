/* PA4 Edges.h
 * Authors: arogers/edscott
 * Date: 6/3/2018
 */

#ifndef EDGES_H
#define EDGES_H
#include <unordered_map>
#include "Actor.h"
#include "Movie.h"
#include <vector>

class Edges {
public:
	unordered_map<MovieNode*, vector<ActorNode*>> edgeMap;

	Edges(vector<MovieNode*> movies);

};

#endif
