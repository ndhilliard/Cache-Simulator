#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Word.h"
#include "Node.h"
#include "Block.h"
#include "Cache.h"
#include "LRU.h"
#include "FIFO.h"

using namespace cal;

int main()
{
	srand(time(nullptr));
	
	Block blocks[10];

	blocks[0].tag() = 0; blocks[0].content() = Word("00000000");
	blocks[1].tag() = 1; blocks[1].content() = Word("00000001");
	blocks[2].tag() = 2; blocks[2].content() = Word("00000010");
	blocks[3].tag() = 3; blocks[3].content() = Word("00000011");
	blocks[4].tag() = 4; blocks[4].content() = Word("00000100");
	blocks[5].tag() = 5; blocks[5].content() = Word("00000101");
	blocks[6].tag() = 6; blocks[6].content() = Word("00000110");
	blocks[7].tag() = 7; blocks[7].content() = Word("00000111");
	blocks[8].tag() = 8; blocks[8].content() = Word("00001000");
	blocks[9].tag() = 9; blocks[9].content() = Word("00001001");

	LRUCache lru;
	FIFOCache fifo;

	for (int i = 0; i < 20; i++) {
		int idx = rand() % 10;
		
		Block& selected = blocks[idx];

		lru.write(selected);
		fifo.write(selected);

		std::cout << "iteration: " << (i + 1) << "\n";
		std::cout << "Selected Block: " << selected << "\n";
		std::cout << "LRU Cache: \n" << lru << "\n";
		std::cout << "Fifo Cache: \n" << fifo << "\n";
		std::cout << "---------------------------- \n";

	}

	return 0;
}
