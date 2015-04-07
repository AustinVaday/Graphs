/**************************************************************************
* AUTHOR        : Austin Vaday
**************************************************************************/
#ifndef UNDIRECTEDGRAPHHEADER_H_
#define UNDIRECTEDGRAPHHEADER_H_

#include <vector>
#include "HeapHeader.h"
#include "Comparators.h"


// Enumeration types used for this graph
enum VertexEnum
{
	UNEXPLORED_VERTEX,
	VISITED_VERTEX
};

enum EdgeEnum
{
	UNEXPLORED_EDGE,
	DISCOVERY_EDGE,
	BACK_EDGE,
	CROSS_EDGE
};


/**************************************************************************
* VERTEX CLASS
* 	Generic "VertexType" indicates what's being stored in the vertex
* 		(Can be a number, a letter, a class, etc)
**************************************************************************/
template <typename VertexType>
class Vertex
{
	public:
		Vertex();
		Vertex(VertexType setVertexData, int setVertexIndex);
		~Vertex();

		void setExploration(int setExplorationStatus);
		VertexType& operator* ();

		int  getExploration() const;
		int  getVertexIndex() const;

	private:
		VertexType 	vertexData;
		int 		vertexIndex;
		VertexEnum  explorationStatus;

};

template <typename VertexType>
Vertex<VertexType>::Vertex()
				  : vertexData(VertexType()),
				    vertexIndex(-1),
				    explorationStatus(UNEXPLORED_VERTEX)
{

}
template <typename VertexType>
Vertex<VertexType>::Vertex(VertexType setVertexData, int setVertexIndex)
				  : vertexData(setVertexData),
				    vertexIndex(setVertexIndex),
				    explorationStatus(UNEXPLORED_VERTEX)
{

}

template <typename VertexType>
Vertex<VertexType>::~Vertex()
{


}

template <typename VertexType>
VertexType& Vertex<VertexType>::operator*()
{
	return vertexData;
}

template <typename VertexType>
void Vertex<VertexType>::setExploration(int setExplorationStatus)
{
	// type cast into enumeration type
	explorationStatus = VertexEnum(setExplorationStatus);
}
template <typename VertexType>
int  Vertex<VertexType>::getExploration() const
{
	// return appropriate exploration status
	switch (explorationStatus)
	{
		case UNEXPLORED_VERTEX: return UNEXPLORED_VERTEX;
			break;
		case VISITED_VERTEX:	return VISITED_VERTEX;
			break;
	}
}
template <typename VertexType>
int  Vertex<VertexType>::getVertexIndex() const
{
	if (vertexIndex == -1)
	{
		throw IndexNotSet();
	}

	return vertexIndex;
}

/**************************************************************************
* EDGE CLASS
*	 Generic "VertexType" indicates what's being stored in the vertex
* 		(Can be a number, a letter, a class, etc)
* 		Edge needs to know this type so that it can point to multiple vertices
* 	 Generic "WeightType" indicates the weight along the edge
**************************************************************************/
template <typename VertexType, typename WeightType>
class Edge
{
	public:
		Edge();
		Edge(Vertex<VertexType>& setVertex1,
			 Vertex<VertexType>& setVertex2,
			 WeightType setWeight);
		Edge(const Edge<VertexType, WeightType>& otherEdge); // Copy Constructor
		~Edge();

		// M U T A T O R S
		// setEdgeData uses setWeight and setVertices method.
		void setEdgeData(Vertex<VertexType>& setVertex1,
						 Vertex<VertexType>& setVertex2,
						 WeightType setWeight);
		void setWeight(WeightType setWeight);
		void setVertices(Vertex<VertexType>& setVertex1,
				 	 	 Vertex<VertexType>& setVertex2);
		void insertVertex(const Vertex<VertexType>& setVertex);	// (Is this needed?)
		void freeVertex(const Vertex<VertexType>& rmVertex);
		void freeEdge();
		void setExploration(int setExplorationStatus);

		// A C C E S S O R S
		int  getExploration() const;
		Vertex<VertexType>* getVertex1() const;
		Vertex<VertexType>* getVertex2() const;
		Vertex<VertexType>* getOpposite(const Vertex<VertexType>& vertex) const;
		bool isIncidentTo(const Vertex<VertexType>& vertex) const;
		bool isAdjacentTo(const Edge<VertexType, WeightType>& otherEdge) const;
		WeightType getWeight() const;

