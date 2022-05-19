//*****************************************************************************
//Nathan Grant and Jiss Xavier
//
//
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup uart_demo
//! @{
//
//*****************************************************************************

// Driverlib includes
#include "rom.h"
#include "rom_map.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "hw_types.h"
#include "hw_ints.h"
#include "uart.h"
#include "interrupt.h"
#include "pin_mux_config.h"
#include "utils.h"
#include "prcm.h"
#include "timer_if.h"
#include "timer.h"
#include "gpio.h"
#include <stdbool.h>
#include <string.h>

// Common interface include
#include "uart_if.h"
#include <stdio.h>
#include "spi.h"
#include "Adafruit_SSD1351.h"
#include "Adafruit_OLED.h"
#include "Adafruit_GFX.h"

//*****************************************************************************
//                          MACROS                                  
//*****************************************************************************
#define APPLICATION_VERSION  "1.4.0"
#define APP_NAME             "UART Echo"
#define CONSOLE              UARTA0_BASE
#define UartGetChar()        MAP_UARTCharGet(UARTA1_BASE)
#define UartPutChar(c)       MAP_UARTCharPut(UARTA1_BASE,c)
#define MAX_STRING_LENGTH    80

#define SPI_IF_BIT_RATE  100000

// Color definitions
#define BLACK           0x0000
#define BLUE            0x001F
#define GREEN           0x07E0
#define CYAN            0x07FF
#define RED             0xF800
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************
volatile int g_iCounter = 0;

int timer_count = 0;
int falling_edge_count = 0;
unsigned int old_time, new_time, time_diff = 0;
unsigned long last_press, curr_press = 0;
unsigned long press_diff = 0;
bool start = false;
int bit_count = 0;
int one_count = 0, zero_count = 0;
unsigned long multiplier = 1;
unsigned long count = 0;
char sequence[32] = "";
char message[21] = "";
int colors[5] = {WHITE, CYAN, RED, YELLOW, GREEN};
int uart_flag = 0;
char character;

#if defined(ccs)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif

//string macros to decode values
const char* ZERO = "00100000110111110000100011110111";
const char* ONE = "00100000110111111000100001110111";
const char* TWO = "00100000110111110100100010110111";
const char* THREE = "00100000110111111100100000110111";
const char* FOUR = "00100000110111110010100011010111";
const char* FIVE = "00100000110111111010100001010111";
const char* SIX = "00100000110111110110100010010111";
const char* SEVEN = "00100000110111111110100000010111";
const char* EIGHT = "00100000110111110001100011100111";
const char* NINE = "00100000110111111001100001100111";
const char* ENTER = "00100000110111111001000001101111";
const char* LAST = "00100000110111110101100010100111";

//*****************************************************************************
//                 GLOBAL VARIABLES -- End
//*****************************************************************************



//*****************************************************************************
//                      LOCAL DEFINITION                                   
//*****************************************************************************

//*****************************************************************************
//
//! Application startup display on UART
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************


//*****************************************************************************
//
//! Board Initialization & Configuration
//!
//! \param  None
//!
//! \return None
//
//*****************************************************************************
static void
BoardInit(void)
{
/* In case of TI-RTOS vector table is initialize by OS itself */
#ifndef USE_TIRTOS
  //
  // Set vector table base
  //
#if defined(ccs)
    MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
#endif
#if defined(ewarm)
    MAP_IntVTableBaseSet((unsigned long)&__vector_table);
#endif
#endif
    //
    // Enable Processor
    //
    MAP_IntMasterEnable();
    MAP_IntEnable(FAULT_SYSTICK);

    PRCMCC3200MCUInit();
}

//*****************************************************************************
//
//!
//! \param  None
//!
//! \return None
//! 
//*****************************************************************************
//GPIO ISHR
void GpioIntHandler(void) {
   

    char val;


    unsigned long ulStatus;
    ulStatus = MAP_GPIOIntStatus(GPIOA1_BASE, true);
    MAP_GPIOIntClear(GPIOA1_BASE, ulStatus);
    if(start) {
        bit_count++;
    }

    //calculate time difference between falling edges
    
    if(falling_edge_count == 0) { //case for first falling edge
        old_time = timer_count;
        new_time = 0;
    } else if(falling_edge_count == 1) { //case for only one falling edge so far
        new_time = timer_count;
        time_diff = new_time - old_time;
    } else { //general cases after the first 2 falling edges
        old_time = new_time;
        new_time = timer_count;
        time_diff = new_time - old_time;
    }
    falling_edge_count++;

    if(start && time_diff>1 && time_diff < 13) { //condition for a '0' value
        val = '0';
    } else if(start && time_diff >= 13 && time_diff < 25) { //condition for a '1' value 
        val = '1';
    } 

    if(strlen(sequence) < 32) { //add up to 32 values
        strncat(sequence, &val, 1);
    }

    

}

