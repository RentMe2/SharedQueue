#include "catch.hpp"
#include "queue/sharedQueue.hpp"
#include <vector>
#include <thread>
#include <future>

//returns number of push operations actually done in total iterations
size_t push(shareQueue::shared_queue &q,size_t total_iter = 100){
    std::string temp {"abc"};
    size_t ret =0;
    while(total_iter>0){
        if(q.push(temp))
            ret++;
        total_iter--;
    }
    return ret;
}
//returns number of pops actually done in total iterations
size_t pop(shareQueue::shared_queue &q, size_t total_iter = 100){
    std::string temp {"abc"};
        size_t count =0;
    while(total_iter>0 && q.size()>0){
            std::string ret = q.pop_b();
            if (!ret.empty() ) {
                count ++ ;
            }
            if( ret != temp) {
                    throw std::runtime_error("STRING MISMATCH");
                }

         total_iter--;
    }
    return count;
}


TEST_CASE("SIMPLE_PUSH_POP_TEST"){
    std::string sample_string = "SAMPLE";
    SECTION("SIMPLE_PUSH"){
        size_t initSize = 50;
        shareQueue::shared_queue q(initSize );//initialize with a size of 500
        for(int i =0;i<initSize ;i++){
            q.push(sample_string);
        }
        REQUIRE(q.push(sample_string) == false );
        REQUIRE(q.size() == initSize );
    }
    SECTION("SIMPLE_POP_B"){
        size_t initSize = 50;
        shareQueue::shared_queue q(initSize );//initialize with a size of 500
        for(int i =0;i<initSize ;i++){
            q.push(sample_string);
        }
        for(int i =0;i<initSize ;i++){
            q.pop();
        }

        REQUIRE(q.size() == 0);
    }
}

TEST_CASE("MULTI_THREAD_PUSH_POP_TEST"){
    size_t maxSize = 500;
    shareQueue::shared_queue q(maxSize);
    std::vector<std::future<size_t>> thrds;
    size_t total_iter = 100;

    thrds.emplace_back(std::async(push, std::ref(q), total_iter));
    //thrds.emplace_back(std::async(push, std::ref(q),total_iter));
    thrds.emplace_back(std::async(pop, std::ref(q),total_iter));
    //thrds.emplace_back(std::async(pop, std::ref(q),total_iter));

    size_t pshs = thrds[0].get();
    size_t pps = thrds[1].get();
    REQUIRE(pps == pshs);
 }