	private:
		Vertex<VertexType> *vertex1;
		Vertex<VertexType> *vertex2;
		WeightType weight;
		EdgeEnum  explorationStatus;


};
template <typename VertexType, typename WeightType>
Edge<VertexType,WeightType>::Edge()
						   : vertex1(nullptr),
						     vertex2(nullptr),
						     weight(WeightType()),
						     explorationStatus(UNEXPLORED_EDGE)
{

}
template <typename VertexType, typename WeightType>
Edge<VertexType,WeightType>::Edge(Vertex<VertexType>& setVertex1,
							      Vertex<VertexType>& setVertex2,
							      WeightType setWeight)
						   : vertex1(&setVertex1),
							 vertex2(&setVertex2),
							 weight(setWeight),
						     explorationStatus(UNEXPLORED_EDGE)

{

}
template <typename VertexType, typename WeightType>
Edge<VertexType,WeightType>::Edge(const Edge<VertexType, WeightType>& otherEdge) // Copy Constructor
{
	// empty for now
}
template <typename VertexType, typename WeightType>
Edge<VertexType,WeightType>::~Edge()
{
	vertex1 = nullptr;
	vertex2 = nullptr;
}
// setEdgeData uses setWeight and setVertices method.
template <typename VertexType, typename WeightType>
void Edge<VertexType,WeightType>::setEdgeData(Vertex<VertexType>& setVertex1,
											  Vertex<VertexType>& setVertex2,
											  WeightType setWeight)
{
	setVertices(setVertex1, setVertex2);
	setWeight(setWeight);

}
template <typename VertexType, typename WeightType>
void Edge<VertexType,WeightType>::setWeight(WeightType setWeight)
{
	weight = setWeight;
}
template <typename VertexType, typename WeightType>
void Edge<VertexType,WeightType>::setVertices(Vertex<VertexType>& setVertex1,
		 	 	 	 	 	 	 	 	 	  Vertex<VertexType>& setVertex2)
{
	vertex1 = &setVertex1;
	vertex2 = &setVertex2;
}

template <typename VertexType, typename WeightType>
void Edge<VertexType,WeightType>::insertVertex(const Vertex<VertexType>& setVertex)
{
	// Set the vertex to any available vertex. If no vertex available,
	// throw error
	if (vertex1 == nullptr)
	{
		vertex1 = &setVertex;
	}
	else if (vertex2 == nullptr)
	{
		vertex2 = &setVertex;
	}
	else
	{
		throw Full();
	}
}

template <typename VertexType, typename WeightType>
void Edge<VertexType,WeightType>::freeVertex(const Vertex<VertexType>& rmVertex)
{
	// Set the vertex to null if rmVertex found. If no vertex found,
	// throw error
	// NOTE: this class does not allocate memory, and thus should not
	// deallocate memory. Deallocation of memory of a vertex object should
	// be handled by an external class (i.e. the graph class)
	if (vertex1 == &rmVertex)
	{
		vertex1 = nullptr;
	}
	else if (vertex2 == &rmVertex)
	{
		vertex1 = nullptr;
	}
	else
	{
		throw NotFound();
	}
}

template <typename VertexType, typename WeightType>
void Edge<VertexType,WeightType>::freeEdge()
{
	vertex1 = nullptr;
	vertex2 = nullptr;
	weight  = 0;
	explorationStatus = EdgeEnum(UNEXPLORED_EDGE);
}

template <typename VertexType, typename WeightType>
void Edge<VertexType,WeightType>::setExploration(int setExplorationStatus)
{
	// type cast into enumeration type
	explorationStatus = EdgeEnum(setExplorationStatus);
}

template <typename VertexType, typename WeightType>
int Edge<VertexType,WeightType>::getExploration() const
{
	// return appropriate exploration status
	switch (explorationStatus)
	{
		case UNEXPLORED_EDGE: 	return UNEXPLORED_EDGE;
			break;
		case DISCOVERY_EDGE:	return DISCOVERY_EDGE;
			break;
		case BACK_EDGE:			return BACK_EDGE;
			break;
		case CROSS_EDGE:		return CROSS_EDGE;
			break;
	}
}