//Timer interrupt handler
void TimerIntHandler(void) {
    //increment global count variable
    Timer_IF_InterruptClear(TIMERA0_BASE);
    timer_count++;
}

void UartIntHandler(void) {
    uart_flag = 1;
    MAP_UARTIntClear(UARTA1_BASE, UART_INT_RX);
}

void decode(void) { //decode function
    if(strcmp(ZERO, sequence) == 0){
        printf("you pressed zero\n");
    } else if(strcmp(ONE, sequence) == 0){
        printf("you pressed one\n");
    } else if(strcmp(TWO, sequence) == 0){
        printf("you pressed TWO\n");
    } else if(strcmp(THREE, sequence) == 0){
        printf("you pressed THREE\n");
    } else if(strcmp(FOUR, sequence) == 0){
        printf("you pressed four\n");
    } else if(strcmp(FIVE, sequence) == 0){
        printf("you pressed five\n");
    } else if(strcmp(SIX, sequence) == 0){
        printf("you pressed six\n");
    } else if(strcmp(SEVEN, sequence) == 0){
        printf("you pressed seven\n");
    } else if(strcmp(EIGHT, sequence) == 0){
        printf("you pressed eight\n");
    } else if(strcmp(NINE, sequence) == 0){
        printf("you pressed nine\n");
    } else if(strcmp(ENTER, sequence) == 0){
        printf("you pressed enter\n");
    } else if(strcmp(LAST, sequence) == 0){
        printf("you pressed last\n");
    }
}




