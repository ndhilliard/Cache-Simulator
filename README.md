# Cache-Simulator
Cache replacement simulator

Built this for a computer architecture course. Implements two cache replacement policies (LRU and FIFO) using doubly linked lists and a hash map combo.

## what it does

Simulates how a cache decides which block to kick out when it's full. The two policies handle that different:

- **LRU** - evicts which block hasn't been used in the logest time
- **FIFO** - evicts whichver block has been sitting there the longest, regardless of how often it's been accessed

** How it's built

The core structure is a doubly linked list for ordering + a hash map for 0(1) lookups. The cache has a fixed capacity, and when it fills up it evicts based on whichver policy you're using

Class Breakdown:

- `Object` - base calss evertyhing enherits from
- `Block` - represents a single cache entry (has a tag, data, ect)
- `Cache` - abstract base class with the shared logic
- `LRUCache` - Inserts at head, ecivts from tail
- `FIFOCache` - inserts at tail, evicts from head
- `HashMap` - Custom hash map, fixed 50 bucket array

- `Main.cpp` - runs a simulation with 10 blocks, 20 random write operations, shows what get evicted and when

## Running it

bash

g++ -o cache main.cpp./cache

## What I learned

Got a lot more comfortable with pointer management, especially avoiding dangling pointer issues when evicting nodes that were still referenced by the hash map.