template <typename VertexType, typename WeightType>
Vertex<VertexType>* Edge<VertexType,WeightType>::getVertex1() const
{
	return vertex1;
}
template <typename VertexType, typename WeightType>
Vertex<VertexType>* Edge<VertexType,WeightType>::getVertex2() const
{
	return vertex2;
}
template <typename VertexType, typename WeightType>
Vertex<VertexType>* Edge<VertexType,WeightType>::getOpposite(const Vertex<VertexType>& vertex) const
{
	// return opposite to vertex
	// checks if vertex1 points to same location as the indicated vertex
	if (vertex1->getVertexIndex() == vertex.getVertexIndex())
	{
//		cerr << "return v2\n";
		return  vertex2;
	}
	else if (vertex2->getVertexIndex() == vertex.getVertexIndex())
	{
//		cerr << "return v1\n";
		return vertex1;
	}
}
template <typename VertexType, typename WeightType>
bool Edge<VertexType,WeightType>::isIncidentTo(const Vertex<VertexType>& vertex) const
{
	// checks if either of the two vertices of this edge are the indicated
	// vertex. If so, then the edge is incident to this vertex.
	if (vertex1 == &vertex || vertex2 == &vertex)
	{
		return true;
	}
	else
	{
		return false;
	}
}
template <typename VertexType, typename WeightType>
bool Edge<VertexType,WeightType>::isAdjacentTo(const Edge<VertexType, WeightType>& otherEdge) const
{
	// checks if the edges share a common vertex
	if (this->getVertex1() == otherEdge.getVertex1() ||
		this->getVertex1() == otherEdge.getVertex2() ||
		this->getVertex2() == otherEdge.getVertex1() ||
		this->getVertex2() == otherEdge.getVertex2())
	{
		return true;
	}
	else
	{
		return false;
	}
}
template <typename VertexType, typename WeightType>
WeightType Edge<VertexType,WeightType>::getWeight() const // could use operator*, but this suffices
{
	return weight;
}


/**************************************************************************
* UNDIRECTED GRAPH CLASS (implemented as an adjacency matrix)
*	 Generic "VertexType" indicates what's being stored in the vertex
* 		(Can be a number, a letter, a class, etc)
* 		Graph needs to know this type so that it can create an Edge.
* 		Edge needs to know this type so that it can point to multiple vertices
* 	 Generic "WeightType" indicates the weight along the edge of the graph
*
***************************************************************************/
template <typename VertexType, typename WeightType>
class UndirectedGraph
{
	public:

		typedef Heap<TopLowestWeight<HeapItem<Edge<VertexType,WeightType>* > >,
								 	 Edge<VertexType,WeightType>* >
									 GraphEdgeHeap;
		UndirectedGraph(int numSize = 10);
	/*--> Copy Constructor HERE <--*/
		~UndirectedGraph();

		// M U T A T O R S
		void insert(VertexType vertexData1,						// MODIFY FOR DIRECTED GRAPH
					VertexType vertexData2,
					WeightType weight);
		void removeVertex(VertexType vertexData);
		void removeVertex(Vertex<VertexType>& rmVertex);		// MODIFY FOR DIRECTED GRAPH
		void removeEdge(Edge<VertexType,WeightType>& rmEdge);
		void removeEdge(VertexType vertexData1,					// MODIFY FOR DIRECTED GRAPH
						VertexType vertexData2,
						WeightType weight);
		void destroy();
		// A C C E S S O R S
		vector<Vertex<VertexType>* >& vertices() const;
		vector<Edge<VertexType,WeightType>* >& edges() const;
		GraphEdgeHeap& incidentEdges(VertexType vertexData); 	// MODIFY FOR DIRECTED GRAPH (need to loop both ROW and COL, instead of just row)
																// add method incidentDIRECTEDEdges????
		vector<Vertex<VertexType>* >& incidentVertices(Edge<VertexType,WeightType>& edge) const;

		// Graph functionality
		void DepthFirstSearch(VertexType vertexData);
		void DepthFirstSearch(Vertex<VertexType> &vertex);		// MODIFY FOR DIRECTED GRAPH
		void discoveryEdges();									// Need to modify all these graph functionality methods
		void backEdges();

		// Output testing
		void display() const;

	private:

		/* given a vertex index (for the matrix), returns a pointer to a
		 * vertex if found, or nullptr if not found */
		Vertex<VertexType>* returnVertexFromIndex(int vertexIndex) const;
		Vertex<VertexType>* returnVertexFromData(VertexType vertexData) const;
		Edge<VertexType,WeightType>* returnEdgeFromData(VertexType vertexData1,
														VertexType vertexData2,
														WeightType weight) const;
		int returnAvailableMatrixIndex() const;

		vector<vector<Edge<VertexType,WeightType>* > > edgeMatrix;
			// 2D-array of pointers to edges (matrix of pointers to edges)
		vector<Vertex<VertexType>* > vertexList;
			// keeps track of our vertices
		vector<Edge<VertexType,WeightType>* > edgeList;
			// keeps track of our edges
		int vertexCount;
		int edgeCount;
		int size;
		GraphEdgeHeap *incidentEdgeList;


};

