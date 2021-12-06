/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STACK_H__
#define __STACK_H__

void stack_init(void);
int stack_push(int data);
int stack_pop(int* data);
int stack_isFull(void);
int stack_isEmpty(void);


#endif
