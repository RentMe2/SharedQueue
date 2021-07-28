#include "queue/sharedQueue.hpp"
#include <iostream>
#include <thread>
using namespace shareQueue;
int main(){
    size_t maxSize = 100;
    shared_queue q(maxSize);
    std::string sample = "sample";
    q.push(sample);
    auto ret = q.pop();

    if(ret.empty()){
        std::cout<<"ERR: Queue is Empty!\n";
    }
    else{
        std::cout<<"Queue Element : " << ret<<"\n";
    }

    return 0;
}
