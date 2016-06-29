#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stack>

using namespace std;

struct Edge {
    int source;
    int target;
    Edge() {source = -1; target = -1;}
};

bool operator==(const Edge& e1, const Edge& e2);
bool operator<(const Edge& e1, const Edge& e2);
bool operator>(const Edge& e1, const Edge& e2);
bool operator<=(const Edge& e1, const Edge& e2);
bool operator>=(const Edge& e1, const Edge& e2);

class Graph {

    public:       
        static string TYPE_ARCS_LIST;
        static string TYPE_ADJACENCY_LIST;

        Graph(int maxSize);
        Graph(const string& filename, const string& type);
        ~Graph();
        
        int numVertices() const;
        int numEdges() const;
        bool hasVertex(int vertex) const;
        bool hasEdge(int source, int target) const;
        set<int> const& vertices() const;
        vector<Edge> edges() const;
        vector<int> const& incomingNeighbors(int vertex) const;
        vector<int> const& outgoingNeighbors(int vertex) const;

        void print(bool edges) const;
        void print() const;
        
        void addVertex(int vertex);
        void addEdge(int source, int target);
        void deleteVertex(int vertex);
        void deleteVertices(const vector<int>& vertices);
        void deleteEdge(int source, int target);
        void deleteEdges(const vector<Edge>& edges);

        
        void mergeVertex(int vertex);
        void mergeVertices(vector<int> vertices);
        void mergeVertices(int vertex1, int vertex2);

        Graph subgraph(vector<int> vs) const;
        int inDegree(int vertex) const;
        int outDegree(int vertex) const;
        int degree(int vertex) const;

        int minDegreeVertex() const;
        int maxDegreeVertex() const;

        bool isSource(int vertex) const;
        bool isSink(int vertex) const;
        bool hasLoop(int vertex) const;

        vector<int> sources() const;
        vector<int> sinks() const;
        vector<int> loops() const;
        
        vector< vector<int> > stronglyConnectedComponents();
        vector<int> vertexToStronglyConnectedComponentNumber();

        Graph groundingKernel() const;
        vector<int> in0();
        vector<int> out0();
        vector<int> loop();
        vector<int> in1();
        vector<int> out1();

        /****************
         * Operator PIE *
         ****************/
        vector<Edge> acyclicEdges();
        vector<Edge> piEdges();
        vector<Edge> pseudoAcyclicEdges();
        vector<Edge> pie();

        /*****************
         * Operator CORE *
         *****************/
        bool isPiVertex(int vertex);
        vector<int> piVertices();
        bool isClique(const vector<int>& vs) const;
        vector<int> core();

        /*****************
         * Operator DOME *
         *****************/
        vector<int> piPredecessors(int vertex) const;
        vector<int> piSuccessors(int vertex) const;
        vector<int> nonPiPredecessors(int vertex) const;
        vector<int> nonPiSuccessors(int vertex) const;
        bool isDominated(int source, int target) const;
        vector<Edge> dominatedEdges() const;
        vector<Edge> dome();

        vector<int> reduce(bool applyIn0,  bool applyOut0, bool applyLoop,
                           bool applyIn1,  bool applyOut1, bool applyPie,
                           bool applyCore, bool applyDome, bool verbose);
        vector<int> reduce(bool verbose=false);
        vector<int> shortestCycle() const;
        bool isAcyclic();
        bool isFeedbackVertexSet(const vector<int>& fvs) const;
        int upperBoundValue(bool verbose=false) const;
        vector<int> upperBoundSolution(bool verbose=false) const;
        int lowerBoundValue(bool verbose=false) const;

        vector<int> minimumFeedbackVertexSet(bool verbose=false) const;

    private:
	vector< vector<int> > _outgoingNeighbors;
	vector< vector<int> > _incomingNeighbors;
        set<int> _vertices;
        vector<bool> _hasVertex;
	int _maxVertices;
	int _numVertices;
	int _numEdges;

        void GraphFromAdjacencyList(const string& filename);
        void GraphFromArcsList(const string& filename);

        void _init(int maxSize);

        vector<int> _shortestCycle(int vertex, int maxLength);

        int _tarjanCurrentIndex;                   
        vector<int> _tarjanIndex;  
        vector<int> _tarjanAncestor;      
        stack<int> _tarjanStack;         
        vector<bool> _tarjanInStack;      
        int _currentComponent;                
        vector<int> _sccsByNum;      
                                                 
        vector< vector<int> > _sccs;               
        void _tarjan(int vertex, bool byNumber);  
                                                  
        vector<int> _mfvs(vector<int> solution, vector<int> bestSolution, int lowerBound,
                          int level, bool reducible, bool verbose);
};

#endif
