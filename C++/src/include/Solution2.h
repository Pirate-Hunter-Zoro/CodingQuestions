#ifndef Solution2_H
#define Solution2_H

#include "Graph.h"

#include<vector>

class Solution2 {

public:
    /**
     * @brief Given a network of connections and a signal source, find the minimum time for all nodes to receive the signal
     * 
     * @param times 
     * @param n 
     * @param k 
     * @return int 
     */
    int networkDelayTime(std::vector<std::vector<int> > &times, int n, int k)
    {
        Graph graph = Graph();
        for (const std::vector<int>& edge : times){
            graph.includeNode(edge.at(0));
            graph.includeNode(edge.at(1));
            graph.connectNodes(edge.at(0), edge.at(1), edge.at(2));
        }

        // perform Dixtra and get the MAXIMUM minimum path from the source
        return graph.getMax(k);
    }

    /**
     * @brief There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. Any server can reach other servers directly or indirectly through the network.
     * A critical connection is a connection that, if removed, will make some servers unable to reach some other server.
     * Return all critical connections in the network in any order.
     *
     * @param n
     * @param connections
     * @return vector<vector<int> >
     */
    std::vector<std::vector<int> > criticalConnections(int n, std::vector<std::vector<int> > &connections)
    {
        // get our graph and nodes
        Graph graph = Graph();
        for (int i=0; i<n; i++)
            graph.includeNode(i);

        // connect the nodes according to the input edges
        for (const std::vector<int>& edge : connections){
            graph.connectNodes(edge.at(0), edge.at(1), 1);
            graph.connectNodes(edge.at(1), edge.at(0), 1);
        }

        // perform depth first search and return the set of all nodes NOT part of a cycle
        return graph.criticalConnections();
    }
};

#endif