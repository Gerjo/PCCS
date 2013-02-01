#include "Graph.h"

// Definition
int FF::NodeType::IdPointer = 0;

FF::Graph::Graph(void) {
    // Set length to 0
    this->m_NodesLength = this->m_MatrixLength = this->m_PatternsMatched = 0;
}

FF::Graph::~Graph(void) {
    // Initial matrix length
    this->m_MatrixLength = 0;

    // Release the adjacency matrix
    this->ReleaseAdjacencyMatrix();

    // Clear the nodes list and connections list
    this->m_Nodes.clear();
    this->m_Connections.clear();
}

void FF::Graph::Test(void) {
#pragma region TestCase
    // Create NodeTypes
    NodeType types[3];
    types[0] = NodeType('a');
    types[1] = NodeType('b');
    types[2] = NodeType('c');
    
    for (int i = 10 ; i <= 1000 ; i *= 10) {
        Node **searchNodes = (Node**) malloc(sizeof(Node*) * i);
        Node **targetNodes = (Node**) malloc(sizeof(Node*) * i);
        Graph *search = new Graph(), *target = new Graph();
        
        int **m = (int**) malloc(sizeof(int*) * i);
        for (int j = 0 ; j < i ; ++j) {
            m[j] = (int*) malloc(sizeof(int) * i);
        }
        
        int connections = 0;
        
        for (int y = 0 ; y < i ; ++y) {
            for (int x = 0 ; x < i ; ++x) {
                m[y][x] = 0;
            }
        }
        
        for (int n = 0 ; n < i ; ++n) {
            int s = (rand() % (i - 1)) + 1;
            
            for (int j = 0 ; j < s ; ++j) {
                int r = rand() % i;
                
                if (m[n][r] == 0 && n != r) {
                    m[n][r] = 1;
                    ++connections;
                }
            }
        }
        
        printf("Generating search graph with %d nodes and %d connections\n", i, connections);
        printf("Generating target graph with %d nodes and %d connections\n", i, connections);
        
        Connection **searchConnections = (Connection**) malloc(sizeof(Connection*) * connections);
        Connection **targetConnections = (Connection**) malloc(sizeof(Connection*) * connections);
        
        // Search
        for (int n = 0 ; n < i ; ++n) {
            searchNodes[n] = new Node(types[rand() % 3]);
            search->AddNode(searchNodes[n]);
        }
        
        int c = 0;
        for (int y = 0 ; y < i ; ++y) {
            for (int x = 0 ; x < i ; ++x) {
                if (m[y][x] == 1) {
                    searchConnections[c] = new Connection(searchNodes[y], searchNodes[x]);
                    search->AddConnection(searchConnections[c++]);
                }
            }
        }
        
        search->Renew();
        
        puts("Search");

        // Target
        for (int n = 0 ; n < i ; ++n) {
            targetNodes[n] = new Node(searchNodes[n]); 
            target->AddNode(targetNodes[n]);
        }
        
        c = 0;
        for (int y = 0 ; y < i ; ++y) {
            for (int x = 0 ; x < i ; ++x) {
                if (m[y][x] == 1) {
                    targetConnections[c] = new Connection(targetNodes[y], targetNodes[x]); 
                    target->AddConnection(targetConnections[c++]);
                }
            }
        }
        
        target->Renew();

        puts("Target");
        
        // Create storage for search result
        std::list<Node*> result;
        
        // Search target for search
        target->Search(search, result);
        
        printf("Found %lu matches\n\n", result.size());
        
        // Delete stuff
        for (int j = 0 ; j < i ; ++j) {
            delete m[j];
        }
        
        delete m;
        
        for (int n = 0 ; n < i ; ++n) {
            delete searchNodes[n];
        }
        
        for (int n = 0 ; n < connections ; ++n) {
            delete searchConnections[n];
        }
        
        for (int n = 0 ; n < i ; ++n) {
            delete targetNodes[n];
        }
        
        for (int n = 0 ; n < connections ; ++n) {
            delete targetConnections[n];
        }
        
        delete searchNodes; delete searchConnections; delete targetNodes; delete targetConnections;
        
        delete search; delete target;
    }
#pragma endregion
}

