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

int main(){

    // open files to scan input and dump output
    freopen("/home/ankit/Desktop/Coursera Courses/Design and Analysis of Algorithms - Part 2/Programming Assignment 3/knapsack1.txt" , "rb" , stdin);
    freopen("/home/ankit/Desktop/Coursera Courses/Design and Analysis of Algorithms - Part 2/Programming Assignment 3/knapsack1Answer.txt" , "wb" , stdout);

    // this variable stores the capacity of the knapsack
    int knapSackSize;
    cin >> knapSackSize;

    // this variable stores the number of items in the input
    int nItems;
    cin >> nItems;

    // this vector of pairs stores the respective values in dollars and the sizes of the respective items
    vector< pair< int , int > > valuesAndSizes;

    // assume a virtual bag with size 0 and value 0
    valuesAndSizes.PB( make_pair( 0 , 0 ) );

    for(int i = 0 ; i < nItems ; ++i){

        // this is a temporary variable that stores the value of the item
        int itemValue;
        // this is a temporary variable that stores the value of the size of the item
        int itemSize;

        cin >> itemValue >> itemSize;

        valuesAndSizes.PB( make_pair( itemValue , itemSize ) );
    }

    // the following dynamic programming approach will solve the knapsack problem

    // this table will help us solve the problem
    int knapsackProblem[ nItems + 1 ][ knapSackSize + 1 ];

    // perform the necessary initializations
    for(int i = 0 ; i < knapSackSize + 1 ; ++i)
        knapsackProblem[0][i] = 0;

    // from the optimal substructure property of the knapsack problem we formulate the following code
    for(int i = 1 ; i < nItems + 1 ; ++i){
        for(int j = 0 ; j <= knapSackSize ; ++j){

            if( j - valuesAndSizes[i].second < 0 ){
                knapsackProblem[i][j] = knapsackProblem[i-1][j];
            }

            else{
                knapsackProblem[i][j] = max( knapsackProblem[i-1][j] , knapsackProblem[i-1][j - valuesAndSizes[i].second] + valuesAndSizes[i].first);
            }

        }
    }

    cout <<"The optimal value for the knapsack problem is : " << knapsackProblem[nItems][knapSackSize] << endl;

    return 0;
}
