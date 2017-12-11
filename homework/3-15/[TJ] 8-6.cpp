#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <climits>
using namespace std;

int main(){
    vector<unsigned> nums;
    string str;
    while (cin >> str){
        unsigned cur = 0;
        for (char i : str){
            cur <<= 1;
            if (i == '1') cur |= 1;
        }
        nums.push_back(cur);
    }
    int dist = INT_MAX;
    int ii, jj;
    for (int i=0; i<nums.size(); i++){
        for (int j=0; j<i; j++){
            if (__builtin_popcount(nums[i]^nums[j]) < dist){
                dist = __builtin_popcount(nums[i]^nums[j]);
                ii = i; jj = j;
            }
        }
    }
    printf("MIN_DIST = %d, i = %d, j = %d\n", dist, ii, jj);
    return 0;
}
