//*****************************************************************************
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
// 
// 
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//    Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the 
//    documentation and/or other materials provided with the   
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

//*****************************************************************************
//
// Application Name     - SPI Demo
// Application Overview - The demo application focuses on showing the required 
//                        initialization sequence to enable the CC3200 SPI 
//                        module in full duplex 4-wire master and slave mode(s).
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup SPI_Demo
//! @{
//
//*****************************************************************************

// Standard includes
#include <string.h>
#include <stdio.h>

// Driverlib includes
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "hw_ints.h"
#include "spi.h"
#include "rom.h"
#include "rom_map.h"
#include "utils.h"
#include "prcm.h"
#include "uart.h"
#include "interrupt.h"
//#include "test.h"

// Common interface includes
#include "uart_if.h"
#include "pin_mux_config.h"

#include "Adafruit_SSD1351.h"
#include "Adafruit_OLED.h"
#include "glcdfont.h"
//extern void Adafruit_Init(void);
void testfastlines(unsigned int color1, unsigned int color2);

// Draw a character
void drawChar(int x, int y, unsigned char c,
                unsigned int color, unsigned int bg, unsigned char size);


#define APPLICATION_VERSION     "1.4.0"
//*****************************************************************************
//
// Application Master/Slave mode selector macro
//
// MASTER_MODE = 1 : Application in master mode
// MASTER_MODE = 0 : Application in slave mode
//
//*****************************************************************************
#define MASTER_MODE      1

#define SPI_IF_BIT_RATE  100000
#define TR_BUFF_SIZE     100

// Color definitions
#define BLACK           0x0000
#define BLUE            0x001F
#define GREEN           0x07E0
#define CYAN            0x07FF
#define RED             0xF800
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

#define MASTER_MSG       "This is CC3200 SPI Master Application\n\r"
#define SLAVE_MSG        "This is CC3200 SPI Slave Application\n\r"

//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************
static unsigned char g_ucTxBuff[TR_BUFF_SIZE];
static unsigned char g_ucRxBuff[TR_BUFF_SIZE];
static unsigned char ucTxBuffNdx;
static unsigned char ucRxBuffNdx;

char string[12] = "Hello World";
int i = 0;
int y = 0;

#if defined(ccs)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif
//*****************************************************************************
//                 GLOBAL VARIABLES -- End
//*****************************************************************************


//*****************************************************************************
//
//! SPI Slave Interrupt handler
//!
//! This function is invoked when SPI slave has its receive register full or
//! transmit register empty.
//!
//! \return None.
//
//*****************************************************************************
static void SlaveIntHandler()
{
    unsigned long ulRecvData;
    unsigned long ulStatus;

    ulStatus = MAP_SPIIntStatus(GSPI_BASE,true);

    MAP_SPIIntClear(GSPI_BASE,SPI_INT_RX_FULL|SPI_INT_TX_EMPTY);

    if(ulStatus & SPI_INT_TX_EMPTY)
    {
        MAP_SPIDataPut(GSPI_BASE,g_ucTxBuff[ucTxBuffNdx%TR_BUFF_SIZE]);
        ucTxBuffNdx++;
    }

    if(ulStatus & SPI_INT_RX_FULL)
    {
        MAP_SPIDataGetNonBlocking(GSPI_BASE,&ulRecvData);
        g_ucTxBuff[ucRxBuffNdx%TR_BUFF_SIZE] = ulRecvData;
        Report("%c",ulRecvData);
        ucRxBuffNdx++;
    }
}

