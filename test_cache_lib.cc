#include <cassert>
#include <iostream>
#include "cache.hh"
#include "fifo_evictor.hh"

void test_set(Cache& items, key_type key, Cache::val_type val, Cache::size_type size)
{
    items.set(key, val, size);
    // Can't use asserts in this function, would require get.
    // Asserted in main()
}

void test_get(Cache& items, key_type key, Cache::size_type& itemSize)
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
    // Global test variables
    Cache::size_type maxmem = 100;
    float max_load_factor = 0.75; 
    Cache::size_type gotItemSize = 0;
    Cache::hash_func testHash = [](key_type key)->Cache::size_type {return static_cast<uint32_t>(key[4]);};
    Cache testCache = Cache(maxmem, max_load_factor, nullptr, testHash);

    // BASIC TESTS

    // Add A
    Cache::byte_type dataA = 'A';
    Cache::val_type pointA = &dataA;
    test_set(testCache, "ItemA", pointA, 50);
    std::cout << "Current memory used: " << testCache.space_used() << "\n";
    // Add B
    Cache::byte_type dataB = 'B';
    Cache::val_type pointB = &dataB;
    test_set(testCache, "ItemB", pointB, 30);
    std::cout << "Current memory used: " << testCache.space_used() << "\n";
    // Add C
    Cache::byte_type dataC = 'C';
    Cache::val_type pointC = &dataC;
    test_set(testCache, "ItemC", pointC, 20);
    std::cout << "Current memory used: " << testCache.space_used() << "\n";
    // Get B (ignore last param)
    test_get(testCache, "ItemB", gotItemSize);
    // Check cache size
    test_space_used(testCache, 100);
    // Delete A
    test_del(testCache, "ItemA");
    // Add D
    Cache::byte_type dataD = 'D';
    Cache::val_type pointD = &dataD;
    test_set(testCache, "ItemD", pointD, 10);
    std::cout << "Current memory used: " << testCache.space_used() << "\n";

    // COMPLEX TESTS
    
    // Modify size of D
    test_set(testCache, "ItemD", pointD, 40);
    std::cout << "Current memory used: " << testCache.space_used() << "\n";
    // Add A (Overflow)
    test_set(testCache, "ItemA", pointA, 50);
    std::cout << "Current memory used: " << testCache.space_used() << "\n";
    // Add A (Way too big)
    test_set(testCache, "ItemA", pointA, 200);
    std::cout << "Current memory used: " << testCache.space_used() << "\n";
    // Get E (which doesn't exist) [Intended Fail] *BEHAVED AS EXPECTED*
    // test_get(testCache, "ItemE", 20);
    // reset cache
    test_reset(testCache);
    std::cout << "Cache Reset!\n";
    // Get A (which doesn't exist) [Intended Fail] *BEHAVED AS EXPECTED*
    // test_get(testCache, "ItemA", 30);
    // Set A, B, and C
    test_set(testCache, "ItemA", pointA, 25);
    test_set(testCache, "ItemB", pointB, 35);
    test_set(testCache, "ItemC", pointC, 10);
    // Check that get modifies its second last param
    test_get(testCache, "ItemC", gotItemSize);
    std::cout << "The size of the item is: " << gotItemSize << "\n";

    // EVICTION POLICY TESTS

    std::cout << "\nTesting eviction policy...\n";
    testCache.~Cache();
    FIFO_Evictor evictPolicy = FIFO_Evictor();
    Cache e_testCache = Cache(maxmem, max_load_factor, &evictPolicy, testHash);
    // Make sure Cache size is initially 0
    std::cout << "Initial size of eviction-equipped cache: " << e_testCache.space_used() << "\n";
    // Fill up cache:
    // Add A
    std::cout << "Adding item of size 50...\n";
    test_set(e_testCache, "ItemA", pointA, 50);
    std::cout << "Current memory used: " << e_testCache.space_used() << " | Expected: 50\n";
    // Add B
    std::cout << "Adding item of size 30...\n";
    test_set(e_testCache, "ItemB", pointB, 30);
    std::cout << "Current memory used: " << e_testCache.space_used() << " | Expected: 80\n";
    // Add C
    std::cout << "Adding item of size 20...\n";
    test_set(e_testCache, "ItemC", pointC, 20);
    std::cout << "Current memory used: " << e_testCache.space_used() << " | Expected: 100\n";
    // Evict A:
    // Add D
    std::cout << "Adding item of size 40...\n";
    test_set(e_testCache, "ItemD", pointD, 40);
    std::cout << "Current memory used: " << e_testCache.space_used() << " | Expected: 90\n";
    // Evict B and C:
    // Add E
    Cache::byte_type dataE = 'E';
    Cache::val_type pointE = &dataE;
    std::cout << "Adding item of size 45...\n";
    test_set(e_testCache, "ItemE", pointE, 45);
    std::cout << "Current memory used: " << e_testCache.space_used() << " | Expected: 85\n";
    // Try something too big for the cache:
    Cache::byte_type dataF = 'F';
    Cache::val_type pointF = &dataF;
    std::cout << "Adding item of size 110...\n";
    test_set(e_testCache, "ItemF", pointF, 110);
    std::cout << "Current memory used: " << e_testCache.space_used() << " | Expected: 85\n";
    // Try getting stuff
    // Get D
    test_get(e_testCache, "ItemD", gotItemSize);
    // Add F:
    std::cout << "Adding item of size 30...\n";
    test_set(e_testCache, "ItemF", pointF, 30);
    std::cout << "Current memory used: " << e_testCache.space_used() << " | Expected: 75\n";
    // Add B, big huge
    std::cout << "Adding item of size 100...\n";
    test_set(e_testCache, "ItemB", pointB, 100);
    std::cout << "Current memory used: " << e_testCache.space_used() << " | Expected: 100\n";

    e_testCache.~Cache();
    return 0;
}
