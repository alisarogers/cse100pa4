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

typedef pair<string, int> movie_pair;

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

	vector<movie_pair> movies_and_years = graph->getMoviesAndYears();

	vector<ActorNode> actorVector = graph->populateNodes(actors, movies_and_years);		


	vector<string> actor1s;
	vector<string> actor2s;
	/* read in the pairs */
	ifstream infile(argv[3]);
	while (infile) {
		string s;
		if (!getline(infile, s)) { break; }

		istringstream ss ( s );
		vector <string> record;
		
		while (ss) {
			string next;
			if (!getline( ss, next, '\t' )) { break; }
			record.push_back(next);		
		}
	
		if(record.size() != 3) {
			continue;
		}

		actor1s.push_back(record[0]);
		actor2s.push_back(record[1]);

	}

	if(!infile.eof()) {
		cerr << "Failed to read " << argv[3] << "!\n";
		
	}
	infile.close();

	int pathLen = 0;

	// open the out text file
	ofstream toWrite;
	toWrite.open(argv[4]);

	// write to the out file
	for (int i = 0; i < actor1s.size(); i++) {
		if(toWrite.is_open()) {
		string str; 
		
		
		vector<string> thePath = graph->findPath(actor1s[i], actor2s[i], pathLen, movies_and_years, actorVector);

			for (int j = 0; j < thePath.size(); j = j + 3) 
			{
				str.append("(" + thePath[j] + ")" + "--" + "[" + thePath[j+1] + "#@" + thePath[j+2] + "]" + "-->");
				toWrite << str << "\n";
			}
		}
	}

	toWrite.close();
	//read in args from test_pairs (arg[3] i think)
	//call find Path

	

	/*Because the loadFromFile method updates each of these vectors
	a line at a time, actors.at(i), movies.at(i), and years.at(i) 
	are all correlated/in sync.*/


/*	for(i=0; i<10; i++)
	{
		//testing that vectors were populated w at least 10 items each
		cout<< actors.at(i)<<endl;
		cout<< movies.at(i)<<endl;
		cout<< years.at(i)<<endl;

	} */



	return 1;
}
