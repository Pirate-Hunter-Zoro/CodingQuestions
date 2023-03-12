#ifndef Graph_H
#define Graph_H

#include "NodeHeap.h"

class Graph{

private:
    std::unordered_map<int, Node*>* allNodeIDs;
    int performed_dixtra_last;
    int maxID;

    /**
     * @brief So that we can create an unordered map of vectors
     * Source: https://www.geeksforgeeks.org/unordered-set-of-vectors-in-c-with-examples/
     */
    struct vectorHasher
    {
        size_t operator()(const std::vector<int> &myVector) const
        {
            std::hash<int> hasher;
            size_t answer = 0;
            for (int i : myVector)
            // look at every element in the vector
            {
                answer ^= hasher(i) + 0x9e3779b9 +
                          (answer << 6) + (answer >> 2); // what the hell is this?
            }
            return answer;
        }
    };

    /**
     * @brief Method to perform Dixtra's algorithm to find the shortest path from the source node to the destination node
     *
     * @param source
     * @param destination
     */
    void performDixtra(int source)
    {
        if (this->allNodeIDs->find(source) == this->allNodeIDs->end())
        {
            // don't have the node
            return;
        }
        else if (source == this->performed_dixtra_last)
        {
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
                    if (idNodePair.second->checkWinningEdge(sourceNode))
                    {
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
                        if (connectedNode->checkWinningEdge(next))
                        {
                            // update the key of connectedNode if it can be improved, and as long as some past or present connection is there, it goes in the heap
                            nodeHeap->insert(connectedNode);
                        }
                    }
                }
            }
        }
        this->performed_dixtra_last = source;
    }

    /**
     * @brief Method to perform a depth first search on the graph, starting at the given node, and removing any edges which are part of a cycle
     * Source: https://leetcode.com/problems/critical-connections-in-a-network/solutions/382638/dfs-detailed-explanation-o-e-solution/
     * @param start - starting node ID
     * @param depth - current depth of the recursive depth first search
     * @param crit_edges - all the edges which are NOT part of a cycle - edges which ARE part of a cycle get removed
     * @param ranks - keep track of the ranks of all nodes
     * @return int
     */
    int depth_first_search(int start, int depth, std::unordered_set<std::vector<int>, vectorHasher> &crit_edges, std::unordered_map<int, int> &ranks){
        if (ranks[start] >= 0){
            // this node is either visited and completed,  or just visited - we just need to return the value and the outer function call will deal with it
            return ranks[start];
        }
        ranks[start] = depth; // update the depth of this current node

        // recursively perform depth first search on all neighbors - we need a stack, and that's exactly what happens with recursive function calls
        int min_back_depth = this->maxID + 1; // we need to keep track of the minimum depth of any node that we can reach from this node - surely NO depth can be more than the number of nodes so we are safe to cap it here
        Node* currentNode = this->allNodeIDs->at(start);
        for (auto connection : currentNode->connected){
            // look at each connected node, and depending on depth values we will decide what to do
            int next = connection.first->id;
            if (ranks[next] == depth-1) // don't visit the node we JUST came from
                continue;
            int lowest_depth_found_from_here = this->depth_first_search(next, depth+1, crit_edges, ranks);
            if (lowest_depth_found_from_here <= depth){
                // this will happen in the presence of a cycle
                crit_edges.erase({start, next});
                crit_edges.erase({next, start}); // could be in either order
                // recursively, this method will remove ALL edges in ANY cycle that can be reached from the start node
            }
            min_back_depth = std::min(min_back_depth, lowest_depth_found_from_here);
        }

        // once we reach this point, the node is fully visited and returned to
        ranks[start] = this->maxID + 1;

        // return the minimum depth found from a depth first search from this node
        return min_back_depth;
    }

public :
    /**
     * @brief Construct a new Graph object
     *
     */
    Graph()
    {
        this->allNodeIDs = new std::unordered_map<int, Node *>;
        this->maxID = -1;
    }

    /**
     * @brief Clear out all of the nodes and edges from this graph
     */
    void clear()
    {
        delete this->allNodeIDs;
        this->allNodeIDs = new std::unordered_map<int, Node *>;
        this->performed_dixtra_last = -1;
        this->maxID = -1;
    }

    /**
     * @brief Include a new node in this graph with the relevant ID
     *
     * @param id
     */
    void includeNode(int id)
    {
        if (this->allNodeIDs->find(id) == this->allNodeIDs->end() && id == this->maxID + 1)
        {
            // we do NOT already have a node with this ID in the graph
            this->allNodeIDs->insert({id, new Node(id)});
            this->performed_dixtra_last = -1;
            this->maxID++;
        }
    }

    /**
     * @brief If possible, connect the two nodes within this graph
     *
     * @param node1
     * @param node2
     * @param weight
     */
    void connectNodes(int node1, int node2, int weight)
    {
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
    int getMax(int source)
    {
        this->performDixtra(source);
        int max_distance = -1;
        for (auto i = this->allNodeIDs->begin(); i != this->allNodeIDs->end(); i++)
        {
            if (i->second->key == INT32_MAX)
            {
                // could not get a connection
                return -1;
            }
            else
            {
                max_distance = std::max(max_distance, i->second->key);
            }
        }

        return max_distance;
    }

    /**
     * @brief Return the list of critical edges, such that removing any edge from said list will disconnect the graph
     * 
     * @return std::vector<std::vector<int> >
     */
    std::vector<std::vector<int> > criticalConnections()
    {
        std::vector<std::vector<int> > crits;
        std::unordered_set<std::vector<int>, vectorHasher> crit_edges;
        std::unordered_map<int, int> ranks;
        for (int i=0; i<this->maxID+1; i++){
            ranks.insert({i, -2});
        }
        for (auto i = this->allNodeIDs->begin(); i != this->allNodeIDs->end(); i++)
        {
            for (auto nodeIDPair : i->second->connected)
            {
                // have we already inserted this edge the other way around?
                if (crit_edges.find({nodeIDPair.first->id, i->first}) == crit_edges.end())
                    crit_edges.insert({i->first, nodeIDPair.first->id}); // node ID to other pointer ID
            }
        }
        
        // automatically removes all of the edges which are part of a cycle
        this->depth_first_search(0, 0, crit_edges, ranks);

        // now just add them to the vector
        for (std::vector<int> edge : crit_edges)
        {
            crits.push_back(edge);
        }
        return crits;
    }

};

#endif