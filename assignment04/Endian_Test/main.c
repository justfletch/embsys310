//return 1 if big endian, 0 if little endian
int CheckEndian(){
    //store an int to fill a 32 bit register with known values
    // 0x41 = 'A', highest byte
    // 0x5A = 'Z', lowest byte
    int testInt = 0x4100005A;
    
    //cast the address of testInt to a character pointer
    char* testChars = (char*)(&testInt);     
    char firstByte = testChars[0];
    
    //If the highest byte is the first byte retrieved, then the system is big endian
    if (firstByte == 'A'){
        return 1;
    }
    
    //If the lowest byte is the first byte reteived, then the system is little endian
    if (firstByte == 'Z'){
        return 0;
    }
    
    // If somehow neither, then fail
    return -1;
}


int main()
    {
        int result = CheckEndian();  //1 = big, 0 = little  
        
        return 0;
    }