template <typename VertexType, typename WeightType>
UndirectedGraph<VertexType,WeightType>::UndirectedGraph(int numSize)
									  : edgeMatrix(numSize),
									    vertexList(),
									    edgeList(),
										vertexCount(0),
									    edgeCount(0),
									    size(numSize),
									    incidentEdgeList(nullptr)
{
	/* Create [size x size] matrix */
	for (int i = 0; i < size; i++)
	{
		(edgeMatrix[i]).resize(size);
	}

	/* initialize every location to nullptr */
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			edgeMatrix[row][col] = nullptr;
		}
	}

}
//--> Copy Constructor HERE <--
template <typename VertexType, typename WeightType>
UndirectedGraph<VertexType,WeightType>::~UndirectedGraph()
{
	destroy();

}

// M U T A T O R S
template <typename VertexType, typename WeightType>
void UndirectedGraph<VertexType,WeightType>::insert(VertexType vertexData1,
													VertexType vertexData2,
													WeightType weight)
{

	Vertex<VertexType> 			*vertex1;
	Vertex<VertexType> 			*vertex2;

	Edge<VertexType,WeightType> *newEdge;

	typename vector<Vertex<VertexType>* >::iterator vectorIt1;
	typename vector<Vertex<VertexType>* >::iterator vectorIt2;
	typename vector<Edge<VertexType, WeightType>* >::iterator edgeIt;
	int newIndex;

	newIndex = this->returnAvailableMatrixIndex();

	vertex1 = this->returnVertexFromData(vertexData1);
	vertex2 = this->returnVertexFromData(vertexData2);

	// if no such existing vertices, create both
	if (vertex1 == nullptr && vertex2 == nullptr)
	{
		vertex1 = new Vertex<VertexType>(vertexData1, newIndex);

		vertexList.push_back(vertex1);
		++vertexCount;

		/* generate new vertex index for second vertex */
		newIndex = this->returnAvailableMatrixIndex();

		vertex2 = new Vertex<VertexType>(vertexData2, newIndex);

		vertexList.push_back(vertex2);
		++vertexCount;
	}
	else if (vertex1 == nullptr)
	{
		vertex1 = new Vertex<VertexType>(vertexData1, newIndex);

		vertexList.push_back(vertex1);
		++vertexCount;
	}
	else if (vertex2 == nullptr)
	{
		vertex2 = new Vertex<VertexType>(vertexData2, newIndex);

		vertexList.push_back(vertex2);
		++vertexCount;
	}

	newEdge = this->returnEdgeFromData(**vertex1, **vertex2, weight);


	// if edge was not found, add it to list
	if (newEdge == nullptr)
	{
		/* create the edge */
		newEdge = new Edge<VertexType,WeightType>(*vertex1, *vertex2, weight);

		edgeList.push_back(newEdge);
		edgeCount++;
	}

	if (vertexCount > size)
	{
		throw Full();
	}
	/* have the edgeMatrix point to this newly created edge */
	/*NOTE: Since this is a undirected graph, we shall equate the transposes */

	edgeMatrix[vertex1->getVertexIndex()][vertex2->getVertexIndex()] = newEdge;
	edgeMatrix[vertex2->getVertexIndex()][vertex1->getVertexIndex()] = newEdge;

}
template <typename VertexType, typename WeightType>
void UndirectedGraph<VertexType,WeightType>::removeVertex(VertexType vertexData)
{
	Vertex<VertexType> *vertexPtr;


	/* Check if vertex exists*/
	vertexPtr = this->returnVertexFromData(vertexData);


	if (vertexPtr!= NULL)
	{
		removeVertex(*vertexPtr);
	}
	else
	{
		throw NotFound();
	}
}
template <typename VertexType, typename WeightType>
void UndirectedGraph<VertexType,WeightType>::removeVertex(Vertex<VertexType>& rmVertex)
{
	typename vector<Vertex<VertexType>* >::iterator vertexIt;
	typename vector<Edge<VertexType,WeightType>* >::iterator edgeIt;

	Vertex<VertexType> *rmVertexPtr;
	Edge<VertexType,WeightType> *rmEdge;
	int index;

	rmVertexPtr = &rmVertex;

	/* iterate to location of vertex in vertexList */
	vertexIt = vertexList.begin();
	while (vertexIt != vertexList.end() && *vertexIt != &rmVertex)
	{
		++vertexIt;
	}

	/* if vertex not found, throw exception */
	if (vertexIt == vertexList.end())
	{
		throw NotFound();
	}

	/* delete vertex, remove from list, set the respective vertex pointer
	 *  in edge to nullptr  */

	// find the edge O(n)
	index = 0;

	// we'll loop through columns
	rmEdge = edgeMatrix[rmVertexPtr->getVertexIndex()][index];

	/* iterate to location of vertex in vertexList */
	edgeIt = edgeList.begin();
	while (edgeIt != edgeList.end() && *edgeIt != rmEdge)
	{
		++edgeIt;
	}

	// since this is an undirected graph, delete by looping thru
	// only either a row or a column (set to nullptr as well).
	while (index < size)
	{
		// free the pointers that any edges may have
		if (rmEdge != nullptr)
		{

			cout << "rmEdge val is: " << rmEdge->getWeight() << endl;
			rmEdge->freeEdge();

			rmEdge = nullptr;

			// set transpose location (b/c undirected graph) to nullptr
			edgeMatrix[index][rmVertexPtr->getVertexIndex()] = nullptr;

			// delete the edge
			delete rmEdge;

			// remove from edge list
			edgeList.erase(edgeIt);
			edgeCount--;
		}

		index++;

		// we'll loop through columns
		rmEdge = edgeMatrix[rmVertexPtr->getVertexIndex()][index];

		edgeIt = edgeList.begin();
		while (edgeIt != edgeList.end() && *edgeIt != rmEdge)
		{
			++edgeIt;
		}

	}

	/* delete vertex itself */
	delete rmVertexPtr;

	/* remove vertex from the vertexList */
	vertexList.erase(vertexIt);
	vertexCount--;

}
template <typename VertexType, typename WeightType>
void UndirectedGraph<VertexType,WeightType>::removeEdge(Edge<VertexType,WeightType>& rmEdge)
{
	typename vector<Edge<VertexType,WeightType>* >::iterator edgeIt;
	Edge<VertexType,WeightType> *rmEdgePtr;
	int indexV1 = -1;
	int indexV2 = -1;

	rmEdgePtr = &rmEdge;

	/* iterate to location of edge in edge list */
	edgeIt = edgeList.begin();
	while (edgeIt != edgeList.end() && *edgeIt != rmEdgePtr)
	{
		++edgeIt;
	}

	/* if vertex not found, throw exception */
	if (edgeIt == edgeList.end())
	{
		throw NotFound();
	}

	/* find inidices of two vertices */
	indexV1 = rmEdgePtr->getVertex1()->getVertexIndex();
	indexV2 = rmEdgePtr->getVertex2()->getVertexIndex();

	/* detach the vertices from the edge */
	rmEdgePtr->freeEdge();

	/* reset positions in edgeMatrix to nullptr */
	edgeMatrix[indexV1][indexV2] = nullptr;
	edgeMatrix[indexV2][indexV1] = nullptr;

	/* deallocate memory for edge */
	delete rmEdgePtr;

	/* remove the edge from edge list */
	edgeList.erase(edgeIt);
	edgeCount--;


}
template <typename VertexType, typename WeightType>
void UndirectedGraph<VertexType,WeightType>::removeEdge(VertexType vertexData1,
														VertexType vertexData2,
														WeightType weight)
{

	Edge<VertexType,WeightType>* edgePtr;

	/* check to see if edge exists */
	edgePtr = this->returnEdgeFromData(vertexData1, vertexData2, weight);

	if (edgePtr != nullptr)
	{
		removeEdge(*edgePtr);
	}
	else
	{
		throw NotFound();
	}

}

