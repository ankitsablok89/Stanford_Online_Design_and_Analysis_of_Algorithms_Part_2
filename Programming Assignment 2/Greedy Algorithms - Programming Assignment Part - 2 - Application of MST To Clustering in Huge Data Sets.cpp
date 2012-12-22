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

// this global variable is used to indicate the number of clusters
// initially the number of clusters will be equal to the number of vertices as each vertex lies in its own isolated component
int nClusters;

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

    // we decrement the number of clusters because every 2 components when connected to each other decrease the number of clusters by 1
    --nClusters;

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
    freopen("/home/ankit/Desktop/Coursera Courses/Design and Analysis of Algorithms - Part 2/Programming Assignment 2/clustering2.txt" , "rb" , stdin);
    freopen("/home/ankit/Desktop/Coursera Courses/Design and Analysis of Algorithms - Part 2/Programming Assignment 2/clustering2Answer.txt" , "wb" , stdout);

    // this variable stores the number of nodes in the graph and the number of bits per label of a graph node
    int nVertices , nBits;
    cin >> nVertices >> nBits;

    // initially the number of clusters is equal to the number of vertices
    nClusters = nVertices;

    // allocate memory to the components and size arrays used in union find algorithms
    component = (int *) malloc ( sizeof(int) * (nVertices + 1) );
    size = (int *) malloc ( sizeof(int) * (nVertices + 1) );

    // now we do the necessary initializations
    for(int i = 0 ; i <= nVertices ; ++i){

        // as each component lies in its own connected component at first
        component[i] = i;

        // as the size of each tree in the algorithm initially is 1
        size[i] = 1;
    }

    // now scan the bit strings coressponding to the nodes in the graph
    // each element in this vector is of the form pair< nodeNumber , bitString >
    vector< pair< int , string > > bitStrings;

    for(int i = 0 ; i < nVertices ; ++i){
        // this is a temporary string used in scanning the bitString of a node in the graph
        string temp = "";
        char ch;

        for(int j = 0 ; j < nBits ; ++j){
            cin >> ch;
            temp += ch;
        }

        bitStrings.PB( make_pair( i+1 , temp ) );
    }

    // now we group all the nodes in the graph based on the count of 1's in their labels
    // this vector should be interpreted as vector of vectors of pairs
    vector< vector< pair< int , string > > > groups( nBits + 1 );

    for(int i = 0 ; i < SZ( bitStrings ) ; ++i){

        // used in counting the number of 1's
        string tempStr = bitStrings[i].second;
        int count = 0;

        for(int j = 0 ; j < LN( tempStr ) ; ++j){
            if( tempStr.at(j) == '1' )
                ++count;
        }

        // make groups based on the count of 1's
        groups[count].PB( bitStrings[i] );
    }

    // now we start clustering the nodes in the groups
    for(int i = 0 ; i < SZ( groups ) ; ++i){

        // now we find the nodes with haming distance < 3 in the list containing i 1's
        for(int j = 0 ; j < SZ( groups[i] ) ; ++j){

            // this is the bit string of point under consideration
            string str1 = groups[i][j].second;

            // first we find for nodes having a hamming distance of less than 3 in its own list
            for(int k = j+1 ; k < SZ( groups[i] ) ; ++k){

                // this is the bit string which is compared with point under consideration bit string
                // for computing the hamming distance
                string str2 = groups[i][k].second;

                // temporary variable used in evaluating hamming Distance
                int hamDist = 0;

                for(int l = 0 ; l < LN( str1 ) ; ++l){
                    if( str1.at(l) != str2.at(l) )
                        ++hamDist;
                }

                if(hamDist < 3){
                    if( !isConnected(groups[i][j].first , groups[i][k].first) )
                        mergeComponents(groups[i][j].first , groups[i][k].first);
                }
            }

            // now we check for nodes in the neighboring lists consisting of i-1 1's
            if( i-1 >= 0 ){
                for(int k = 0 ; k < SZ( groups[i-1] ) ; ++k){

                    // this is the bit string which is compared with the point under consideration bit string
                    // for computing the hamming distance
                    string str3 = groups[i-1][k].second;

                    // temporary variable used in evaluating hamming distance
                    int hamDist = 0;

                    for(int l = 0 ; l < LN( str1 ) ; ++l){
                        if( str1.at(l) != str3.at(l) )
                            ++hamDist;
                    }

                    if(hamDist < 3){
                        if( !isConnected(groups[i][j].first , groups[i-1][k].first) )
                            mergeComponents( groups[i][j].first , groups[i-1][k].first);
                    }
                }
            }

            // now we check for nodes in the neighboring lists consisting of i-2 1's
            if( i-2 >= 0 ){
                for(int k = 0 ; k < SZ( groups[i-2] ) ; ++k){

                    // this is the bit string which is compared with the point under consideration bit string
                    // for computing the hamming distance
                    string str4 = groups[i-2][k].second;

                    // temporary variable used in evaluating hamming distance
                    int hamDist = 0;

                    for(int l = 0 ; l < LN( str1 ) ; ++l){
                        if( str1.at(l) != str4.at(l) )
                            ++hamDist;
                    }

                    if(hamDist < 3){
                        if( !isConnected(groups[i][j].first , groups[i-2][k].first) )
                            mergeComponents( groups[i][j].first , groups[i-2][k].first);
                    }
                }
            }

            // now we check for nodes in the neighboring lists consisting of i+1 1's
            if( i+1 <= nBits ){
                for(int k = 0 ; k < SZ( groups[i+1] ) ; ++k){

                    // this is the bit string which is compared with the point under consideration bit string
                    // for computing the hamming distance
                    string str5 = groups[i+1][k].second;

                    // temporary variable used in evaluating hamming distance
                    int hamDist = 0;

                    for(int l = 0 ; l < LN( str1 ) ; ++l){
                        if( str1.at(l) != str5.at(l) )
                            ++hamDist;
                    }

                    if(hamDist < 3){
                        if( !isConnected(groups[i][j].first , groups[i+1][k].first) )
                            mergeComponents( groups[i][j].first , groups[i+1][k].first);
                    }
                }
            }

            // now we check for nodes in the neighboring lists consisting of i+2 1's
            if( i+2 <= nBits ){
                for(int k = 0 ; k < SZ( groups[i+2] ) ; ++k){

                    // this is the bit string which is compared with the point under consideration bit string
                    // for computing the hamming distance
                    string str6 = groups[i+2][k].second;

                    // temporary variable used in evaluating hamming distance
                    int hamDist = 0;

                    for(int l = 0 ; l < LN( str1 ) ; ++l){
                        if( str1.at(l) != str6.at(l) )
                            ++hamDist;
                    }

                    if(hamDist < 3){
                        if( !isConnected(groups[i][j].first , groups[i+2][k].first) )
                            mergeComponents( groups[i][j].first , groups[i+2][k].first);
                    }
                }
            }

        }

    }

    cout << "The number of clusters are : " << nClusters << endl;

    return 0;
}
