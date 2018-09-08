/*
 * File:   initPIC.h
 * Autor: Jose Pablo Guerra
 * 
 *=============================================
 *               DESCRIPCION:
 *=============================================
 * 
 * LIBRERIA PARA CONFIGURACION DEL PIC. 
 * INCLUYE CONFIGURACION DEL OSCILADOR INTERNO DE 4MHz Y 8MHz
 * ESTA CONFIGURACION ESTA PARA UTILIZARSE EN EL PIC16F887
 * 
 * ADEMAS INCLUYE:
 * 
 * CONFIGURACION DE LOS PUERTOS
 * TIMER 1 Y 0
 * ADC
 * 
 * ============================================
 *
 * Creado el 8 de septiembre, 2018, 11:51 AM
 * *******************************************************************************
 * Rev.         Día            Comebtarios
 *   v1.0.0      8/09/2018      Falta configurar TMR0 y agregar otras librerias
 *   v2.0.0      8/09/2018      Timer0 configurado, aun faltan otras librerias
 ******************************************************************************/

//***************************
//Declaracion de constantes
//***************************
#define LOW 0b11011100 //TMR1L
#define HIGH 0b00001011 // TMR1H
//en conjunto estas anteriores determinan el valor inicial del Timer1 para utilizarse como temporizador
//puede usarse la constante valTMR1 para declarla como entero en un solo registro. 

#define valTMR1 0;

#define ConfigTMR1 0b0011001
#define valTMR0 0 //valor inicial del Timer0 para temporizador

//***************************
//Inicializacion de puertos, cambiar de ser necesario.
//***************************

void initPorts(void){
    ANSEL = 0;
    ANSELH = 0;
    PORTB = 0;
    PORTC = 0;
    PORTA = 0;
    PORTD = 0;
    PORTE = 0;
    TRISD = 0;
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
}

//***************************
//           TIMERS
//***************************
void initTMR1(void){
    
    T1CON = ConfigTMR1; //Configuracion inicial del TMR1
    TMR1H=HIGH;     // Registros para control de tiempo, delay de 1s.
    TMR1L=LOW;   
    
//    TMR1 = valTMR1; descomentar para utilizar un valor entero y no los dos registros de arriba.
    
    TMR1IE=1;       //Habilita interrupciones
    GIE=1;          //Enable Global Interrupt
    PEIE=1;         //Enable the Peripheral Interrupt
    TMR1ON = 1;     //Start Timer1    
}

void initTMR0(void){
    OPTION_REGbits.T0CS=0;//El timer0 actuara como temporizador
    OPTION_REGbits.PSA=0;//El prescaler se le asigna al timer0
    OPTION_REGbits.PS2=1;//con estos 3 bits a 1
    OPTION_REGbits.PS2=1;//se elige el prescaler
    OPTION_REGbits.PS2=1;//de 256
    
    INTCONbits.GIE=1;//habilita las interrupciones
    INTCONbits.TMR0IE=1;//habilita el uso de la interrupción tmr0 PIC 
                        //por desborde
    INTCONbits.TMR0IF=0;//a 0 para que detecte la interrupción tmr0 PIC
                        //por desborde
    
    TMR0= valTMR0;//se inicializa a este valor para obtener 50ms de temporización
}
//***************************
//    OSCILADORES INTERNOS
//***************************
void OSC8() {
    IRCF2 = 1;
    IRCF1 = 1;
    IRCF0 = 0; //Oscilador de 8 MHZ.

    OSTS = 0; //utilizo oscilador interno

    HTS = 1; // OSCILADOR ESTABLE
    SCS = 1; // OSCILADOR INTERNO PARA EL CLOCK DEL SISTEMA
}

//----------
void OSC4(void){
    
    IRCF0 = 0;  //FRECUENCIA DE OSCILACION
    IRCF1 = 1;
    IRCF2 = 1;
    OSTS = 0;   //OSCILADOR INTERNO
    HTS = 1;    //OSCILADOR ESTABLE
    SCS = 1;    //OSCILADOR INTERNO
    return;
}

//***************************
//        MODULO ADC
//***************************

void ADC(void){
    
    ADFM = 0;       //JUSTIFICADO A LA IZQUIERDA
    VCFG1 = 0;      //VCC COMO REFERENCIA DE VOLTAJE -
    VCFG0 = 0;      //VDD COMO REFERENCIA DE VOLTAJE +
    
    ADCS0 = 0;      //ADC CONVERSION CLOCK SELECT BITS
    ADCS1 = 1;
    
    CHS0 = 1;       //CONFIGURO AN1 COMO MI PIN ANALOGICO
    CHS1 = 0;
    CHS2 = 0;
    CHS3 = 0;
    
    ADON = 1;       //HABILITAMOS EL MODULO ADC
    
    return;
}
