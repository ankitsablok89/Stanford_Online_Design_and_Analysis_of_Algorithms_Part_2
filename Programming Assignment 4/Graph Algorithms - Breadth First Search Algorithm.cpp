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

// this function performs the necessary initializations
int basicFunc(int nVertices , int nEdges , bool directed);

// this function is used to insert an edge into the graph
int insertEdge(int vertex1 , int vertex2 , bool directed);

// this function performs the breadth first search algorithm on a graph
int doBFS(int source , int destination);

// this function is used to display the adjacecny list of the graph
int displayGraph();

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
    
    getchar();
    getchar();

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
    
    // these variables store the source and the destination for the breadth first search algorithm
    int source , destination;

    cout << "Please enter the source vertex from where the search will begin : ";
    cin >> source;
    
    cout << "Please enter the destination vertex you want to find in the graph : ";
    cin >> destination;
    
    // this function will be called to check if there's a path that connects any 2 vertices in the graph
    doBFS( source , destination );
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

int doBFS(int source , int destination){
    
    // this array is used to tell if the node has been visited or not
    bool *visited = (bool *) malloc ( sizeof( bool ) * (G -> nVertices));
    
    // initially all the vertices are in the unvisited state so mark each entry in the visited array as false
    for(int i = 0 ; i < G -> nVertices ; ++i)
            visited[ i ] = false;
    
    // this queue helps us identify the possible neighbors of the nodes under consideration
    queue< int > Q;
    
    // first push the source vertex onto the queue and mark it as visited
    Q.push( source );
    visited[ source ] = true;
    
    while( !Q.empty() ){
           
           // now extrace the front element of the queue
           int front = Q.front();
           
           if( front == destination ){
               cout << "The destination node you are looking for is present in the graph." << endl;
               return 0;
           }
           
           // pop the element just extracted from the front of the queue
           Q.pop();
           
           // traverse through the dequeued node's adjacency list to see if there are any elements that haven't been visited
           struct Node *temp = G -> adjList[ front ];
           
           while( temp != NULL ){
                  
                  if( !visited[ temp -> adjInfo ] ){
                      Q.push( temp -> adjInfo );
                      visited[ temp -> adjInfo ] = true;
                  }
                  
                  temp = temp -> next;
           }
    }
    
    if( Q.empty() )
        cout << "The destination node you are looking for is not present in the graph or the graph might be disconnected" << endl;
    
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
