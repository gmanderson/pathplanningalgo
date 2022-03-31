#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver(){
    nodesExplored = new NodeList();
}

PathSolver::~PathSolver(){
    delete nodesExplored;
}

void PathSolver::forwardSearch(Env env){
    Node* start;
    Node* goal;
    Node* nodeP;
    Node* nodeQ;
    NodeList* openList = new NodeList();

    //FIND START AND GOAL
    for(int i = 0; i < ENV_DIM; i++){
        for(int j = 0; j<ENV_DIM; j++){
            if(env[i][j] == SYMBOL_START){
                start = new Node(i, j, 0);
            }
            if(env[i][j] == SYMBOL_GOAL){
                goal = new Node(i, j, 0);
            }
        }
    }

    // ADD START TO OPEN LIST
    openList->addElement(start);
    // // SELECT START AS FIRST NODE P
    nodeP = openList->getNode(0);

    
    // REPEAT WHILE NODE P IS NOT GOAL
    while(!((nodeP->getCol() == goal->getCol()) && (nodeP->getRow() == goal->getRow()))){
        int smallestDistance = NODE_LIST_ARRAY_MAX_SIZE;
        // RUN THROUGH OPEN LIST TO CHECK IF EXISTS IN CLOSED LIST
        for (int i = 0; i < openList->getLength(); i++)
        {
            bool exists = false;
            for(int j = i; j < nodesExplored->getLength(); j++){
                if((openList->getNode(i)->getCol() == nodesExplored->getNode(j)->getCol()) 
                    && (openList->getNode(i)->getRow() == nodesExplored->getNode(j)->getRow()))
                {
                    exists = true;
                }
            }

            // IF DOES NOT EXIST IN CLOSED LIST, ASSIGN NODE P BY SMALLEST DISTANCE
            if(!exists){
                int estimatedDistance = openList->getNode(i)->getEstimatedDist2Goal(goal);
                
                if(estimatedDistance <= smallestDistance){
                    nodeP = openList->getNode(i);
                    break; 
                }
            }
        }

        // CHECK IF CAN ADVANCE
        // RIGHT
        if(env[nodeP->getRow()][nodeP->getCol()+1] == SYMBOL_EMPTY 
            || env[nodeP->getRow()][nodeP->getCol()+1] == SYMBOL_GOAL){
            // CREATE NODE Q FOR NEW POSITION
            nodeQ = new Node(nodeP->getRow(), (nodeP->getCol()+1), 0);
            // SET THE DISTANCE TRAVELLED IN THE NODE BY ADDING 1 TO EXISTING DISTANCE
            nodeQ->setDistanceTraveled(nodeP->getDistanceTraveled()+1);

            // ADD Q TO OPEN LIST P IF NOT ALREADY THERE
            bool qExists = false;
            for(int i = 0; i < openList->getLength(); i++){
                if((openList->getNode(i)->getCol() == nodeQ->getCol()) 
                    && (openList->getNode(i)->getRow() == nodeQ->getRow())){
                    qExists = true;
                }
            }
            if(!qExists){
                openList->addElement(nodeQ);
            }            
        }

        // LEFT
        if(env[nodeP->getRow()][nodeP->getCol()-1] == SYMBOL_EMPTY 
            || env[nodeP->getRow()][nodeP->getCol()-1] == SYMBOL_GOAL){
            // ADD NEW POSITION TO OPEN LIST
            nodeQ = new Node(nodeP->getRow(), (nodeP->getCol()-1), 0);
            // SET THE DISTANCE TRAVELLED IN THE NODE BY ADDING 1 TO EXISTING DISTANCE
            nodeQ->setDistanceTraveled(nodeP->getDistanceTraveled()+1);

            // ADD Q TO OPEN LIST P IF NOT ALREADY THERE
            bool qExists = false;
            for(int i = 0; i < openList->getLength(); i++){
                if((openList->getNode(i)->getCol() == nodeQ->getCol()) 
                    && (openList->getNode(i)->getRow() == nodeQ->getRow())){
                    qExists = true;
                }
            }
            if(!qExists){
                openList->addElement(nodeQ);
            }
        }

        // DOWN
        if(env[nodeP->getRow()+1][nodeP->getCol()] == SYMBOL_EMPTY 
            || env[nodeP->getRow()+1][nodeP->getCol()] == SYMBOL_GOAL){
            // ADD NEW POSITION TO OPEN LIST
            nodeQ = new Node((nodeP->getRow()+1), nodeP->getCol(), 0);
            // SET THE DISTANCE TRAVELLED IN THE NODE BY ADDING 1 TO EXISTING DISTANCE
            nodeQ->setDistanceTraveled(nodeP->getDistanceTraveled()+1);

            // ADD Q TO OPEN LIST P IF NOT ALREADY THERE
            bool qExists = false;
            for(int i = 0; i < openList->getLength(); i++){
                if((openList->getNode(i)->getCol() == nodeQ->getCol()) 
                    && (openList->getNode(i)->getRow() == nodeQ->getRow())){
                    qExists = true;
                }
            }
            if(!qExists){
                openList->addElement(nodeQ);
            }
        }

        // UP
        if(env[nodeP->getRow()-1][nodeP->getCol()] == SYMBOL_EMPTY 
            || env[nodeP->getRow()-1][nodeP->getCol()] == SYMBOL_GOAL){
            // ADD NEW POSITION TO OPEN LIST
            nodeQ = new Node((nodeP->getRow()-1), nodeP->getCol(), 0);
            // SET THE DISTANCE TRAVELLED IN THE NODE BY ADDING 1 TO EXISTING DISTANCE
            nodeQ->setDistanceTraveled(nodeP->getDistanceTraveled()+1);

            // ADD Q TO OPEN LIST P IF NOT ALREADY THERE
            bool qExists = false;
            for(int i = 0; i < openList->getLength(); i++){
                if((openList->getNode(i)->getCol() == nodeQ->getCol()) 
                    && (openList->getNode(i)->getRow() == nodeQ->getRow()))
                {
                    qExists = true;
                }
            }
            if(!qExists){
                openList->addElement(nodeQ);
            }
        }

        // ADD NODE P TO CLOSED LIST C
        nodesExplored->addElement(nodeP);
    }
}