void FF::Graph::Reindex(void) {
    // Reindex the nodes
    for (unsigned int i = 0 ; i < this->m_Nodes.size() ; ++i) {
        this->m_Nodes.at(i)->Position = i;
    }
}

void FF::Graph::Renew(void) {
    this->Reindex();
    
    // Rebuild the adjacency matrix
    this->CreateAdjacencyMatrix();
}

void FF::Graph::AddNode(Node *node) {
    // Add the node to the back of the nodes list
    this->m_Nodes.push_back(node);

    // No need to renew the adjacency matrix yet
}

void FF::Graph::AddConnection(Connection *connection) {
    // Add the connection to the back of the connections list
    this->m_Connections.push_back(connection);

    // Increase the connection retain count of both nodes in the connection
    ++connection->A->ConnectionRetainCount;
    ++connection->B->ConnectionRetainCount;
}

void FF::Graph::RemoveNode(Node *node) {
    // Used to check whether or node the to be removed node was found
    bool found = false;

    // Remove the node from the nodes list
    {
        std::deque<Node*>::iterator it;
        for (it = this->m_Nodes.begin() ; it != this->m_Nodes.end() ; ++it) {
            if (*it == node) {
                this->m_Nodes.erase(it);
                found = true;
            }
        }
    }

    // Only do the rest if we've found the deleted node
    if (found && node->ConnectionRetainCount > 0) {
        // Remove all connections referring to the deleted node
        std::deque<Connection*>::iterator it;
        for (it = this->m_Connections.begin() ; it != this->m_Connections.end() ; ++it) {
            // In case either A or B is our deleted node
            if ((*it)->A == node || (*it)->B == node) {
                // Delete the connection
                this->m_Connections.erase(it);
            }
        }
        
        // Reindex the nodes list
        this->Reindex();

        // Re-create the adjacency matrix
        this->CreateAdjacencyMatrix();
    }

    // Set the connection retain count of the node to 0
    node->ConnectionRetainCount = 0;
}

void FF::Graph::RemoveConnection(Connection *connection) {
    // Remove the indicated connection
    std::deque<Connection*>::iterator it;
    for (it = this->m_Connections.begin() ; it != this->m_Connections.end() ; ++it) {
        if (*it == connection) {
            // Decrease the node connection retain count
            --(*it)->A->ConnectionRetainCount;
            --(*it)->B->ConnectionRetainCount;

            // Delete the node if the connection retain count is zero (or less, just to be sure)
            if ((*it)->A->ConnectionRetainCount <= 0) {
                this->RemoveNode((*it)->A);
            }
            if ((*it)->B->ConnectionRetainCount <= 0) {
                this->RemoveNode((*it)->B);
            }

            // Delete the connection
            this->m_Connections.erase(it);
        }
    }
}

void FF::Graph::SearchInMatches(Graph *other, std::list<Node*> &matches, std::list<Pattern> &patterns, std::list<Node*> &affectedNodes, std::bitset<MAX_NODES> &affectedNodesBitset) {
    // Iterate over the matches
    std::list<Node*>::const_iterator it;

    for (it = matches.begin() ; it != matches.end() ; ++it) {
        // Search patterns
        std::list<Pattern>::iterator pit;

        for (pit = patterns.begin() ; pit != patterns.end() ; ) {
            // There should never by affected nodes at this point in the matches, yet
            // check if this really is the case (could be skipped in a production implementation)
            if (!affectedNodesBitset[(*it)->Position]) {
                // If the key of the pattern matches the match type and it is not marked as affected
                if (this->m_Matrix[(*it)->Position][this->m_MatrixLength - 1] >= (*pit).RequirementsLength && (*pit).Key == (*it)->Type) {
                    // Call the search for patterns routine with new parameters
                    SearchState s = this->SearchForPatterns(other, (*it)->Position, *pit, patterns, affectedNodes, affectedNodesBitset);

                    // No need to search any further in case of a leaf
                    if (s == LEAF) {
                        pit = patterns.erase(pit);
                        break;
                    } else if(s == TRAVERSE) {
                        pit = patterns.erase(pit);
                    } else {
                        ++pit;
                    }
                } else {
                    ++pit;
                }
            } else {
                ++pit;
            }
        }
    }
}

