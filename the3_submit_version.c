#include "Includes.h"
#include <stdio.h>
#define DISPLAY0 0x3f
#define DISPLAY1 0x06
#define DISPLAY2 0x5b
#define DISPLAY3 0x4f
#define DISPLAY4 0x66
#define DISPLAY5 0x6D
#define DISPLAY6 0x7D
#define DISPLAY7 0x07
#define DISPLAY8 0xff

typedef enum {TEM_STATE, CDM_STATE, TSM_STATE} game_state_t;
game_state_t game_state = TEM_STATE;

uint8_t charValue = 0x00;
uint8_t isRE3Pressed = 0x00;
uint8_t isRE2Pressed = 0x00;
uint8_t isRE1Pressed = 0x00;
uint8_t isRE0Pressed = 0x00;
uint8_t isRE4Pressed = 0x00;
uint8_t isRE5Pressed = 0x00;
uint8_t defineValue = 0x00;
uint8_t customSelected = 0x00;
uint8_t tmr_counter_400 = 0; 
uint8_t temp = 0x00;
uint8_t temp1 = 0x00;
uint8_t customCount=0x00;
uint8_t temp_precust=0x00;
uint8_t temp_text=0x00;
uint8_t temp_customText=0x00;


uint8_t cursorX =0;
uint8_t cursorY =0;