template <typename VertexType, typename WeightType>
void UndirectedGraph<VertexType,WeightType>::destroy()
{
	//NOTE: You can re-implement this method by looping (wrapping)
	// over the removeVertex method!

	typename vector<Vertex<VertexType>* >::iterator vertexIt;

	// Part 1
	if (incidentEdgeList != nullptr)
	{
		delete incidentEdgeList;
	}

	// Part 2
	for (vertexIt = vertexList.begin(); vertexIt != vertexList.end(); ++vertexIt)
	{
		if (*vertexIt != nullptr)
		{
			delete *vertexIt;
			*vertexIt = nullptr;
		}
	}

	typename vector<Edge<VertexType, WeightType>* >::iterator edgeIt;

	for (edgeIt = edgeList.begin(); edgeIt != edgeList.end(); ++edgeIt)
	{
		if (*edgeIt != nullptr)
		{
			delete *edgeIt;

			*edgeIt = nullptr;
		}

	}

	vertexList.clear();
	edgeList.clear();



	//reset matrix back to defaults
	/* initialize every location to nullptr */
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			edgeMatrix[row][col] = nullptr;
		}
	}

}

/**************************************************************************
 *  A wrapper for the true DFS (for user simplicity)
 **************************************************************************/
template <typename VertexType, typename WeightType>
void UndirectedGraph<VertexType,WeightType>::DepthFirstSearch(VertexType vertexData)
{
	Vertex<VertexType> *vertex;

	vertex = returnVertexFromData(vertexData);

	/* finds the vertex from the data provided, calls real DFS */
	DepthFirstSearch(*vertex);
}

