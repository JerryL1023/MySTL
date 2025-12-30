#include"../src/eVector.hpp"
#include<iostream>
#include<vector>

using namespace std;

int main(){
    eVector<int> evec = {1,2,3,4,5};

    auto it1 = evec.erase(evec.begin() + 1,evec.begin() + 4);
    for(auto& x : evec) cout << x << ' ';

    cout << *it1 << endl;
    cout << endl;



    cout << "============stl_vector==============" << endl;
    vector<int> std_vec = {1,2,3,4,5};
    auto it2 = std_vec.erase(std_vec.begin() + 1,std_vec.begin() + 4);

    for(auto& x : std_vec) cout << x << ' ';
    cout << *it2 << endl;
    cout << endl;
    return 0;

    return 0;
}