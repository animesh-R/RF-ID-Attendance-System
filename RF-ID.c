#include<avr/io.h>
#define F_CPU 10000000UL
#include<util/delay.h>
#define Baud_Rate 1200UL
#define ubrr_value ((F_CPU/(16UL*Baud_Rate))-1)

void usart_init();
void usart_send(unsigned char d);
unsigned char usart_rec();

#define rs PA0
#define rw PA1
#define e PA2

void lcd_cmd(char a)
{
PORTA=a;
PORTA&=~(1<<rs);
PORTA&=~(1<<rw);
PORTA|=(1<<e);
_delay_ms(10);
PORTA&=~(1<<e);
}

void lcd_data(char a)
{
PORTB=a;
PORTB|=(1<<rs);
PORTB&=~(1<<rw);
PORTB|=(1<<e);
_delay_ms(10);
PORTB&=~(1<<e);
}


/*void lcd_cmd(char a)
{
int y;
y=a&0xf0;
cmd(y);

y=(a<<4)&0xf0;
cmd(y);
}

void lcd_data(char a)
{
int y;
y=a&0xf0;
data(y);

y=(a<<4)&0xf0;
data(y);
}
*/
void string(char *s)
{
 int i;
 for(i=0;s[i]!='\0';i++)
 {
  lcd_data(s[i]);
  }
}

void main()
{

DDRA=0xFF;
DDRB=0xFF;
DDRD=0x00;
  
lcd_cmd(0x02);
lcd_cmd(0x20);
lcd_cmd(0x28);
lcd_cmd(0x0e);
lcd_cmd(0x06);

usart_init();

lcd_cmd(0x80);
string("WELCOME");
lcd_cmd(0x01);
lcd_cmd(0x80);

string("HI-TECHNOLOGY");
lcd_cmd(0xc0);
string("SOLUTIONS");
lcd_cmd(0x01);
lcd_cmd(0x80);
string("EMBEDDED");
lcd_cmd(0xc0);
string("SYSTEM");
lcd_cmd(0x01);
lcd_cmd(0x80);
string("RF-ID BASED");
lcd_cmd(0xc0);
string("ATTENDANCE SYSTEM");
lcd_cmd(0x01);
lcd_cmd(0x80);
string("USING");
lcd_cmd(0xc0);
string("UART");
lcd_cmd(0x01);
lcd_cmd(0x80);
string("SUBMITTED BY ");
lcd_cmd(0xc0);
string("ANIMESH RAWAT");
lcd_cmd(0x01);

 while(1)
 {
 int i;
 char a[12];
for(i=0;i<12;i++)
{
a[i]=usart_rec();
usart_send(a[i]);
}

if((a[0]=='1')&&(a[1]=='8')&&(a[2]=='0')&&(a[3]=='0')&&(a[4]=='8')&&(a[5]=='9')&&(a[6]=='2')&&(a[7]=='8')&&(a[8]=='1')&&(a[9]=='1')&&(a[10]=='A')&&(a[11]=='8'))
{
lcd_cmd(0x80);
string("ACCESS GRANT TO");
lcd_cmd(0xc5);
string("ANIMESH");
lcd_cmd(0x01);
}



else if((a[0]=='1')&&(a[1]=='8')&&(a[2]=='0')&&(a[3]=='0')&&(a[4]=='8')&&(a[5]=='9')&&(a[6]=='0')&&(a[7]=='F')&&(a[8]=='3')&&(a[9]=='C')&&(a[10]=='A')&&(a[11]=='2'))
{
lcd_cmd(0x80);
string("ACCESS GRANT TO");
lcd_cmd(0xc6);
string("ANSHU");
lcd_cmd(0x01);
}

else if((a[0]=='1')&&(a[1]=='8')&&(a[2]=='0')&&(a[3]=='0')&&(a[4]=='8')&&(a[5]=='8')&&(a[6]=='F')&&(a[7]=='E')&&(a[8]=='C')&&(a[9]=='7')&&(a[10]=='A')&&(a[11]=='9'))
{
lcd_cmd(0x80);
string("ACCESS GRANT TO");
lcd_cmd(0xc6);
string("ATUL");
lcd_cmd(0x01);
}

else if((a[0]=='1')&(a[1]=='8')&(a[2]=='0')&(a[3]=='0')&(a[4]=='8')&(a[5]=='9')&(a[6]=='0')&(a[7]=='2')&(a[8]=='9')&(a[9]=='0')&(a[10]=='0')&(a[11]=='3'))
{
lcd_cmd(0x80);
string("ACCESS GRANT TO");
lcd_cmd(0xc6);
string("RITU");
lcd_cmd(0x01);
}

else
{
lcd_cmd(0x80);
string("ACCESS DENIED");
lcd_cmd(0x01);
lcd_cmd(0x80);
string("UNAUTHORISED");
lcd_cmd(0xc0);
string("ACCESS");
lcd_cmd(0x01);
}

}
}

void usart_init()
{
 UBRRL=ubrr_value;
 UBRRH=(ubrr_value>>8);
 UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
 UCSRB=(1<<UCSZ2);
 UCSRB=(1<<RXEN)|(1<<TXEN);
 }

 void usart_send(unsigned char data)
 {
  while(!(UCSRA&(1<<UDRE)))
  {
    }
UDR=data;
}

unsigned char usart_rec()
{
 while(!(UCSRA&(1<<RXC)))
 {
   }
   return UDR;
 }