/**************************************************************************
 *  A recursive definition for a depth-first search!
 **************************************************************************/
template <typename VertexType, typename WeightType>
void UndirectedGraph<VertexType,WeightType>::DepthFirstSearch(Vertex<VertexType> &vertex)
{
	GraphEdgeHeap listOfEdges; // list of edges sorted by lowest weight
	Edge<VertexType, WeightType> *edgePtr = nullptr;
	Vertex<VertexType> *oppositeVertex = nullptr;

	int size = 0;

	if (vertex.getExploration() == UNEXPLORED_VERTEX)
	{
		cout << "Vertex visited: " << *vertex << endl;
	}

	/* Set vertex VISITED */
	vertex.setExploration(VISITED_VERTEX);

	/* Retrieve all possible edges */
	listOfEdges = incidentEdges(*vertex);

	/* call method incidentDIRECTEDEdges if directed graph */

	/* compute size of this list */
	size = listOfEdges.getNumElements();

	/* iterate throughout list -- by removing the front */
	for (int i = 0; i < size; i++)
	{

		/* remove top from list and have edgePtr point to the item */
		edgePtr = listOfEdges.removeTop().getData();

//		cerr << "Current Edge: " << edgePtr->getWeight() << endl;

		/* perform operations ONLY if edge is unexplored! */
		if (edgePtr->getExploration() == UNEXPLORED_EDGE)
		{
			/* locate the opposite vertex and have oppositeVertex point to it */
			oppositeVertex = edgePtr->getOpposite(vertex);

			/* If the opposite vertex has not been visited, recursively call
			 * this method */
			if (oppositeVertex->getExploration() == UNEXPLORED_VERTEX)
			{
//				cerr << **oppositeVertex << " is UNEXPLORED.\n";
				/* set edge status to a discovery edge */
				edgePtr->setExploration(DISCOVERY_EDGE);

				/* recurse other adjacent edges*/
				DepthFirstSearch(*oppositeVertex);
			}
			else /* we have a back edge! */
			{
//				cerr << "OUT\n";
				edgePtr->setExploration(BACK_EDGE);
			}
		}

	}





}

// A C C E S S O R S
template <typename VertexType, typename WeightType>
vector<Vertex<VertexType>* >& UndirectedGraph<VertexType,WeightType>::vertices() const
{
	return vertexList;
}
template <typename VertexType, typename WeightType>
vector<Edge<VertexType,WeightType>* >& UndirectedGraph<VertexType,WeightType>::edges() const
{
	return edgeList;
}

template <typename VertexType, typename WeightType>
typename UndirectedGraph<VertexType,WeightType>::GraphEdgeHeap& UndirectedGraph<VertexType,WeightType>::incidentEdges(VertexType vertexData)
{
	Edge<VertexType,WeightType> * edgePtr;
	Vertex<VertexType> *vertexPtr;

	// if the incidentEdgeList (ptr) is not equal to nullptr, then we
	// have already allocated memory previously (so delete it).
	if (incidentEdgeList != nullptr)
	{
		delete incidentEdgeList;
		incidentEdgeList = nullptr;
	}

	if (incidentEdgeList == nullptr)
	{
		incidentEdgeList = new GraphEdgeHeap;
	}
	else
	{
		cout << "Error -- incidentEdgeList allocation of memory failure.\n";
	}


	/* Find the vertex from the given vertex data */
	vertexPtr = this->returnVertexFromData(vertexData);

	if (vertexPtr != nullptr)
	{
		int index = 0;

		/* Point edgePtr to an edge (if it exists) in the specified row
		 * that corresponds to the vertex index */
		edgePtr = edgeMatrix[vertexPtr->getVertexIndex()][index];

		/* loop through a column of the adjacency matrix (const row) */
		while (index < size)
		{
			/* if the element is not equal to nullptr, push it on vector
			 * this means that an edge is connected to this vertex */
			if (edgePtr != nullptr)
			{
				incidentEdgeList->insert(edgePtr);

			}

			index++;
			edgePtr = edgeMatrix[vertexPtr->getVertexIndex()][index];

		}
	}
	else
	{
		throw NotFound();
	}

	/* return the heap (i.e. priority queue) */
	return *incidentEdgeList;
}

