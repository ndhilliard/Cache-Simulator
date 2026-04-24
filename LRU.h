#ifndef LRU_H
#define LRU_H

#include <iostream>
#include <string>
#include "Node.h"
#include "HashMap.h"

namespace cal {

	class LRUCache : public Cache {
	private:
		size_t size;

		LRUCache(const LRUCache& obj) = delete;
		LRUCache& operator=(const LRUCache rhs) = delete;

	public:
		LRUCache() : Cache(5), size(0) {}

		virtual ~LRUCache() {}

		Node<Block>* read(size_t key) override {
			if (!values.contains(key)) {
				return nullptr;
			}

			Node<Block>* node = values[key];

			if (node == head) {
				return node;
			}

			if (node->prev() != nullptr) {
				node->prev()->next() = node->next();
			}

			if (node->next() != nullptr) {
				node->next()->prev() = node->prev();
			}

			if (node == tail) {
				tail = node->prev();
			}

			node->prev() = nullptr;
			node->next() = head;

			if (head != nullptr) {
				head->prev() = node;
			}

			head = node;

			return node;
		}

		void write(Block& obj) override {
			size_t key = obj.tag();

			if (values.contains(key)) {
				transfer(values[key]->data().content(), obj.content());
				read(key);
			} else {
				values.put(obj);
				Node<Block>* node = values[key];

				node->next() = head;
				node->prev() = nullptr;

				if (head != nullptr) {
					head->prev() = node;
				}

				head = node;

				if (tail == nullptr) {
					tail = node;
				}

				size += 1;

				if (size == capacity()) {
					Node<Block>* temp = tail;

					if(tail->prev() != nullptr) {
						tail->prev()->next() = nullptr;
					}

					tail = tail->prev();

					temp->prev() = nullptr;
					temp->next() = nullptr;

					// hopefully this fixes my error
					values[temp->data().tag()] = nullptr;
					delete temp;

					size -= 1;
				}
			}
		}
	};
}

#endif
