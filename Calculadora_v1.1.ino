#include "expression_parser.h"
#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Keypad.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(10, 11, 12);
File archivo;

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

int n_filas_1=0;
int n_columnas_1=0;

const byte ROWS = 9;
const byte COLS = 6;
char hexaKeys[ROWS][COLS] = {
  {'S','A','U','R','M','O'},
  {'_','_','L','D','_','_'},
  {'/','r','_','^','ñ','l'},
  {'_','_','h','s','c','t'},
  {'_','_','(',')','_','_'},
  {'7','8','9','d','a','_'},
  {'4','5','6','x','%','_'},
  {'1','2','3','+','-','_'},
  {'0','.','_','_','=','_'}
};
byte rowPins[ROWS] = {0,1,13,9,6,5,3,2,11}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {18,19,20,21,22,23}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() {
  Serial.begin(9600);
  while (!Serial) {;}
  if (!SD.begin(4)) {;}
  display.begin();
  display.setContrast(50);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);

  iniciar_sd(1);
  n_filas_columnas();
  leer_sd(0,0);
  
  Serial.print(parse_expression("1+2"));
}

void loop() {
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }
}

void iniciar_sd(int n_archivo){
  String n_archivo_string = String(n_archivo);
  n_archivo_string=n_archivo_string+".txt";
  archivo=SD.open(n_archivo_string);
}

void n_filas_columnas(){
  archivo.seek(0);
  int caracter=0;
  int i=0;
  while(caracter!=13){
    caracter=archivo.read(); 
    i++;
  }
  n_columnas_1=i-1;
  n_filas_1=archivo.size()/(n_columnas_1+2);
}


void leer_sd(int x,int y){
  int leido=0;
  display.clearDisplay();
  for(int i=0;i<48;i++){
    archivo.seek(x+(y+i)*(n_columnas_1+2));
    for(int j=0;j<21;j++){
      leido=archivo.read();
      if(leido==48){}
      if(leido==49){display.drawPixel(j*4+3,i, BLACK);}
      if(leido==50){display.drawPixel(j*4+2,i, BLACK);}
      if(leido==51){display.drawPixel(j*4+3,i, BLACK);display.drawPixel(j*4+2,i, BLACK);}
      if(leido==52){display.drawPixel(j*4+1,i, BLACK);}
      if(leido==53){display.drawPixel(j*4+1,i, BLACK);display.drawPixel(j*4+3,i, BLACK);}
      if(leido==54){display.drawPixel(j*4+1,i, BLACK);display.drawPixel(j*4+2,i, BLACK);}
      if(leido==55){display.drawPixel(j*4+3,i, BLACK);display.drawPixel(j*4+2,i, BLACK);display.drawPixel(j*4+1,i, BLACK);}
      if(leido==56){display.drawPixel(j*4,i, BLACK);}
      if(leido==57){display.drawPixel(j*4,i, BLACK);display.drawPixel(j*4+3,i, BLACK);}
      if(leido==65){display.drawPixel(j*4,i, BLACK);display.drawPixel(j*4+2,i, BLACK);}
      if(leido==66){display.drawPixel(j*4,i, BLACK);display.drawPixel(j*4+3,i, BLACK);display.drawPixel(j*4+2,i, BLACK);}
      if(leido==67){display.drawPixel(j*4,i, BLACK);display.drawPixel(j*4+1,i, BLACK);}
      if(leido==68){display.drawPixel(j*4,i, BLACK);display.drawPixel(j*4+3,i, BLACK);display.drawPixel(j*4+1,i, BLACK);}
      if(leido==69){display.drawPixel(j*4,i, BLACK);display.drawPixel(j*4+1,i, BLACK);display.drawPixel(j*4+2,i, BLACK);}
      if(leido==70){display.drawPixel(j*4,i, BLACK);display.drawPixel(j*4+1,i, BLACK);display.drawPixel(j*4+2,i, BLACK);display.drawPixel(j*4+3,i, BLACK);}
  }
}
display.display();
}

  
  
  
  
  
  
  
  
  
  
  
  

