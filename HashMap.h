#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <string>
#include "Node.h"
#include "Block.h"

namespace cal {

	class HashMap {
	private:
		Node<Block>* data[50];

		HashMap(const HashMap& obj) = delete;
		HashMap& operator=(const HashMap& rhs) = delete;

		static size_t hash(size_t key) {
			return key % 50;
		}

	public:
		HashMap() {
			for (size_t i = 0; i < 50; i++) {
				data[i] = nullptr;
			}
		}

		~HashMap() {
			for (size_t i = 0; i < 50; i++) {
				data[i] = nullptr;
			}
		}

		bool contains(size_t key) {
			size_t idx = hash(key);
			Node<Block>* current = data[idx];

			while (current != nullptr) {
				if (current->data().tag() == key) {
					return true;
				}
				current = current->next();
			}
			return false;
		}

		Node<Block>*& operator[](size_t key) {
			return data[hash(key)];
		}

		const Node<Block>*& operator[](size_t key) const {
			static const Node<Block>* result;

			result = const_cast<HashMap*>(this)->operator[](key);
			
			return result;
		}

		void put(Block& obj) {
			size_t key = obj.tag();

			if (contains(key)) {
				Node<Block>*& node = (*this)[key];
				transfer(node->data().content(), obj.content());
			} else {
				size_t idx = hash(key);
				Node<Block>* node = new Node<Block>(obj);
				data[idx] = node;
			}
		}
	};
}

#endif
