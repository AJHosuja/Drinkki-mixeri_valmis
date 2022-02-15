#include <Wire.h> // Kirjasto mitä käytetään
#include <LiquidCrystal_I2C.h> // Kirjasto mitä käytetään
#include <Keypad.h> // Kirjasto mitä käytetään

#define Password_Length 5 // salasanan pituus 4 merkkiä
char z;
//void valinnat();
char Data[Password_Length]; // määritetään pin koodin pituus eli 4 merkkiä
byte data_count = 0; // nollataan datacount
void clearData(); // aliohjelma
int esp = 0; // muuttujia paljon
int q = 0;
int y = 0;
int k = 0;
int avain = 0;
int o = 1;
int i = 1;
int juom1;
int juom2;
int arvo1, arvo2;
char key;
const byte ROWS = 4; //pin koodin rivit
const byte COLS = 4; // sarakkeet
char keys[ROWS][COLS] = { // määritetään taulukko pin koodille
  
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; //pinni paikat arduinolla
byte colPins[COLS] = {6,7,8,9}; //

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );// määritetään keypad
LiquidCrystal_I2C lcd(0x27, 16, 2); // näyttö

// Vaa'an Määritykset alkaa
#include "HX711.h"  
#define LOADCELL_DOUT_PIN  10  // pinnit mihin arduino menee.
#define LOADCELL_SCK_PIN  11

HX711 scale;

float calibration_factor = (198880.00 / 0.45359237) / 1000.00;  //Vaa'an kalibrointi kerroin, jotta ulostulo on grammoina
int testi=0;
float paino;
int x=0;
int ohjaus=0;
int tilaus=0;
char valinta;

int P1=1;
int P1Ohjaus=0;

int P2=1;
int P2Ohjaus=0;

int P3=1;
int P3Ohjaus=0;

int P4=1;
int P4Ohjaus=0;

int P12apu=0;

int vodka;
int rommi;
int cola;
int energiajuoma;

// Vaa'an Määritykset loppuu


void setup(){
  Serial.begin(9600); // serial asennetaan
 
  lcd.begin(); // määritetään lcd näyttö
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  pinMode(23, OUTPUT); // vodka // pinnit
  pinMode(24, OUTPUT); // energiajuoma
  pinMode(25, OUTPUT); // Coca-cola
  pinMode(26, OUTPUT); // Rommi
  digitalWrite(23, HIGH); // nostetaan pinnit yläasentoon jolloin pumput ei toimi
  digitalWrite(24, HIGH);
  digitalWrite(25, HIGH);
  digitalWrite(26, HIGH);

// Vaa'an Määritykset alkaa

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare(); //Taaraa vaa'an
  scale.set_scale(calibration_factor);

  paino = scale.get_units();
// Vaa'an Määritykset loppuu
  
}
  
