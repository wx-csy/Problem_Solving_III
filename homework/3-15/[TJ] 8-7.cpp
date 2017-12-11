#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <climits>
using namespace std;

int main(){
    vector<unsigned> nums;
    string str;
    unsigned len;
    while (cin >> str){
        unsigned cur = 0;
        for (char i : str){
            cur <<= 1;
            if (i == '1') cur |= 1;
        }
        nums.push_back(cur);
        len = str.length();
    }
    for (unsigned i = 0; i < (1<<len); i++){
        for (int j=0; j<nums.size(); j++){
            if (__builtin_popcount(i&nums[j])&1) goto nxt;
        }
        for (int j = len-1; j>=0; j--){
            cout << bool(i&(1<<j));
        }
        cout << endl;
nxt:;
    }
    return 0;
}
