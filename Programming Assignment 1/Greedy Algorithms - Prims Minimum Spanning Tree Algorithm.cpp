        // I/O Includes

        #include<new>
        #include<cstdio>
        #include<cctype>
        #include<cmath>
        #include<cstdlib>
        #include<cstring>
        #include<sstream>
        #include<iostream>
        #include<strstream>

        // Data Structure Includes

        #include<map>
        #include<set>
        #include<list>
        #include<stack>
        #include<deque>
        #include<queue>
        #include<vector>
        #include<bitset>
        #include<string>
        #include<iterator>
        #include<algorithm>

        // Standard Namespace Inclusion

        using namespace std;

        // Supporting Macros

        #define SZ( C )                 ( ( int ) ( ( C ).size() ) )
        #define ALL( C )                ( C ).begin() , ( C ).end()
        #define TR( C , it )            for( typeof( ( C ).begin() ) it = ( C ).begin(); it != ( C ).end() ; ++it )
        #define LN( STRING )            ( ( int ) ( STRING ).length() )
        #define SPRESENT( C , x )       ( ( ( C ).find( x ) ) != ( C ).end() )
        #define CPRESENT( C , x )       ( find( ALL( C ) , x ) != ( C ).end() )
        #define PB                      push_back

        // Typedefed Versions of Data Types

        typedef vector< int > VI;
        typedef vector< VI > VVI;
        typedef vector< string > VS;
        typedef pair< int ,int > PII;
        typedef long long LL;
        typedef unsigned long long ULL;

        // this structure is used to represent the node in a graph
        struct EdgeNode{

               // this stores the adjacecny information of a node
               int adjacentVertex;

               // this stores the edge weight
               int edgeWeight;

               // this stores a pointer to the next node in the adjacecny list of a vertex
               struct EdgeNode *next;
        };

        // this structure is used to represent the graph data structure
        struct Graph{

               // this stores the number of vertices in the graph
               int nVertices;

               // this stores the number of edges in the graph
               int nEdges;

               // this stores the adjacecny list coressponding to the graph
               struct EdgeNode **adjList;
        };

        // this is the gloabl graph data structure that is accessible everywhere and has been initialized to NULL
        struct Graph *G = NULL;

        int main(){

            // open files to scan input and dump output
            freopen("/home/ankit/Desktop/Coursera Courses/Design and Analysis of Algorithms - Part 2/Programming Assignment 1/edges.txt" , "rb" , stdin);
            freopen("/home/ankit/Desktop/Coursera Courses/Design and Analysis of Algorithms - Part 2/Programming Assignment 1/PrimsOutput.txt" , "wb" , stdout);

            // this varibles store the number of vertices and number of edges in the graph
            int nVertices , nEdges;
            cin >> nVertices >> nEdges;

            // allocate memory to the graph data structure
            G = ( struct Graph * ) malloc ( sizeof( struct Graph ) );

            // after allocating memory make some assignments
            (G -> nVertices) = nVertices;
            (G -> nEdges) = nEdges;
            (G -> adjList) = (struct EdgeNode **) malloc ( sizeof( struct EdgeNode * ) * ( (G -> nVertices) + 1) );

            // initialize all the pointers in the adjList to NULL
            for(int i = 0 ; i < (G -> nVertices)+1 ; ++i)
                    G -> adjList[i] = NULL;

            // now we start inserting the edges in the graph
            for(int i = 0 ; i < (G->nEdges) ; ++i){
                    int startVertex , endVertex , edgeWeight;
                    cin >> startVertex >> endVertex >> edgeWeight;

                    // allocate a new edge node
                    struct EdgeNode *tempEdgeNode;
                    tempEdgeNode = (struct EdgeNode *) malloc ( sizeof( struct EdgeNode ) );

                    tempEdgeNode->adjacentVertex = endVertex;
                    tempEdgeNode->edgeWeight = edgeWeight;
                    tempEdgeNode->next = G -> adjList[startVertex];
                    G->adjList[startVertex] = tempEdgeNode;

                    // and as we have assumed the graph to be undirected we add the equivalent edge in the graph
                    tempEdgeNode = (struct EdgeNode *) malloc ( sizeof( struct EdgeNode ) );

                    tempEdgeNode->adjacentVertex = startVertex;
                    tempEdgeNode->edgeWeight = edgeWeight;
                    tempEdgeNode->next = G -> adjList[endVertex];
                    G->adjList[endVertex] = tempEdgeNode;
            }

            cout << "The adjacency list representation of the graph is as follows -: " << endl;

            // display the input graph
            for(int i = 0 ; i < (G -> nVertices) + 1 ; ++i){

                    if( G -> adjList[i] != NULL ){

                        cout << i << "-->";
                        struct EdgeNode *traverse = G->adjList[i];

                        while(traverse != NULL){
                           cout <<"(" << traverse -> adjacentVertex <<"," << traverse -> edgeWeight <<")" << "->";
                           traverse = traverse -> next;
                        }

                        cout << endl;
                    }
            }

            cout << endl << endl;

            // Prims algorithm begins here

            if( G == NULL )
                cout << "The weight of the minimum spanning tree of the graph is : 0" << endl << endl;

            else{

                 // this variable will store the vertex that is being considered at this point of time
                 int vertexConsidered;

                 // this is a vector that stores the possible edges that are considered in forming an MST
                 vector< pair < int , pair < int , int > > >   possibleEdges;

                 // this is a set that stores the spanned vertices
                 set< int > spannedVertices;

                 // we start growing the tree from vertex 1
                 vertexConsidered = 1;

                 // this variable stores the weight of the minimum spanning tree
                 LL mstWt = 0;

                 while( (int)spannedVertices.size() != G->nVertices ){

                        // add the vertex under consideration to the spanned set
                        spannedVertices.insert( vertexConsidered );

                        // scan the adjacency list of the vertex considered and add it to the vector of possible edges
                        struct EdgeNode *temp = G->adjList[ vertexConsidered ];

                        while( temp != NULL ){
                               possibleEdges.PB( make_pair( temp->edgeWeight , make_pair( vertexConsidered , temp->adjacentVertex ) ) );
                               temp = temp -> next;
                        }

                        // sort all the possible edges by weight at any given moment
                        sort( ALL( possibleEdges ) );

                        // now select the edge of minimum weight that crosses the frontier
                        for(int i = 0 ; i < SZ( possibleEdges) ; ++i){

                                if( spannedVertices.find( possibleEdges[ i ].second.first ) != spannedVertices.end() && spannedVertices.find( possibleEdges[ i ].second.second ) == spannedVertices.end() )
                                {
                                    vertexConsidered = possibleEdges[ i ].second.second;
                                    mstWt += possibleEdges[ i ].first;

                                    break;
                                }

                        }

                 }

                 cout << "The weight of the minimum spanning tree of the graph is : " << mstWt << endl << endl;

            }

            getchar();
            getchar();

            return 0;
        }
