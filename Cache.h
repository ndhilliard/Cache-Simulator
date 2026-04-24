#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <string>
#include "HashMap.h"

namespace cal {

	class Cache : public Object {
	protected:
		Node<Block>* head;
		Node<Block>* tail;
		HashMap values;

	private:
		size_t CAP;

		Cache(const Cache& obj) = delete;
		Cache& operator=(const Cache& rhs) = delete;

		std::string toString() const override {
			std::stringstream out;

			Node<Block>* current = head;
			
			while (current != nullptr) {
				out << current->data();
				
				if (current->next() != nullptr) {
					out << "\n";
				}
				current = current->next();
			}
			return out.str();
		}

	public:
		Cache() : head(nullptr), tail(nullptr), CAP(50) {}

		Cache(size_t cap) : head(nullptr), tail(nullptr) {
			if (cap >= 2 && cap <= 50) {
				CAP = cap;
			} else {
				CAP = 50;
			}
		}

		virtual ~Cache() {
			clear(head);
		}

		size_t capacity() const {
			return CAP;
		}

		virtual Node<Block>* read(size_t key) = 0;

		virtual void write(Block& obj) = 0;
	};
}

#endif
