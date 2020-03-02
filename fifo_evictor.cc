#include "fifo_evictor.hh"

class FIFO_Evictor(Evictor){
public:
    void touch_key(const key_type& touchedKey){
        keys.push_front(touchedKey);
    }

    const key_type evict(){
        //This code may cause problems if something is "double-touched", or
        //added (and evicted) twice. Unclear.
        auto lastVal = keys.back();
        keys.pop_back();
        return lastVal;
    }
}