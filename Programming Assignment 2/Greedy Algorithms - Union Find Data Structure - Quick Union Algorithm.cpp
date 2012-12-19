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

// this function is used to find the root of an object in the id array
int root(int *id , int object){
    while(object != id[object])
        object = id[object];

    return object;
}

// this function is used to perform the union operation
void unionOperation(int *id , int nObjects , int obj1 , int obj2){
    // this is the quick-union implementation of the union-find data structure
    // it involved just the updation of a single entry in the id array

    int obj1Root = root(id , obj1);
    int obj2Root = root(id , obj2);

    id[obj1Root] = obj2Root;

}

// this function is used to perform the find operation and this is a constant time operation in this case
bool findOperation(int *id , int obj1 , int obj2){
    // here we just need to check if the roots of the 2 objects are the same or not
    // if the roots are same then the 2 objects lie in the same connected component
    // else they don't
    return root(id , obj1) == root(id , obj2);
}

// this function is used to display the state of the array at any point of time
void displayArray(int *id , int nObjects){

    cout <<"The current state of the array is -: \n";
    for(int i = 0 ; i < nObjects ; ++i)
        cout << id[i] << " ";
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

    // initially all the object lie in there own connected components i.e no object is connected to any
    // other object initially and is connected to iteself only
    for(int i = 0 ; i < nObjects ; ++i)
        id[i] = i;

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
                    unionOperation(id , nObjects , object1 , object2);
                else
                    cout <<"They are already connected" << endl << endl;

                displayArray(id , nObjects);
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

                displayArray(id , nObjects);
            break;
        }

    }while( choice != -1 );

    return 0;
}
