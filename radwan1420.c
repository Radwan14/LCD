
long counter=0, counter2=0;

//Timer 0 initiallisations
void InitTimer0()
{
  //OPTION Register
  OPTION_REG.T0CS = 0; //Internal instruction cycle clock (CLKOUT)
  OPTION_REG.PSA = 0;  //Prescaler is assigned to the Timer0 module

  //PS2:PS0: Prescaler Rate Select bits, Prescaler 1:64
  OPTION_REG.PS2 = 1;
  OPTION_REG.PS1 = 0;
  OPTION_REG.PS0 = 1;


  TMR0 = 99; //Timer0 starts counting value

  //INTCON Register
  INTCON.TMR0IE = 1; //1 = Enables the TMR0 Interrupt
  INTCON.PEIE=1;  //Enables all unmasked peripheral interrupts
  INTCON.GIE = 1; //1 = Enables all interrupts

}


//isr
void Interrupt()
{
  if(INTCON.TMR0IF == 1)   //if timer0 interrupt occured
  {
     INTCON.TMR0IF = 0;  //reset timer0 interrupt flag
     TMR0 = 99; //Timer0 starts counting again

     counter++; //counts 1 second

     counter2++; //counts 2 seconds

     if(counter == 6000)
     {
       counter=0;
       portb.b0 = ~portb.b0; //toggle led
     }

     if(counter2 == 200)
     {
       counter2=0;
       portb.b1 = ~portb.b1; //toggle led
     }


  }
}




// LCD module connections
sbit LCD_RS at RB2_bit;
sbit LCD_EN at RB3_bit;
sbit LCD_D4 at RB4_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D7 at RB7_bit;

sbit LCD_RS_Direction at TRISB2_bit;
sbit LCD_EN_Direction at TRISB3_bit;
sbit LCD_D4_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D7_Direction at TRISB7_bit;
// End LCD module connections

 char value_1 = 'A';
 char value_2 = 'B';


int x =0;

void main() {
  Lcd_Init();  // Initialize LCD

  Lcd_Cmd(_LCD_CLEAR);   // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);   // Cursor off
 Lcd_Out(1, 1, "Radwan");
 Lcd_Chr(2, 1, value_1);
 Lcd_Chr(2, 6, value_2);

 trisb.rb1=1;
while(1)
{
 if(portb.rb0==1)
{
  x++;
}
}
   InitTimer0(); //Timer 0 initiallisations

   //pin B0 as output
   trisb.b0 = 0;
   portb.b0 = 0;

   trisb.b1 = 0;
   portb.b1 = 0;


}
trisb.b0=1;//B0 as input
 trisb.b7=0;portb.b7 = 0 ; //B7 as output

 loop:

   if(portb.b0==0) // if switch has prsseo


 {
portb.rb7 = 1;// turn on led

      }
    if(portb.b1==0) // if switch has prsseo


 {
portb.rb7 = 0;// turn on led

      }
goto loop;

}




