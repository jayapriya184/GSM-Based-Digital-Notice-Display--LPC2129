#include "project.h"
#include <string.h>
#define GREEN_LED (1<<23)
#define RED_LED (1<<24)
#define BUZZER (1<<25)
#define BUTTON (1<<26)

void ALERT_INIT(void)
{
IODIR1 |= GREEN_LED | RED_LED | BUZZER;
IODIR1 &= ~BUTTON;
IOSET1 = GREEN_LED | RED_LED | BUZZER;
}

void NORMAL_ALERT(void)
{
IOSET1 = RED_LED | BUZZER;
IOCLR1 = GREEN_LED;
}

void EMERGENCY_ALERT(void)
{
IOSET1 = GREEN_LED;
IOCLR1 = RED_LED | BUZZER;
GSM_TRANSMIT("EMERGENCY ALERT! Please check immediate");
}

void BUZZER_OFF(void)
{
IOSET1 = BUZZER;
}

void BUTTON_CHECK(void)
{
if((IOPIN1 & BUTTON) == 0)
{
BUZZER_OFF();
}
}
void GSM_INIT(void)
{
UART0_STRING("AT\r\n");
delay_milliseconds(1000);
UART0_STRING("AT\r\n");
delay_milliseconds(1000);
UART0_STRING("AT+CMGF=1\r\n");
delay_milliseconds(1000);
UART0_STRING("AT+CNMI=2,2,0,0,0\r\n");
delay_milliseconds(1000);
}
void GSM_TRANSMIT(char *s)
{
UART0_STRING("AT+CMGF=1\r\n");
delay_milliseconds(1000);
UART0_STRING("AT+CMGS=\"+919381058662\"\r\n");
delay_milliseconds(1000);
UART0_STRING(s) ;
delay_milliseconds(1000);
UART0_TX(26); 
delay_milliseconds(5);
}
void GSM_RECEIVE(void)
{
unsigned char ch;
unsigned int i = 0;
unsigned char capture = 0;
char msg[160];
while(1)
{
BUTTON_CHECK();
if(U0LSR & 0x01)
{
ch = U0RBR;
if(ch == '*')
{
i = 0;
capture = 1;
continue;
}
if(ch == '#' && capture == 1)
{
msg[i] = '\0';
capture = 0;
LCD_COMMAND(0x01);
LCD_COMMAND(0x80);
LCD_STR((unsigned char *)msg);

if(strstr(msg,"EMERGENCY") != NULL)
{
EMERGENCY_ALERT();
}
else
{
NORMAL_ALERT();
}
i = 0;
}
/* STORE ONLY DATA BETWEEN * AND # */
else if(capture == 1)
{
if(i < 159)
{
msg[i++] = ch;
}
}
}
}
}
