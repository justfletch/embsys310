
void swap_pointer(int** aPtrPtr, int** bPtrPtr){
  int* tempPtr;
  //set tempPtr to value at address of aPtr [*aPtrPtr]
  tempPtr = *aPtrPtr; 
  //set value at address of aPtr [*aPtrPtr] to value at address of bPtr [*bPtrPtr]
  *aPtrPtr = *bPtrPtr; 
  //set value at address of bPtr [*bPtrPtr] to tempPtr
  *bPtrPtr = tempPtr;
}


int main()
{
  
   int* aPtr;
    int* bPtr;
    
    int a = 100;
    int b = 5;
    
    aPtr = &a;
    bPtr = &b;
    
    swap_pointer(&aPtr, &bPtr);
   
    
  return 0;
}
