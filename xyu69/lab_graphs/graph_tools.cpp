/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */

    initialization(graph);
	int min = 100000;
	Vertex min_point_1;
	Vertex min_point_2;

    vector<Edge> vec_edge = graph.getEdges();
    vector<Vertex> vec_vertex = graph.getVertices();

    for(auto & v : vec_edge){
    	if(v.weight < min){
    		min = v.weight;
    		min_point_1 = v.source;
    		min_point_2 = v.dest;
    	}
    }   
    graph.setEdgeLabel(min_point_1, min_point_2, "MIN");
    return min;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    /*initial*/
   initialization(graph);
    /*Traversal*/
    queue<Vertex> q;
    graph.setVertexLabel(start, "VISITED");
    q.push(start);
    unordered_map<Vertex, int> distance;
    distance[start] = 0;
    int dis;
    Vertex find;
    unordered_map<Vertex, Vertex> preVertex;

    while(! q.empty()){
    	Vertex orig_v = q.front();
    	q.pop();
    	vector<Vertex> adj = graph.getAdjacent(orig_v);
        for(auto & a : adj){
            if(graph.getVertexLabel(a) == "UNEXPLORED"){
                graph.setVertexLabel(a, "VISITED");
                graph.setEdgeLabel(orig_v, a, "DISCOVERY");
                q.push(a);
                distance[a] = distance[orig_v] + 1;
                preVertex[a] = orig_v;
            }
            else if(graph.getEdgeLabel(orig_v, a) == "UNEXPLORED"){
                graph.setEdgeLabel(orig_v, a, "CROSS");
            }
            if(a == end){
                dis = distance[a];
                break;
            }
        }
    }
    find = end;
    while(find != start){
        Vertex pre = preVertex[find];
        graph.setEdgeLabel(pre, find, "MINPATH");
        find = pre;
    }    
    return dis;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    initialization(graph);
    vector<Edge> vec_edge = graph.getEdges();
    vector<Vertex> vec_vertex = graph.getVertices();
    sort(vec_edge.begin(), vec_edge.end());
    DisjointSets set;
    set.addelements( (int)vec_vertex.size() );
    int counts = 0;
    for(auto & e : vec_edge){
        if(set.find(e.source) != set.find(e.dest)){
            set.setunion(e.source, e.dest);
            graph.setEdgeLabel(e.source, e.dest, "MST");
            counts++;
        }
        if(counts >= (int)vec_vertex.size()-1)
            break;
    }
}


void GraphTools::initialization(Graph & graph){

    vector<Edge> vec_edge = graph.getEdges();
    vector<Vertex> vec_vertex = graph.getVertices();

    for(auto & v : vec_vertex){
        graph.setVertexLabel(v, "UNEXPLORED");
    }
    
    for(auto & e : vec_edge){
        graph.setEdgeLabel(e.source, e.dest, "UNEXPLORED");
    }

}