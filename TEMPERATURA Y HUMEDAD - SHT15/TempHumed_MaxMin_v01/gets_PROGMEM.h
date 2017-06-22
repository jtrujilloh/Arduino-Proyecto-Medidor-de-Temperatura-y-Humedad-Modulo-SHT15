#include "strings_PROGMEM.h"

char buffer[350];

//PARAMETROS INICIALIZACION LCD
char* getLCD_LINEA_1() {
  strcpy_P(buffer,(char*)strLCD_LINEA_1);
  return buffer;
}
char* getLCD_LINEA_2() {
  strcpy_P(buffer,(char*)strLCD_LINEA_2);
  return buffer;
}
char* getLCD_LINEA_3() {
  strcpy_P(buffer,(char*)strLCD_LINEA_3);
  return buffer;
}
char* getLCD_LINEA_4() {
  strcpy_P(buffer,(char*)strLCD_LINEA_4);
  return buffer;
}

//PARAMETROS INDOOR
char* getMARCA_INDOOR() {
  strcpy_P(buffer,(char*)strMarca);
  return buffer;
}
char* getTAMANO_INDOOR() {
  strcpy_P(buffer,(char*)strTamano);
  return buffer;
}

char* getTIPO_ILUMINACION_INDOOR() {
  strcpy_P(buffer,(char*)strTipoIluminacion);
  return buffer;
}
char* getPOTENCIA_FOCO_INDOOR() {
  strcpy_P(buffer,(char*)strWatts);
  return buffer;
}
char* getESTADO_ILUMINACION_INDOOR() {
  strcpy_P(buffer,(char*)strEstadoIluminacion);
  return buffer;
}


//[Get's JSON]
char* getJSON_MONITOREO() {
  strcpy_P(buffer,(char*)str_JSON_MONITOREO);
  return buffer;
}
char* getMONITOREO_PARAM_MARCA() {
  strcpy_P(buffer,(char*)strParamMonitoreo_1);
  return buffer;
}
char* getMONITOREO_PARAM_TAMANO() {
  strcpy_P(buffer,(char*)strParamMonitoreo_2);
  return buffer;
}
char* getMONITOREO_PARAM_TEMP_C() {
  strcpy_P(buffer,(char*)strParamMonitoreo_3);
  return buffer;
}
char* getMONITOREO_PARAM_TEMP_F() {
  strcpy_P(buffer,(char*)strParamMonitoreo_4);
  return buffer;
}
char* getMONITOREO_PARAM_HUMEDAD() {
  strcpy_P(buffer,(char*)strParamMonitoreo_5);
  return buffer;
}

char* getMONITOREO_PARAM_ILUMINACION_TIPO() {
  strcpy_P(buffer,(char*)strParamMonitoreo_6);
  return buffer;
}
char* getMONITOREO_PARAM_ILUMINACION_WATTS() {
  strcpy_P(buffer,(char*)strParamMonitoreo_7);
  return buffer;
}
char* getMONITOREO_PARAM_ILUMINACION_ESTADO() {
  strcpy_P(buffer,(char*)strParamMonitoreo_8);
  return buffer;
}
