/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // outgoing edges
	bool visited;          // auxiliary field
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool processing = false;
	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set
	vector<vector<int>> warshallPath;
	vector<vector<double>> warshallDist;
	vector<vector<double>> warshallWeight;

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void dijkstraShortestPath(const T &s);
	void dijkstraShortestPathOld(const T &s);
	void unweightedShortestPath(const T &s);
	void bellmanFordShortestPath(const T &s);
	vector<T> getPath(const T &origin, const T &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;
	void buildArrays();
	int getVertexIndex(const T& info) const;

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {

    for(int i = 0; i < this->vertexSet.size();i++){

        this->vertexSet.at(i)->dist = INF;
        this->vertexSet.at(i)->path = NULL;
        this->vertexSet.at(i)->visited = false;
    }

    Vertex<T>* startVertex = this->findVertex(origin);

    if(!startVertex)
        return;

    startVertex->dist = 0;

    MutablePriorityQueue<Vertex<T>> prior_queue;

    prior_queue.insert(startVertex);
    startVertex->visited = true;

    while(!prior_queue.empty()) {

        Vertex<T>* currentVertex = prior_queue.extractMin();

        vector<Edge<T>> edges = currentVertex->adj;

        for(int i = 0; i < edges.size(); i++){

            Edge<T> currentAdj = edges.at(i);

            if(currentAdj.dest->getDist() > currentVertex->getDist() + currentAdj.weight){

                currentAdj.dest->dist = currentVertex->getDist() + currentAdj.weight;
                currentAdj.dest->path = currentVertex;

                if(!currentAdj.dest->visited){

                    prior_queue.insert(currentAdj.dest);
                    currentAdj.dest->visited = true;
                }else{


                    prior_queue.decreaseKey(currentAdj.dest);
                }

            }

        }

    }

}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const {

    Vertex<T> *currentVertex = findVertex(dest);
    vector<T> res = {currentVertex->getInfo()};

    while ((currentVertex = currentVertex->getPath()) != NULL)
        res.insert(res.begin(), currentVertex->getInfo());

        return res;

}

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {

    for(int i = 0; i < this->vertexSet.size();i++){

        this->vertexSet.at(i)->dist = INF;
        this->vertexSet.at(i)->path = NULL;
        this->vertexSet.at(i)->visited = false;
    }

    Vertex<T>* startVertex = this->findVertex(orig);

    if(!startVertex)
        return;

    startVertex->dist = 0;

    queue<Vertex<T>*> queue;

    queue.push(startVertex);
    startVertex->visited = true;

    while(!queue.empty()) {

        Vertex<T>* currentVertex = queue.front();
        queue.pop();


        vector<Edge<T>> edges = currentVertex->adj;

        for(int i = 0; i < edges.size(); i++){

            Edge<T> currentAdj = edges.at(i);

            if(!currentAdj.dest->visited){

                queue.push(currentAdj.dest);


                currentAdj.dest->dist = currentVertex->getDist() + 1;
                currentAdj.dest->path = currentVertex;
                currentAdj.dest->visited = true;

            }

        }

    }



}

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {

    for(int i = 0; i < this->vertexSet.size();i++){

        this->vertexSet.at(i)->dist = INF;
        this->vertexSet.at(i)->path = NULL;
    }

    Vertex<T>* startVertex = this->findVertex(orig);

    if(!startVertex)
        return;

    startVertex->dist = 0;

    for(int i = 1; i < this->vertexSet.size() ;i++){

        for(int j = 0; j < this->vertexSet.size();j++){

            Vertex<T>* currentVertex = vertexSet.at(j);

            for(int k = 0; k < currentVertex->adj.size();k++){

                Edge<T> currentEdge = currentVertex->adj.at(k);

                if( (currentEdge.dest->getDist() > currentVertex->getDist() + currentEdge.weight)){

                    currentEdge.dest->dist = currentVertex->getDist() + currentEdge.weight;
                    currentEdge.dest->path = currentVertex;

                }

            }


        }


    }


}


/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {


    this->buildArrays();

    for(int k = 0; k < this->vertexSet.size();k++){

        for(int i = 0; i < this->vertexSet.size();i++){

            for(int j = 0; j < this->vertexSet.size();j++){


                if(warshallDist[i][j] > warshallDist[i][k] + warshallDist[k][j]){


                    warshallDist[i][j] = warshallDist[i][k] + warshallDist[k][j];
                    warshallPath[i][j] = warshallPath[k][j];

                }

            }


        }

    }



}

template<class T>
void printVector(vector<vector<T>> v){


    for(int i = 0; i < v.size(); i++){

        for(int j = 0; j < v.at(0).size(); j++){


            cout << v[i][j] << "    ";

        }


        cout << endl;
    }


    cout << endl;
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;

	int startIndex = this->getVertexIndex(orig);
	int endIndex = this->getVertexIndex(dest);
    int currentIndex = endIndex;

    printVector(warshallPath);
    printVector(warshallDist);
    printVector(warshallWeight  );


	res.insert(res.begin(),vertexSet.at(currentIndex)->info);

	while(currentIndex != startIndex){

	    currentIndex = warshallPath[orig][currentIndex];
        res.insert(res.begin(),vertexSet.at(currentIndex)->info);
	}


	return res;
}

template<class T>
int Graph<T>::getVertexIndex(const T& info) const{

    for(int i = 0; i < this->vertexSet.size();i++){

        if(this->vertexSet.at(i)->getInfo() == info)
            return i;

    }

    return -1;
}

template<class T>
void Graph<T>::buildArrays(){

    vector<vector<int>> warshallPath(this->vertexSet.size());
    vector<vector<double>> warshallDist(this->vertexSet.size());
    vector<vector<double>> warshallWeight(this->vertexSet.size());


    for(int i = 0; i < this->vertexSet.size();i++){

        vector<int> temp(this->vertexSet.size(),-1);
        vector<double> temp2(this->vertexSet.size(),INF);
        vector<double> temp3(this->vertexSet.size(),0);

        warshallPath.at(i) = temp;
        warshallDist.at(i) = temp2;
        warshallWeight.at(i) = temp3;

    }

    for(int i = 0; i < this->vertexSet.size();i++){

        Vertex<T>* currentVertex = this->vertexSet.at(i);

        for(int j = 0; j < currentVertex->adj.size();j++){

                Edge<T> currentEdge = currentVertex->adj.at(j);

                warshallWeight[i][this->getVertexIndex(currentEdge.dest->getInfo())] = currentEdge.weight;
                warshallPath[i][this->getVertexIndex(currentEdge.dest->getInfo())] = i;


        }

    }


    for(int i = 0; i < this->vertexSet.size(); i++){

        for(int j = 0; j < this->vertexSet.size(); j++){


            if(warshallWeight[i][j] == 0){

                if(i != j){

                    warshallWeight[i][j] == INF;
                }

            }

            warshallDist[i][j] = warshallWeight[i][j];
            warshallPath[i][j] = i;

        }

    }


    this->warshallPath = warshallPath;
    this->warshallDist = warshallDist;
    this->warshallWeight = warshallWeight;



}


#endif /* GRAPH_H_ */
