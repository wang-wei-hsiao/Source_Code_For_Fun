#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;
static int size;
static int subsize; /* sqrt(size) */

/* print matrix*/
void print(vector<vector<int>>&matrix) {
    for (int i=0; i<size; i++) {
        for (int k=0; k<size; k++) {
            cout << matrix[i][k] << " ";
        }
        cout << endl;
    }
}
/* check the box that contains (i,k)*/
void box_is_valid (vector<vector<int>>&matrix, int i, int k,vector<bool> &value) {
    int x = i - i%subsize;
    int y = k - k%subsize;
    
    for (int dx = 0; dx<subsize; dx++) {
        for (int dy = 0; dy<subsize; dy++) {
            if( matrix[x+dx][y+dy]!=0 ) {
                int index = matrix[x+dx][y+dy]-1;
                value[index] = false;
            }
        }
    }
}

void column_is_valid (vector<vector<int>>&matrix, int i, int k ,vector<bool> &value) {
    for (int x=0; x<size; x++){
        if( matrix[x][k]!=0 ) {
            int index = matrix[x][k]-1;
            value[index] = false;
        }
    }
}

void row_is_valid (vector<vector<int>>&matrix, int i, int k ,vector<bool> &value) {
    for (int y=0; y<size; y++){
        if( matrix[i][y]!=0 ) {
            int index = matrix[i][y]-1;
            value[index] = false;
        }
    }
}

/* find possible value at (i,k) */
vector<bool> valid_value(vector<vector<int>>&matrix, int i, int k) {
    vector<bool> value(size,true);
    row_is_valid(matrix, i, k, value);
    column_is_valid(matrix, i, k, value);
    box_is_valid(matrix, i, k, value);

    return value;
}

/* solve (i,k) */
bool solve(vector<vector<int>>&matrix, int i, int k) {
    if(i == size)
        return true;
    
    pair<int,int> next(i,k+1); /* next empty element */
    while(true) {
        if( next.second==size ){
            next.second = 0;
            next.first++;
        }
        if( next.first==size ) // no more empty element
            break;
        if( matrix[next.first][next.second]==0 ) // find the next empty element
            break;
        next.second++;
    }
    
    vector<bool> value = valid_value(matrix, i, k); /* index 0~size-1 -> possible value = index+1 */
    for (int a=0 ; a<size; a++) {
        if( value[a]==true ) {
            matrix[i][k] = a+1;
            if( solve(matrix, next.first, next.second) )
                return true;
            else
                matrix[i][k]=0;
        }
    }
    
    return false; // all cases fail, end of this function
}

/* start solve from the first empty element */
bool solve(vector<vector<int>>&matrix) {
    int i=0, k=0;
    
    while(matrix[i][k]!=0) {
        k++;
        if(k==size){
            k=0;
            i++;
        }
        if(i == size)
            return true;
    }
    return solve(matrix,i,k);
}

void solution(vector<vector<int>>&matrix) {
    if(solve(matrix)){
        print(matrix);
    }else {
        cout << "NO" <<endl;
    }
}

int main()
{
    vector<int>input;
    
    int num;
    while(cin >> num) {
        input.push_back(num);
    }
    size = sqrt(input.size());
    subsize = sqrt(size);
    
    vector<vector<int>>matrix(size);
    int a=0;
    for (int i=0; i<size; i++) {
        for (int k=0; k<size; k++) {
            matrix[i].push_back(input[a++]);
        }
    }
    
    solution(matrix);
    return 0;
}

/*

 1. input
 push into 1d vector
 get size N
 assign to 2D vector

 2. solve():
 
 
 3. (examinations of 3 necssary conditions )
 box_is_valid():
 column_is_valid():
 row_is_valid():
 
 */
