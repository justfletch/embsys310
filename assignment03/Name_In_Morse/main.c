//This program repeatedly displays "justin " in International Morse Code
//using LED1 on the B-L475E-IOT01A1 evaluation board


//AHB2 clock base, enable register
#define RCC_BASE 0x40021000
#define RCC_AHB2ENR (*((unsigned int*)(RCC_BASE + 0x4C))) // Offset of 0x4C from RCC_BASE

//GPIOA address base, mode, output data registers
#define GPIOA_BASE 0x48000000
#define GPIOA_MODER (*((unsigned int*)(GPIOA_BASE + 0x0))) // Offset of 0x0 from GPIO_BASE
#define GPIOA_ODR (*((unsigned int*)(GPIOA_BASE + 0x14))) // Offset of 0x14 from GPIO_BASE

//bit to toggle for GPIOX5 output (using PA5 for LED1)
#define ODR5 (1<<5)

//number of counts per time unit
#define TIME_UNIT_LENGTH 250000

//Morse Code timings needed, measured in time units
#define DOT 1
#define DASH 3
#define SAME_LETTER_SPACE 1
#define NEXT_LETTER_SPACE 3
#define NEXT_WORD_SPACE 7

//delay for given counts
void delay(int delayCounts) {
    int counter = 0;
    //delay until counter is equal to delayCounts
    while (counter < delayCounts) {
        counter++;
    }
}

//single Blink of LED, with delay by given time units
void TimedLEDBlink(int BlinkTimeInUnits) {
    //turn on LED via PA5
    GPIOA_ODR |= ODR5;
    //wait the given amount of time
    delay (BlinkTimeInUnits*TIME_UNIT_LENGTH);
    //turn off LED via PA5
    GPIOA_ODR &= ~ODR5;
}

//display the full character in Morse Code (letter or number)
void MorseDisplayCharacter(int const character[], int characterArraySize){
    for(int i = 0; i < characterArraySize; i++) {
        //add spacing before dash/dot if continuing to display the same character
        if(i > 0) { 
            delay(SAME_LETTER_SPACE*TIME_UNIT_LENGTH);
        }
        //blink LED with duration of dash/dot units, provided by character array value
        TimedLEDBlink(character[i]);
    }
}

//delay for appropriate amount of time between letters
void MorseDisplayLetterSpace() {
    delay(NEXT_LETTER_SPACE*TIME_UNIT_LENGTH);
}

//delay for appropriate amount of time between words
void MorseDisplayWordSpace() {
    delay(NEXT_WORD_SPACE*TIME_UNIT_LENGTH);
}

//constant arrays for morse code letters needed
const int j[4] = {DOT, DASH, DASH, DASH};
const int u[3] = {DOT, DOT, DASH};
const int s[3] = {DOT, DOT, DOT};
const int t[1] = {DASH};
const int i[2] = {DOT, DOT};
const int n[2] = {DASH, DOT};

int main()
    {
        // Enable the clock to Port A (GPIOA)
        // Port A is bit 0 of RCC_AHB2ENR.
        // 0b1 = 0x01
        RCC_AHB2ENR = RCC_AHB2ENR | 0x1; // Existing value bit-wise OR'd with 0b00000...00001
        
        // Setup the GPIO port to become an output. PA5
        // PA5 mode is controlled by bit 10 & bit 11 of it's GPIO mode register
        GPIOA_MODER = GPIOA_MODER & 0xFFFFF7FF; // Existing value bit-wise AND'd with 0xFFFFF7FF to enforce '01' in bit 10 & bit 11. 0xD results in "0111"
        GPIOA_ODR &= ~ODR5; //ensure LED is in off state
        
        
        while(1){
            // Display justin in morse code
            MorseDisplayCharacter(j, (sizeof(j)/sizeof(j[0])));
            MorseDisplayLetterSpace();
            MorseDisplayCharacter(u, (sizeof(u)/sizeof(u[0])));
            MorseDisplayLetterSpace();
            MorseDisplayCharacter(s, (sizeof(s)/sizeof(s[0])));
            MorseDisplayLetterSpace();
            MorseDisplayCharacter(t, (sizeof(t)/sizeof(t[0])));
            MorseDisplayLetterSpace();
            MorseDisplayCharacter(i, (sizeof(i)/sizeof(i[0])));
            MorseDisplayLetterSpace();
            MorseDisplayCharacter(n, (sizeof(n)/sizeof(n[0])));
            
            //Add word space after blinding user #BlindedByTheLight
            MorseDisplayWordSpace();
        }
        
        return 0;
    }
