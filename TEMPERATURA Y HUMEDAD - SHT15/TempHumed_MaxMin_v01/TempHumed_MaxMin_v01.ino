#include <Time.h>

/*
 * COMPILAR CON IDE Arduino 1.0.3
 */

#include "lcd_chars.h"
#include "gets_PROGMEM.h"
#include "strings_PROGMEM_RW.h"
#include <SoftwareSerial.h>
#include <stdlib.h>
#include <avr/pgmspace.h>

//SENSOR
#include <SHT1x.h>
//LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

SoftwareSerial RFSerial(10, 11); // RX, TX
#define RF_SET_HC11_12 9

//MACROS: no gasta RAM pero si memoria de Programa y además, no utiliza pila de llamadas.
#define PGMSTR(x) (__FlashStringHelper*)(x)
#define RFSERIAL_PRINT(str){ RFSerial.print(str); }
#define RFSERIAL_PRINTLN(str){ RFSerial.println(str); }

//SENSOR
// Specify data and clock connections and instantiate SHT1x object
#define dataPin  A3
#define clockPin A2
SHT1x SHT_15(dataPin, clockPin);

int vPrecision_Decimal_RealTime = 2;
int vPrecision_Decimal_MinMax = 2;
float vTemp_Min = 500.0000;
float vTemp_Max = 0.0000;
float vHume_Min = 500.0000;
float vHume_Max = 0.0000;

float vTemp_Control_Extractor = 27;

//LCD
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

#define  LED_OFF  0
#define  LED_ON  1
LiquidCrystal_I2C lcd(0x27,20,4);  // Configura la direcci�n del LCD a 0x27 para pantallas de 20Caracteres y 4 lineas
LiquidCrystal_I2C lcd_Secundario(0x26,20,4);  // Configura la direcci�n del LCD a 0x27 para pantallas de 20Caracteres y 4 lineas

//---------------------
#define AND    &&
#define OR     ||
#define NOT    !

unsigned long Temporizador_1;
unsigned char Intermitencia_1;
unsigned char Activacion = 1;
//---------------------

//------------
//TIEMPO
time_t t;

//RELE - EXTRACTOR

#define PIN_RELE 12

char message_buff[350];

//PARAMETROS INDOOR
/*
String vMarca = "CULTIBOX";
String vTamano = "80x80";

String vIluminacion_Tipo = "SODIO";
String vIluminacion_Watts = "250";
String vIluminacion_Estado = "ON";
*/

String pubStringJSON;

void setup()
{ 
  Serial.begin(19200);
  SETUP_RF_HC11_12();
  
  setTime(21,22,00,27,06,2016);
  
  pubStringJSON = getJSON_MONITOREO();
  
  INICIALIZA_LCD();
  PRINT_INICIANDO_SISTEMA();
  INICIALIZA_HARDWARE();
}

void SETUP_RF_HC11_12()
{
  pinMode(RF_SET_HC11_12, OUTPUT);
  delay(100);
  digitalWrite(RF_SET_HC11_12, HIGH);
  delay(100);
  RFSerial.begin(19200);
}

void loop()
{  
  t = now();
  INFORMACION_MONITOR();
  delay(1000);
}

