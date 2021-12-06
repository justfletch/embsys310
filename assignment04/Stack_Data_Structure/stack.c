#include "stack.h"
#define STACK_SIZE 3

// Backing store
int StackStore[STACK_SIZE];

// Stack pointer for current data
// stackPtr will be set to zero on initialization, and then be set to point at the last value stored in the stack
int* stackPtr;

// LIFO Stack is empty if stackPtr is set to 0 (set by either initialization or pop function)
// LIFO Stack is full if stackPtr == address of last element in the stack

// Initialize internals of the queue

//void stack_init(void);
//int stack_push(int data);
//int stack_pop(int* data);
//int stack_isFull(void);
//int stack_isEmpty(void);

// Initialize the internals of the stack
void stack_init(void)
    {
        for (int i = 0; i< STACK_SIZE; i++){
            StackStore[i] = 0;
        }
        stackPtr = 0;
    }

// Add data to stack
// If stack is full return error
// Otherwise return success
int stack_push(int data)
    {
        // Stack is full if stackPtr == address of last element in the stack.
        if (stackPtr == &StackStore[STACK_SIZE-1])
            {
                return -1;
            }
        // If stackPtr is 0, then stack is empty. Start at first element
        if (stackPtr == 0)
            {
                stackPtr = &StackStore[0];
            }
        // Else increment stackPtr
        else {
            stackPtr++;
        }
        //store data
        *stackPtr = data;
        return 0;
    }


// Get data from stack
// If stack is empty return error
// Otherwise return success
int stack_pop(int* data)
    {
        // If stackPtr is 0, then stack is empty. Start at first element
        if (stackPtr == 0)
            {
                return -1;
            }
        
        //If stack is not empty, set value at data to value at the current stackPtr
        *data = *stackPtr;
        
        // If stackPtr was the first element in the stack, then the stack is now empty
        // so reset stackPtr to 0
        if (stackPtr == &StackStore[0])
            {
                stackPtr = 0;
            }
        // If stackPtr was not first element, decrement stack Ptr
        else 
            {
                stackPtr--;
            }
        return 0; 
    }

int stack_isFull(){
    if (stackPtr == &StackStore[STACK_SIZE-1])
            {
                return 1;
            }
     return 0; 
}
int stack_isEmpty(){
    if (stackPtr == 0)
            {
                return 1;
            }
    return 0;
}
