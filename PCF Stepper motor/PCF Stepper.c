/*****************************************************************************/
// C?digo para realizar escritura digital en el PCF8574AP, esto para controlar
// dos motores a paso bipolares
// Desarrollado por: Gustavo Trejo -Agosto de 2021
/*****************************************************************************/
#INCLUDE<16F887.h>
#DEVICE ADC=10
#FUSES XT,PUT,NOPROTECT,BROWNOUT,NOLVP,WDT
#USE delay(internal=8000000)
#USE I2C(MASTER, SDA=PIN_C4, SLOW, SCL=PIN_C3, NOFORCE_SW)
#use standard_io(c)

#BYTE PORTB=6
#BYTE OPTION_REG=0X81

#DEFINE M1D PORTB,0
#DEFINE M1I PORTB,1
#DEFINE M2D PORTB,2
#DEFINE M2I PORTB,3


/***************************Variables globales********************************/
int8 btns1=0;
int8 btns2=0;
int8 after1=0;
int8 after2=0;

void main(){
set_tris_b(0b1111111);
setup_wdt(WDT_2304MS); //config del watchdog cada 2.304 segundos
bit_clear(OPTION_REG,7);
while(true){

   //motor 1
   if(!bit_test(M1D)&&bit_test(M1I)){ //derecha
      btns1=7;
      after1=3;
   }
   else if(!bit_test(M1I)&&bit_test(M1D)){ //izquierda
      btns1=5;
      after1=1;
   }
   else{ //off
      btns1=8;
      after1=8;
   }
   
   //motor 2   
   if(!bit_test(M2D)&&bit_test(M2I)){ //derecha
      btns2=7;
      after2=3;
   }
   else if(!bit_test(M2I)&&bit_test(M2D)){ //izquierda
      btns2=5;
      after2=1;
   }
   else{ //off
      btns2=8;
      after2=8;
   }
   
   i2c_start(); // envio de datos
   i2c_write(0x70); 
   i2c_write((btns1*16)+btns2);//1111*16=11111010
   delay_ms(1);
   i2c_write((after1*16)+after2);
   i2c_stop();
   restart_wdt();
}
}
