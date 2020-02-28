#include <cassert>
#include "cache.hh"

void test_set(Cache items, key_type key, val_type val, size_type size)
{
    items.set(key, val);
    //Can't use asserts in this function, would require get. Assert this in main.
}

void test_get(Cache items, key_type key, size_type itemSize)
{
    foo = items.get(key, itemSize)
    assert(foo != nullptr);
}

void test_del(Cache items, key_type key)
{
    items.del(key);
    assert(items.m_cache_vals.find(key) == items.m_cache_vals.end());
}

void test_space_used(Cache items, size_type target_size)
{
    foo = items.space_used();
    assert(foo == target_size);
}

void test_reset(Cache items)
{
    items.reset();
    assert(items.m_cache_vals.size() == 0);
    assert(items.m_cache_sizes.size() == 0);
}

int main()
{
    testCache = Cache(100);
    test_set(testCache, "ItemA", /*?*/, 50);
    test_set(testCache, "ItemB", /*?*/, 30);
    test_set(testCache, "ItemC", /*?*/, 20);
    test_get(testCache, "ItemB", 30);
    test_space_used(testCache, 100);

    ~testCache();
    return 0;
}