template <typename VertexType, typename WeightType>
vector<Vertex<VertexType>* >& UndirectedGraph<VertexType,WeightType>::incidentVertices(Edge<VertexType,WeightType>& edge) const
{
	vector<Vertex<VertexType>* > incidentVerticesList;

	incidentVerticesList.push_back(edge.getVertex1());
	incidentVerticesList.push_back(edge.getVertex2());

	/* return the vector */
	return incidentVerticesList;
}

template <typename VertexType, typename WeightType>
void UndirectedGraph<VertexType,WeightType>::discoveryEdges()
{
	cout << endl << "DISCOVERY EDGES:\n";

	typename vector<Edge<VertexType,WeightType>* >::const_iterator edgeIt;

	if (edgeList.empty())
	{
		cout << "N/A\n";
	}
	else
	{
		for (edgeIt = edgeList.cbegin(); edgeIt != edgeList.cend(); ++edgeIt)
		{
			if ((*edgeIt)->getExploration() == DISCOVERY_EDGE)
			{
			cout << "The edge that connects "
				 << setw(10)
				 << **((*edgeIt)->getVertex1())
				 << " and "
				 << setw(10)
				 << **((*edgeIt)->getVertex2())
				 << " with weight: "
				 << (*edgeIt)->getWeight()
				 << " is a discovery edge." << endl;

			}
		}
	}
}
template <typename VertexType, typename WeightType>
void UndirectedGraph<VertexType,WeightType>::backEdges()
{
	cout << endl << "BACK EDGES:\n";

	typename vector<Edge<VertexType,WeightType>* >::const_iterator edgeIt;

	if (edgeList.empty())
	{
		cout << "N/A\n";
	}
	else
	{
		for (edgeIt = edgeList.cbegin(); edgeIt != edgeList.cend(); ++edgeIt)
		{
			if ((*edgeIt)->getExploration() == BACK_EDGE)
			{
			cout << "The edge that connects "
				 << setw(10)
				 << **((*edgeIt)->getVertex1())
				 << " and "
				 << setw(10)
				 << **((*edgeIt)->getVertex2())
				 << " with weight: "
				 << (*edgeIt)->getWeight()
				 << " is a back edge." << endl;

			}
		}
	}
}


template <typename VertexType, typename WeightType>
void UndirectedGraph<VertexType,WeightType>::display() const
{
	Vertex<VertexType> *vertexPtr;

	cout << left;

	cout << "THE ADJACENCY MATRIX:\n";
	cout << "=================================================================\n";
	// outputs vertex horizontal header
	cout << setw(15) << "";

	// loop throughout (width) size of matrix, output horizontal HEADER
	for (int index = 0; index < size; index++)
	{
		cout << setw(9);

		/* returns a vertex that has a vertexIndex of index.
		 * returns nullptr if not found */
		vertexPtr = returnVertexFromIndex(index);

		if (vertexPtr == nullptr)
		{
			cout << "N/A ";
		}
		else
		{
			// output vertex data
			cout << **vertexPtr << " ";		}

	}

	cout << endl;

	// outputs vertex horizontal dashes beneath header
	cout << setw(15) << "";
	for (int i = 0; i < size; i++)
	{
		cout << setw(10) << "----- ";
	}

	cout << endl;

	// loop throughout (width) size of matrix, output vertical HEADER
	for (int row = 0; row < size; row++)
	{
		cout << setw(15);

		/* returns a vertex that has a vertexIndex of index.
		 * returns nullptr if not found */
		vertexPtr = returnVertexFromIndex(row);

		if (vertexPtr == nullptr)
		{
			cout << "N/A" << "| ";
		}
		else
		{
			// output vertex data
			cout << **vertexPtr << "| ";
		}

		// outputs element in each column (of the same row)
		for (int col = 0; col < size; col++)
		{
			cout << setw(10);
			if (edgeMatrix[row][col] == nullptr)
			{
				cout << "0";
			}
			else
			{
				cout << edgeMatrix[row][col]->getWeight();
			}
		}
		cout << endl << endl;


	}


	/* OUTPUT VERTEX DATA */
	cout << endl << "VERTEX INFO:\n";
	cout << "There exists " << vertexList.size() << " vertices.\n";

	typename vector<Vertex<VertexType>* >::const_iterator vertexIt;

	if (vertexList.empty())
	{
		cout << "N/A\n";
	}
	else
	{
		for (vertexIt = vertexList.cbegin(); vertexIt != vertexList.cend(); ++vertexIt)
		{
			if (*vertexIt != nullptr)
			{
				cout << "The vertex " << ***vertexIt << " has index: " << (*vertexIt)->getVertexIndex() << endl;
			}
		}
	}

	/* OUTPUT EDGE DATA */
	cout << endl << "EDGE INFO:\n";
	cout << "There exists " << edgeList.size() << " edges.\n";

		typename vector<Edge<VertexType,WeightType>* >::const_iterator edgeIt;

		if (edgeList.empty())
		{
			cout << "N/A\n";
		}
		else
		{
			for (edgeIt = edgeList.cbegin(); edgeIt != edgeList.cend(); ++edgeIt)
			{
				cout << "The edge connecting "
					 << setw(10)
					 << **((*edgeIt)->getVertex1())
					 << " and "
					 << setw(10)
					 << **((*edgeIt)->getVertex2())
					 << " has weight: "
					 << (*edgeIt)->getWeight() << endl;
			}
		}

	cout << right;

	cout << "=================================================================\n";
}

