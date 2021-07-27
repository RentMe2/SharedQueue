#pragma once

#include <vector>
#include <string>
#include <mutex>
#include <condition_variable>
#include <atomic>
namespace shareQueue{
    class shared_queue{
    public:
        shared_queue()=delete;
        explicit shared_queue(size_t initial_size){
            _capacity = initial_size;
            _size = 0;
            _data.reserve(initial_size);
            for (size_t count=0; count < initial_size; count ++)
                _data.emplace_back();
        }

        /**
         * push method adds provided element in to the data array. Uses a mutex for thread safety.
         * return true or false if the opertion is permissible.
         * @param input
         * @return boolean true or false if current operation is permissible
         */
        bool push(const std::string& input)noexcept{

            try{
                std::unique_lock<std::mutex> lck(_pushMutex);
                if (_size == _capacity) { return false; }

                _data[_pushIndex] = (input);
                _pushIndex = getNextIndex(_pushIndex);
                _size++;
                _myCond.notify_one();
                return true;
            }
            catch (std::exception&e) {
                //log exception
                return false;
            }
        }
        /**
         * pop method simply pops an element from the queue. Blocking call untill any data is pushed
         *
         * @return string data
         */
        std::string pop_b()noexcept{

            try{
                std::unique_lock<std::mutex> lck(_popMutex);

                if (_size == 0) {
                    {
                        std::unique_lock<std::mutex> lck2(_myMutex);
                        _myCond.wait(lck2, [&] { return _size != 0; });
                    }
                }
                auto temp = _data[_popIndex];
                _size--;
                _popIndex = getNextIndex(_popIndex);
                return temp;
            }
            catch (std::exception&e) {
                //log exception
                return "";
            }
        }
        /**
         * pop method simply pops an element from the queue. Blocking call untill any data is pushed
         *
         * @return string data . Empty string is returned if no data is available
         */
        std::string pop()noexcept{

            try{
                std::unique_lock<std::mutex> lck(_popMutex);

                if (_size == 0)
                    return "";
                auto temp = _data[_popIndex];
                _size--;
                _popIndex = getNextIndex(_popIndex);
                return temp;
            }
            catch (std::exception&e) {
                //log exception
                return "";
            }
        }
        /**
         * Return size of the queue. Not a recommended way because of multithreaded usage
         * @return returns current size of the queue
         */
        size_t size(){
            return _size;
        }
        ~shared_queue()=default;
    private:
        /**
         * getNextIndex comptes net index. If provided param current index reaches current capacity/data-limit
         * it is reset back to zero like in a circular linked-list
         * @param currIndex
         * @return returns next Index
         *
         */
        size_t getNextIndex(std::atomic_uint & currIndex)noexcept{
            if(currIndex == _capacity-1){
               return 0;
            }
            return currIndex+1;
        }
    private:
        std::mutex _pushMutex;
        std::mutex _popMutex;
        std::mutex _myMutex;
        std::condition_variable _myCond;
        std::atomic_uint _pushIndex=0;
        std::atomic_uint _popIndex=0;
        std::atomic_uint _size =0;
        size_t _capacity =0;
        std::vector<std::string> _data;
    };

}
