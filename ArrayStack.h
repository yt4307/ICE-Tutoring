#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include <iostream>


using namespace std;

class StackEmpty {
public:
    StackEmpty(const string& err) { }
};

class StackFull {
public:
    StackFull(const string& err) { }
};


template <typename E>
class ArrayStack {
    enum { DEF_CAPACITY = 100 };		// default stack capacity
public:
    ArrayStack(int cap = DEF_CAPACITY);		// constructor from capacity
    int size() const;				// number of items in the stack
    bool empty() const;				// is the stack empty?
    const E& top() const throw(StackEmpty);	// get the top element
    void push(const E& e) throw(StackFull);	// push element onto stack
    void pop() throw(StackEmpty);		// pop the stack
    // ...housekeeping functions omitted
private:                                	// member data
    E* S;					// array of stack elements
    int capacity;				// stack capacity
    int t;					// index of the top of the stack
};


template <typename E> ArrayStack<E>::ArrayStack(int cap)
    : S(new E[cap]), capacity(cap), t(-1) { }	// constructor from capacity

template <typename E> int ArrayStack<E>::size() const
{
    return (t + 1);
}				// number of items in the stack

template <typename E> bool ArrayStack<E>::empty() const
{
    return (t < 0);
}				// is the stack empty?

template <typename E>				// return top of stack
const E& ArrayStack<E>::top() const throw(StackEmpty) {
    if (empty()) throw StackEmpty("Top of empty stack");
    return S[t];
}


template <typename E>				// push element onto the stack
void ArrayStack<E>::push(const E& e) throw(StackFull) {
    if (size() == capacity) throw StackFull("Push to full stack");
    S[++t] = e;
}

template <typename E>				// pop the stack
void ArrayStack<E>::pop() throw(StackEmpty) {
    if (empty()) throw StackEmpty("Pop from empty stack");
    --t;
}


#endif
