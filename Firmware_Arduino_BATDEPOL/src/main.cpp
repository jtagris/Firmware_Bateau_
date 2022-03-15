#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>



// INIT One Wire
#define ONE_WIRE_BUS 2 
OneWire oneWire (ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
//###################################


// Variables PID 
int Valeur_PID = 0;
int kp = 10; int PID_p = 0;
int ErreurPID = 0;

int Consigne_Temp = 60;
volatile int Temperature = 20;
//#############################

//Variables PWM
 volatile int VitessePompe = 0;
//#############################

//Variables Debit
volatile uint32_t Impulsions = 0;
volatile int CompteurTemp = 0;
//######################




void ISRImpulsions()
{
  Impulsions++;
}





void PWM_Pompe()
  {
    analogWrite(10,VitessePompe);
  }



int Regul_PID()
  {
    ErreurPID = Consigne_Temp - Temperature;
    PID_p = ErreurPID * kp;
    Valeur_PID = PID_p;

    if (Valeur_PID > 255)
    {
    Valeur_PID = 255;
    }

    if (Valeur_PID < 0)
    {
      Valeur_PID = 0;
    }
    
    VitessePompe = 255 - Valeur_PID;

    return VitessePompe;
  }



int GetTemp()
{

}




void setup()
  {
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(2), ISRImpulsions, RISING);
    Serial.println("INIT OK");

    TCCR1A = 0b00000000;
    TCCR1B = 0b00000011;

    TCNT1H = 0b10000101;
    TCNT1L = 0b11101110;
  }




void flag();
  {
    Serial.println("Test");

    Impulsions = CompteurTemp;
    Impulsions = 0;
  }



ISR (TIMER1_OVF_vect)
  {
    flag();
  }


int Debit()
{
  int flow = CompteurTemp
}

void loop()
  {

  }