void INFORMACION_MONITOR()
{
    // Read values from the sensor
    float temp_c = SHT_15.readTemperatureC();
    float temp_f = SHT_15.readTemperatureF();
    float humedad = SHT_15.readHumidity();
    
    char charVal_TempC[5]; //temporarily holds data from vals 
    char charVal_TempF[5]; //temporarily holds data from vals 
    char charVal_Hum[5]; //temporarily holds data from vals 
    
    dtostrf(temp_c, 2, 2, charVal_TempC);
    dtostrf(temp_f, 2, 2, charVal_TempF);
    dtostrf(humedad, 2, 2, charVal_Hum);
    
    String stringVal = "";
    
    pubStringJSON = getJSON_MONITOREO();
    //Serial.println(pubStringJSON);

    pubStringJSON.replace(getMONITOREO_PARAM_MARCA(), String(getMARCA_INDOOR()));
    pubStringJSON.replace(getMONITOREO_PARAM_TAMANO(), String(getTAMANO_INDOOR()));

    stringVal = "";
    for(int i=0;i<sizeof(charVal_TempC);i++)
    {
      stringVal += charVal_TempC[i];
    }
    //Serial.println(String(stringVal));
    pubStringJSON.replace(getMONITOREO_PARAM_TEMP_C(), String(stringVal));

    stringVal = "";
    for(int i=0;i<sizeof(charVal_TempF);i++)
    {
      stringVal += charVal_TempF[i];
    }
    //Serial.println(String(stringVal));
    pubStringJSON.replace(getMONITOREO_PARAM_TEMP_F(), String(stringVal));
    
    stringVal = "";
    for(int i=0;i<sizeof(charVal_Hum);i++)
    {
      stringVal += charVal_Hum[i];
    }
    //Serial.println(String(stringVal));
    pubStringJSON.replace(getMONITOREO_PARAM_HUMEDAD(), String(stringVal));

    pubStringJSON.replace(getMONITOREO_PARAM_ILUMINACION_TIPO(), String(getTIPO_ILUMINACION_INDOOR()));
    pubStringJSON.replace(getMONITOREO_PARAM_ILUMINACION_WATTS(), getPOTENCIA_FOCO_INDOOR());
    pubStringJSON.replace(getMONITOREO_PARAM_ILUMINACION_ESTADO(), String(getESTADO_ILUMINACION_INDOOR()));
    
    //Serial.println(pubStringJSON);
    
    //RFSerial.print(pubStringJSON);
    RFSERIAL_PRINT(pubStringJSON)
    
    //RFSerial.flush();
    
    /*
    String aa = "{\"INDOOR\":{\"Tamaño\": \"80x80x160\", ";
    //aa.toCharArray(message_buff, aa.length()+1);
    
    RFSerial.print(aa);
    RFSerial.print("\"Temperatura\": {\"");
    RFSerial.print(charVal_TempC);
    RFSerial.print(" °C\", ");
    RFSerial.print(charVal_TempF);
    RFSerial.print(" °F | ");
    RFSerial.print("Humedad: ");
    RFSerial.print(charVal_Hum);
    RFSerial.print(" %");
    RFSerial.print(";");
    */
    
    /*
    RFSerial.print("[FOCO 250W]: ON;");
    RFSerial.print("[EXTRACTOR]: ON;");
    RFSerial.print("[INTRACTOR]: ON;");
    */
    /*
    RFSerial.print("{");
    RFSerial.print("\"INDOOR\":{");
    RFSerial.print("\"CLASE\":{");
    RFSerial.print("\"MARCA\": \"CULTIBOX\",");
    RFSerial.print("\"TAMANO\": \"80x80\"");
    RFSerial.print("},");
    RFSerial.print("\"TEMPERATURA\":{");
    RFSerial.print("\"°C\": \"");
    RFSerial.print(temp_c);
    RFSerial.print(" °C\",");
    RFSerial.print("\"°F\": \"");
    RFSerial.print(temp_f);
    RFSerial.print(" °F\"");
    RFSerial.print("},");
    RFSerial.print("\"HUMEDAD\":{");
    RFSerial.print("\"AMBIENTE\": \"");
    RFSerial.print(humedad);
    RFSerial.print(" %\",");
    RFSerial.print("},");
    RFSerial.print("\"ILUMINACION\":{");
    RFSerial.print("\"TIPO\": \"Sodio\",");
    RFSerial.print("\"WATTS\": 250,");
    RFSerial.print("\"ESTADO\": \"ON\"");
    RFSerial.print("},");
    RFSerial.print("\"VENTILACION\":{");
    RFSerial.print("\"INTRACCION\":{");
    RFSerial.print("\"GENERAL\": \"ON\"");
    RFSerial.print("},");
    RFSerial.print("\"EXTRACCION\":{");
    RFSerial.print("\"GENERAL\": \"ON\"");
    RFSerial.print("}");
    RFSerial.print("}");
    RFSerial.print("}");
    RFSerial.print("};");
    */
    
    //-------------------------------------------------------
    LCD_TEMPERATURA_C(0, temp_c);

    LCD_HUMEDAD(1, humedad);
    LCD_STATUS_EXTRACCION(0);

    CALCULO_TEMPERATURA_MIN_MAX(2, temp_c);
    CALCULO_HUMEDAD_MIN_MAX(3, humedad);
    //-------------------------------------------------------
    
}

