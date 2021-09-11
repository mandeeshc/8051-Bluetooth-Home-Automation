#include<stdio.h>
#include<string.h>
#define LCD P0
sbit RS = P1^0;
sbit EN = P1^1;
//int credit[4];
char arr_t[10];

void delay_lcd(int);
void init_LCD();
void lcd_data(char);
void lcd_string(char *);
void clear_arr_t();
void disp_val(char,int,int);
void lcd_cmd(char);
void disp_val_float(char,float,int);
//****************************************
void delay_lcd(int DD)
{
	int i,j;
	for(i=1;i<=50;i++)
	{
		for(j=1;j<=DD;j++);
	}
}
//****************************************
void init_LCD()
{
	RS=0;
	lcd_cmd(0x38);
	delay_lcd(100);
	lcd_cmd(0x01);
	delay_lcd(100);
	lcd_cmd(0x0F);
	delay_lcd(100);
	lcd_cmd(0x0C);
	delay_lcd(100);
	lcd_cmd(0x80);
	delay_lcd(100);
	lcd_data('O');
	delay_lcd(100);
	lcd_data('K');
	delay_lcd(1000);
	lcd_cmd(0x01);
	delay_lcd(100);
	lcd_cmd(0x80);
}
//****************************************
void lcd_data(char dta)
{
	RS=1;
	LCD = dta;
	EN=1;
	delay_lcd(10);
	EN=0;
}
//****************************************
void lcd_string(char *dat)
	{
	 while(*dat)
	 lcd_data(*dat++);
	}
//****************************************
void lcd_clear()
{
	lcd_cmd(0x01);
	lcd_cmd(0x80);
}	
/*void disp_val(char add, int value, int space)
{	
	char arr_t[10];
	int c1=0,i;
	int v1=value;	
	lcd_cmd(add);
	for(i=0;i<space;i++)
	{
		lcd_data(' ');
	}
	if(v1!=0)
	{	
		while(v1!=0)	
		{			
			arr_t[c1] = (v1%10)+48;
			v1 = v1/10;
			c1++; 
		}  
		lcd_cmd(add);
		for(i=c1-1;i>=0;i--)
		{
			lcd_data(arr_t[i]);
		}
	}
	else
	{
		lcd_cmd(add);
		lcd_data('0');		
	}
}*/
//****************************************
void lcd_cmd(char cmmd)
{
	RS=0;
	//delay_lcd(100);
	LCD = cmmd;
	EN=1;
	delay_lcd(10);
	EN=0;
}	

//****************************************
/*void disp_val_float(char add, float total, int space)
{
  int i=0;
  int wholeNum = total;//wouldn't hurt to cast it to avoid warning
  int decimalNum = (int) ((total - wholeNum) * 100);
  char idata wholeNumStr[6];
  char idata decNumStr[4];
  char idata numStr[10];       
  char decPtStr = '.';     
  sprintf(wholeNumStr, "%d", wholeNum);
  //itoa(wholeNum,wholeNumStr,10);
  //itoa( decimalNum,decNumStr,10);
  sprintf(decNumStr, "%d", decimalNum);
  strcpy(numStr, wholeNumStr);
  strcat(numStr, ".");
  strcat(numStr, decNumStr);
  strcat(numStr, "\0");
  lcd_cmd(add);
  for(i=0;i<space;i++)
  {
      lcd_data(' '); 
  }
  i=0;
  lcd_cmd(add);
  while(numStr[i]!='\0')
  {
      lcd_data(numStr[i]);
    i++;
  }
}*/

//****************************************