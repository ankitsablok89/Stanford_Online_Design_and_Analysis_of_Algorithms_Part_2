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

// this constant is used in Floyd-Warshall's algorithm to compute shortest paths
const int INF = 10000;

int main(){

     // open files to scan input and dump output
    freopen("/home/ankit/Desktop/Coursera Courses/Design and Analysis of Algorithms - Part 2/Programming Assignment 4/g3.txt" , "rb" , stdin);
    freopen("/home/ankit/Desktop/Coursera Courses/Design and Analysis of Algorithms - Part 2/Programming Assignment 4/g3Answer.txt" , "wb" , stdout);

    // these variables will store the number of vertices and the number of edges respectively
    int nVertices , nEdges;
    cin >> nVertices >> nEdges;

    cout << "The number of vertices in the graph are : " << nVertices << " \nThe number of edges in the graph are : " << nEdges << endl;

    // this 2D array stores the adjacency matrix representation of the graph
    int **graph;

    graph = (int **) malloc ( sizeof( int * ) * ( nVertices + 1 ) );

    for(int i = 0 ; i < nVertices + 1 ; ++i)
            graph[ i ] = ( int * ) malloc ( sizeof( int ) * ( nVertices + 1 ) );

    // initially the graph has no edges at all hence the weight of every edge is marked as infinity
    for(int i = 0 ; i < nVertices + 1 ; ++i){
            for(int j = 0 ; j < nVertices + 1 ; ++j)
                    graph[ i ][ j ] = INF;
    }

    // scan the edges from the graph
    for(int i = 0 ; i < nEdges ; ++i){

            // these temporary variables are used to represent the vertices involved in the edge and the edge weight
            int v1 , v2 , wt;
            cin >> v1 >> v2 >> wt;

            // this will make an edge in the graph
            graph[ v1 ][ v2 ] = wt;
    }

    // now the Floyd-Warshall Algorithm begins
    for(int k = 1 ; k < nVertices + 1 ; ++k){
            for(int i = 1 ; i < nVertices + 1 ; ++i){
                    for(int j = 1 ; j < nVertices + 1 ; ++j){
                            graph[ i ][ j ] = min( graph[ i ][ j ] , graph[ i ][ k ] + graph[ k ][ j ] );
                    }
            }
    }


    for(int i = 0 ; i < nVertices + 1 ; ++i){
            for(int j = 0 ; j < nVertices + 1 ; ++j)
                    cout << graph[ i ][ j ] << " ";
            cout << endl;
    }

    // this variable is used to check if there is a negative weight cycle that is present in the graph
    bool negCycle = false;

    // for checking the negative weight cycle just check if any of the diagonal elements has value < 0
    for(int i = 1 ; i < nVertices + 1 ; ++i){
            if( graph[ i ][ i ] < 0 )
                negCycle = true;
    }

    if( negCycle )
        cout << "Negative weight cycle present." << endl;

    else{

         int minDist = INF;

         for(int i = 1 ; i < nVertices + 1 ; ++i){
                 for(int j = 1 ; j < nVertices + 1 ; ++j){

                         if( i != j ){
                             if( minDist > graph[ i ][ j ] )
                                 minDist = graph[ i ][ j ];
                         }
                 }
         }

         cout << "The shortest shortest path distance is : " << minDist << endl;
    }

    return 0;
}

