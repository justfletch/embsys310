int counter = 0;

#define RCC_BASE 0x40021000
#define RCC_AHB2ENR (*((unsigned int*)(RCC_BASE + 0x4C))) // Offset of 0x4C from RCC_BASE

#define GPIOA_BASE 0x48000000
#define GPIOB_BASE 0x48000400
#define GPIOA_MODER (*((unsigned int*)(GPIOA_BASE + 0x0))) // Offset of 0x0 from GPIO_BASE
#define GPIOB_MODER (*((unsigned int*)(GPIOB_BASE + 0x0))) // Offset of 0x0 from GPIO_BASE
#define GPIOA_ODR (*((unsigned int*)(GPIOA_BASE + 0x14))) // Offset of 0x14 from GPIO_BASE
#define GPIOB_ODR (*((unsigned int*)(GPIOB_BASE + 0x14))) // Offset of 0x14 from GPIO_BASE


#define ODR14 (1<<14)
#define ODR5 (1<<5)

int main()
    {
        // Enable the clock to Port A (GPIOA) & Port B (GPIOB)
        // Port A is bit 0 of RCC_AHB2ENR. Port B is bit 1 of RCC_AHB2ENR.
        // Setting both to 1 will enable the clock for the ports.
        // 0b11 = 0x3
        RCC_AHB2ENR = RCC_AHB2ENR | 0x3; // Existing value bit-wise OR'd with 0b00000...00011
        
        // Setup the GPIO ports to become an output. PA5 & PB14.
        // PA5 mode is controlled by bit 10 & bit 11 of it's GPIO mode register
        // PB14 mode is controlled by bit 28 & bit 29 of it's GPIO mode register
        GPIOA_MODER = GPIOA_MODER & 0xFFFFF7FF; // Existing value bit-wise AND'd with 0xFFFFF7FF to enforce '01' in bit 10 & bit 11. 0xD results in "0111"
        GPIOB_MODER = GPIOB_MODER & 0xDFFFFFFF; // Existing value bit-wise AND'd with 0xDFFFFFFF to enforce '01' in bit 28 & bit 29. 0xD results in "1101"
        
        
        while(1){
            // Toggle PA5 & Turn on PB14
            GPIOA_ODR ^= ODR5; //LED Toggle. bit-wise XOR on bit 
            GPIOB_ODR |= ODR14; //LED ON. bit-wise OR on bit 
            
            while (counter < 75000) {
                counter++;
            }
            counter = 0;
        }
        
        return 0;
    }

//0x0800.0000 --> 0x08FF.FFFF
//1MB ROM space
