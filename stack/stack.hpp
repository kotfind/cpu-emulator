#pragma once

#include <cstdlib>
#include <new>

namespace stack {
    class EmptyStackException : public std::exception {
        public:
            const char* what() {
                return "the stack is empty";
            }
    };

    class StackIndexOverflowException : public std::exception {
        public:
            const char* what() {
                return "the size of stack is less than index";
            }
    };

    class StackMovedException : public std::exception {
        public:
            const char* what() {
                return "the stack has been moved";
            }
    };

    template<typename DataT>
    class Stack {
        public:
            Stack() 
              : data(new DataT[1]),
                capacity(1),
                size(0)
            {}

            Stack(const Stack& other)
              : data(nullptr)
            {
                *this = other;
            }

            Stack(Stack&& other)
              : data(nullptr)
            {
                *this = std::move(other);
            }

            ~Stack() {
                delete[] data;
            }

            Stack& operator=(const Stack& other) {
                size = other.size;
                capacity = std::max(1UZ, size);
                delete[] data;
                data = new DataT[capacity];

                for (size_t i = 0; i < size; ++i) {
                    data[i] = other.data[i];
                }

                return *this;
            }

            Stack& operator=(Stack&& other) {
                delete[] data;
                data = other.data;
                size = other.size;
                capacity = other.capacity;

                other.data = nullptr;
                other.size = 0;
                other.capacity = 0;

                return *this;
            }

            DataT& push(DataT&& value) {
                check_if_moved();
                increment_size();
                return data[size - 1] = std::move(value);
            }

            DataT& push(const DataT& value) {
                check_if_moved();
                increment_size();
                return data[size - 1] = value;
            }

            DataT pop() {
                check_if_moved();
                if (is_empty()) {
                    throw EmptyStackException();
                }
                return data[--size];
            }

            DataT& top() const {
                check_if_moved();
                if (is_empty()) {
                    throw EmptyStackException();
                }
                return data[size - 1];
            }

            DataT& nth(size_t i) const {
                check_if_moved();
                if (i < size) {
                    return data[size - 1 - i];
                }
                throw StackIndexOverflowException();
            }

            bool is_empty() const {
                check_if_moved();
                return size == 0;
            }

        private:
            void increment_size() {
                if (size + 1 > capacity) {
                    capacity *= 2;
                    auto* data_new = new DataT[capacity];
                    for (size_t i = 0; i < size; ++i) {
                        data_new[i] = std::move(data[i]);
                    }

                    delete[] data;
                    data = data_new;
                }
                ++size;
            }

            void check_if_moved() const {
                if (data == nullptr) {
                    throw StackMovedException();
                }
            }

            DataT* data;
            size_t capacity;
            size_t size;
    };
};
