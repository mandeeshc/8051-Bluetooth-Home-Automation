#include <REGX52.H>
#include "lcd.c"
sbit RELAY1 = P2^0;
sbit RELAY2 = P2^1;
sbit RELAY3 = P2^2;
sbit RELAY4 = P2^3;
sbit LED1 = P3^4;  // If required else ignore
sbit LED2 = P3^5;
sbit LED3 = P3^6;
sbit LED4 = P3^7;
//****************************************
char rec,stop=0,var=0;	   
//****************************************
void tx_UART(char);
//****************************************
void init_serial()
{
	TMOD = 0x21;	     // Timer 1, 8 bit Auto-reload   
	TH1 = -3;            // 9600 Baud Rate 
	SCON = 0x50;
	IE = 0x90;	         // For Enabling Serial Port Interrupt		   
	TR1 = 1;				  
}	 
//****************************************
void delay_ms(int DD)
{
	int i,j;
	for(i=1;i<=1275;i++)
	{
		for(j=1;j<=DD;j++);
	}
}
//****************************************
void serial() interrupt 4
{	
	RI=0;
	rec = SBUF;
	var = rec;
}

//****************************************
void tx_UART(char v)
{	
	IE = 0x00;	
	TI=0;
	SBUF = v;
	while(TI!=1);
	TI=0;
	IE = 0x90;
}

void tx_UART_string(char *str)
{
	while(*str)
	tx_UART(*str++);
}
//****************************************
int main()
{
	RELAY1 = 0;RELAY2 = 0;	RELAY3 = 0;RELAY4 = 0;
	init_LCD();
	lcd_string("   Bluetooth    ");
	lcd_cmd(0xC0);
	lcd_string("Home Automation ");
	LED1 = 0; LED2 = 0;	LED3 = 0; LED4 = 0;
	delay_ms(50);
	LED1 = 1; LED2 = 1;	LED3 = 1; LED4 = 1;
	init_serial();
	//tx_UART('O');tx_UART('K'); 
	tx_UART_string("System Started");
	lcd_clear();
	lcd_string("D1:OFF    D2:OFF");
	lcd_cmd(0xC0);
	lcd_string("D3:OFF    D4:OFF");	
		
	while(1)
	{
		// Relay ON : q,w,e,r
		// Relay OFF : a,s,d,f
		if(var=='q')
		{
			lcd_cmd(0x80);
			lcd_string("D1:ON ");
			RELAY1=1;
			var=0;
		}

		else if(var=='w')
		{
			lcd_cmd(0x80);
			lcd_string("D1:OFF");
			RELAY1=0;
			var=0;
		}
		else if(var=='e')
		{
			lcd_cmd(0x8A);
			lcd_string("D2:ON ");
			RELAY2=1;
			var=0;
		 }
		 else if(var=='r')
		 {
			lcd_cmd(0x8A);
			lcd_string("D2:OFF");
			RELAY2=0;
			var=0; 
		 }
		 else if(var=='a')
		{
			lcd_cmd(0xC0);
			lcd_string("D3:ON ");
			RELAY3=1;
			var=0;
		 }
		 else if(var=='s')
		 {
			lcd_cmd(0xC0);
			lcd_string("D3:OFF");
			RELAY3=0;
			var=0;
		 }
		 else if(var=='d')
		{
			lcd_cmd(0xCA);
			lcd_string("D4:ON ");
			RELAY4=1;
			var=0;
		 }
		 else if(var=='f')
		 {
			lcd_cmd(0xCA);
			lcd_string("D4:OFF");
			RELAY4=0;
			var=0;
		 }
	}
	return 0;
}
//****************************************