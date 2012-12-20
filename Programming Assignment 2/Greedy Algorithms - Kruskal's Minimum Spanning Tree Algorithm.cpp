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

// this is the global component pointer that will be used to form the component array in the algorithm
// each entry in this array indicates the component number to which the ith entry belongs
int *component;

// this is the global array size that will be used to record the size of the component which is essentially
// the number of nodes in the component
int *size;

// this function is used to implement the find operation in the union find data structure and is used
// to find the root of the connected component of a vertex
int findRoot(int v){
    while( v != component[v] ){
        v = component[v];
    }

    return v;
}

// this function is used to implement the union operation in the union find data structure and is used to
// merge two connected components together
int mergeComponents(int v1 , int v2){
    int root1 = findRoot(v1);
    int root2 = findRoot(v2);

    if( size[root1] > size[root2] ){
        component[root2] = root1;
        size[root1] += size[root2];
    }

    else{
        component[root1] = root2;
        size[root2] += size[root1];
    }
}

// this function is used to check if the 2 components are connected or not
bool isConnected(int v1 , int v2){
    // just check if the roots of the 2 vertices are the same or not
    return findRoot(v1) == findRoot(v2);
}

int main(){

// open files to scan input and dump output
freopen("/home/ankit/Desktop/edges.txt" , "rb" , stdin);
freopen("/home/ankit/Desktop/Kruskals Output.txt" , "wb" , stdout);

// this varibles store the number of vertices and number of edges in the graph
int nVertices , nEdges;
cin >> nVertices >> nEdges;

// allocate memory to the component array, we start with vertex 1 and hence allocate 1 more entry than the
// number of vertices input in the algorithm
component = (int *) malloc ( sizeof(int) * (nVertices+1) );
size = (int *) malloc ( sizeof(int) * (nVertices + 1) );

// perform the initializations
for(int i = 0 ; i < nVertices + 1 ; ++i){
    // each vertex initially lies in its own isolated component
    component[i] = i;
    // size of each component is initially 1 as there is only 1 vertex in each component at start-up
    size[i] = 1;
}

// this is a vector that we use to store an edge in the graph this can be interpreted as
// vector< pair< edgeWeight , pair< vertex1 , vertex2 > > >
vector< pair< int , pair< int ,int > > > edges;

for(int i = 0 ; i < nEdges ; ++i){
    // temporary variables used in forming an edge
    int vertex1 , vertex2 , edgeWeight;

    // scan the inputs
    cin >> vertex1 >> vertex2 >> edgeWeight;

    edges.PB( make_pair( edgeWeight , make_pair( vertex1 , vertex2 ) ) );
}

// sort all the edges in increasing order by edgeWeight
sort( ALL( edges ) );

// this is the weight of the minimum spanning tree of the graph
long long mstWeight = 0;

for(int i = 0 ; i < SZ( edges ) ; ++i){
    if( !isConnected( edges[i].second.first , edges[i].second.second ) ){
        mstWeight += edges[i].first;
        mergeComponents( edges[i].second.first , edges[i].second.second );
    }
}

cout <<"The weight of the minimum spanning tree is : " << mstWeight << endl;

return 0;

}