void FF::Graph::PrintAdjacencyMatrix(void) {
    printf("   ");

    for (int i = 0 ; i < this->m_MatrixLength - 1 ; ++i) {
        printf("%c%d ", this->m_Nodes[i]->Type.Object, this->m_Nodes[i]->Position);
    }
    
    puts("");

    for (int y = 0 ; y < this->m_MatrixLength - 1 ; ++y) {
        printf("%c%d", this->m_Nodes[y]->Type.Object, this->m_Nodes[y]->Position);
        
        for (int x = 0 ; x < this->m_MatrixLength - 1 ; ++x) {
            printf(" %d ", this->m_Matrix[y][x]);
        }

        printf("| %d", this->m_Matrix[y][this->m_MatrixLength - 1]);

        puts("");
    }

    puts("");
}

FF::SearchState FF::Graph::SearchForPatterns(Graph *other, int row, Pattern &pattern, std::list<Pattern> &patterns, std::list<Node*> &affectedNodes, std::bitset<MAX_NODES> &affectedNodesBitset)
{
    // Fetch the current node
    Node *node = this->m_Nodes[row];

    if (affectedNodesBitset[node->Position]) {
        return NONE;
    }
    
    // Only if the pattern key is of the node's type
    if (this->m_Matrix[row][this->m_MatrixLength - 1] >= pattern.RequirementsLength && pattern.Key == node->Type) {
        // Create storage for the found matches
        std::list<Node*> matches;

        int nonTraversableMatches = 0;
        
        // Iterate of the columns for the given row
        #pragma omp parallel for ordered schedule(dynamic)
        for (unsigned int i = 0 ; i < this->m_Nodes.size() ; ++i) {
            // Narrow our matches set by only adding matches that were not yet marked
            // as affected
            if (!affectedNodesBitset[this->m_Nodes[i]->Position]) {
                // If the matrix contains a connection at row,i
                if (this->m_Matrix[row][i] == 1) {
                    // In case of a match
                    if (pattern.Requirements & (1 << this->m_Nodes[i]->Type.GetId())) {
                        matches.push_back(this->m_Nodes[i]);
                    }
                    // Nothing to do
                    else {
                        
                    }
                }
            } else {
                ++nonTraversableMatches;
            }
        }
        
        int s = matches.size() + nonTraversableMatches;

        // If the row contains all required types
        if (s >= pattern.RequirementsLength && s > 0) {
            // Invalidate the pattern
            pattern.Key = NullNodeType();
            
            ++this->m_PatternsMatched;

            // Mark the node as affected
            affectedNodesBitset.set(this->m_Nodes[row]->Position);
            
            // Insert the node into the affected nodes list
            affectedNodes.push_back(this->m_Nodes[row]);

            // Recursively search for more matches
            this->SearchInMatches(other, matches, patterns, affectedNodes, affectedNodesBitset);

            // Return searchstate
            return TRAVERSE;
        }
        // Row does not contain all required types, but is a leaf
        else if (s == 0 && pattern.RequirementsLength == 0) {
            // Invalidate the pattern
            pattern.Key = NullNodeType();

            ++this->m_PatternsMatched;
            
            // Mark the node as affected
            affectedNodesBitset.set(this->m_Nodes[row]->Position);
            
            // Insert the node into the affected nodes list
            affectedNodes.push_back(this->m_Nodes[row]);

            // Return searchstate
            return LEAF;
        }
    }
    
    return NONE;
}

