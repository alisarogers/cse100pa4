/* PA4 ActorGraph.cpp
 * Authors: arogers/edscott
 * Date: 6/2/2018
 *
*/
#ifndef ACTORGRAPH_CPP
#define ACTORGRAPH_CPP

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <unordered_map>
#include "MovieNode.h"
#include "ActorNode.h"

using namespace std;


class ActorGraph {

private:
	vector<string> actors;
	vector<string> movies;
	vector<int> years;
	
	vector<ActorNode*> actorNodes;
	vector<MovieNode*> movieNodes;
	
public:
	vector<string> ActorGraph::getActors()
	{
		return this->actors;
	}
	vector<string> ActorGraph::getMovies()
	{
		return this->movies;
	}

	vector<int> ActorGraph::getYears()
	{
		return this->years;
	}

	bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges)
	{
		
   		// Initialize the file stream
		ifstream infile(in_filename);

		bool have_header = false;

 		// keep reading lines until the end of file is reached
		while (infile) {
        	string s;

        	// get the next line
       		if (!getline( infile, s )) break;

        	if (!have_header) {
      		// skip the header
           	have_header = true;
            	continue;
        	}

      		istringstream ss( s );
  		vector <string> record;

      		while (ss) {
           		string next;

          		// get the next string before hitting a tab character and put it in 'next'
           		if (!getline( ss, next, '\t' )) break;

          		record.push_back( next );
        	}

    		if (record.size() != 3) {
        		// we should have exactly 3 columns
            		continue;
        	}

     		string actor_name(record[0]);
	        string movie_title(record[1]);
        	int movie_year = stoi(record[2]);

        	this->actors.push_back(actor_name);
      		this->movies.push_back(movie_title);
        	this->years.push_back(movie_year);
   	
	 
        // we have an actor/movie relationship, now what?
	}	

	if(!infile.eof()) {
		cerr << "Failed to read " << in_filename << "!\n";
		return false;
	}
	infile.close();
	
	return true;

	}
	
	ActorNode* ActorGraph::findPath(string actor1, string actor2, vector<MovieNode*> movies, vector<ActorNode> actorVector, unordered_map<MovieNode*, vector<ActorNode*>> movieMap)
	{

	}


	ActorNode* ActorGraph::createShortestPath(ActorNode* finalActor);
	ActorNode* ActorGraph::printPath(ActorNode* firstActor);
	vector<ActorNode*> ActorGraph::populateActorNodes(vector<string> actors, vector<string> movies, vector<int> years);

#endif //ACTORGRAPH_H
