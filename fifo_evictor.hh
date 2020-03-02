#include <deque>
#include "evictor.hh"

class FIFO_Evictor(Evictor){
public:
    //Deques are good for dual-ended operations (vectors have no push_front). 
    //https://en.cppreference.com/w/cpp/container/deque
    std::deque<key_type> keys;

    void touch_key(const key_type& touchedKey);
    const key_type evict();
}