//*****************************************************************************
//
//! SPI Master mode main loop
//!
//! This function configures SPI modelue as master and enables the channel for
//! communication
//!
//! \return None.
//
//*****************************************************************************
void MasterMain()
{
//    printf("hey\n");

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

    //testfastlines(YELLOW, BLUE);


}
//*****************************************************************************
//
//! SPI Slave mode main loop
//!
//! This function configures SPI modelue as slave and enables the channel for
//! communication
//!
//! \return None.
//
//*****************************************************************************
void SlaveMain()
{
    //
    // Initialize the message
    //
    memcpy(g_ucTxBuff,SLAVE_MSG,sizeof(SLAVE_MSG));

    //
    // Set Tx buffer index
    //
    ucTxBuffNdx = 0;
    ucRxBuffNdx = 0;

    //
    // Reset SPI
    //
    MAP_SPIReset(GSPI_BASE);

    //
    // Configure SPI interface
    //
    MAP_SPIConfigSetExpClk(GSPI_BASE,MAP_PRCMPeripheralClockGet(PRCM_GSPI),
                     SPI_IF_BIT_RATE,SPI_MODE_SLAVE,SPI_SUB_MODE_0,
                     (SPI_HW_CTRL_CS |
                     SPI_4PIN_MODE |
                     SPI_TURBO_OFF |
                     SPI_CS_ACTIVEHIGH |
                     SPI_WL_8));

    //
    // Register Interrupt Handler
    //
    MAP_SPIIntRegister(GSPI_BASE,SlaveIntHandler);

    //
    // Enable Interrupts
    //
    MAP_SPIIntEnable(GSPI_BASE,SPI_INT_RX_FULL|SPI_INT_TX_EMPTY);

    //
    // Enable SPI for communication
    //
    MAP_SPIEnable(GSPI_BASE);

    //
    // Print mode on uart
    //
    Message("Enabled SPI Interface in Slave Mode\n\rReceived : ");
}

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
//! Main function for spi demo application
//!
//! \param none
//!
//! \return None.
//
//*****************************************************************************
void main()
{
    //
    // Initialize Board configurations
    //
    BoardInit();

    //
    // Muxing UART and SPI lines.
    //
    PinMuxConfig();

    //
    // Enable the SPI module clock
    //
    MAP_PRCMPeripheralClkEnable(PRCM_GSPI,PRCM_RUN_MODE_CLK);

    //
    // Initialising the Terminal.
    //
    //InitTerm();

    //
    // Clearing the Terminal.
    //
    //ClearTerm();

    //
    // Display the Banner
    //
    //Message("\n\n\n\r");
    //Message("\t\t   ********************************************\n\r");
    //Message("\t\t        CC3200 SPI Demo Application  \n\r");
    //Message("\t\t   ********************************************\n\r");
    //Message("\n\n\n\r");

    //
    // Reset the peripheral
    //
    MAP_PRCMPeripheralReset(PRCM_GSPI);

#if MASTER_MODE

    MasterMain();

#else

    SlaveMain();

#endif

    //printf("hey\n");
    //Adafruit_Init();
    //testfastlines(YELLOW, BLUE);

    while(1)
    {
        fillScreen(BLACK);


        //print hello world
        for(i = 0; i < 12; i++) {
            drawChar(0 + (i*5), 30, string[i], WHITE, BLACK, 1);
        }

        fillScreen(BLACK);

        //print all characters from glcfont.h
        for(i = 4; i < 1016; i++) {
            drawChar(30, 30, font[i], BLACK, WHITE, 1);
        }

        fillScreen(BLACK);

        //8 bands of different colors horizontally across the screen
        drawFastHLine(0, 1, 128, RED);
        drawFastHLine(0, 11, 128, YELLOW);
        drawFastHLine(0, 21, 128, CYAN);
        drawFastHLine(0, 31, 128, BLUE);
        drawFastHLine(0, 41, 128, GREEN);
        drawFastHLine(0, 51, 128, MAGENTA);
        drawFastHLine(0, 61, 128, WHITE);
        drawFastHLine(0, 71, 128, 0xFF80); //ORANGE Line

        fillScreen(BLACK);

        //8 bands of different colors vertically across the screen
        drawFastVLine(1, 0, 128, RED);
        drawFastVLine(11, 0, 128, YELLOW);
        drawFastVLine(21, 0, 128, CYAN);
        drawFastVLine(31, 0, 128, BLUE);
        drawFastVLine(41, 0, 128, GREEN);
        drawFastVLine(51, 0, 128, MAGENTA);
        drawFastVLine(61, 0, 128, WHITE);
        drawFastVLine(71, 0, 128, 0xFF80);

        fillScreen(BLACK);

    //Call Testlines() to display diagonal lines
    testlines(CYAN);

    fillScreen(BLACK);

    //Draw a pattern of rectangles
    testdrawrects(CYAN);

    fillScreen(BLACK);

    //Call TestFillRects()
    testfillrects(RED, CYAN);

    fillScreen(BLACK);

    //Call testFillCirlces
    testfillcircles(64, RED);

    fillScreen(BLACK);

    //Call testDrawCircles
    testdrawcircles(30, CYAN);

    fillScreen(BLACK);

    //Call Test Round Rects
    testroundrects(CYAN);

    fillScreen(BLACK);

    //Call Test triangles
    testtriangles(RED);

    }


}