char ourChar[1];
char predefined[37] = {' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3', '4','5','6','7','8','9'};
char precust[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char text[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
uint8_t customText[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

uint8_t index = 0;

void Pulse(void){
    PORTBbits.RB5 = 1;
    __delay_us(30);
    PORTBbits.RB5 = 0;
    __delay_us(30);
}

void SendBusContents(uint8_t data){
  PORTD = PORTD & 0x0F;           // Clear bus
  PORTD = PORTD | (data&0xF0);     // Put high 4 bits
  Pulse();                        
  PORTD = PORTD & 0x0F;           // Clear bus
  PORTD = PORTD | ((data<<4)&0xF0);// Put low 4 bits
  Pulse();
}

void scrollText(){
    // LCD clear'lamak gerekebilir.
    PORTBbits.RB2 = 0;
    SendBusContents(0x0C); // Display on, cursor off, blink off.
    PORTBbits.RB2 = 0;
    SendBusContents(0x82);
    PORTBbits.RB2 = 1;
    SendBusContents(' '); // Display on, cursor off, blink off.
    PORTBbits.RB2 = 0;
    SendBusContents(0x81);
    PORTBbits.RB2 = 1;
    SendBusContents(' '); // Display on, cursor off, blink off.
    PORTBbits.RB2 = 0;
    SendBusContents(0x80);
    PORTBbits.RB2 = 1;
    SendBusContents(' '); // Display on, cursor off, blink off.
    PORTBbits.RB2 = 0;
    SendBusContents(0x8b);
    PORTBbits.RB2 = 1;
    SendBusContents(' '); // Display on, cursor off, blink off.
    PORTBbits.RB2 = 0;
    SendBusContents(0x8c);
    PORTBbits.RB2 = 1;
    SendBusContents(' '); // Display on, cursor off, blink off.
    PORTBbits.RB2 = 0;
    SendBusContents(0x8d);
    PORTBbits.RB2 = 1;
    SendBusContents(' '); // Display on, cursor off, blink off.
    PORTBbits.RB2 = 0;
    SendBusContents(0x8e);
    PORTBbits.RB2 = 1;
    SendBusContents(' '); // Display on, cursor off, blink off.
    PORTBbits.RB2 = 0;
    SendBusContents(0x8f);
    PORTBbits.RB2 = 1;
    SendBusContents(' '); // Display on, cursor off, blink off.
    PORTBbits.RB2 = 0;
    SendBusContents(0x83);
    PORTBbits.RB2 = 1;
    SendBusContents('f'); // Display on, cursor off, blink off.
    PORTBbits.RB2 = 0;
    SendBusContents(0x84);
    PORTBbits.RB2 = 1;
    SendBusContents('i'); // Display on, cursor off, blink off.
    PORTBbits.RB2 = 0;
    SendBusContents(0x85);
    PORTBbits.RB2 = 1;
    SendBusContents('n'); // Display on, cursor off, blink off.
    PORTBbits.RB2 = 0;
    SendBusContents(0x86);
    PORTBbits.RB2 = 1;
    SendBusContents('i'); // Display on, cursor off, blink off.
    PORTBbits.RB2 = 0;
    SendBusContents(0x87);
    PORTBbits.RB2 = 1;
    SendBusContents('s'); // Display on, cursor off, blink off.
    PORTBbits.RB2 = 0;
    SendBusContents(0x88);
    PORTBbits.RB2 = 1;
    SendBusContents('h'); // Display on, cursor off, blink off.
    PORTBbits.RB2 = 0;
    SendBusContents(0x89);
    PORTBbits.RB2 = 1;
    SendBusContents('e'); // Display on, cursor off, blink off.
    PORTBbits.RB2 = 0;
    SendBusContents(0x8a);
    PORTBbits.RB2 = 1;
    SendBusContents('d'); // Display on, cursor off, blink off.

    tmr_counter_400 = 0; 
    while(1){
        ;
    }
}
void tmr_init() {
    INTCONbits.TMR0IE = 1;
    INTCONbits.GIE = 1;
    T0CON = 0xC7; // pre-scale 256 counter 76
    TMR0L = 0x83; // initial value = 0 
}

void __interrupt(high_priority) highPriorityISR(void) {
    if (INTCONbits.TMR0IF) { 
        INTCONbits.TMR0IF=0;
        TMR0L = 0x83; // initial value = 0
        if(tmr_counter_400 == 124){
            // do work
            temp_customText = customText[15];
            temp_text = text[15];
            temp_precust = precust[15];
            for(int i=0;i<16;i++){
                if (i ==0){
                    precust[15] = precust[i];
                    customText[15] = customText[i];
                    text[15] = text[i];
                    continue;
                }
                else if (i == 15){
                    precust[14] = temp_precust;
                    customText[14] = temp_customText;
                    text[14] = temp_text;
                    continue;
                }
                precust[i-1] = precust[i];
                customText[i-1] = customText[i];
                text[i-1] = text[i];
            }
            PORTBbits.RB2 = 0;
            //    SendBusContents(0x0C); // Display on, cursor off, blink off.
            SendBusContents(0xc0);
            PORTBbits.RB2 = 1;
            for (int i =0;i<16;i++){
                if (precust[i] == 0){
                    SendBusContents(text[i]);
                }
                else{
                    SendBusContents(customText[i]);
                }
            }
            tmr_counter_400 = 0;
        }
        else{
            tmr_counter_400++;
        }
    }
}


void CreateChar(uint8_t addr, uint8_t charmap[]) {
    addr &= 0x7; // we only have 8 locations 0-7
    PORTBbits.RB2 = 0;
    SendBusContents(0x40 | (addr << 3)); // Set the address for custom char.
    for (uint8_t i=0; i<8; i++) {
        PORTBbits.RB2 = 1;
        SendBusContents(charmap[i]);
    }
}

// we store the recently defined custom char value in this array.
uint8_t ledToDisplayMap[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};

// we get the custom char array elements in this function from the leds.
void ledToDisplay(){
    ledToDisplayMap[0] = ((PORTAbits.RA0 << 4) | (PORTBbits.RB0 << 3) | (PORTCbits.RC0 << 2) | (PORTDbits.RD0 << 1));
    ledToDisplayMap[1] = ((PORTAbits.RA1 << 4) | (PORTBbits.RB1 << 3) | (PORTCbits.RC1 << 2) | (PORTDbits.RD1 << 1));
    ledToDisplayMap[2] = ((PORTAbits.RA2 << 4) | (PORTBbits.RB2 << 3) | (PORTCbits.RC2 << 2) | (PORTDbits.RD2 << 1));
    ledToDisplayMap[3] = ((PORTAbits.RA3 << 4) | (PORTBbits.RB3 << 3) | (PORTCbits.RC3 << 2) | (PORTDbits.RD3 << 1));
    ledToDisplayMap[4] = ((PORTAbits.RA4 << 4) | (PORTBbits.RB4 << 3) | (PORTCbits.RC4 << 2) | (PORTDbits.RD4 << 1));
    ledToDisplayMap[5] = ((PORTAbits.RA5 << 4) | (PORTBbits.RB5 << 3) | (PORTCbits.RC5 << 2) | (PORTDbits.RD5 << 1));
    ledToDisplayMap[6] = ((PORTAbits.RA6 << 4) | (PORTBbits.RB6 << 3) | (PORTCbits.RC6 << 2) | (PORTDbits.RD6 << 1));
    ledToDisplayMap[7] = ((PORTAbits.RA7 << 4) | (PORTBbits.RB7 << 3) | (PORTCbits.RC7 << 2) | (PORTDbits.RD7 << 1));
}

void toggleLed(){
    switch(cursorX){
        case 0:
            switch(cursorY){
                case 0:
                    PORTAbits.RA0 = !PORTAbits.RA0;
                    break;
                case 1:
                    PORTAbits.RA1 = !PORTAbits.RA1;
                    break;
                case 2:
                    PORTAbits.RA2 = !PORTAbits.RA2;
                    break;
                case 3:
                    PORTAbits.RA3 = !PORTAbits.RA3;
                    break;
                case 4:
                    PORTAbits.RA4 = !PORTAbits.RA4;
                    break;
                case 5:
                    PORTAbits.RA5 = !PORTAbits.RA5;
                    break;
                case 6:
                    PORTAbits.RA6 = !PORTAbits.RA6;
                    break;
                case 7:
                    PORTAbits.RA7 = !PORTAbits.RA7;
                    break;
            }
            
            
            break;
        case 1:
            switch(cursorY){
                case 0:
                    PORTBbits.RB0 = !PORTBbits.RB0;
                    break;
                case 1:
                    PORTBbits.RB1 = !PORTBbits.RB1;
                    break;
                case 2:
                    PORTBbits.RB2 = !PORTBbits.RB2;
                    break;
                case 3:
                    PORTBbits.RB3 = !PORTBbits.RB3;
                    break;
                case 4:
                    PORTBbits.RB4 = !PORTBbits.RB4;
                    break;
                case 5:
                    PORTBbits.RB5 = !PORTBbits.RB5;
                    break;
                case 6:
                    PORTBbits.RB6 = !PORTBbits.RB6;
                    break;
                case 7:
                    PORTBbits.RB7 = !PORTBbits.RB7;
                    break;
            }
            break;
        case 2:
            switch(cursorY){
                case 0:
                    PORTCbits.RC0 = !PORTCbits.RC0;
                    break;
                case 1:
                    PORTCbits.RC1 = !PORTCbits.RC1;
                    break;
                case 2:
                    PORTCbits.RC2 = !PORTCbits.RC2;
                    break;
                case 3:
                    PORTCbits.RC3 = !PORTCbits.RC3;
                    break;
                case 4:
                    PORTCbits.RC4 = !PORTCbits.RC4;
                    break;
                case 5:
                    PORTCbits.RC5 = !PORTCbits.RC5;
                    break;
                case 6:
                    PORTCbits.RC6 = !PORTCbits.RC6;
                    break;
                case 7:
                    PORTCbits.RC7 = !PORTCbits.RC7;
                    break;
            }
            break;
        case 3:
            switch(cursorY){
                case 0:
                    PORTDbits.RD0 = !PORTDbits.RD0;
                    break;
                case 1:
                    PORTDbits.RD1 = !PORTDbits.RD1;
                    break;
                case 2:
                    PORTDbits.RD2 = !PORTDbits.RD2;
                    break;
                case 3:
                    PORTDbits.RD3 = !PORTDbits.RD3;
                    break;
                case 4:
                    PORTDbits.RD4 = !PORTDbits.RD4;
                    break;
                case 5:
                    PORTDbits.RD5 = !PORTDbits.RD5;
                    break;
                case 6:
                    PORTDbits.RD6 = !PORTDbits.RD6;
                    break;
                case 7:
                    PORTDbits.RD7 = !PORTDbits.RD7;
                    break;
            }
            break;
            
    }
    ledToDisplay();
}

void handleCursorXDisplay(){
    
    PORTHbits.RH3 = 0;
    PORTHbits.RH2 = 1;
    PORTHbits.RH1 = 0;
    PORTHbits.RH0 = 0;
    
  
    switch(cursorX){
        case 0:
            PORTJ=DISPLAY0;
            break;
         case 1:
            PORTJ=DISPLAY1;
            break;
         case 2:
            PORTJ=DISPLAY2;
            break;
         case 3:
            PORTJ=DISPLAY3;
            break;              
            
    }
     while (temp < 250){
         while (temp1 < 5){
            temp1++;
        }
        temp1=0;
        temp++;
    }
    PORTJ = 0;
    temp = 0;
    temp1=0;   
}
void handleCursorYDisplay(){
    
    PORTHbits.RH3 = 1;
    PORTHbits.RH2 = 0;
    PORTHbits.RH1 = 0;
    PORTHbits.RH0 = 0;
    
  
    switch(cursorY){
        case 0:
            PORTJ=DISPLAY0;
            break;
         case 1:
            PORTJ=DISPLAY1;
            break;
         case 2:
            PORTJ=DISPLAY2;
            break;
         case 3:
            PORTJ=DISPLAY3;
            break;
         case 4:
            PORTJ=DISPLAY4;
            break;
         case 5:
            PORTJ=DISPLAY5;
            break;
         case 6:
            PORTJ=DISPLAY6;
            break;
         case 7:
            PORTJ=DISPLAY7;
            break;   
    }
     while (temp < 250){
         while (temp1 < 5){
            temp1++;
        }
        temp1=0;
        temp++;
    }
    PORTJ = 0;
    temp = 0;
    temp1=0;   
}
void handleCountDisplay(){
    
    PORTHbits.RH3 = 0;
    PORTHbits.RH2 = 0;
    PORTHbits.RH1 = 0;
    PORTHbits.RH0 = 1;
    
  
    switch(customCount){
        case 0:
            PORTJ=DISPLAY0;
            break;
         case 1:
            PORTJ=DISPLAY1;
            break;
         case 2:
            PORTJ=DISPLAY2;
            break;
         case 3:
            PORTJ=DISPLAY3;
            break;
         case 4:
            PORTJ=DISPLAY4;
            break;
         case 5:
            PORTJ=DISPLAY5;
            break;
         case 6:
            PORTJ=DISPLAY6;
            break;
         case 7:
            PORTJ=DISPLAY7;
            break;
         case 8:
            PORTJ=DISPLAY8;
            break;
                    
            
    }
     while (temp < 250){
         while (temp1 < 5){
            temp1++;
        }
        temp1=0;
        temp++;
    }
    PORTJ = 0;
    temp = 0;
    temp1=0;   
}
void InitLCD(void) {
    // Initializing by Instruction
    __delay_ms(20);
    PORTD = 0x30;
    Pulse();
    
    __delay_ms(6);
    PORTD = 0x30;
    Pulse();
    
    __delay_us(300);
    PORTD = 0x30;
    Pulse();
    
    __delay_ms(2);
    PORTD = 0x20;
    Pulse();
    PORTBbits.RB2 = 0;
    SendBusContents(0x2C);
    SendBusContents(0x0C);
    SendBusContents(0x01);
}
void move_cursor(unsigned int result){
 
    switch(result/64){
        case 0:
            PORTBbits.RB2 = 0;
            SendBusContents(0x80);
            index=0;
            break;
            
          case 1:
            PORTBbits.RB2 = 0;
            SendBusContents(0x81);
            index=1;
            break;
            
         case 2:
            PORTBbits.RB2 = 0;
            SendBusContents(0x82);
            index=2;
            break;
            
         case 3:
            PORTBbits.RB2 = 0;
            SendBusContents(0x83);
            index=3;
            break;
            
        case 4:
            PORTBbits.RB2 = 0;
            SendBusContents(0x84);
            index=4;
            break;
            
        case 5:
            PORTBbits.RB2 = 0;
            SendBusContents(0x85);
            index=5;
            break;
            
        case 6:
            PORTBbits.RB2 = 0;
            SendBusContents(0x86);
            index=6;
            break;
            
         case 7:
            PORTBbits.RB2 = 0;
            SendBusContents(0x87);
            index=7;
            break;
            
         case 8:
            PORTBbits.RB2 = 0;
            SendBusContents(0x88);
            index=8;
            break;
            
        case 9:
            PORTBbits.RB2 = 0;
            SendBusContents(0x89);
            index=9;
            break;
            
        case 10:
            PORTBbits.RB2 = 0;
            SendBusContents(0x8A);
            index=10;
            break;
            
        case 11:
            PORTBbits.RB2 = 0;
            SendBusContents(0x8B);
            index=11;
            break;
            
        case 12:
            PORTBbits.RB2 = 0;
            SendBusContents(0x8C);
            index=12;
            break;
            
        case 13:
            PORTBbits.RB2 = 0;
            SendBusContents(0x8D);
            index=13;
            break;
            
        case 14:
            PORTBbits.RB2 = 0;
            SendBusContents(0x8E);
            index=14;
            break;
            
        case 15:
            PORTBbits.RB2 = 0;
            SendBusContents(0x8F);
            index=15;
            break;
    }
    
}
void selectChar(int val){
    ourChar[0] = predefined[val];
}

void button_task_RE2(){ 
   
    switch(game_state){
        case TEM_STATE: // forward predefined characters
            if (PORTEbits.RE2 == 1 && isRE2Pressed == 0){
                    isRE2Pressed = 1;
                    charValue++;
                    if (charValue == 37){
                        charValue = 0;
                    }
                    customSelected = 0;
                    selectChar(charValue);
                    precust[index] = 0;
                    text[index] = ourChar[0];
                    PORTBbits.RB2 = 1;
                    SendBusContents(text[index]);
                }
            else if ((PORTEbits.RE2 == 0 && isRE2Pressed == 1)){
                    isRE2Pressed = 0;
                }
            
            break;
        
        case CDM_STATE: // move cursor position to the up
            if (PORTEbits.RE2 == 1 && isRE2Pressed == 0){
                    isRE2Pressed = 1;
                    if(cursorY>0){
                        cursorY--;
                    }
                }
            else if ((PORTEbits.RE2 == 0 && isRE2Pressed == 1)){
                    isRE2Pressed = 0;
                }
            break;
        case TSM_STATE:
            break;
            
    }
}
void button_task_RE1(){ 
    switch(game_state){
        case TEM_STATE: // backward predefined characters
            if (PORTEbits.RE1 == 1 && isRE1Pressed == 0){
                isRE1Pressed = 1;
                charValue--;
                if (charValue == 255){
                    charValue = 36;
                }
                customSelected = 0;
                selectChar(charValue);
                precust[index] = 0;
                text[index] = ourChar[0];
                PORTBbits.RB2 = 1;
                SendBusContents(text[index]);
            }

            else if ((PORTEbits.RE1 == 0 && isRE1Pressed == 1)){
                    isRE1Pressed = 0;
                }
            break;
        
        case CDM_STATE: // move cursor position to the down
            if (PORTEbits.RE1 == 1 && isRE1Pressed == 0){
                    isRE1Pressed = 1;
                    if(cursorY<7){
                        cursorY++;
                    }

                }

            else if ((PORTEbits.RE1 == 0 && isRE1Pressed == 1)){
                    isRE1Pressed = 0;
                }
            break;
        case TSM_STATE:
            break;
            
    }
}
void button_task_RE3(){ 
    switch(game_state){
        case TEM_STATE: // backward custom characters
            if (PORTEbits.RE3 == 1 && isRE3Pressed == 0){
                isRE3Pressed = 1;
                defineValue--;
                if (defineValue == 255){
                    defineValue = customCount;
                }
                 if(defineValue==0){
                     precust[index] = 1;
                     customText[index]=defineValue;
                    PORTBbits.RB2 = 1;
                    SendBusContents(' ');
                    
                }
                else{
                precust[index] = 1;
                customText[index]=defineValue-1;
                PORTBbits.RB2 = 1;
                SendBusContents(customText[index]);
                }
            }

            else if ((PORTEbits.RE3 == 0 && isRE3Pressed == 1)){
                isRE3Pressed = 0;
            }
            break;
            
        case CDM_STATE: // move cursor position to the right
            if (PORTEbits.RE3 == 1 && isRE3Pressed == 0){
                isRE3Pressed = 1;
                if(cursorX>0){
                    cursorX--;
                }
            }

            else if ((PORTEbits.RE3 == 0 && isRE3Pressed == 1)){
                isRE3Pressed = 0;
            }
            break;
            
        case TSM_STATE:
            break;
    }
}
void button_task_RE0(){ 
    switch(game_state){
        case TEM_STATE: // forward custom characters
            if (PORTEbits.RE0 == 1 && isRE0Pressed == 0){
                isRE0Pressed = 1;
                defineValue++;
                customSelected = 1;

                if (defineValue == (customCount+1)){
                    defineValue = 0;
                }
                if(defineValue==0){
                     precust[index] = 1;
                     customText[index]=defineValue;
                    PORTBbits.RB2 = 1;
                    SendBusContents(' ');
                    
                }
                else{
                precust[index] = 1;
                customText[index]=defineValue-1;
                PORTBbits.RB2 = 1;
                SendBusContents(customText[index]);
                }
            }

            else if ((PORTEbits.RE0 == 0 && isRE0Pressed == 1)){
                isRE0Pressed = 0;
            }
            break;
        
        case CDM_STATE: // move cursor position to the right
            if (PORTEbits.RE0 == 1 && isRE0Pressed == 0){
                isRE0Pressed = 1;
                if(cursorX<3){
                    cursorX++;
                }
            }

            else if ((PORTEbits.RE0 == 0 && isRE0Pressed == 1)){
                isRE0Pressed = 0;
            }
            break;
            
        case TSM_STATE:
            break;
    }
}
void button_task_RE5(){
    switch(game_state){
        case TEM_STATE: // if re5 pressed game state switches to the TSM state.
            if (PORTEbits.RE5 == 1 && isRE5Pressed == 0){
                isRE5Pressed = 1;
                game_state = TSM_STATE;
                tmr_init();
                scrollText();
            }
            
            else if ((PORTEbits.RE5 == 0 && isRE5Pressed == 1)){
                isRE5Pressed = 0;
            }
            break;
        
        case CDM_STATE:
            // in this mode, if re5 pressed we set cursor position to the initial position and clear leds.
            if (PORTEbits.RE5 == 1 && isRE5Pressed == 0){
                isRE5Pressed = 1;
                
                CreateChar(customCount, ledToDisplayMap);
                cursorX = 0;
                cursorY = 0;
                customCount++;
                defineValue = customCount;
                precust[index] = 1;
                customText[index]=customCount-1;
                PORTBbits.RB2 = 0;
                SendBusContents(0x80 + index);
                PORTBbits.RB2 = 1;
                SendBusContents(customText[index]);
                game_state=TEM_STATE;
                
                PORTA=0x00;
                PORTB=0x00;
                PORTC=0x00;
                PORTD=0x00;
                                  
                        
            }

            else if ((PORTEbits.RE5 == 0 && isRE5Pressed == 1)){
                isRE5Pressed = 0;
            }
            break;
            
        case TSM_STATE:
            
            break;
    }
}
void button_task_RE4(){ 
    switch(game_state){
        case TEM_STATE: // forward custom characters
            // When game state is TEM we adjust adcons as initial states. Since we are done using portA pins as led. 
            ADCON0 = 0x31; // Channel 12; Turn on AD Converter
            ADCON1 = 0x00; // All analog pins
            ADCON2 = 0xAA;
            GODONE = 1; // Start ADC conversion
            while(GODONE); // Poll and wait for conversion to finish.
            unsigned int result = (ADRESH << 8) + ADRESL;
            move_cursor(result);
            if (PORTEbits.RE4 == 1 && isRE4Pressed == 0){
                isRE4Pressed = 1;
                game_state = CDM_STATE;
                PORTA=0x00;
                PORTB=0x00;
                PORTC=0x00;
                PORTD=0x00;
            }
            else if ((PORTEbits.RE4 == 0 && isRE4Pressed == 1)){
                    isRE4Pressed = 0;
            }
            break;
        
        case CDM_STATE:
             
            ADCON1 = 0x0f; // All digital pins to be able to use portA pins as outputs.
            if (PORTEbits.RE4 == 1 && isRE4Pressed == 0){
                isRE4Pressed = 1;
                toggleLed();
            }
            else if ((PORTEbits.RE4 == 0 && isRE4Pressed == 1)){
                isRE4Pressed = 0;
            }
            break;
        case TSM_STATE:
            break;
    }
}



void main(void) {
    // Set ADC Inputs
    TRISH = 0x10; // AN12 input RH4
    // Set LCD Outputs
    TRISB = 0x00; // LCD Control RB2/RB5
    TRISD = 0x00; // LCD Data  RD[4-7]
    // Configure ADC
    ADCON0 = 0x31; // Channel 12; Turn on AD Converter
    ADCON1 = 0x00; // All analog pins
    ADCON2 = 0xAA; // Right Align | 12 Tad | Fosc/32
    ADRESH = 0x00;
    ADRESL = 0x00;
    
    TRISE = 0xff;
    PORTE = 0x00;

    TRISA = 0x00;
    PORTA = 0x00;

    TRISC = 0x00;
    PORTC = 0x00;
    PORTB = 0x00;
    PORTD = 0x00;
    
    TRISJ = 0x00;
    PORTJ = 0x00;

    InitLCD();
    __delay_ms(30);

    PORTBbits.RB2 = 0;
    SendBusContents(0x0E); // Display on, cursor on, blink off.
    SendBusContents(0x06); // Turn off display shift.
    SendBusContents(0x02);
    while(1){
      button_task_RE0();
      button_task_RE1();
      button_task_RE2();
      button_task_RE3();
      button_task_RE4();
      button_task_RE5();
      handleCountDisplay();
      handleCursorXDisplay();
      handleCursorYDisplay();
    }
    return;                                
}

