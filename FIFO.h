#ifndef FIFO_H
#define FIFO_H

#include <iostream>
#include <string>
#include "Node.h"
#include "HashMap.h"

namespace cal {

	class FIFOCache : public Cache {

	private:
		size_t size;

		FIFOCache(const FIFOCache& obj) = delete;
		FIFOCache& operator=(const FIFOCache& rhs) = delete;

	public:

		FIFOCache() : Cache(5), size(0) {}

		virtual ~FIFOCache() {}

		Node<Block>* read(size_t key) override {
			
			if (!values.contains(key)) {
				return nullptr;
			}
			return values[key];
		}

		void write(Block& obj) override {
			
			size_t key = obj.tag();

			if (values.contains(key)) {
				transfer(values[key]->data().content(), obj.content());
			} else {

				values.put(obj);
				Node<Block>* node = values[key];

				node->prev() = tail;
				node->next() = nullptr;

				if (tail != nullptr) {
					tail->next() = node;
				}

				tail = node;

				if (head == nullptr) {
					head = node;
				}

				size += 1;

				if (size == capacity()) {
					Node<Block>* temp = head;

					if (head->next() != nullptr) {
						head->next()->prev() = nullptr;
					}

					head = head->next();

					temp->prev() = nullptr;
					temp->next() = nullptr;

					values[temp->data().tag()] = nullptr;
					delete temp;

					size -= 1;
				}
			}
		}
	};
}

#endif
