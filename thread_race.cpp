#include<iostream>
#include<thread>
#include<vector>
#include<cassert>
#include<algorithm>

using namespace std;

struct List{

    struct Node{
        
        int    _x;
        Node * _next;
        Node(int y) : _x(y), _next(NULL){}

    };

    Node * _head;
    List() : _head(nullptr) {}

    void insert(int x){

        auto node = new Node(x);
        node->_next = _head;
        _head = node;

    }
    int count() const;

};

int List::count() const {

    int cnt = 0;
    auto tmp = _head;
    while(tmp != nullptr){
        cnt++;
        tmp = tmp->_next;
    }   
    
    return cnt;
}

void thread_function(List &list){
    
    for(int i = 0; i < 100 ; i++){
        list.insert(i);
    }
}

int main(){
    
    List list;
    vector<thread> workers;

    for(int i = 0 ; i < 10 ; i++){
        workers.push_back(thread(&thread_function, ref(list)));
    }

    for_each(workers.begin(), workers.end(), [](thread& th)
        {   
            th.join();
        }
    );

    int count = list.count();
    cout << "Total Elements = " << count << endl;
    return 0;

}
