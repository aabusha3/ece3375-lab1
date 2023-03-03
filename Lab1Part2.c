// Allocate memory spaces for LED, 7-segment display and switches
#define LED_BASE			0xFF200000
#define HEX3_HEX0_BASE		0xFF200020
#define SW_BASE				0xFF200040

// Declare variables to store addresses using *
// Volatile is needed for compilation
volatile int * SWITCHES = (int *) SW_BASE;
volatile int * HEX = (int *) HEX3_HEX0_BASE;

// Delay time as per the lab manual
volatile int DELAY_LENGTH = 700000;
volatile int count;
volatile int switchValue;

// Display hexadecimal
void DisplayHex(int input)
{
    // Declare an unsigned 8-bit type array with 16 elements to represent the digits
    const unsigned char hexTable[16] = {
        0x3F, 0x06, 0x5B, 0x4F, 
        0x66, 0x6D, 0x7D, 0x07, 
        0x7F, 0x6F, 0x77, 0x7C, 
        0x39, 0x5E, 0x79, 0x71
    };
    // Assign relevant hex value if input is within the hexadecimal range
    if(input < 16){
        *(HEX) = hexTable[input];
    }
    // Else give 0x00
    else{
        *(HEX) = 0x00;
    }
}


// Return switch value of the first 4 switches (0b01111 = 0x0F)
int ReadSwitches(void)
{
    switchValue = *(SWITCHES) &= 0x3FF;
    return switchValue;
}

	
int main(void) {
    while(1){
        // Store switch value then take input to display hex
        int input = ReadSwitches();

        // Map read switch value to correct digit
        DisplayHex(input);

        // Start delay loop similar to part 1
        for(count = DELAY_LENGTH; count != 0; --count);
    }
}
