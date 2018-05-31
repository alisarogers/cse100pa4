#include "ActorGraph.h"

using namespace std;

int main (int argc, char** argv)
{
	ActorGraph * graph = new ActorGraph();
	bool test = graph->loadFromFile(argv[1], 0);
	int i;
	vector<string> actors = graph->getActors();
	vector<string> movies = graph->getMovies();
	vector<int> years = graph->getYears();


	for(i=0; i<10; i++)
	{
		cout<< actors.at(i)<<endl;
		cout<< movies.at(i)<<endl;
		cout<< years.at(i)<<endl;

	}
	return 1;
}