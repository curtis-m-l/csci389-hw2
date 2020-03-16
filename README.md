# CSCI 389 Homework 03: Hash it out
Created by Maxx Curtis and Casey Harris.


## Test Cases/Results:

| Test: | Description: | Casey/Maxx | Aaron/Alex | Jonah/Elijah | Reilly/James |
| ---   | ---          | ---        | ---        | ---          | ---          |
| test_basic_operation | Performs simple operations with set, get, del, and reset | PASSED | PASSED | PASSED | PASSED |
| test_modify | Verifies that the cache can overwwrite existing values without duplication | PASSED | FAILED | FAILED | FAILED |
| test_reduction | Tests reducing the size of a cache element | FAILED | PASSED | PASSED | PASSED |
| test_set_object_cache_size | Tests adding an element of precisely the size of the cache to an empty cache | PASSED | PASSED | PASSED | PASSED |
| test_cache_bounds | Attempts to set an object larger than the size of the cache | PASSED | PASSED | PASSED | PASSED |
| test_overflow_no_evictor | Tests functionality when the cache overflows without an evictor | PASSED | PASSED | PASSED | PASSED |
| test_get_nonexistant_item | Attempts to get an item that never existed, and another that was deleted | PASSED | PASSED | PASSED | PASSED |
| test_basic_evictor | Performs basic operations on a cache that has an eviction policy, but does not prompt an eviction | PASSED | FAILED | FAILED | FAILED |
| test_cache_bounds_with_evictor | Tests functionality when the cache overflows with an evictor | PASSED | FAILED | FAILED | FAILED |
| test_uneccessary_eviction | Tests whether evictons occur when the cache should not evict | PASSED | FAILED | FAILED | FAILED |
| test_eviction | Directly tests 'touch_key' and 'evict' without using the cache API | PASSED | FAILED | PASSED | FAILED |
| test_evict_all | Tests functionality when evicting the entire cache is required | FAILED | FAILED | FAILED | FAILED |
| test_size_zero_does_not_evict | Test that adding a new element of size zero does not cause eviction | FAILED | FAILED | FAILED | FAILED |

### Casey/Maxx (Ours):
Our code was able to pass all of the non-evictor tests except for 'test reduction' which attempts to reduce the value of
	an object in an already full cache. This test mainly exists to make sure that the set() function correctly calculates size
	before rejecting values, and as it turns out we miscalculated sizes in scenarios where an item's size is reduced.
	We were unable to pass "evict all" and "test size zero does not evict", and as you'll see in the following paragraphs,
	no one else was either. This implies that our test code is bugged somehow, but after closer examinination we were unable to
	find a reason why this might be. As far as we can tell, all four caches fail to account for these scenarios.

### Aaron/Alex:
No linking or compilation errors.
	Aaron and Alex's code passe all of the non-evictor tests, with the exception of "modify value", in which their 
	get() command fails to update 'val_size' correctly.
	They fail to pass any of the evictor tests, which is very odd. We've examined our test code and were unable to find any
	reason that our code should pass while the other's fail, so these are counted as failures.

### Jonah/Elijah:
Jonah and Elijah's code was the only one (besides ours) to pass test_eviction. This means that their evictor works on its own,
but there was a problem with connecting the evictor and the cache, resulting in the failure of the other evictor tests. We're not sure whether that problem stems from our use of evictors or their implementation, as everyone but us failed all of the evictor tests. Jonah and Elijah's code failed due to apparent double-frees of pointers -- we weren't able to track down the source of the problem.

They also failed test_modify, meaning their code was poorly equipped to handle changing the size of an individual element in the cache. Interestingly, the cache updated its size correctly, but when we called get() the second parameter of that  function did not update correctly. They did pass the same series of asserts when we updated an element of the cache to be a smaller size, however.

### Reilly/James:
Like Jonah and Elijah's code, Reilly and James' evictor tests failed due to double-freeing pointers. In addition, their code raised issues when modifying a value in the cache, but passed when the object's replacement was a smaller size. (It also failed in the same manner, where the second parameter of a get function failed to update correctly. I swear I tested these files separately. --Casey)

However, one notable difference is that this code also failed the direct test of the evictor due to pointer double-frees. This hints to us that the issue probably resides in their code for that one, instead of the construction of our test. 