void loop(){


  lcd.setCursor(0,0);
  lcd.print("Anna PIN koodi"); // kysytään PIN koodia

  char customKey = keypad.getKey(); //ottaa numeron pini levyltä tallentaa
   if (customKey) {
    Data[data_count] = customKey;   // tallentaa pinkoodia aina Data[] muuttjaan kunnes se on 4 numeroinen
    lcd.setCursor(data_count, 1);
    lcd.print(Data[data_count]);
    data_count++;
  }
  if (data_count == Password_Length - 1) { // kun pin on 4 numeroinen

    
    Serial.print(Data); // printtaa pin koodin serialiin josta esp 32 lukee sen
    lcd.clear();
    esp = 0;
    q = 0;
    y = 0;
    while (esp == 0) {  // while looppi jolla saadaan ohjelma pysymään kiinni
      
 lcd.setCursor(0, 0);
 lcd.print("Odottaa...."); // odottaa tietoa esp32
 if ( Serial.available() == 1 ) {  // kun tietosaadaan 
 String pin = Serial.readString(); // se tallennetaan
 y = pin.toFloat(); // muutetaan floateiksi
}
        
if (y == 1) { // jos saadaan arvo 1 eli käyttäjä löytyi 

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Hei ");
lcd.setCursor(0,1);
lcd.print("kayttaja!");
delay(1500);
avain = 1;

  while(avain==1){  // käsketään valita juoma
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Valitse juoma");
    lcd.setCursor(0,1);
    lcd.print("1,2,3,4?");
      k = 0;

    while(k==0){  // while loopilla pysäytetään ohjelma
    key = 0;
    key = keypad.getKey(); 
    if(key!=0){ // ku käyttäjä on antanut juomansa while loop avataan
          k++;
          }
     }
  if (key =='1'){ // juoma 1
    lcd.clear();  // tyhjentää näytön
    lcd.setCursor(0,0); // Lisää kursorin 0,0 kohtaan
    lcd.print("Valitsit juoman");
    lcd.setCursor(0,1);
    lcd.print("1:");

    pumppujenOhjaus(key); // lähettää valitun juoman aliohjelmaan nimeltä  pumppujenOhjaus. Samat toiminnot on kaikilla juomavalinnoilla.
    avain++;

  }
  else if (key =='2'){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Valitsit juoman");
    lcd.setCursor(0,1);
    lcd.print("2:");

    pumppujenOhjaus(key);
    avain++;  
  }
  else if (key =='3'){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Valitsit juoman");
    lcd.setCursor(0,1);
    lcd.print("3:");

    pumppujenOhjaus(key);
    avain++;
   
    
  }
  else if (key =='4'){
        lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Valitsit juoman");
    lcd.setCursor(0,1);
    lcd.print("4:");
    pumppujenOhjaus(key);
    avain++;
  }

  else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.println("Yrita uudestaan");
    delay(2500);
      }
  
  
  }
        
 lcd.clear();
 esp++;
           }

if (y == 2) { // jos esp32 moduuli antaa 2 eli käyttäjää ei löydy. Mennään alkuun 
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Kayttajaa ei");
            lcd.setCursor(0,1);
            lcd.print("loydy");
            delay(5000);
            esp++;
             
            }} 
      clearData(); // Tyhjennetään tallennettu pin data jolloin ohjelma voi aloittaa alusta.
      lcd.clear(); 
    }
    
  }


