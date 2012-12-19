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

// this function is used to find the root of an object i.e the root of the connected component in which the
// object lies
int root(int *id , int object){

    // this is the list of nodes that occur on the path from the node to the root
    list<int> nodesOnPath;

    // we follow the parent pointers of the object in the connected component to get to the root
    while( object != id[object] ){
        nodesOnPath.PB(object);
        object = id[object];
    }

    // now this is the step that flattens the tree
    TR(nodesOnPath , it){
        id[*it] = object;
    }

    return object;
}

// this function is used to perform the union operation i.e to merge one rooted tree into the other one
void unionOperation(int *id , int *sz , int nObjects , int obj1 , int obj2){

    int obj1Root = root(id , obj1);
    int obj2Root = root(id , obj2);

    if( sz[ obj1Root ] < sz[ obj2Root ] ){
        id[ obj1Root ] = obj2Root;
        sz[ obj2Root ] += sz[ obj1Root ];
    }

    else{
        id[ obj2Root ] = obj1Root;
        sz[ obj1Root ] += sz[ obj2Root ];
    }
}

// this function is used to perform the find operation i.e to check if 2 objects are connected to each
// other via a path in the network
bool findOperation(int *id , int obj1 , int obj2){

    // just check if the roots of the 2 objects are the same or not which is an indication wether
    // the 2 objects lie in the same component or not
    return root(id, obj1) == root(id , obj2);
}

// this function is used to display the state of the arrays at any point of time
void displayArray(int *id , int *sz , int nObjects){

    cout <<"The current state of the id array is : \n";
    for(int i = 0 ; i < nObjects ; ++i)
        cout << id[i] << " ";
    cout << endl << "The current state of the sz array is : \n";
    for(int i = 0 ; i < nObjects ; ++i)
        cout << sz[i] << " ";

    cout << endl << endl;
}


int main(){

    // this variable stores the number of objects in the set that we use to demonstrate the union-find
    // data structure
    int nObjects;
    cout <<"Please enter the number of objects to perform the union-find operations on : ";
    cin >> nObjects;

    // this is the data structure that we use in performing the Quick-Find Union-Find Algorithm
    int id[nObjects];

    // this is the data structure that we use to store the size of the tree rooted at ith index
    int sz[nObjects];

    // initially all the object lie in there own connected components i.e no object is connected to any
    // other object initially and is connected to iteself only
    for(int i = 0 ; i < nObjects ; ++i){
            // initially all the objects lie in their own connected components and are only connected to
            // themselves
            id[i] = i;
            // initially the size of every tree in the forest is 1 because each tree just consists of a
            // single node
            sz[i] = 1;
    }

    // this variable stores the choice of the user to perform a specific operation
    int choice;

    // now we start performing queries on the union-find data structure
    do{
        cout <<"Please Enter \n1. To Perform Union of 2 Objects \n2. To Find if 2 Objects are Connected \n3. To Exit \nEnter Choice : ";
        cin >> choice;

        switch(choice){
            case 1:
                int object1 , object2;
                cout <<"Please enter object number 1 : ";
                cin >> object1;
                cout <<"Please enter object number 2 : ";
                cin >> object2;

                if( !findOperation(id , object1 , object2) )
                    unionOperation(id , sz , nObjects , object1 , object2);
                else
                    cout <<"They are already connected" << endl << endl;

                displayArray(id , sz , nObjects);
            break;

            case 2:
                int obj1 , obj2;
                cout <<"Please enter object 1 : ";
                cin >> obj1;
                cout << "Please enter object 2 : ";
                cin >> obj2;

                if( !findOperation(id , obj1 , obj2) )
                    cout <<"The 2 objects are not connected." << endl << endl;
                else
                    cout <<"The 2 objects are connected." << endl << endl;

                displayArray(id , sz , nObjects);
            break;
        }

    }while( choice != -1 );

    return 0;
}
