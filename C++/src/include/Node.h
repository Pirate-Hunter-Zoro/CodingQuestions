#ifndef Node_H
#define Node_H

#include<utility>
#include<iostream>
#include<cmath>
#include<unordered_set>
#include<unordered_map>

class Node {

    friend class NodeHeap;
    friend class Graph;

private:

    int key;
    int id;
    int numConnectedSoFar;

    std::pair<Node*, int> winningConnection;
    std::unordered_map<Node*, int> connected;

    /**
     * @brief Make a default constructor
     *
     */
    Node() {}

    /**
     * @brief Construct a new Node object
     *
     * @param id
     */
    Node(int id)
    {
        this->id = id;
        this->key = INT32_MAX;
        this->numConnectedSoFar = 0;
    }

    /**
     * @brief Method to connect this node to the other node with the input ID
     *
     * @param otherNodeID
     */
    void connect(Node *otherNodePointer, int weight)
    {
        if (this != otherNodePointer)
        {
            // connect the input node to this node - there is an edge from this node to the input node
            this->connected.insert({otherNodePointer, weight});
            this->numConnectedSoFar++;
        }
    }

    /**
     * @brief Replace the key with a lesser value if the input is in fact lesser
     *
     * @param newKey
     */
    bool updateKey(int newKey)
    {
        if (this->key > newKey)
        {
            this->key = newKey;
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * @brief Get the Connection Weight associated from this node to another node
     *
     * @param otherNodePointer
     * @return int
     */
    int getConnectionWeight(Node *otherNodePointer)
    {
        if (this->connected.find(otherNodePointer) != this->connected.end())
        {
            return this->connected[otherNodePointer];
        }
        else
        {
            return INT32_MAX;
        }
    }

    /**
     * @brief Check this connection against a node's other connections in the current algorithm - if no connection is present afterwards return false
     *
     * @param otherNode
     * @return true
     * @return false
     */
    bool checkWinningEdge(Node *otherNode)
    {
        if (this != otherNode && otherNode->getConnectionWeight(this) != INT32_MAX)
        {
            if ((this->winningConnection).first != nullptr)
            {
                if (this->key > otherNode->key + otherNode->getConnectionWeight(this))
                {
                    // this edge results in a shorter path from the source
                    this->winningConnection.first = otherNode;
                    this->winningConnection.second = otherNode->getConnectionWeight(this);
                    this->key = this->winningConnection.second + otherNode->key;
                }
            }
            else if (otherNode->getConnectionWeight(this) != INT32_MAX) // we don't yet have a winning connection
            {
                if (otherNode->getConnectionWeight(this) != INT32_MAX)
                { // otherNode DOES in fact connect to this node
                    this->winningConnection.first = otherNode;
                    this->winningConnection.second = otherNode->getConnectionWeight(this);
                    this->key = this->winningConnection.second + otherNode->key;
                }
            }
            return true;
        }
        // there was no new connection so we rely on previous connections
        return (this->winningConnection).first != nullptr;
    }

public:
    /**
     * @brief Getter for the degree of this node
     * 
     * @return int 
     */
    int getDegree() {
        return this->numConnectedSoFar;
    }

    /**
     * @brief Method to print out a node object
     * 
     * @param os 
     * @param node 
     * @return std::ostream& 
     */
    friend std::ostream& operator<<(std::ostream& os, const Node& node){
        os << "ID:" << node.id << "; Key:" << node.key;
        return os;
    }

};

#endif