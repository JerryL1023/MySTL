#include <iostream>
#include "../src/eVector.hpp" 

using namespace std;

//测试动态扩容
void printState(eVector<int>& vec) {
    cout << "[State] Size: " << vec.size() 
         << " | Capacity: " << vec.capacity() << endl;
}

void verifyData(eVector<int>& vec) {
    cout << "[Check] Data integrity: ";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl << endl;
}

int main() {
    cout << "=== Test Start: Dynamic Expansion Logic ===" << endl;

    // 1. 初始化测试
    eVector<int> vec; 
    cout << "1. Initial State:" << endl;
    printState(vec);

    // 2. 边界扩容测试 (推入元素直到触发扩容)
    int testCount = 10; 
    cout << "2. Pushing " << testCount << " elements..." << endl;

    for (int i = 0; i < testCount; i++) {
        int val = i; 
        vec.push_back(i);
        
        cout << " -> Pushed " << val << ": ";
        // 每次 push 后打印状态，观察何时 capacity 翻倍
        cout << "Size=" << vec.size() << ", Cap=" << vec.capacity();
        
        // 简单的扩容提示
        if (vec.size() == vec.capacity()) {
            cout << " (Full, next push will trigger resize)";
        }
        cout << endl;
    }

    // 3. 数据完整性检查
    cout << "3. Verifying data after expansion..." << endl;
    verifyData(vec);

    // 4. 测试 pop (缩容逻辑通常 vector 不自动做，但要测试 size 是否正确减少)
    cout << "4. Popping one element..." << endl;
    vec.pop();
    printState(vec);
    
    return 0;
}