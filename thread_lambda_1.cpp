#include<iostream>
#include<thread>
#include<vector>
#include<algorithm>

using namespace std;


int main(){
    vector<thread> workers;
    for(int i=0;i<10;i++){
        workers.push_back(thread([i]()
        {
            cout << "Hello From Thread " << i << "\n";     
        }));
    }
    cout << "Hello World!\n";
    for_each(workers.begin(), workers.end(), [](thread &th)
        {
            th.join();
        });
    return 0;

}
