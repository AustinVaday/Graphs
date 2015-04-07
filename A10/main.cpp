/**************************************************************************
* AUTHOR        : Austin Vaday
* Assignment #  : 10
* CLASS         : CS1D
* SECTION       : T TH: 5:30 - 7:20 P.M.
* DUE DATE      : 4/2/15
**************************************************************************/
#include "header.h"

//#define TESTING
/**************************************************************************
**************************************************************************/
int main()
{

	// Calls the function "PrintHeader" to output a class header
	cout << PrintHeader ("Undirected Graph and DFS", 'A', 10);

	try
	{

	#ifdef TESTING
		UndirectedGraph<string,int> graph(5);

		graph.insert("v0","v1",10);

		graph.insert("v2","v3",20);

		graph.insert("v2","v4",60);

		graph.insert("v2", "v1", 80);


		graph.display();

		cout << "Remove v4\n";
		graph.removeVertex("v4");

		graph.display();

		cout << "Remove edge v2, v1, 80\n";
		graph.removeEdge("v2", "v1", 80);

		graph.display();

		cout << "Remove edge v2, v3, 20\n";
		graph.removeEdge("v2", "v3", 20);

		graph.display();

		cout << "Remove v1 \n";
		graph.removeVertex("v1");

		cout << "Insert v3, v4, 100 \n";
		graph.insert("v3", "v4", 100);

		graph.display();

		cout << "Insert v1, v4, 150 \n";
		graph.insert("v1", "v4", 150);

		graph.display();
	#else

		UndirectedGraph<string,int> graph(12); // 12 vertices
//		UndirectedGraph<string,int>::GraphEdgeHeap *gHeap;

		/* connect all nodes of graph */
		graph.insert("Seattle", "San Fran", 807);
		graph.insert("Seattle", "Chicago", 2097);
		graph.insert("Seattle", "Denver", 1331);

		graph.insert("San Fran", "Denver", 1267);
		graph.insert("San Fran", "Los Ang", 381);

		graph.insert("Los Ang", "Denver", 1015);
		graph.insert("Los Ang", "Kansas C", 1663);
		graph.insert("Los Ang", "Dallas", 1435);

		graph.insert("Denver", "Chicago", 1003);
		graph.insert("Denver", "Kansas C", 599);

		graph.insert("Chicago", "Boston", 983);
		graph.insert("Chicago", "New York", 787);
		graph.insert("Chicago", "Kansas C", 533);

		graph.insert("Kansas C", "Dallas", 496);
		graph.insert("Kansas C", "New York", 1260);
		graph.insert("Kansas C", "Atlanta", 864);

		graph.insert("Dallas", "Atlanta", 781);
		graph.insert("Dallas", "Houston", 239);

		graph.insert("Houston", "Atlanta", 810);
		graph.insert("Houston", "Miami", 1187);

		graph.insert("Boston", "New York", 214);

		graph.insert("New York", "Atlanta", 888);

		graph.insert("Atlanta", "Miami", 661);

		graph.display();





		/* testing heap structure */
		/*
		gHeap = &(graph.incidentEdges("Denver"));

		cout << "Displaying incident edges to Denver:\n";

	     int size = gHeap->getNumElements();
		for (int i = 0; i < size; i++)
		{
			cout << "Incident Edge # " << i+1 << " has weight: ";
			cout << gHeap->removeTop().getData()->getWeight();
			cout << endl;
		}

		gHeap = &(graph.incidentEdges("Kansas C"));

		cout << "Displaying incident edges to Kansas C:\n";

	    size = gHeap->getNumElements();
		for (int i = 0; i < size; i++)
		{
			cout << "Incident Edge # " << i+1 << " has weight: ";
			cout << gHeap->removeTop().getData()->getWeight();
			cout << endl;
		}

		gHeap = &(graph.incidentEdges("Dallas"));

		cout << "Displaying incident edges to Dallas:\n";

	    size = gHeap->getNumElements();
		for (int i = 0; i < size; i++)
		{
			cout << "Incident Edge # " << i+1 << " has weight: ";
			cout << gHeap->removeTop().getData()->getWeight();
			cout << endl;
		}

		gHeap = &(graph.incidentEdges("Chicago"));

		cout << "Displaying incident edges to Chicago:\n";

	    size = gHeap->getNumElements();
		for (int i = 0; i < size; i++)
		{
			cout << "Incident Edge # " << i+1 << " has weight: ";
			cout << gHeap->removeTop().getData()->getWeight();
			cout << endl;
		}
		*/

		cout << "DFS: \n";
		graph.DepthFirstSearch("Los Ang");

		graph.discoveryEdges();
		graph.backEdges();

	#endif /*TESTING*/


	}
	catch (const OutOfRange&)
	{
		cout << "Inside Catch -- OutOfRange\n";

	}
	catch (const NotFound&)
	{
		cout << "Inside Catch -- NotFound\n";

	}
	catch (const Full&)
	{
		cout << "Inside Catch -- Full\n";

	}
	catch (const Empty&)
	{
		cout << "Inside Catch -- Empty\n";

	}
	catch (const NoParent&)
	{
		cout << "Inside Catch -- No Parent\n";

	}
	catch (const ExternalNode&)
	{
		cout << "Inside Catch -- External Node\n";

	}
	catch (const RootAlreadyExists&)
	{
		cout << "Inside Catch -- Root Already Exists\n";

	}
	catch (const TreeError&)
	{
		cout << "Inside Catch -- Tree Error\n";
		cout << "Check your tree insertions and/or deletions\n";

	}
	catch (const BadHash&)
	{
		cout << "Inside Catch -- Bad Hash\n";
		cout << "Please check your hashing class!\n";
	}
	catch (const IndexNotSet&)
	{
		cout << "Inside Catch -- IndexNotSet\n";
		cout << "Please check your Vertex class!\n";
	}
	catch(...)
	{
		cout << "Inside Catch All\n";
	}


	return 0;

}