void LCD_TEMPERATURA_C(int pLinea_LCD, double pTemp_C)
 {
   lcd.setCursor(0,pLinea_LCD);
   lcd.print("Te:");
   //lcd.setCursor(9,pLinea_LCD);
   lcd.print(pTemp_C, vPrecision_Decimal_RealTime); //vPrecision_Decimal_RealTime
   lcd.setCursor(8,pLinea_LCD);
   lcd.printByte(1);
   lcd.print("C");   
 }
 
  void LCD_TEMPERATURA_F(int pLinea_LCD, double pTemp_F)
 {
   lcd.setCursor(0,pLinea_LCD);
   lcd.print("Te:");
   //lcd.setCursor(9,pLinea_LCD);
   lcd.print(pTemp_F, vPrecision_Decimal_RealTime); //
   lcd.setCursor(8,pLinea_LCD);
   lcd.printByte(1);
   lcd.print("F");   
 }
 
 void LCD_HUMEDAD(int pLinea_LCD, double pHumedad)
 {
   lcd.setCursor(0,pLinea_LCD);
   lcd.print("Hu:");
   lcd.print(pHumedad, vPrecision_Decimal_RealTime); //vPrecision_Decimal_RealTime
   //lcd.print(pHumedad, DEC);
   lcd.setCursor(8,pLinea_LCD);
   lcd.print(" %");
 }
 
 void CALCULO_TEMPERATURA_MIN_MAX(int pLinea_LCD, float pTemp_C)
 {
   //TEMPERATURA °C - MINIMA
   if (pTemp_C < vTemp_Min)
   {
     vTemp_Min = pTemp_C;
     lcd.setCursor(0,pLinea_LCD);
     lcd.print("T");
     lcd.printByte(2);
     lcd.print(":");
     lcd.print(vTemp_Min, vPrecision_Decimal_MinMax); //lcd.print(pTemp_C, DEC);
     lcd.printByte(0);
   }
   //TEMPERATURA °C - MAXIMA
   if (pTemp_C > vTemp_Max)
   {
     vTemp_Max = pTemp_C;
     lcd.setCursor(11,pLinea_LCD);
     lcd.print("T");
     lcd.printByte(3);
     lcd.print(":");
     lcd.print(vTemp_Max, 2);
     lcd.printByte(0);
   }
   
   if (pTemp_C >= vTemp_Control_Extractor)
   {
      ENCENDER_EXTRACCION(HIGH);
   } 
   else if (pTemp_C < vTemp_Control_Extractor)
   {
      ENCENDER_EXTRACCION(LOW);
   }
 }
 
 void CALCULO_HUMEDAD_MIN_MAX(int pLinea_LCD, float pHumedad)
 {
   //% HUMEDAD - MINIMA
   if (pHumedad < vHume_Min)
   {
     vHume_Min = pHumedad;
     lcd.setCursor(0,pLinea_LCD);
     lcd.print("H");
     lcd.printByte(2);
     lcd.print(":");
     lcd.print(vHume_Min, vPrecision_Decimal_MinMax);
     lcd.print("%");
   }
   //% HUMEDAD - MAXIMA
   if (pHumedad > vHume_Max)
   {
     vHume_Max = pHumedad;
     lcd.setCursor(11,pLinea_LCD);
     lcd.print("H");
     lcd.printByte(3);
     lcd.print(":");
     lcd.print(vHume_Max, 2);
     lcd.print("%");
   }
 }

void LCD_STATUS_EXTRACCION(int pLinea_LCD)
{
   lcd.setCursor(11,pLinea_LCD);
   lcd.printByte(7);
   lcd.print(vTemp_Control_Extractor, 0);
   lcd.print(" Fan");
   lcd.setCursor(19,pLinea_LCD);
   lcd.printByte(6);
}

void INICIALIZA_LCD()
{
  //LCD - PRINCIPAL
  lcd.init(); // Inicializa LCD
  lcd.clear(); //Limpia todo el texto del LCD
  //lcd.setBacklight(LED_ON);
  lcd.setBacklight(LED_OFF);
  delay(100);
  
  lcd.createChar(0, Char_Grados_Izq);
  lcd.createChar(1, Char_Grados_Der);
  lcd.createChar(2, Char_ArrowDOWN);
  lcd.createChar(3, Char_ArrowUP);
  lcd.createChar(4, Char_Loading);
  lcd.createChar(5, Char_ON_Light);
  lcd.createChar(6, Char_OFF_Light);
  lcd.createChar(7, Char_ArrowUpDown);
  
  //Enciente la Retroiluminacion del LCD por I2C
  lcd.backlight(); //Enciende la retroiluminacion 
}

