
#include <Keypad.h>
#include <Wire.h>  // biblioteca respposnsavel pela comunicação I2C
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>   //Inclui a biblioteca do DS3231 Shield

LiquidCrystal_I2C lcd (0x3F,20,4);  // // 0x3F representa o endereço hexadecimal do modulo I2C alguns modulos
DS3231 clock;
RTCDateTime dt;

  
int vetor[8];
int limite = 7;
int contador =0;
int hora,minuto,segundo,dia,mes,ano;
int aux =0;

const byte ROWS = 4; //4 linhas
const byte COLS = 4; //3 colunas
//define os caracteres de cada botao
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6',},
  {'7','8','9',},
  {'*','0','#','-'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //conexão dos pinos das linhas
byte colPins[COLS] = {9,8, 7, 6}; //conexão dos pinos das colunas

//iniciliza e instancia o objeto customKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
int customKey;
// char customKey; 
 int numero;

void setup(){
  lcd.init(); 
  clock.begin();
    //clock.setDateTime(2018,07,21,21,24,00);

}
  
void loop(){
   
  // Print a message to the LCD.
  
  lcd.backlight();
  lcd.setCursor(0,2);   // assim como as biblioteas comuns para display LCD os comandos para este modulo são bem parecidos
  lcd.print("ALTERAR HORARIO:");

  lcd.setCursor(0,0);
  lcd.print(dt.day ); lcd.setCursor(2,0); lcd.print("/");
  lcd.setCursor(3,0);   
  lcd.print(dt.month); lcd.setCursor(5,0);lcd.print("/");
  lcd.setCursor(6,0); 
  lcd.print(dt.year);  

  if(dt.hour<10)
  {
    lcd.setCursor(11,0); lcd.print("O");
    lcd.setCursor(12,0); lcd.print(dt.hour);lcd.setCursor(13,0); lcd.print(":");    
  }
  else{
  lcd.setCursor(11,0);
  lcd.print(dt.hour ); lcd.setCursor(13,0); lcd.print(":");
  }
  lcd.setCursor(14,0);   
  lcd.print(dt.minute); lcd.setCursor(16,0);lcd.print(":");
  lcd.setCursor(17,0); 
  lcd.print(dt.second);

////////////////////////////////////////////////////////////////////////////////////////////
      dt = clock.getDateTime();
  
   customKey = customKeypad.getKey_int(); // comando getKey responsável por recuperar o valor do botao precionado

    if (customKey != 10) // valor 10 na comparação serve para recuperar o numero zero
    {
    numero = customKey;
    vetor[contador]=numero;
    lcd.setCursor(contador,3); 
    lcd.print(vetor[contador]);

     contador++;

    }

    
    if(contador == 5) // identifica se foram digitados todos os numeros relativos á hora e transfroma os valores no vetor para inteiros 
    {
      hora = (vetor[0]*10) + vetor[1];
      minuto = (vetor[2]*10) + vetor[3];
      segundo = (vetor[4]*10)+ vetor[5];
    }


    if((contador == limite) && (vetor[contador]== 0)) // CONDIÇÃO PARA QUE SEJA ALTERADO O HORARIO NO RTC
  { 
    lcd.clear();
   clock.setDateTime(dt.year,dt.month,dt.day,hora,minuto,segundo);
    contador =0;
  }

 
}
