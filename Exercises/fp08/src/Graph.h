/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <cmath>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;

constexpr auto INF = std::numeric_limits<double>::max();

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
template <class T>
class Vertex {
	T info;
	vector<Edge<T> *> outgoing;  // adj
	vector<Edge<T> *> incoming;
	Edge<T> * addEdge(Vertex<T> *dest, double c, double f);
	Vertex(T in);

	bool visited;  // for path finding
	Edge<T> *path; // for path finding

public:
	T getInfo() const;
	vector<Edge<T> *> getAdj() const;
	friend class Graph<T>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {
}

template <class T>
Edge<T> *Vertex<T>::addEdge(Vertex<T> *dest, double c, double f) {
	Edge<T> * e = new Edge<T>(this, dest, c, f);
	this->outgoing.push_back(e);
	dest->incoming.push_back(e);
	return e;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
vector<Edge<T> *> Vertex<T>::getAdj() const {
	return this->outgoing;
}


/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
template <class T>
class Edge {
	Vertex<T> * orig;
	Vertex<T> * dest;
	double capacity;
	double flow;
	Edge(Vertex<T> *o, Vertex<T> *d, double c, double f=0);

public:
	double getFlow() const;
	Vertex<T> *getDest() const;

	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w, double f): orig(o), dest(d), capacity(w), flow(f){}

template <class T>
double Edge<T>::getFlow() const {
	return flow;
}

template <class T>
Vertex<T>* Edge<T>::getDest() const {
	return dest;
}


/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	Vertex<T>* findVertex(const T &inf) const;
	void resetFlows();
    bool findAugmentationPath(T source, T target);
    void testAndVisit(queue<Vertex<T>*>& vertexQueue, Edge<T>* edge, Vertex<T>* vertex, double residual);
    double findMinResidualAlongPath(T source, T target);
    void augmentFlowAlongPath(T source, T target, double f);

public:
	vector<Vertex<T> *> getVertexSet() const;
	Vertex<T> *addVertex(const T &in);
	Edge<T> *addEdge(const T &sourc, const T &dest, double c, double f=0);
	void fordFulkerson(T source, T target);

};

template <class T>
Vertex<T> * Graph<T>::addVertex(const T &in) {
	Vertex<T> *v = findVertex(in);
	if (v != nullptr)
		return v;
	v = new Vertex<T>(in);
	vertexSet.push_back(v);
	return v;
}

template <class T>
Edge<T> * Graph<T>::addEdge(const T &sourc, const T &dest, double c, double f) {
	auto s = findVertex(sourc);
	auto d = findVertex(dest);
	if (s == nullptr || d == nullptr)
		return nullptr;
	else
		return s->addEdge(d, c, f);
}

template <class T>
Vertex<T>* Graph<T>::findVertex(const T & inf) const {
	for (auto v : vertexSet)
		if (v->info == inf)
			return v;
	return nullptr;
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}


/* FLOW FUNCTIONS */

template <class T>
void Graph<T>::resetFlows(){

    for(Vertex<T>* v : this->vertexSet){

        for(Edge<T>* e : v->incoming){

            e->flow = 0;
        }

        for(Edge<T>* e : v->outgoing){

            e->flow = 0;
        }
    }


}


template <class T>
bool Graph<T>::findAugmentationPath(T source, T target){

    for(Vertex<T>* v : this->vertexSet)
        v->visited = false;

    Vertex<T>* startVertex = findVertex(source);
    Vertex<T>* endVertex = findVertex(target);

    queue<Vertex<T>*> vertexQueue;

    vertexQueue.push(startVertex);

    while(!vertexQueue.empty() && !endVertex->visited){

        Vertex<T>* currentVertex = vertexQueue.front();
        vertexQueue.pop();

        for(Edge<T>* e : currentVertex->outgoing)
            testAndVisit(vertexQueue,e,e->getDest(),e->capacity - e->getFlow());

        for(Edge<T>* e : currentVertex->incoming)
            testAndVisit(vertexQueue,e,e->orig,e->getFlow());
    }

    return endVertex->visited;
}

template <class T>
void Graph<T>::testAndVisit(queue<Vertex<T>*>& vertexQueue, Edge<T>* edge, Vertex<T>* vertex, double residual){


    if(!vertex->visited && residual > 0){

        vertex->visited = true;
        vertex->path = edge;
        vertexQueue.push(vertex);

    }

}

template <class T>
double Graph<T>::findMinResidualAlongPath(T source, T target){

    double f = INF;

    Vertex<T>* vertex = findVertex(target);
    Vertex<T>* sourceVertex = findVertex(source);

    while(vertex->getInfo() != sourceVertex->getInfo()){

        Edge<T>* pathEdge = vertex->path;

        if(pathEdge->getDest()->getInfo() == vertex->getInfo()){

            f < pathEdge->capacity - pathEdge->getFlow() ? f = f : f = pathEdge->capacity - pathEdge->getFlow();
            vertex = pathEdge->orig;
        }
        else{

            f < pathEdge->getFlow() ? f = f : f = pathEdge->getFlow();
            vertex = pathEdge->dest;

        }


    }

    return f;
}

template <class T>
void Graph<T>::augmentFlowAlongPath(T source, T target, double f){

    Vertex<T>* vertex = findVertex(target);
    Vertex<T>* sourceVertex = findVertex(source);

    while(vertex->getInfo() != sourceVertex->getInfo()){

        Edge<T>* pathEdge = vertex->path;

        if(pathEdge->getDest()->getInfo() == vertex->getInfo()){

            pathEdge->flow += f;
            vertex = pathEdge->orig;
        }
        else{

            pathEdge->flow -= f;
            vertex = pathEdge->dest;

        }

    }

}


/**
 * Finds the maximum flow in a graph using the Ford Fulkerson algorithm
 * (with the improvement of Edmonds-Karp).
 * Assumes that the graph forms a flow network from source vertex 's'
 * to sink vertex 't' (distinct vertices).
 * Receives as arguments the source and target vertices (identified by their contents).
 * The result is defined by the "flow" field of each edge.
 */
template <class T>
void Graph<T>::fordFulkerson(T source, T target) {


    resetFlows();

    while(findAugmentationPath(source,target)){

        double f = findMinResidualAlongPath(source,target);
        augmentFlowAlongPath(source,target,f);

    }




}


#endif /* GRAPH_H_ */
