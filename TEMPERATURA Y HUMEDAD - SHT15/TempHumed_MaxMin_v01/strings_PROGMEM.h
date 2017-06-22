#include <avr/pgmspace.h>

//PARAMETROS INICIALIZACION LCD
prog_char strLCD_LINEA_1[] PROGMEM = "       SISTEMA      ";
prog_char strLCD_LINEA_2[] PROGMEM = "   AUTOMATIZACION   ";
prog_char strLCD_LINEA_3[] PROGMEM = "TEMPERATURA  HUMEDAD";
prog_char strLCD_LINEA_4[] PROGMEM = "       v0.2-20161106";

//PARAMETROS INDOOR
prog_char strMarca[] PROGMEM = "CULTIBOX";
prog_char strTamano[] PROGMEM = "80x80x160";

prog_char strTipoIluminacion[] PROGMEM = "SODIO";
prog_char strWatts[] PROGMEM = "250";
prog_char strEstadoIluminacion[] PROGMEM = "ON";

//[JSON - STATUS MONITOR + PARAMETROS]
//prog_char str_JSON_MONITOREO[] PROGMEM = "{\"INDOOR\":{\"CLASE\":{\"MARCA\": \"(1)\",\"TAMANO\": \"(2)\"},\"TEMPERATURA\":{\"°C\": \"(3) °C\",\"°F\": \"(4) °F\"},\"HUMEDAD\":{\"AMBIENTE\": \"(5) %\",},\"ILUMINACION\":{\"TIPO\": \"(6)\",\"WATTS\": (7),\"ESTADO\": \"(8)\"},\"VENTILACION\":{\"INTRACCION\":{\"GENERAL\": \"ON\"},\"EXTRACCION\":{\"GENERAL\": \"ON\"}}}};";
prog_char str_JSON_MONITOREO[] PROGMEM = "{\"INDOOR\":{\"CLASE\":{\"MARCA\": \"(1)\",\"TAMANO\": \"(2)\"},\"TEMPERATURA\":{\"°C\": (3),\"°F\": (4)},\"HUMEDAD\":{\"AMBIENTE %\": (5)},\"ILUMINACION\":{\"TIPO\": \"(6)\",\"WATTS\": (7),\"ESTADO\": \"(8)\"},\"VENTILACION\":{\"INTRACCION\":{\"GENERAL\": \"ON\"},\"EXTRACCION\":{\"GENERAL\": \"ON\"}},\"RULES\":{\"R_ILUMINACION\":{\"TEST\": 0},\"R_VENTILACION\":{\"TEST\": 0}}}};";

prog_char strParamMonitoreo_1[] PROGMEM = "(1)";
prog_char strParamMonitoreo_2[] PROGMEM = "(2)";
prog_char strParamMonitoreo_3[] PROGMEM = "(3)";
prog_char strParamMonitoreo_4[] PROGMEM = "(4)";
prog_char strParamMonitoreo_5[] PROGMEM = "(5)";
prog_char strParamMonitoreo_6[] PROGMEM = "(6)";
prog_char strParamMonitoreo_7[] PROGMEM = "(7)";
prog_char strParamMonitoreo_8[] PROGMEM = "(8)";
