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
};

#endif