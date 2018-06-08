#include "ActorGraph.h"
#include "ActorNode.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/*  USE BFS TO FIND THE PATH
 *  use queue to track all the visited actors
 */

class ActorNode;
class ActorGraph;

int main (int argc, char** argv)
{
	//creates new ActorGraph pointer
	ActorGraph * graph = new ActorGraph();

	//loads the file 
	bool test = graph->loadFromFile(argv[1], 0);
	int i;

	//loads actors from file into actors vector
	vector<string> actors = graph->getActors();

	//loads movies from file into movies vector
	vector<string> movies = graph->getMovies();

	//loads years from fileinto years vector
	vector<int> years = graph->getYears();

	graph->populateNodes(actors, movies, years);		

	vector<string> actor1s;
	vector<string> actor2s;
	/* read in the pairs */
	ifstream infile(argv[3]);
	bool have_header = false;	
	while (infile) {
		
		/*this chunk gets one line at a time */
		string s;
		if (!getline(infile, s)) { break; }
	
		if (!have_header) {
			have_header = true;
			continue;
		}
	
		istringstream ss ( s );
		vector <string> record;
		
		/* separate the line by tabs */
		while (ss) {
			string next;
			/* if the part we're reading is a tab, skip it*/
			if (!getline( ss, next, '\t' )) { break; }

			/* only record non tab items*/
			record.push_back(next);		
		}
	
		if(record.size() != 2) {
			continue;
		}

		actor1s.push_back(record[0]);
		actor2s.push_back(record[1]);

	}

	if(!infile.eof()) {
		cerr << "Failed to read " << argv[3] << "!\n";
		
	}
	infile.close();

	//read in args from test_pairs (arg[3] i think)
	//call find Path

	//open out text file
	ofstream toWrite;
	toWrite.open(argv[4]);

	ActorNode* actor2Node;
	ActorNode* actor1Node;
	string print;
	toWrite << "(actor)--[movie#@year]-->(actor)--..." << endl;	
	for(int i = 0; i < actor1s.size(); i++) 
	{
		if(*argv[3] == 'u')
		{
			actor2Node = graph->findPath(actor1s[i], actor2s[i], graph->actorNodes); 
		} else {
			actor2Node = graph->findWeightedPath(actor1s[i], actor2s[i], graph->actorNodes); 
		}
		print = graph->printPath(actor2Node, actor1s[i]);
		toWrite << print << endl;
	}	
	toWrite.close();

	/*Because the loadFromFile method updates each of these vectors
	a line at a time, actors.at(i), movies.at(i), and years.at(i) 
	are all correlated/in sync.*/


	return 1;
}
