
#ifndef ACTORNODE_H
#define ACTORNODE_H

#include <string>
#include <vector>

using namespace std;

typedef pair<string, int> movie_pair;
 
class ActorNode {

public:

    //holds name of the actor
    string name;

    //holds running list of movies the Actor was in
    vector <movie_pair> moviesIn;

    //initializes ActorNode with a name
    ActorNode(string actorName)
    {
      this->name = actorName;
    }

	
    ActorNode();

    vector<string> path;

    //adds movie to moviesIn vector
    void addMovies(movie_pair movie);

    void addToPath(string);

};


#endif // HCNODE_H