/* given a vertex index (for the matrix), returns a pointer to a
 * vertex if found, or nullptr if not found */
template <typename VertexType, typename WeightType>
 Vertex<VertexType>* UndirectedGraph<VertexType,WeightType>::returnVertexFromIndex(int searchVertexIndex) const
{
	typename vector<Vertex<VertexType>* >::const_iterator vertexIt;

	vertexIt = vertexList.cbegin();
	while (vertexIt != vertexList.cend())
	{
		if ((*vertexIt)->getVertexIndex() == searchVertexIndex)
		{
			return *vertexIt;
		}

		++vertexIt;
	}

	return nullptr;

}

template <typename VertexType, typename WeightType>
 Vertex<VertexType>* UndirectedGraph<VertexType,WeightType>::returnVertexFromData(VertexType vertexData) const
{
	typename vector<Vertex<VertexType>* >::const_iterator vertexIt;

	/* Check if vertex exists*/
	vertexIt = vertexList.cbegin();
	while (vertexIt != vertexList.cend())
	{
		// compare the two vertex VALUES
		if (***vertexIt == vertexData)
		{
			return *vertexIt;
		}
		else
		{
			++vertexIt;
		}
	}

	return nullptr;

}

template <typename VertexType, typename WeightType>
 Edge<VertexType,WeightType>* UndirectedGraph<VertexType,WeightType>::returnEdgeFromData(VertexType vertexData1,
																						 VertexType vertexData2,
																						 WeightType weight) const
{
	typename vector<Edge<VertexType,WeightType>* >::const_iterator edgeIt;

	Vertex<VertexType> *v1;
	Vertex<VertexType> *v2;


	/* Check if vertex exists*/
	edgeIt = edgeList.cbegin();

	while (edgeIt != edgeList.cend() )
	{
		v1 = (*edgeIt)->getVertex1();
		v2 = (*edgeIt)->getVertex2();

		// compare to see if edge has same vertex values and weight
		if (**v1 == vertexData1 &&
		    **v2 == vertexData2 &&
		   (*edgeIt)->getWeight() == weight)
		{
			return *edgeIt;
		}
		else
		{
			++edgeIt;
		}

	}

	return nullptr;

}
/*
 *  Returns the first available index that may represent a vertex
 *
 */
template <typename VertexType, typename WeightType>
int UndirectedGraph<VertexType,WeightType>::returnAvailableMatrixIndex() const
{
//	/* return fail state if maxed out */
//	if (vertexCount == size)
//	{
//		return -1;
//	}

	int index = 0;
	bool indexFound = false; /*Outer While loop*/
	bool indexExists = false;/*Inner While loop*/

	Vertex<VertexType> *vertexPtr;
	typename vector<Vertex<VertexType>* >::const_iterator vertexIt;

	while (index < size && !indexFound)
	{
		vertexIt = vertexList.cbegin();

		/* attempt to find the smallest available index possible */
		while (vertexIt != vertexList.cend() && !indexExists)
		{
			/* if the indices match,  exists */
			if (index == (*vertexIt)->getVertexIndex())
			{
				indexExists = true;
			}
			else
			{
				vertexIt++;
			}
		}

		if (!indexExists)
		{
			indexFound = true;
		}
		else
		{
			indexExists = false;
			index++;
		}
	}

	return index;

}


#endif /* UNDIRECTEDGRAPHHEADER_H_ */
