#include<assert.h>
#include"stack.h"

int main()
{
    int result1;
    int result2;
    int result3;
    int result4;
    int testInt;
    
    // *******************************************************************
    // Test1: Retrieve item from an empty stack
    // Check if stack is empty after init
    // Check if stack is full after init
    // *******************************************************************
    // Arrange:
    result1 = 42;
    result2 = 42;
    result3 = 42;
    testInt= 8001;
    stack_init();
    
    // Act:
    result1 = stack_pop(&testInt);
    result2 = stack_isEmpty();
    result3 = stack_isFull();
      
    // Assert:
    assert(-1 == result1);
    assert(1 == result2);
    assert(0 == result3);
    assert(8001 == testInt);
    
    
    // *******************************************************************
    // Test2: Successfully retrieve an item from the stack
    //  Check if stack is full after pushing a single item
    // Check if stack is empty after retrieving the last item
    // *******************************************************************
    // Arrange:
    result1 = 42;
    result2 = 42;
    result3 = 42;
    result4 = 42;
    testInt = 8001;
    stack_init();
    
    // Act:
    result1 = stack_push(50);
    result2 = stack_isFull();
    result3 = stack_pop(&testInt);
    result4 = stack_isEmpty();
    
    // Assert:
    assert(0 == result1);
    assert(0 == result2);
    assert(0 == result3);
    assert(1 == result4);
    assert(50 == testInt);
    
    
    // *******************************************************************
    // Test3: Fill stack, then pop all items.
    // *******************************************************************
    // Arrange:
    testInt = 8001;
    stack_init();
    
    // Act:
    stack_push(65);
    stack_push(750);
    stack_push(2);                                    
    
    // Assert:
    assert(0 == stack_pop(&testInt));
    assert(2 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(750 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(65 == testInt);

    
    // *******************************************************************
    // Test4: Fill stack, then push one more item, should fail
    // *******************************************************************
    // Arrange:
    testInt = 8001;
    stack_init();
    
    // Act:
    stack_push(235);
    stack_push(55555);
    stack_push(64);
    
    // Assert:
    assert(-1 == stack_push(489));

    assert(0 == stack_pop(&testInt));
    assert(64 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(55555 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(235 == testInt);



    // ***********************************************************************
    // Test5: Fill stack, retrieve one item, then add item, then retieve all
    // ***********************************************************************
    // Arrange:
    testInt = 8001;
    stack_init();
    
    // Act:
    stack_push(875);
    stack_push(-465);
    stack_push(9874094);
    
    // Assert:
    assert(0 == stack_pop(&testInt));
    assert(9874094 == testInt);

    assert(0 == stack_push(540547));

    assert(0 == stack_pop(&testInt));
    assert(540547 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(-465 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(875 == testInt);

    // ***********************************************************************
    // Test6: Fill stack and retrieve all items. Do it twice in a row. 
    // Check if stack is empty after init
    // Check if stack is empty while it is partially full. 
    // Check if stack is empty after retrieving all values
    // ***********************************************************************
    // Arrange:
    testInt = 8001;
    stack_init();
    
    // Act:
    stack_push(-875);
    stack_push(465);
    stack_push(-874094);
    
    // Assert:
    assert(0 == stack_pop(&testInt));
    assert(-874094 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(465 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(-875 == testInt);

    assert(0 == stack_push(98740986));
    assert(0 == stack_push(-987098));
    assert(0 == stack_push(-3));
    
    assert(-1 == stack_push(15));

    assert(0 == stack_pop(&testInt));
    assert(-3 == testInt);
   
    assert(0 == stack_pop(&testInt));
    assert(-987098 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(98740986 == testInt);

    return 0;
}
