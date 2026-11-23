#include <LPC21XX.H>
/* LCD PIN CONFIGURATION */
#define LCD_d ((1<<18)|(1<<19)|(1<<21)|(1<<22)|(1<<23)|(1<<24)|(1<<25)|(1<<27))
#define RS (1<<8)
#define E (1<<9)

void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);
void LCD_INTEGER(int);
void LCD_STR(unsigned char *);

void delay_seconds(unsigned int);
void delay_milliseconds(unsigned int);

void UART0_CONFIG(void);
void UART0_TX(unsigned char);
void UART0_STRING(char *);
unsigned char UART0_RX(void);

void GSM_INIT(void);
void GSM_TRANSMIT(char *);
void GSM_RECEIVE(void);

void ALERT_INIT(void);
void NORMAL_ALERT(void);
void EMERGENCY_ALERT(void);
void BUTTON_CHECK(void);
void BUZZER_OFF(void);
