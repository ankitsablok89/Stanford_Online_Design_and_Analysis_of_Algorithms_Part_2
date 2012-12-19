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

    // open the input file describing the jobs using the freopen function
    freopen("/home/ankit/Desktop/Coursera Courses/Design and Analysis of Algorithms - Part 2/Programming Assignment 1/jobs.txt" , "rb" , stdin);

    // open the output file to write the answer to job scheduling problem describing the optimal assignment
    // of jobs and writes down the sum of minimum weighted completion times
    freopen("/home/ankit/Desktop/Coursera Courses/Design and Analysis of Algorithms - Part 2/Programming Assignment 1/Question-1-Answer-Greedy-Ratio.txt" , "wb" , stdout);

    // this variable stores the number of jobs in the input file
    int n_jobs;
    cin >> n_jobs;

    // now as the input file consists of the inputs weight of the job and the length of the job
    // we store it in a vector which stores the weight and length of a job
    vector< pair< int , int > > jobs;

    for(int i = 0 ; i < n_jobs ; ++i){

        // these temporary variables store the weight and length of the jobs
        int weight;
        int length;

        cin >> weight >> length;

        // make a pair and add it to vector jobs
        jobs.PB( make_pair( weight , length ) );
    }

    // this vector stores the ratio (wj / lj) of the jobs provided in the input
    vector< pair< double , pair< int , int > > > greedyVector;

    for(int i = 0 ; i < SZ( jobs ) ; ++i){
        greedyVector.PB( make_pair( (double)jobs[i].first / (double)jobs[i].second , make_pair( jobs[i].first , jobs[i].second ) ) );
    }

    // now sort all the elements in the greedy vector
    sort( ALL( greedyVector ) );
    // now reverse all the elements of the greedy vector
    reverse( ALL( greedyVector ) );

    // these variables are used to evaluate the weighted sum and the completion times
    // for the jobs
    ULL weightSum = 0;
    ULL completionTime = 0;

    for(int i = 0 ; i < SZ( greedyVector ) ; ++i){
        completionTime += greedyVector[i].second.second;
        weightSum += greedyVector[i].second.first * completionTime;
    }

    cout << "The minimum weighted sum is : " << weightSum << endl;

    return 0;
}
