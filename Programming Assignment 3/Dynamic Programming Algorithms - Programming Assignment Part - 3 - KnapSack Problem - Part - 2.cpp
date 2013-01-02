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

// this vector will store all the items provided to us vector< pair< itemValue , itemWeight > >
vector< pair< LL , LL > > items;

// this map will serve as a search table for our memoized top-down recursive procedure to compute the optimal value
// map< pair< nItems , knapsackSize > , optimalValue >
map< pair< LL , LL > , LL > searchTable;

// this function will help us evaluate the optimal value for the respective number of items and a given knapsack capacity
LL computeOptimal(LL nItems , LL knapsackCapacity);

int main(){

    freopen("/home/ankit/Desktop/Coursera Courses/Design and Analysis of Algorithms - Part 2/Programming Assignment 3/knapsack2.txt","rb",stdin);
    freopen("/home/ankit/Desktop/Coursera Courses/Design and Analysis of Algorithms - Part 2/Programming Assignment 3/knapsack2Answer.txt","wb",stdout);

    LL knapsackSize;
    cin >> knapsackSize;

    LL nItems;
    cin >> nItems;

    // this is a dummy item that we have added
    items.PB( make_pair( 0 , 0 ) );

    for(LL i = 0 ; i < nItems ; ++i){

        LL tempVal , tempWeight;
        cin >> tempVal >> tempWeight;

        items.PB( make_pair( tempVal , tempWeight ) );
    }

    // now we call the computeOptimal function to evaluate the optimal value for the given number of items and the knapsack
    // size
    computeOptimal(nItems , knapsackSize);

    cout << "The optimal value is : " << ( (searchTable.find( make_pair( nItems , knapsackSize ) ) ) -> second )<< endl;

    return 0;
}

LL computeOptimal(LL nItems , LL knapsackCapacity){

    if( nItems == 0 || knapsackCapacity == 0)
        return 0;

    else{

        // if the value for the given number of items and a given knapsack capacity is already present in the map
        // just return the value
        if( searchTable.find( make_pair( nItems , knapsackCapacity ) ) != searchTable.end() ){
            return ( ( searchTable.find( make_pair( nItems , knapsackCapacity ) ) ) -> second );
        }

        else{

            if( items[ nItems ].second > knapsackCapacity ){
                computeOptimal(nItems - 1 , knapsackCapacity);
                searchTable.insert( make_pair( make_pair( nItems , knapsackCapacity )  , searchTable.find( make_pair(nItems - 1 , knapsackCapacity) )->second ) );
            }

            else{
                 computeOptimal(nItems - 1 , knapsackCapacity);
                 computeOptimal(nItems - 1 , knapsackCapacity - items[nItems].second);

                 LL value = max( items[nItems].first + (searchTable.find( make_pair( nItems - 1 , knapsackCapacity - items[nItems].second ) )->second) , (searchTable.find( make_pair( nItems - 1 , knapsackCapacity ) )->second));

                 searchTable.insert( make_pair( make_pair( nItems , knapsackCapacity ) , value));
            }
        }
    }
}
