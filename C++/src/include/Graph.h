#ifndef Graph_H
#define Graph_H

#include "NodeHeap.h"

class Graph{

private:
    std::unordered_map<int, Node*>* allNodeIDs;
    int performed_dixtra_last;

    /**
     * @brief Method to perform Dixtra's algorithm to find the shortest path from the source node to the destination node
     *
     * @param source
     * @param destination
     */
    void performDixtra(int source)
    {
        if (this->allNodeIDs->find(source) == this->allNodeIDs->end()){
            // don't have the node
            return;
        }
        else if (source == this->performed_dixtra_last){
            // already performed dixtra
            return;
        }

        // firstly, refresh all key values
        for (std::pair<int, Node *> idNodePair : *(this->allNodeIDs))
        {
            idNodePair.second->key = INT32_MAX;
            idNodePair.second->winningConnection.first = nullptr;
            idNodePair.second->winningConnection.second = INT32_MAX;
        }

        if ((*this->allNodeIDs).find(source) != (*this->allNodeIDs).end())
        {
            // we do have the source node
            Node *sourceNode = (*this->allNodeIDs)[source];
            sourceNode->key = 0;

            // we need a set of explored Nodes to ensure no cycle creation occurs
            std::unordered_set<int> exploredNodeIds;
            exploredNodeIds.insert(sourceNode->id);

            // we need a heap of our nodes
            NodeHeap *nodeHeap = new NodeHeap;
            // firstly, insert the source node
            for (std::pair<int, Node *> idNodePair : *(this->allNodeIDs))
            {
                if (idNodePair.second != sourceNode)
                {
                    if (idNodePair.second->checkWinningEdge(sourceNode)) {
                        // if this node is directly connected to our source, it is updated here
                        nodeHeap->insert(idNodePair.second);
                    }
                }
            }

            // now keep going until all other nodes are explored
            while (nodeHeap->size > 0)
            {
                Node *next = nodeHeap->extractMin();
                exploredNodeIds.insert(next->id);
                for (std::pair<Node *, int> nextEdge : next->connected)
                {
                    // look at all of the connections associated with this node that we have picked - we need to update the connected nodes' keys
                    Node *connectedNode = nextEdge.first;
                    if (exploredNodeIds.find(connectedNode->id) == exploredNodeIds.end())
                    {
                        // ONLY if we are not creating a cycle
                        nodeHeap->remove(connectedNode);
                        if (connectedNode->checkWinningEdge(next)){
                            // update the key of connectedNode if it can be improved, and as long as some past or present connection is there, it goes in the heap
                            nodeHeap->insert(connectedNode);
                        }
                    }
                }
            }
        }
        this->performed_dixtra_last = source;
    }

public:

    /**
     * @brief Construct a new Graph object
     * 
     */
    Graph(){
        this->allNodeIDs = new std::unordered_map<int, Node*>;
    }

    /**
     * @brief Clear out all of the nodes and edges from this graph
     */
    void clear(){
        delete this->allNodeIDs;
        this->allNodeIDs = new std::unordered_map<int, Node*>;
        this->performed_dixtra_last = -1;
    }

    /**
     * @brief Include a new node in this graph with the relevant ID
     * 
     * @param id 
     */
    void includeNode(int id){
        if (this->allNodeIDs->find(id) == this->allNodeIDs->end()){
            // we do NOT already have a node with this ID in the graph
            this->allNodeIDs->insert({id, new Node(id)});
            this->performed_dixtra_last = -1;
        }
    }

    /**
     * @brief If possible, connect the two nodes within this graph
     * 
     * @param node1 
     * @param node2 
     * @param weight 
     */
    void connectNodes(int node1, int node2, int weight) {
        if ((*this->allNodeIDs).find(node1) != (*this->allNodeIDs).end() && (*this->allNodeIDs).find(node2) != (*this->allNodeIDs).end())
        {
            // we do have both nodes
            (*this->allNodeIDs)[node1]->connect((*this->allNodeIDs)[node2], weight);
        }
    }

    /**
     * @brief Return the MAXIMUM minimum distance from the source node to any other node
     * 
     * @param source 
     * @return int 
     */
    int getMax(int source){
        this->performDixtra(source);
        int max_distance = -1;
        for (auto i = this->allNodeIDs->begin(); i != this->allNodeIDs->end(); i++){
            if (i->second->key == INT32_MAX){
                // could not get a connection
                return -1;
            } else {
                max_distance = std::max(max_distance, i->second->key);
            }
        }

        return max_distance;
    }

};

#endif