NodeList* PathSolver::getNodesExplored(){
    // CALLS COPY CONSTRUCTOR
    NodeList* newNodesExplored = new NodeList(*nodesExplored);
    return newNodesExplored;
}

NodeList* PathSolver::getPath(Env env){
    NodeList* path = new NodeList();
    // GET GOAL FROM END OF LIST
    Node* node = nodesExplored->getNode(nodesExplored->getLength()-1);
    // ADD GOAL TO PATH LIST
    path->addElement(node);

    // ADD NEIGHBOUR NODES TO LIST IF DISTANCE IS ONE LESS THAN PREVIOUS
    for(int i = nodesExplored->getLength()-1; i >= 0; i--){
        if(((node->getCol()-1 == nodesExplored->getNode(i)->getCol()) 
                && (node->getRow() == nodesExplored->getNode(i)->getRow()))
            || ((node->getRow()-1 == nodesExplored->getNode(i)->getRow()) 
                && (node->getCol() == nodesExplored->getNode(i)->getCol()))
            || ((node->getCol()+1 == nodesExplored->getNode(i)->getCol()) 
                && (node->getRow() == nodesExplored->getNode(i)->getRow()))
            || ((node->getRow()+1 == nodesExplored->getNode(i)->getRow()) 
                && (node->getCol() == nodesExplored->getNode(i)->getCol())))
        {
                if(nodesExplored->getNode(i)->getDistanceTraveled() == (node->getDistanceTraveled()-1)){
                        node = nodesExplored->getNode(i);
                        path->addElement(node);
            }
        }
    }

    // PLACE REVERSED LIST IN CORRECT ORDER FROM START TO GOAL
    NodeList* correctPath = new NodeList();
    for(int i = path->getLength()-1; i >=0; i--){
        correctPath->addElement(path->getNode(i));
    }


    // return new NodeList(*correctPath); // SHOULD RETURN DEEP COPY, FAILS
    return correctPath;
}


//-----------------------------