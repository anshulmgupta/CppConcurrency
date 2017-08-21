#include<iostream>
#include<thread>
#include<vector>
#include<cassert>
#include<algorithm>

using namespace std;

void thread_function(int i){
 
    cout << "Hello From Thread " << i << "\n";

}

int main(){
    vector<thread> worker;
    for(int i=0;i<10;i++){
        auto th = thread(&thread_function, i);
        worker.push_back(move(th));
        assert(!th.joinable());
    }
    cout << "Hello World!\n";
    for_each(worker.begin(), worker.end(), [](thread& th)
        {   
            assert(th.joinable());
            th.join();
        }
    );
    return 0;

}
