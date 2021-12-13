
void swap_pointer(int** aPtrPtr, int** bPtrPtr){
  int* tempPtr;
  //set tempPtr to value at address of aPtrPtr [aPtr]
  tempPtr = *aPtrPtr; 
  //set value at address of aPtrPtr [aPtr] to value at address of bPtrPtr [bPtr]
  *aPtrPtr = *bPtrPtr; 
  //set value at address of bPtrPtr [bPtr] to tempPtr
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
