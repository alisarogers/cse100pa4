
#ifndef ACTORNODE_H
#define ACTORNODE_H

#include <string>
#include <vector>

using namespace std;

 
class ActorNode {

public:

    //holds name of the actor
    string name;

    //holds running list of movies the Actor was in
    vector <string> moviesIn;

    //initializes ActorNode with a name
    ActorNode(string actorName)
    {
      this->name = actorName;
    }

    //adds movie to moviesIn vector
    void addMovies(string movie);
};


#endif // HCNODE_H