void FF::Graph::Search(Graph *other, std::list<Node*> &result) {
    // Clear the result list
    result.clear();

    // Create a bitset as storage for marking affected nodes
    std::bitset<MAX_NODES> affectedNodesBitset;

    // Get a list of patterns from the other graph
    std::list<Pattern> patterns;
    other->GetPatterns(patterns);
    
    // Search the graph
    #pragma omp parallel for ordered schedule(dynamic)
    for (unsigned int i = 0 ; i < this->m_Nodes.size() ; ++i) {
        if (this->m_PatternsMatched < patterns.size()) {
            this->SearchForPatterns(other, i, patterns.front(), patterns, result, affectedNodesBitset);
        } else {
            i = this->m_Nodes.size();
        }
    }
}

void FF::Graph::ReleaseAdjacencyMatrix(void) {
    // Set the matrix length to 0
    this->m_MatrixLength = 0;

    if (this->m_MatrixLength && this->m_Matrix != 0) {
        // Delete rows
        for (int i = 0 ; i < this->m_MatrixLength ; ++i) {
            delete this->m_Matrix[i];
        }

        // Delete the matrix and set to 0
        delete this->m_Matrix; this->m_Matrix = 0;
    }
}

void FF::Graph::CreateAdjacencyMatrix(void) {
    // First off, release the current adjacency matrix
    this->ReleaseAdjacencyMatrix();

    // Reserve some storage to store our adjacency matrix, needs one extra element for summary
    const long l = this->m_Nodes.size() + 1;               
    
    this->m_Matrix = (int**) malloc( sizeof( int* ) * l ); // Reserve the two dimensional array
    for (int i = 0 ; i < l ; ++i) {
        this->m_Matrix[i] = (int*) malloc( sizeof( int ) * l );

        // Clear all elements
        for( int j = 0 ; j < l ; ++j ) {
            this->m_Matrix[i][j] = 0;
        }
    }

    int positionA, positionB; positionA = positionB = 0;

    // Fill the adjacency matrix
    for (unsigned int i = 0 ; i < this->m_Connections.size() ; ++i) {
        positionA = this->m_Connections.at(i)->A->Position;
        positionB = this->m_Connections.at(i)->B->Position;

        // A can visit B, so set a 1 horizontally
        this->m_Matrix[positionA][positionB] = 1;

        // Increase row and column counts
        ++this->m_Matrix[positionA][l - 1];
        ++this->m_Matrix[l - 1][positionB];
    }

    // Set the matrix length
    this->m_MatrixLength = int( l );
}

bool PatternListSortPredicate(const FF::Pattern &a, const FF::Pattern &b);

bool PatternListSortPredicate(const FF::Pattern &a, const FF::Pattern &b) {
    return a.RequirementsLength > b.RequirementsLength;
}

void FF::Graph::GetPatterns(std::list<Pattern> &patternList) {
    // Clear the pattern list
    patternList.clear();

    for (unsigned int i = 0 ; i < this->m_Nodes.size() ; ++i) {
        Pattern p;

        // Set the key
        p.Key = this->m_Nodes[i]->Type;

        // Build the list containing requirements
        for (unsigned int j = 0 ; j < this->m_Nodes.size() ; ++j) {
            if (this->m_Matrix[i][j] == 1) {
                // Mask in the NodeType id for quick lookup in the search sweep
                p.Requirements |= 1 << this->m_Nodes[j]->Type.GetId();
                
                // Increase the length of the requirements "set"
                ++p.RequirementsLength;
            }
        }

        // Push back the pattern in the patternlist
        patternList.push_back(p);
    }

    patternList.sort( &PatternListSortPredicate );
}