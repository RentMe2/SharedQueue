#include "queue/sharedQueue.hpp"
#include <iostream>
#include <thread>
using namespace shareQueue;
void push(shared_queue &q){
    std::string temp {"abc"};
    size_t total_iter = 100;
    while(total_iter>0){
        q.push(temp);
        total_iter--;
    }
}
void pop(shared_queue &q){
    std::string temp {"abc"};
    size_t total_iter = 100;
    while(total_iter>0){
        std::string ret =q.pop_b();
        if( !ret.empty() and ret!= temp ){
            std::cout<<("STRING MISMATCH\n\n");
            return;
        }
        total_iter--;
    }
}
int main(){
    size_t maxSize = 100;
    shared_queue q(maxSize);
    std::vector<std::thread> thrds;

    thrds.emplace_back(std::thread(push, std::ref(q)));
    thrds.emplace_back(std::thread(push, std::ref(q)));
    thrds.emplace_back(std::thread(pop, std::ref(q)));
    thrds.emplace_back(std::thread(pop, std::ref(q)));

    for(auto&thrd:thrds)
        thrd.join();

    if(q.size() != 0){
        std::cout<<("INCORRECT SIZE\n");
        std::cout<<("SIZE : " )<<q.size() <<"\n";
    }else{
        std::cout<<("TEST CASE PASSED\n");
    }


    return 0;
}