void main() {

    unsigned long ulStatus;
    unsigned long uartStatus;
    //
    // Initailizing the board
    //
    BoardInit();
    //
    // Muxing for Enabling UART_TX and UART_RX.
    //
    PinMuxConfig();
    //
    // Initialising the Terminal.
    //
    InitTerm();
    //
    // Clearing the Terminal.

    MAP_UARTConfigSetExpClk(UARTA1_BASE,MAP_PRCMPeripheralClockGet(PRCM_UARTA1), //config uart
    UART_BAUD_RATE, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
    UART_CONFIG_PAR_NONE));


    //
    ClearTerm();

    //initialize SPI:
    // Reset SPI
        //
    MAP_SPIReset(GSPI_BASE);

        //
        // Configure SPI interface
        //
    MAP_SPIConfigSetExpClk(GSPI_BASE,MAP_PRCMPeripheralClockGet(PRCM_GSPI),
    SPI_IF_BIT_RATE,SPI_MODE_MASTER,SPI_SUB_MODE_0,
    (SPI_SW_CTRL_CS |
    SPI_4PIN_MODE |
    SPI_TURBO_OFF |
    SPI_CS_ACTIVEHIGH |
    SPI_WL_8));

        //
        // Enable SPI for communication
        //
    MAP_SPIEnable(GSPI_BASE);



   // MAP_SPIEnable(GSPI_BASE);
    Adafruit_Init();

    fillScreen(0);
    fillCircle(5, 5, 5, WHITE);
    //testtriangles();

   
    //MAP_UARTFlowControlSet(UARTA1_BASE, UART_FLOWCONTROL_NONE);
    MAP_UARTFIFODisable(UARTA1_BASE);

    //Register interrupt handlers
    MAP_GPIOIntRegister(GPIOA1_BASE, GpioIntHandler);
    //MAP_TimerIntRegister(TIMERA0_BASE, TIMER_A,TimerIntHandler);
    MAP_UARTIntRegister(UARTA1_BASE, UartIntHandler);

    //Declare as falling edge interrupt
    MAP_GPIOIntTypeSet(GPIOA1_BASE, 0x10, GPIO_FALLING_EDGE);
    //TimerControlEvent(TIMERA0_BASE, TIMER_A, TIMER_EVENT_NEG_EDGE);

    ulStatus = MAP_GPIOIntStatus(GPIOA1_BASE, false);
    MAP_GPIOIntClear(GPIOA1_BASE, ulStatus);

    //uartStatus = MAP_UARTIntStatus(UARTA1_BASE, false);
    //MAP_UARTIntClear(UARTA1_BASE, uartStatus);

    MAP_GPIOIntEnable(GPIOA1_BASE, 0x10);
    MAP_UARTIntEnable(UARTA1_BASE, UART_INT_RX);

    //Initialize Timer interrupt
    Timer_IF_Init(PRCM_TIMERA0, TIMERA0_BASE, TIMER_CFG_PERIODIC, TIMER_A, 0);

    //Setup Timer
    Timer_IF_IntSetup(TIMERA0_BASE, TIMER_A, TimerIntHandler);

    //start timer
    MAP_TimerLoadSet(TIMERA0_BASE, TIMER_A, 8000);
    MAP_TimerEnable(TIMERA0_BASE, TIMER_A);

    //x coordinate of text on OLED
    int x = 0;
    int x2 = 0;
    int color_count = 0;

    //last character that was typed
    int last_button = 15; //initialize to a value that we dont use
    char last_letter;
    char temp;

    //long int value = 0;
    while(1) {

        UARTCharPut(UARTA1_BASE, 'H');

        if(time_diff >= 130 && time_diff <= 140) {
            start = true;
            bit_count = 0;
        }

        if(uart_flag) {
            printf("Got a message");
            character = UARTCharGet(UARTA1_BASE);
            drawChar(0 + (x2*6), 90, character, colors[color_count % 5], BLACK, 1);
            x2++;
            uart_flag = 0;
        }

        if(bit_count == 32) { //we've gotten a value

            start = false;
            bit_count = 0;
            printf("sequence: %s\n", sequence);
            

            last_press = curr_press;
            curr_press = timer_count;
            press_diff = curr_press - last_press;

            //check which button was pressed

            if(strcmp(ZERO, sequence) == 0){
                drawChar(0 + (x*6), 30, ' ', WHITE, BLACK, 1);
                x++;
                temp = ' ';
                strncat(message, &temp, 1);
                last_button = 0;
                printf("you pressed zero\n");
            } else if(strcmp(ONE, sequence) == 0){
                color_count++;
                fillCircle(5, 5, 5, colors[color_count % 5]);
                last_button = 1;
                printf("you pressed one\n");
            } else if(strcmp(TWO, sequence) == 0){
                if(last_button == 2 && press_diff < 12500) { //also check for time delay here
                    if(last_letter == 'A') {
                        x--;
                        drawChar(0 + (x*6), 30, 'B', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'B';
                        message[strlen(message) - 1] = '\0'; //delete last char
                        strncat(message, &last_letter, 1); //append to string
                    } else if(last_letter == 'B') {
                        x--;
                        drawChar(0 + (x*6), 30, 'C', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'C';
                        message[strlen(message) - 1] = '\0'; //delete last char
                        strncat(message, &last_letter, 1); //append to string
                    } else if(last_letter == 'C') {
                        drawChar(0 + (x*6), 30, 'A', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'A';
                        strncat(message, &last_letter, 1); //append to string
                    }
                } else {
                        drawChar(0 + (x*6), 30, 'A', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'A';
                        strncat(message, &last_letter, 1); //append to string
                }
                last_button = 2;
                printf("you pressed TWO\n");
            } else if(strcmp(THREE, sequence) == 0){
                  if(last_button == 3 && press_diff < 12500) { //also check for time delay here
                    if(last_letter == 'D') {
                        x--;
                        drawChar(0 + (x*6), 30, 'E', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'E';
                        message[strlen(message) - 1] = '\0'; //delete last char
                        strncat(message, &last_letter, 1); //append to string
                    } else if(last_letter == 'E') {
                        x--;
                        drawChar(0 + (x*6), 30, 'F', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'F';
                        message[strlen(message) - 1] = '\0'; //delete last char
                        strncat(message, &last_letter, 1); //append to string
                    } else if(last_letter == 'F') {
                        drawChar(0 + (x*6), 30, 'D', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'D';
                        strncat(message, &last_letter, 1); //append to string
                    }
                } else {
                        drawChar(0 + (x*6), 30, 'D', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'D';
                        strncat(message, &last_letter, 1); //append to string
                }
                last_button = 3;
                printf("you pressed THREE\n");
            } else if(strcmp(FOUR, sequence) == 0){
                  if(last_button == 4 && press_diff < 12500) { //also check for time delay here
                    if(last_letter == 'G') {
                        x--;
                        drawChar(0 + (x*6), 30, 'H', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'H';
                        message[strlen(message) - 1] = '\0'; //delete last char
                        strncat(message, &last_letter, 1); //append to string
                    } else if(last_letter == 'H') {
                        x--;
                        drawChar(0 + (x*6), 30, 'I', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'I';
                        message[strlen(message) - 1] = '\0'; //delete last char
                        strncat(message, &last_letter, 1); //append to string
                    } else if(last_letter == 'I') {
                        drawChar(0 + (x*6), 30, 'G', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'G';
                        strncat(message, &last_letter, 1); //append to string
                    }
                } else {
                        drawChar(0 + (x*6), 30, 'G', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'G';
                        strncat(message, &last_letter, 1); //append to string
                }
                last_button = 4;
                printf("you pressed four\n");
            } else if(strcmp(FIVE, sequence) == 0){
                  if(last_button == 5 && press_diff < 12500) { //also check for time delay here
                    if(last_letter == 'J') {
                        x--;
                        drawChar(0 + (x*6), 30, 'K', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'K';
                        message[strlen(message) - 1] = '\0'; //delete last char
                        strncat(message, &last_letter, 1); //append to string
                    } else if(last_letter == 'K') {
                        x--;
                        drawChar(0 + (x*6), 30, 'L', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'L';
                        message[strlen(message) - 1] = '\0'; //delete last char
                        strncat(message, &last_letter, 1); //append to string
                    } else if(last_letter == 'L') {
                        drawChar(0 + (x*6), 30, 'J', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'J';
                        strncat(message, &last_letter, 1); //append to string
                    }
                } else {
                        drawChar(0 + (x*6), 30, 'J', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'J';
                        strncat(message, &last_letter, 1); //append to string
                }
                last_button = 5;
                printf("you pressed five\n");
            } else if(strcmp(SIX, sequence) == 0){
                  if(last_button == 6 && press_diff < 12500) { //also check for time delay here
                    if(last_letter == 'M') {
                        x--;
                        drawChar(0 + (x*6), 30, 'N', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'N';
                        message[strlen(message) - 1] = '\0'; //delete last char
                        strncat(message, &last_letter, 1); //append to string
                    } else if(last_letter == 'N') {
                        x--;
                        drawChar(0 + (x*6), 30, 'O', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'O';
                        message[strlen(message) - 1] = '\0'; //delete last char
                        strncat(message, &last_letter, 1); //append to string
                    } else if(last_letter == 'O') {
                        drawChar(0 + (x*6), 30, 'M', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'M';
                        strncat(message, &last_letter, 1); //append to string
                    }
                } else {
                        drawChar(0 + (x*6), 30, 'M', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'M';
                        strncat(message, &last_letter, 1); //append to string
                }
                last_button = 6;
                printf("you pressed six\n");
            } else if(strcmp(SEVEN, sequence) == 0){
                  if(last_button == 7 && press_diff < 12500) { //also check for time delay here
                    if(last_letter == 'P') {
                        x--;
                        drawChar(0 + (x*6), 30, 'Q', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'Q';
                        message[strlen(message) - 1] = '\0'; //delete last char
                        strncat(message, &last_letter, 1); //append to string
                    } else if(last_letter == 'Q') {
                        x--;
                        drawChar(0 + (x*6), 30, 'R', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'R';
                        message[strlen(message) - 1] = '\0'; //delete last char
                        strncat(message, &last_letter, 1); //append to string
                    }  else if(last_letter == 'R') {
                        x--;
                        drawChar(0 + (x*6), 30, 'S', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'S';
                        message[strlen(message) - 1] = '\0'; //delete last char
                        strncat(message, &last_letter, 1); //append to string
                    } else if(last_letter == 'S') {
                        drawChar(0 + (x*6), 30, 'P', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'P';
                        strncat(message, &last_letter, 1); //append to string
                    }
                } else {
                        drawChar(0 + (x*6), 30, 'P', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'P';
                        strncat(message, &last_letter, 1); //append to string
                }
                last_button = 7;
                printf("you pressed seven\n");
            } else if(strcmp(EIGHT, sequence) == 0){
                if(last_button == 8 && press_diff < 12500) { //also check for time delay here
                    if(last_letter == 'T') {
                        x--;
                        drawChar(0 + (x*6), 30, 'U', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'U';
                        message[strlen(message) - 1] = '\0'; //delete last char
                        strncat(message, &last_letter, 1); //append to string
                    } else if(last_letter == 'U') {
                        x--;
                        drawChar(0 + (x*6), 30, 'V', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'V';
                        message[strlen(message) - 1] = '\0'; //delete last char
                        strncat(message, &last_letter, 1); //append to string
                    } else if(last_letter == 'V') {
                        drawChar(0 + (x*6), 30, 'T', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'T';
                        strncat(message, &last_letter, 1); //append to string
                    }
                } else {
                        drawChar(0 + (x*6), 30, 'T', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'T';
                        strncat(message, &last_letter, 1); //append to string
                }
                last_button = 8;
                printf("you pressed eight\n");
            } else if(strcmp(NINE, sequence) == 0){
                if(last_button == 9 && press_diff < 12500) { //also check for time delay here
                    if(last_letter == 'W') {
                        x--;
                        drawChar(0 + (x*6), 30, 'X', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'X';
                        message[strlen(message) - 1] = '\0'; //delete last char
                        strncat(message, &last_letter, 1); //append to string
                    } else if(last_letter == 'X') {
                        x--;
                        drawChar(0 + (x*6), 30, 'Y', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'Y';
                        message[strlen(message) - 1] = '\0'; //delete last char
                        strncat(message, &last_letter, 1); //append to string
                    }  else if(last_letter == 'Y') {
                        x--;
                        drawChar(0 + (x*6), 30, 'Z', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'Z';
                        message[strlen(message) - 1] = '\0'; //delete last char
                        strncat(message, &last_letter, 1); //append to string
                    } else if(last_letter == 'Z') {
                        drawChar(0 + (x*6), 30, 'W', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'W';
                        strncat(message, &last_letter, 1); //append to string
                    }
                } else {
                        drawChar(0 + (x*6), 30, 'W', colors[color_count % 5], BLACK, 1);
                        x++;
                        last_letter = 'W';
                        strncat(message, &last_letter, 1); //append to string
                }
                last_button = 9;
                printf("you pressed nine\n");
            } else if(strcmp(ENTER, sequence) == 0){
                last_button = 10;
                int k;
                for(k = 0; k < strlen(message); k++) {
                    UartPutChar(message[k]);
                }
                printf("message is: %s\n", message);
                memset(message, 0, 21); //clear the string
                printf("you pressed enter\n");
            } else if(strcmp(LAST, sequence) == 0){
                x--;
                drawChar(0 + (x*6), 30, ' ', WHITE, BLACK, 1);
                last_button = 11;
                message[strlen(message) - 1] = '\0'; //delete last char
                printf("you pressed last\n");
            }



            memset(sequence, 0, 32); //clear the string
        }
//
    }

}





//    DisplayBanner(APP_NAME);
//    Message("\t\t****************************************************\n\r");
//   Message("\t\t\t        CC3200 UART Echo Usage        \n\r");
//    Message("\t\t Type in a string of alphanumeric characters and  \n\r");
//    Message("\t\t pressenter, the string will be echoed. \n\r") ;
//    Message("\t\t Note: if string length reaches 80 character it will \n\r");
//    Message("\t\t echo the string without waiting for enter command \n\r");
//    Message("\t\t ****************************************************\n\r");
//    Message("\n\n\n\r");
//    Message("cmd#");
//    while(1)
//    {
//        //
//        // Fetching the input from the terminal.
//        //
//        cCharacter = UartGetChar();
//        g_iCounter++;
//        if(cCharacter == '\r' || cCharacter == '\n' ||
//           (iStringLength >= MAX_STRING_LENGTH -1))
//        {
//            if(iStringLength >= MAX_STRING_LENGTH - 1)
//            {
//                UartPutChar(cCharacter);
//                cString[iStringLength] = cCharacter;
//                iStringLength++;
//            }
//            cString[iStringLength] = '\0';
//            iStringLength = 0;
//            //
//            // Echoes the input string
//            //
//            Report("\n\rcmd#%s\n\rcmd#", cString);
//        }
//        else
//        {
//            UartPutChar(cCharacter);
//            cString[iStringLength] = cCharacter;
//            iStringLength++;
//        }
//    }


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

    

