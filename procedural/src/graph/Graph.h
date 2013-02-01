/**********************************************************************************
 * Graph implementation using adjacency matrices
 *
 * This is a graph implementation supporting my paper 'Fast exact graph matching
 * using adjacency matrices'. The implementation features search operations that
 * allow for searching a graph instance (target) with another graph instance (search).
 *
 * As well as these search operations, the graph also provides common implementations
 * of useful operations to perform on a graph.
 *
 * By  Marlon Etheredge <marlon.etheredge@hva.nl>
 *
 * Todo:
 * - The current implementation of the search algorithm only allows for simple graphs
 *   to be searched, need to test for more complex cases and adjust the algorithm for
 *   supporting these more complex cases.
 * - Implement common graph operations.
 * - The current masking of requirements 'only' allows 64-bits to be encoded in the
 *   requirements field for a pattern, this need to be adjusted so that more than 64 
 *   nodetypes are supported.
 **********************************************************************************/

#pragma once

#include <deque>
#include <list>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <bitset>

namespace PGC{
    class Center;
}

#define MAX_NODES 100000
namespace FF {
    // Forward declaration
    class Graph;
    // NodeType, represents the type of a node, currently implemented using a char type
    class NodeType
    {
    private:
        static int IdPointer; // Id pointer to the last NodeType created
        
        long m_Id;            // Id of this NodeType
    public:
        char Object; // Currently NodeType is implemented using a char
        
        NodeType(void)        { this->m_Id = NodeType::IdPointer++; }
        NodeType(char object) { this->m_Id = NodeType::IdPointer++; this->Object = object; }

        long GetId()           { return this->m_Id; }
        
        virtual bool operator ==(const NodeType &b) const { return this->Object == b.Object; }
    };

    // NullNodeType, always returns false in equals-operator
    class NullNodeType : public NodeType
    {
    public:
        bool operator ==(const NodeType &b) const { return false; }
    };

    // Node, represents a node within the graph
    typedef struct Node
    {
        int      Position;              // Position in set and matrix
        NodeType Type;                  // Type of the node
        PGC::Center* center;
        int      ConnectionRetainCount; // Count of references still existing to this node

        Node(Node *node) { this->Type = node->Type; this->ConnectionRetainCount = 0; }
        Node(NodeType type) { this->Type = type; this->ConnectionRetainCount = 0; }
    } Node;

    // Connection, represents a connection within the graph
    typedef struct Connection
    {
        Node *A, *B; // Connection 

        Connection(Node *a, Node *b) { this->A = a; this->B = b; }
    } Connection;

    // Pattern, contains Key and Requirements:
    // Key: NodeType that this pattern has
    // Requirements: NodeTypes that this Key requires
    typedef struct Pattern
    {
        NodeType Key;
        
        // No need to perform slow searches inside a set, just mask NodeTypes
        // inside the Requirements mask (favoring speed)
        // Todo: Currently 'only' supports up to 64 nodetypes to be masked into the
        //       field (depending on specifications of long type)
        long     Requirements;
        
        int      RequirementsLength;
        
        Pattern(void) { this->RequirementsLength = this->Requirements = 0; }
    } Pattern;

    // Search states, used within search sweeps to indicate the status
    // of the sweep
    enum SearchState
    {
        LEAF,
        TRAVERSE,
        NONE
    };

    // Graph class
    class Graph
    {
    private:
        int   m_NodesLength;                   // The number of nodes in this graph
        int   m_MatrixLength;                  // The length of the matrix
        int **m_Matrix;                        // The matrix representing the graph

        int m_PatternsMatched;
        
        std::deque<Node*>       m_Nodes;       // The nodes inside this graph
        std::deque<Connection*> m_Connections; // The connections inside this graph

        // Search in the matches found in SearchForPatterns
        void SearchInMatches(
            Graph *other,                    // The other graph (search graph)
            std::list<Node*> &matches,       // The matches found in SearchForPatterns
            std::list<Pattern> &patterns,    // List of patterns that are available
            std::list<Node*> &affectedNodes, // The nodes that are affected in the last search sweep
            std::bitset<MAX_NODES> &affectedNodesBitset // The bitset containing data on nodes that are affected
        );          
        // Search for patterns in matrix
        SearchState SearchForPatterns(
            Graph *other,                    // The other graph (search graph)
            int row,                         // The row to search
            Pattern &pattern,                // The pattern to search
            std::list<Pattern> &patterns,    // List of patterns that are available
            std::list<Node*> &affectedNodes, // The nodes that are affected in the row by pattern
            std::bitset<MAX_NODES> &affectedNodesBitset      // The bitset containing data on nodes that are affected
        ); 
    public:
        // Construct a new Graph with initial size
        Graph(void);
        // Destruct this Graph instance
        ~Graph(void);

        // Reindex the node positions
        void Reindex(void);                                                 
        
        // Testcase (prove that the implementation works)
        static void Test(void);                                             

        // Search the graph for another graph
        void Search(
            Graph *other,            // The other graph (search graph)
            std::list<Node*> &result // The result of the search operation (containing affected nodes)
        );                

        void Renew(void);
        
        // Add a node to the graph, please note that the adjacency matrix will not yet rebuild
        void AddNode(
            Node *node              // Node to add
        );
        
        // Add a connection to the graph
        void AddConnection(
            Connection *connection // Connection to add
        ); 
        
        // Remove a node from the graph, graph is not responsible for releasing memory
        void RemoveNode(
            Node *node // Node to be removed
        );
        
        // Remove a connection from the graph, graph is not responsible for releasing memory
        void RemoveConnection(
            Connection *connection // Connection to be removed
        );

        void PrintAdjacencyMatrix(void);

        // Release the memory of the adjacency matrix so that a new adjacency matrix can be created
        void ReleaseAdjacencyMatrix(void);     
        
        // Create an adjacency matrix according to the nodes and connections
        void CreateAdjacencyMatrix(void);                                   

        // Set a list of patterns for this Graph
        void GetPatterns(
            std::list<Pattern> &patternList // List that will be filled with patterns in this graph
        );                  
    };
};