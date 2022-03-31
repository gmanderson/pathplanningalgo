#include "Node.h"
#include <iostream>

Node::Node(int row, int col, int dist_traveled)
{
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
}

Node::~Node(){
    this->row = 0;
    this->col = 0;
    this->dist_traveled = 0;
}

int Node::getRow(){
    return this->row;
}

int Node::getCol(){
    return this->col;
}

int Node::getDistanceTraveled(){
    return this->dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal){
    // Estimated distance = distance_travelled of node p + Manhattan distance from p to Goal
    int estimateDist2Goal = dist_traveled + (abs(this->col - goal->col) + abs(this->row - goal->row));
    return estimateDist2Goal; 
}
    
//--------------------------------                             