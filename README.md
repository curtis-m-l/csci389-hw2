# CSCI 389 Homework 02: Hash it out


## Basic Cache Operations:

	Our initial design mainly made use of the standard library's unordered map for
	basic cache operations. We used to unordered maps: one to hold the values stored
	in the cache, and another for the sizes of each object. In retrospect, instead of
	creating a whole new map to hold sizes, we could have made a single unordered map
	full of size-value tuples, but this version is nearly as efficient. The initial 
	design had no evicition policy, and threw out new values as soon as the cache was
	full. (Though it still allowed existing values to be edited if there was space.)
	set(), get(), and del() make use of the unordered map operations emplace() find(),
	and erase() respectively to interact with the cache. reset() merely used the
	unordered map operation clear() to empty both maps after resetting m_current_mem.


## Testing:

	Our test program is fairly simple. It consists mainly of a series of test functions
	and a large list of possible scenarios. Such as:
		- Basic operations, such as set(), get(), and delete() on a basic set of data
		- Modifying the size of existing values
		- Using set() to overflow the cache
		- Resizing stored values to overflow the cache
		- Setting values larger than the cache size
		- Getting elements that don't exist
		- Deleting elements that don't exist
		- Checking that get() returns the correct size


## Performance: 

	According to the official documentation for the standard library's unordered map,
	the average case performance for emplace(), find(), and erase() are all O(1). We
	found out that unordered map uses a hash function, and in addition it allows the
	user to pass it a hash function in its constructor. So if the user passes the cache
	a hash function, the cache constructor passes it to the unordered map. If no function
	is passed, it merely uses the standard library has function std::hash().

## Collision Resolution:

	Unordered map already uses seperate chaining to handle collision resolution, and
	we didn't see any reason to change that. This is evidenced by the unordered map
	member bucket_size, which returns the number of objects stored in a particular bucket
	based on its hash value.

## Dynamic Resizing:

	Our cache makes use of the unordered map operation rehash() to handle resizing.
	If the user passes a load factor, the cache constructor passes it to the unordered 
	maps using max_load_factor().

## Eviction Policy:
	
	To allow the user to pass their own evicition policy, we added a series of checks to
	set() to handle scenarios in which values need to be evicted, and one extra check in
	get() which lets the Evictor know when a value has been touched. This last check
	mainly exists to allow for an LRU eviction policy, but we didn't end up implementing
	one. All of our tests surrounding eviction focus on a simple FIFO policy.
