/**************************************************************************************
* In the code for milestone 2, after finding the start and end goal, the start is
* added as the first node to the open list. A loop then checks that while the node is
* not the goal, it checks to see if the node is in the closed list and if not that it
* has the smallest distance to the goal out of the available nodes in the open list.
* Each space around the node is checked to see if it is empty or the goal, and if it
* doesn't exist in the open list it is added along with the distance travelled. The
* current node is then added to the closed list, and the loop continues until the
* goal is reached.

* In the code for milestone 3, the getPath function in PathSolver.cpp was implemented 
* by working through the list of explored nodes backwards from the goal to the start,
* comparing each one to the previous node by their coordinates to determine the 
* direction. These are added to a list, which is then reversed to place the nodes in 
* forward order. This list is used by the printEnvStdout function in main to determine 
* which coordinates to change before printing.

* Issues encountered along the way have included getting the deep copy of the list to
* return, tests with large islands caused issues with getting a direct path rather than
* other nodes, and determining if a node exists in the closed list through comparison.
* In the end most of these issues were overcome through trial and error.
***************************************************************************************/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);


int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    // std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Environment 
    Env env;
    readEnvStdin(env);
    
    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathSolver* pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);

    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathSolver->getPath(env);

    printEnvStdout(env, solution);

    delete pathSolver;
    delete exploredPositions;
    delete solution;

}

void readEnvStdin(Env env){
    for(int i = 0; i < ENV_DIM; i++){
        for(int j=0; j<ENV_DIM; j++){
            std::cin >> env[i][j];
        }
    }

}

void printEnvStdout(Env env, NodeList* solution) {

    // REPLACES EMPTY POSITIONS IN ENV WITH DIRECTION MARKER
    for(int i = 0; i < solution->getLength(); i++){
        if(env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] == SYMBOL_EMPTY){
            if((solution->getNode(i+1)->getCol()-1) == solution->getNode(i)->getCol()){
                env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = '>';
            }
            if((solution->getNode(i+1)->getCol()+1) == solution->getNode(i)->getCol()){
                env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = '<';
            }
            if((solution->getNode(i+1)->getRow()-1) == solution->getNode(i)->getRow()){
                env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = 'v';
            }
            if((solution->getNode(i+1)->getRow()+1) == solution->getNode(i)->getRow()){
                env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = '^';
            }
        }
    }

    // PRINT THE EDITED ENV
    for(int i = 0; i < ENV_DIM; i++){
        for(int j=0; j<ENV_DIM; j++){
            std::cout << env[i][j];
        }
        // STOP NEWLINE FROM PRINTING ON FINAL LINE
        if(i+1 != ENV_DIM){
            std::cout << std::endl;
        }

    }
}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINT OUT NODE LIST" << std::endl;
    for(int i = 0; i < nodeList->getLength(); ++i){
        std::cout << nodeList->getNode(i)->getRow();
        std::cout << nodeList->getNode(i)->getCol();
        std::cout << nodeList->getNode(i)->getDistanceTraveled() << std::endl;
    }

    delete nodeList;
}