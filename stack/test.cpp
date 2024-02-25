#include "test_utils/test_utils.hpp"
#include "stack.hpp"

#include <algorithm>
#include <vector>

using Stack = stack::Stack<int>;

TESTING_BEGIN

    TEST(default constructor)
        Stack s;

        ASSERT(s.is_empty());
    ENDTEST

    TEST(copy constructor)
        Stack s1;
        for (int i = 1; i <= 4; ++i) {
            s1.push(i);
        }

        Stack s2(s1);
        for (int i = 4; i >= 1; --i) {
            ASSERT_EQ(s2.pop(), i);
        }
        ASSERT(s2.is_empty());
    ENDTEST

    TEST(move constructor)
        Stack s1;
        for (int i = 1; i <= 4; ++i) {
            s1.push(i);
        }

        Stack s2(std::move(s1));
        for (int i = 4; i >= 1; --i) {
            ASSERT_EQ(s2.pop(), i);
        }
        ASSERT(s2.is_empty());

        try {
            s1.top();
            FAIL
        } catch(const stack::StackMovedException&) {
        } catch(...) {
            FAIL
        }
    ENDTEST

    TEST(copy operator=)
        Stack s1;
        for (int i = 1; i <= 4; ++i) {
            s1.push(i);
        }

        Stack s2;
        s2 = s1;
        for (int i = 4; i >= 1; --i) {
            ASSERT_EQ(s2.pop(), i);
        }
        ASSERT(s2.is_empty());
    ENDTEST

    TEST(move operator=)
        Stack s1;
        for (int i = 1; i <= 4; ++i) {
            s1.push(i);
        }

        Stack s2;
        s2 = std::move(s1);
        for (int i = 4; i >= 1; --i) {
            ASSERT_EQ(s2.pop(), i);
        }
        ASSERT(s2.is_empty());

        try {
            s1.top();
            FAIL
        } catch(const stack::StackMovedException&) {
        } catch(...) {
            FAIL
        }
    ENDTEST

    TEST(copy push and top)
        stack::Stack<std::vector<int>> s1;
        for (int i = 1; i <= 4; ++i) {
            std::vector v = {i, 2*i, 3*i, 4*i};
            ASSERT_EQ(s1.push(v), v);
            ASSERT_EQ(s1.top(), v);
        }
    ENDTEST

    TEST(move push)
        stack::Stack<std::vector<int>> s1;
        for (int i = 1; i <= 4; ++i) {
            std::vector v1 = {i, 2*i, 3*i, 4*i};
            auto v2 = v1;
            ASSERT_EQ(s1.push(std::move(v1)), v2);
            ASSERT_EQ(s1.top(), v2);
        }
    ENDTEST

    TEST(pop)
        Stack s;
        for (int i = 1; i <= 4; ++i) {
            s.push(i);
        }

        for (int i = 4; i >= 1; --i) {
            ASSERT_EQ(s.pop(), i);
        }
        ASSERT(s.is_empty());
    ENDTEST

    TEST(is_empty)
        Stack s;
        ASSERT(s.is_empty());
        s.push(1);
        ASSERT(!s.is_empty());
        s.pop();
        ASSERT(s.is_empty());
    ENDTEST

    TEST(top on empty stack)
        Stack s;

        try {
            s.top();
            FAIL
        } catch(const stack::EmptyStackException&) {
        } catch(...) {
            FAIL
        }
    ENDTEST

    TEST(pop empty stack)
        Stack s;

        try {
            s.pop();
            FAIL
        } catch(const stack::EmptyStackException&) {
        } catch(...) {
            FAIL
        }
    ENDTEST

TESTING_END
