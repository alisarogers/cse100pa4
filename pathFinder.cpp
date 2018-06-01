#include "ActorGraph.h"

using namespace std;

/*  USE BFS TO FIND THE PATH
 *  use queue to track all the visited actors
 */


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

	/*Because the loadFromFile method updates each of these vectors
	a line at a time, actors.at(i), movies.at(i), and years.at(i) 
	are all correlated/in sync.*/


	for(i=0; i<10; i++)
	{
		//testing that vectors were populated w at least 10 items each
		cout<< actors.at(i)<<endl;
		cout<< movies.at(i)<<endl;
		cout<< years.at(i)<<endl;

	}
	return 1;
}
