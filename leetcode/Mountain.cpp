#include <iostream>
#include<vector>
#include <map>
using namespace std;

class Solution {
public:
    bool validMountainArray(vector<int>& A) {
        if(A.size() <= 2)
            return false;
        int fIndex = 0;
        for(int i = 0; i < A.size()-1; i++) {
            if(A[i] >= A[i+1]) {
                fIndex = i;
                break;
            }
        }
        if(fIndex == 0)
            return false;
                                
        for(int j = fIndex; j < A.size(); j++){
            if(A[j+1] >= A[j] )
                return false;
        }
        
        return true;                            
    }

};

int main()
{
    Solution s;
    vector<int> v1 = {1,2,3,2,1};
    vector<int> v2 = {1,2,3,2,5};
    vector<int> v3 = {1,1,3,2,1};
    vector<int> v4 = {1,2,3,4,5};
    vector<int> v5 = {0,3,2,1};
    cout<< s.validMountainArray(v1) <<endl;
    cout<< s.validMountainArray(v2) <<endl;
    cout<< s.validMountainArray(v3) <<endl;
    cout<< s.validMountainArray(v4) <<endl;
    cout<< s.validMountainArray(v5) <<endl;
    map<int,string> m1 = {};
    m1[0]="g";
    m1[1] ="c";
    m1[2]="s";
    m1[4]="s";
    m1[6]="s";
    typedef map<int,string>::iterator mIter;
    mIter it = m1.begin();
    for(; it != m1.end(); it++) {
        cout << it->first << "-->" << it->second << endl;
    }
    return 0;
}

