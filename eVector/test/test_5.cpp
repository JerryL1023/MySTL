#include "../src/eVector.hpp"
#include<vector>

using namespace std;

int main(){
    eVector<int> vec = {1,2,3,4};
    //修改前，会出现bug
    for(int i=0;i<10;i++){
        vec.insert(vec.begin(),vec[vec.size()-1]);
    }

    for(auto& x : vec) cout << x << ' ';
    cout << endl;

    cout << "===========================" << endl;
    vector<int> std_vec = {1,2,3,4};
    for(int i=0;i<10;i++){
        std_vec.insert(std_vec.begin(),std_vec[std_vec.size()-1]);
    }

    for(auto& x : std_vec) cout << x << ' ';
    cout << endl;
    return 0;
}