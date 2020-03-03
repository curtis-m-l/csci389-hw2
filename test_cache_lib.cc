#include <cassert>
#include <iostream>
#include "cache.hh"

void test_set(Cache& items, key_type key, Cache::val_type val, Cache::size_type size)
{
    items.set(key, val, size);
    //Can't use asserts in this function, would require get. Assert this in main.
}

void test_get(Cache& items, key_type key, Cache::size_type itemSize)
{
    Cache::val_type got_item = items.get(key, itemSize);
    assert(got_item != nullptr);
}

void test_del(Cache& items, key_type key)
{
    bool delete_success = items.del(key);
    assert(delete_success);
}

void test_space_used(Cache& items, Cache::size_type target_size)
{
    Cache::size_type used_space = items.space_used();
    assert(used_space == target_size);
}

void test_reset(Cache& items)
{
    items.reset();
    assert(items.space_used() == 0);
}

int main()
{
    //Basic tests
    Cache testCache = Cache(100);
    //Add A
    Cache::byte_type dataA = 'A';
    Cache::val_type pointA = &dataA;
    test_set(testCache, "ItemA", pointA, 50);
    std::cout << "Current memory used: " << testCache.space_used() << "\n";
    //Add B
    Cache::byte_type dataB = 'B';
    Cache::val_type pointB = &dataB;
    test_set(testCache, "ItemB", pointB, 30);
    std::cout << "Current memory used: " << testCache.space_used() << "\n";
    //Add C
    Cache::byte_type dataC = 'C';
    Cache::val_type pointC = &dataC;
    test_set(testCache, "ItemC", pointC, 20);
    std::cout << "Current memory used: " << testCache.space_used() << "\n";
    //Get B (ignore last param)
    test_get(testCache, "ItemB", 30);
    //Check cache size
    test_space_used(testCache, 100);
    //Delete A
    test_del(testCache, "ItemA");
    //Add D
    Cache::byte_type dataD = 'D';
    Cache::val_type pointD = &dataD;
    test_set(testCache, "ItemD", pointD, 10);
    std::cout << "Current memory used: " << testCache.space_used() << "\n";
    //Complex Tests
    //Modify size of D
    test_set(testCache, "ItemD", pointD, 40);
    std::cout << "Current memory used: " << testCache.space_used() << "\n";
    //Add A (Overflow)
    test_set(testCache, "ItemA", pointA, 50);
    std::cout << "Current memory used: " << testCache.space_used() << "\n";
    //Add A (Way too big)
    test_set(testCache, "ItemA", pointA, 200);
    std::cout << "Current memory used: " << testCache.space_used() << "\n";
    //Get E (which doesn't exist) [Intended Fail]
    //test_get(testCache, "ItemE", 20);
    //reset cache
    test_reset(testCache);
    std::cout << "Cache Reset!\n";
    //Get A (which doesn't exist) [Intended Fail]
    //test_get(testCache, "ItemA", 30);
    //Set A, B, and C
    test_set(testCache, "ItemA", pointA, 25);
    test_set(testCache, "ItemB", pointB, 35);
    test_set(testCache, "ItemC", pointC, 10);
    //Check that get modifies its second last param
    Cache::size_type gotItemSize = 0;
    test_get(testCache, "ItemC", gotItemSize);
    std::cout << "The size of the item is: " << gotItemSize << "\n";

    testCache.~Cache();
    return 0;
}