void pumppujenOhjaus(char tilaus){ // Char tilaus on juoman numero
  

          if (tilaus == '1' || tilaus == '2'  || tilaus == '3' || tilaus == '4') { // jos juoma on joku 1-4 se tarvii databasesta kertoimen
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("valmistetaan");
            lcd.setCursor(0,1);
            lcd.print("juomaa: "); 
            lcd.print(tilaus);
            lcd.print("....");
           Serial.print(tilaus); // lähettää juoman tiedot mistä haluamme tietoa
              valinta = tilaus;
              int whilelooppi2 = 0;
 
              
            
               while (whilelooppi2 == 0) {       // pysäyttää ohjelman kunnes lukee takaisin saadun kertoimen      
                if (Serial.available() > 0){ // kunnes serialissa on luettavaa
                  String juom1 = Serial.readString(); // lukee serialin tallentaa sen stringiksi 
                  int juom2 = juom1.toInt(); // muutetaan int muotoon
                   arvo1 = juom2; // juoman kerroin on arvo1
                   delay(1000);
                  whilelooppi2++; // puretaan while looppi
                
                }
               }
               }

  
  if (valinta == '1'){ // jos valitaan juoma 1 määritellään mitkä pumput saa olla käynnissä
    ohjaus = 1; // laitetaan ohjaus päälle
    P1Ohjaus = 1; // Rommi
    P2Ohjaus = 0; // Vodka
    P3Ohjaus = 1; // Coca-Cola
    P4Ohjaus = 0; // Energiajuoma
    x = 2;
    scale.tare(); //Taarataan vaaka
   rommi = 50;  //määritetään rommin paino 
   rommi = rommi / 5; // Rommi asetetaan 10grammaksi
   rommi = rommi * arvo1; // Esp32 moduulilta saatu kerroin kerrotaan 10g. jolloin saadaan rommin todellinen paino
   cola = 225 - rommi; // colan määrä on 225 - rommin määrä jolloin juomasta tulee 225g
    // SAMAT komentit kaikkiin valintoihin

  }
  
  else if (valinta == '2'){
   ohjaus = 1;
   P1Ohjaus = 0;  // Rommi
   P2Ohjaus = 1;  // Vodka
   P3Ohjaus = 0;  // Coca-Cola
   P4Ohjaus = 1;  // Energiajuoma
   x = 2;
   scale.tare(); 
   vodka = 50;
   vodka = vodka / 5;
   vodka = vodka * arvo1;
   energiajuoma = 225 - vodka;

  }
  
  else if (valinta == '3'){
   ohjaus = 1;
   P1Ohjaus = 1;  // Rommi
   P2Ohjaus = 0;  // Vodka
   P3Ohjaus = 0;  // Coca-Cola
   P4Ohjaus = 1;  // Energiajuoma
   x = 2;
   scale.tare(); //Reset the scale to 0
   rommi = 50;
   rommi = rommi / 5;
   rommi = rommi * arvo1;
   energiajuoma = 225 - rommi;

  }
  
  else if (valinta == '4'){
   ohjaus = 1;
   P1Ohjaus = 0;  // Rommi
   P2Ohjaus = 1;  // Vodka
   P3Ohjaus = 1;  // Coca-Cola
   P4Ohjaus = 0;  // Energiajuoma
   x = 2;
   scale.tare(); //Reset the scale to 0
   vodka = 50;
   vodka = vodka / 5;
   vodka = vodka * arvo1;
   cola = 225 - vodka;

  }  
  

lcd.clear(); 


//Pumpun 1 ohaus
if (ohjaus == 1 && P1Ohjaus == 1){ // jos ohaus on 1 ja pumppu 1 
  P1 = 0; // P1 while looppi avataan

}
else{
  P1 = 2;
}

while (P1 < 1){
  digitalWrite(23, LOW); // aloitetaan pumpun yksi pumppaaminen
  paino = scale.get_units(); // Vaaka mittaa kokoajan painon määrän
  lcd.setCursor(0,0); 
  lcd.print(paino);
  if (paino >= rommi){ // kun paino on yli sallitun määrän toteutetaan tämä looppi
  P1Ohjaus = 0; // pumpun 1 ohaus nollataan
  P1 = 1; // tämä while loop puretaan
  valinta = 0; // laitetaan valinta 0 :ksi
  digitalWrite(23, HIGH); //nostetaan pinni jolloin pumppu ei käy
  scale.tare(); //Taarataan vaaka
  }
  // SAMAT komentit kaikkien pumppujen ohjauksessa
  
 //Näitä voi käyttää testauksessa 
//  Serial.print("Reading P1: ");
//  Serial.print(paino, 0);
//  Serial.println(" g"); 
  }

//Pumpun 2 ohaus
if (ohjaus == 1 && P2Ohjaus == 1){
   P2 = 0;
}
else{
  P2 = 2;
}
while (P2 < 1){
  digitalWrite(24, LOW); //Pumpun 2 ohjaus piste
  paino = scale.get_units();
  lcd.setCursor(0,0); 
  lcd.print(paino);
  if (paino >= vodka){
  P2Ohjaus = 0;
  P2 = 1;
  valinta = 0;
  digitalWrite(24, HIGH); //Pumpun 2 ohjaus piste
  scale.tare(); //Reset the scale to 0

  }


// Näitä voi käyttää testauksessa   
//  Serial.print("Reading P2: ");
//  Serial.print(paino, 0);
//  Serial.println(" g"); 
  }

//Pumpun 3 ohaus
if (ohjaus == 1 && P3Ohjaus == 1){
   P3 = 0;
   //Reset the scale to 0
}
else{
  P3 = 2;
}
while (P3 < 1){
   digitalWrite(25, LOW); //Pumpun 3 ohjaus piste
  paino = scale.get_units();
  lcd.setCursor(0,0); 
  lcd.print(paino);
  if (paino > cola){
  P3Ohjaus = 0;
  P3 = 1;
  valinta = 0;
  digitalWrite(25, HIGH); //Pumpun 3 ohjaus piste
  scale.tare(); //Reset the scale to 0
  }


  // Näitä voi käyttää testauksessa 
//  Serial.print("Reading P3: ");
//  Serial.print(paino, 0);
//  Serial.println(" g"); 

  }


//Pumpun 4 ohaus
if (ohjaus == 1 && P4Ohjaus == 1){
   P4 = 0;
}
else{
  P4 = 2;
}
while (P4 < 1){
  digitalWrite(26, LOW); //Pumpun 4 ohjaus piste
  paino = scale.get_units();
  lcd.setCursor(0,0); 
  lcd.print(paino);
  if (paino > energiajuoma){
  P4Ohjaus = 0;
  P4 = 1;
  valinta = 0;
  digitalWrite(26, HIGH); //Pumpun 4 ohjaus piste
  scale.tare(); //Reset the scale to 0
  }


  // Näitä voi käyttää testauksessa 
//  Serial.print("Reading P4: ");
//  Serial.print(paino, 0);
//  Serial.println(" g"); 
  }

  int palauteloop = 0;
  int lukeminen = 0;
  lcd.clear();    // kysytään käyttäjältä haluatko antaa palautetta?
      lcd.setCursor(0,0);
      lcd.print("Haluatko antaa");
      lcd.setCursor(0,1);
      lcd.print("palautetta?");
      delay(2500);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("1=Kylla, 2=Ei");
  while (palauteloop==0){ //Pysäytetään ohjelma whileloopilla.
      char pallaute = keypad.getKey(); // odottaa mitä käyttäjä laittaa
      if (pallaute) {
        lcd.clear();
        if (pallaute == '2'){ // jos käyttäjä ei halua antaa palautetta.
        Serial.print("3"); // Lähettää esp32 tiedon että ei annettu palautetta
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Kiitos!");
        palauteloop++; // purkaa whileloopin
        }
      if (pallaute=='1'){ // jos haluaa antaa palautetta.
        lcd.setCursor(0,0);
        lcd.print("Laimeampaa? = 1 vai,"); // kysytään jatkokysymys
        lcd.setCursor(0,1);
        lcd.print("Vahvempaa? = 2");
        int LtaiV = 0;
     while (LtaiV == 0){ // pysäytetään while loopilla
      char VL = keypad.getKey();
      if (VL == '1'){ // jos haluaa laimeempaa
      Serial.print("1"); // lähetettään esp 32 tieto että asiakas halusi laimeampaa
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Juoma on ensker-");
      lcd.setCursor(0,1);
      lcd.print("ralla laimeampaa");
      delay(2000);
      LtaiV++;
      palauteloop++;
      }
      if (VL == '2'){ // jos vahvempaa
      Serial.print("2"); // lähetetään tieto että vahvempaa
      lcd.clear(); 
      lcd.setCursor(0,0);
      lcd.print("Juoma on ensker-");
      lcd.setCursor(0,1);
      lcd.print("ralla vahvempaa");
      delay(2000);
      LtaiV++;
      palauteloop++;
                    }

                }

              
            }


        
}

delay(1000);
}
clearData(); // tyhjentää taas pin koodin
}





  
void clearData() {
  while (data_count != 0) {
    Data[data_count--] = 0; // joka byte kirjoitetaan 0:ksi
  }
  return;
}



  