void INICIALIZA_HARDWARE()
{
  //INICIALIZA HARDWARE
  pinMode(PIN_RELE, OUTPUT);
  digitalWrite(PIN_RELE, HIGH);
  delay(1000);
  digitalWrite(PIN_RELE, LOW); 
}

void ENCENDER_EXTRACCION(int command)
{
  if(command == 0) //FAN OFF
  {
    digitalWrite(PIN_RELE, LOW);
    lcd.setCursor(19,0);
    lcd.printByte(6);
    
  } else if (command == 1) //FAN ON
  {
    digitalWrite(PIN_RELE, HIGH);
    lcd.setCursor(19,0);
    lcd.printByte(5);
  }
  
}

void PRINT_INICIANDO_SISTEMA()
{  
  
  lcd.setCursor(0,0);
  lcd.print(getLCD_LINEA_1());
  lcd.setCursor(0,1);
  lcd.print(getLCD_LINEA_2());
  lcd.setCursor(0,2);
  lcd.print(getLCD_LINEA_3());
  lcd.setCursor(0,3);
  lcd.print(getLCD_LINEA_4());
  lcd.setCursor(0,3);
  for(int i = 1; i <= 20; i++)
  {
    lcd.printByte(4);
    delay(200);
  }
  
  delay(1000);
  
  lcd.clear();
}

//------------------------
//TEMPORIZADORES

//-------------------------------------------------
/*
La primera función que vamos a escribir se llamará iniTemp() y se encarga de arrancar un cronómetro 
(reloj secundario) indicando el tiempo que deseamos que se cuente. 

La segunda función será chkTemp() y nos dirá los milisegundos que  restan para que el 
cronómeto alcance el tiempo deseado.
*/
//iniTemp() Function
//Arranca un temporizador durante un numero de milisegundos
//Modo de Uso: iniTemp( &lT1, 1000);
void iniTemp(unsigned long *Cronometro, unsigned long Time)
{
  *Cronometro = millis() + Time; //Presición de Milisegundos
  //*Cronometro = micros() + Time; //Presición de Microsegundos
}

// chkTemp() Function.
// Devuelve en unidades de 1ms el tiempo que resta del temporizador
// Modo de Uso: nVar1 = iniTemp( &lT1 );
unsigned long chkTemp(unsigned long *Cronometro)
{
  if( *Cronometro > millis() )
  {
     return (*Cronometro - millis() ); //Presición de Milisegundos
     //return (*Cronometro - micros() ); //Presición de Microsegundos
  } 
  else
  {
     return 0; 
  }
}


/*
Antes de utilizar estas dos funciones y ver con detalle cómo están escritas, 
vamos a construir una tercera, a la que llamaremos parpadeo() y que utiliza las 
dos anteriores para generar una intermitencia de una frecuencia determinada. 
Su código es el siguiente:
*/

// Parpadeo() Function.
// Parpadeo
// Modo de Uso: Parpadeo( input, 1000, &lT1, &salida_parpadeo)

void Parpadeo( unsigned char in, 
               unsigned long tiempo, 
               unsigned long *Cronometro, 
               unsigned char *out)
{
   if ( in AND NOT ( (chkTemp(Cronometro) > 0 ? 1 : 0 ) ) )
   {
      iniTemp( Cronometro, tiempo );
      *out = NOT *out;
   } 
   else if( NOT in )
   {
      *out = 0; 
   }
}

void Pulso(unsigned char Task, 
           unsigned long Time, 
           unsigned long *AuxT1, 
           unsigned char *AuxTm1, 
           unsigned char *Out)
{
  if (Task AND NOT *AuxTm1)
  {
     iniTemp( AuxT1, Time );
     *AuxTm1 = 1; 
  }
  else if (NOT Task AND *AuxTm1)
  {
     *AuxTm1 = 0; 
  }
  *Out = ( ( chkTemp( AuxT1 ) > 0 ? 1 : 0 ) ) AND Task;
}
