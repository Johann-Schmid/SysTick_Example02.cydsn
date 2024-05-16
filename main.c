#include <project.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_PRIORITY (3u)
#define LIGHT_OFF (0u)
#define LIGHT_ON (1u)
#define EOM_CR 0x0D // message separator char (\r)
#define EOM_LF 0x0A // message separator char (\n)

/* Global Variables */
uint32 msCount;
volatile uint32 intSW[6] = {0};
volatile bool boSW[6] = {false};
volatile bool boUART[6] = {false};

/* Function Prototypes */
void SysTickISRCallback(void);
void HandleSwitch(uint8 switchIndex, char* buffer, char* time);

CY_ISR(GPIO0IsrHandler) {     
    /* Clear pending Interrupt */
    isr_GPIO_0_ClearPending();
    
    /* Clear pin Interrupt */
    SW0_ClearInterrupt();

    intSW[0] = msCount;
    boSW[0] = true; 
}
CY_ISR(GPIO1IsrHandler) {     
    /* Clear pending Interrupt */
    isr_GPIO_1_ClearPending();
    
    /* Clear pin Interrupt */
    SW1_ClearInterrupt();

    intSW[1] = msCount;
    boSW[1] = true;  
}
CY_ISR(GPIO2IsrHandler) {     
    /* Clear pending Interrupt */
    isr_GPIO_2_ClearPending();
    
    /* Clear pin Interrupt */
    SW2_ClearInterrupt();

    intSW[2] = msCount;
    boSW[2] = true;  
}
CY_ISR(GPIO3IsrHandler) {     
    /* Clear pending Interrupt */
    isr_GPIO_3_ClearPending();
    
    /* Clear pin Interrupt */
    SW3_ClearInterrupt();

    intSW[3] = msCount;
    boSW[3] = true;   
}
CY_ISR(GPIO4IsrHandler) {     
    /* Clear pending Interrupt */
    isr_GPIO_4_ClearPending();
    
    /* Clear pin Interrupt */
    SW4_ClearInterrupt();

    intSW[4] = msCount;
    boSW[4] = true;   
}
CY_ISR(GPIO5IsrHandler) {     /* Clear pending Interrupt */
    isr_GPIO_5_ClearPending();
    
    /* Clear pin Interrupt */
    SW5_ClearInterrupt();

    intSW[5] = msCount;
    boSW[5] = true;   
}

int main()
{
    char time[16u];
    char buffer[128u];
    uint32 byte, i;
    bool boCRLF;
    bool boStart;
    
    const int RxBufferSize = 128;
    char RxBuffer[RxBufferSize];
    char *RxWriteIndex = RxBuffer;
    
    boCRLF = false;
    boStart = false;
    
    msCount = 0u;

    /* Initialize interrupts and set priorities */
    isr_GPIO_0_StartEx(GPIO0IsrHandler);
    isr_GPIO_1_StartEx(GPIO1IsrHandler);
    isr_GPIO_2_StartEx(GPIO2IsrHandler);
    isr_GPIO_3_StartEx(GPIO3IsrHandler);
    isr_GPIO_4_StartEx(GPIO4IsrHandler);
    isr_GPIO_5_StartEx(GPIO5IsrHandler);

    isr_GPIO_0_SetPriority(DEFAULT_PRIORITY);
    isr_GPIO_1_SetPriority(DEFAULT_PRIORITY);
    isr_GPIO_2_SetPriority(DEFAULT_PRIORITY);
    isr_GPIO_3_SetPriority(DEFAULT_PRIORITY);
    isr_GPIO_4_SetPriority(DEFAULT_PRIORITY);
    isr_GPIO_5_SetPriority(DEFAULT_PRIORITY);

    CyGlobalIntEnable;
    
    LED_Write(LIGHT_OFF);
    UART_Start();

    CySysTickInit();
    
    for (i = 0u; i < CY_SYS_SYST_NUM_OF_CALLBACKS; ++i)
    {
        if (CySysTickGetCallback(i) == NULL)
        {
            CySysTickSetCallback(i, SysTickISRCallback);
            break;
        }
    }

    UART_UartPutString("BeeMill 2V0\r\n");

    for (;;)
    {
        while ((byte = UART_UartGetChar()) != 0)
        {
            if ((byte == EOM_CR) || (byte == EOM_LF))
            {
                boCRLF = true;
                byte = '\0';
            }
            *RxWriteIndex = byte;
            RxWriteIndex = RxWriteIndex + 1;
            *RxWriteIndex = '\0';
            if (RxWriteIndex >= RxBuffer + RxBufferSize) RxWriteIndex = RxBuffer;
        }

        if (boCRLF)
        {
            boCRLF = false;
            RxWriteIndex = RxBuffer;
            sprintf(buffer, "%s", RxBuffer);

            if (strcmp("start", buffer) == 0)
            {
                boStart = true;
                msCount = 0;
                CySysTickEnable();
                isr_GPIO_0_Enable();
                isr_GPIO_1_Enable();
                isr_GPIO_2_Enable();
                isr_GPIO_3_Enable();
                isr_GPIO_4_Enable();
                isr_GPIO_5_Enable();
                LED_Write(LIGHT_ON);
            }
            if (strcmp("stop", buffer) == 0)
            {
                boStart = false;
                CySysTickStop();
                isr_GPIO_0_Disable();
                isr_GPIO_1_Disable();
                isr_GPIO_2_Disable();
                isr_GPIO_3_Disable();
                isr_GPIO_4_Disable();
                isr_GPIO_5_Disable();
                LED_Write(LIGHT_OFF);
            }

            UART_UartPutString(buffer);
        }

        for (i = 0; i < 6; ++i)
        {
            if (boSW[i] && boStart)
            {
                HandleSwitch(i, buffer, time);
            }
        }
    }
}

void HandleSwitch(uint8 switchIndex, char* buffer, char* time)
{
    sprintf(buffer, "Input%u;", switchIndex);
    UART_UartPutString(buffer);

    sprintf(time, "%lu;", intSW[switchIndex]);
    UART_UartPutString(time);

    sprintf(buffer, "%u\r\n", boUART[switchIndex]);
    UART_UartPutString(buffer);

    // Toggle the LED based on switch index
    switch (switchIndex)
    {
        case 0: LED_GPIO0_Write(~LED_GPIO0_Read()); break;
        case 1: LED_GPIO1_Write(~LED_GPIO1_Read()); break;
        case 2: LED_GPIO2_Write(~LED_GPIO2_Read()); break;
        case 3: LED_GPIO3_Write(~LED_GPIO3_Read()); break;
        case 4: LED_GPIO4_Write(~LED_GPIO4_Read()); break;
        case 5: LED_GPIO5_Write(~LED_GPIO5_Read()); break;
    }

    boUART[switchIndex] = !boUART[switchIndex];
    boSW[switchIndex] = false;
}

void SysTickISRCallback(void)
{
    msCount++;
}
