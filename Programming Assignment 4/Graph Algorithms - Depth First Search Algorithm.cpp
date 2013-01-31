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

// this is the structure of a node in the adjacency list of a vertex in the graph
struct Node{

       // this integer stores the number of the vertex which is adjacent to a given vertex
       int adjInfo;

       // this is a pointer to the next node in the list
       struct Node *next;

};

// this is the structure of a graph
struct Graph{

       // this variable stores the number of vertices in the graph
       int nVertices;

       // this variable stores the number of edges in the graph
       int nEdges;

       // this variable is used to tell if the graph is directed or not
       bool directed;

       // this double pointer is used to store the adjacecny list of the graph data structure
       Node **adjList;
};

// this graph pointer is made global so that it is accessible to all the functions, we assume undirected graph implementations for this algorithm
Graph *G;

// this pointer is used to form an array which stores if a vertex has been visited or not
int *visited;

// this pointer is used to form an array that stores the parent pointers of a node
int *parent;

// this function performs the necessary initializations
int basicFunc(int nVertices , int nEdges , bool directed);

// this function is used to insert an edge into the graph
int insertEdge(int vertex1 , int vertex2 , bool directed);

// this function is used to display the adjacecny list of the graph
int displayGraph();

// this function is used to perform a depth first search traversal of a graph
int doDFS();

// this function helps the depth first search procedure above in traversing the graph
int dfsVisit(int vertex);

int main(){

    // this variable is used to scan the number of vertices from the client
    int nVertices;
    // this variable is used to scan the number of edges in the graph from the client
    int nEdges;

    cout << "Please enter the number of vertices in the graph : ";
    cin >> nVertices;

    cout << "Please enter the number of edges in the graph : ";
    cin >> nEdges;

    // call this function to perform the necessary initializations
    basicFunc(nVertices , nEdges , false);

    return 0;
}

int basicFunc(int nVertices , int nEdges , bool directed){

    // allocate memory to the graph pointer
    G = ( struct Graph * ) malloc ( sizeof( struct Graph ) );

    // perform the necessary initializations
    G -> nVertices = nVertices;
    G -> nEdges = nEdges;
    G -> directed = directed;
    G -> adjList = NULL;

    // allocate memory for the adjacency list of the graph
    G -> adjList = ( struct Node ** ) malloc ( sizeof( struct Node * ) *  ( G -> nVertices ));

    // this will initialize all the vertex pointers in the adjacency list to NULL
    for(int i = 0 ; i < G -> nVertices ; ++i)
            G -> adjList[i] = NULL;

    cout << "Please start entering the edges that constitute the graph." << endl;

    for(int i = 0 ; i <  G -> nEdges ; ++i){

            // these temporary variables store the vertices involved in the edge
            int vertex1 , vertex2;

            cout << "Please enter vertex1 involved in the edge " << i+1 << " : ";
            cin >> vertex1;

            cout << "Please enter vertex2 involved in the edge " << i+1 << " : ";
            cin >> vertex2;

            insertEdge(vertex1 , vertex2 , G -> directed);
    }

    cout << "The graph you entered is as follows : \n";

    // call this function to display the graph
    displayGraph();
        
    // call the doDFS procedure here to perform a DFS traversal of the graph
    doDFS();
    
    cout << "\nThe parent subgraph is as follows as calculated by the DFS procedure : ";
    
    for(int i = 0 ; i < G -> nVertices ; ++i)
            cout << parent[ i ] << " --> ";
    
    cout << endl;

}

int doDFS(){
    
    // allocate memory to the visited node
    visited = ( int * ) malloc ( sizeof( int ) * ( G -> nVertices ) );
    
    // allocate memory to the parent node
    parent = ( int * ) malloc ( sizeof( int ) * ( G -> nVertices ) );
    
    // every node in the visited array will have entries -1 , 0 or 1 corresponding to white, gray and black vertices
    // every node in the parent array corresponds to the parent of the node in the graph
    for(int i = 0 ; i < G -> nVertices ; ++i){
            visited[ i ] = -1;
            parent[ i ] = i;
    }
    
    // call dfsVisit to visit the nodes now
    for(int i = 0 ; i < G -> nVertices ; ++i){
            
            // visit the vertex iff its still white that is its still in undiscovered state
            if(visited[ i ] == -1)
               dfsVisit( i );
    }
    
}

int dfsVisit(int vertex){
    
    // set the visited field of the vertex as 0 as now we have discovered the vertex
    visited[ vertex ] = 0;
    
    // this is a pointer that is used to scan the adjacency list of the vertex
    struct Node *temp = G -> adjList[ vertex ];
    
    while( temp != NULL ){
           
           // if the vertex in the adjacency list is still white in color then discover it by marking it gray
           if( visited[ temp -> adjInfo ] == -1 ){
               
               // mark the vertex gray
               visited[ temp -> adjInfo ] = 0;
               
               // also assign the parent of the vertex
               parent[ temp -> adjInfo ] = vertex;
               
               // call the dfsVisit procedure recursively
               dfsVisit( temp -> adjInfo );
           }
           
           temp = temp -> next;
           
    }
    
    // after scanning the adjacecny list of the vertex mark the vertex as black
    visited[ vertex ] = 1;
}


int insertEdge(int vertex1 , int vertex2 , bool directed){

    // allocate a temporary node
    struct Node *temp = (struct Node *) malloc ( sizeof( struct Node ) );
    temp -> adjInfo = vertex2;
    temp -> next = G -> adjList[vertex1];
    G -> adjList[vertex1] = temp;

    // this condition is used to check if the graph is undirected
    if( !directed ){
        insertEdge( vertex2 , vertex1 , true );
    }

}


int displayGraph(){

    for(int i = 0 ; i < G -> nVertices ; ++i){

            // temporary pointer that is used to scan through the adjacecny list
            struct Node *temp = G -> adjList[i];

            cout << i << " : ";

            while( temp != NULL ){
                   cout << temp -> adjInfo << " -> ";
                   temp = temp -> next;
            }

            cout << endl;
    }

}
