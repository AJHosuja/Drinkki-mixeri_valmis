#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>


#define FIREBASE_HOST "data-base-8992b-default-rtdb.firebaseio.com" // FIREBASE tiedot
#define FIREBASE_AUTH "c2zkarekabthvj3OPiXJYJJgH0kS1IWWTvEMSpmR"
#define WIFI_SSID "Hosuja (1))" // WLAN tiedot
#define WIFI_PASSWORD "12345678A"
float k, d;
int a, c, timer;
#define RXp2 16
#define TXp2 17
int i = 0;
void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2); // arduinolle yhteys

  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // Yhdistää WLAN
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Yhdistetty: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
}
void loop() {
    c = 0;
   if (Serial2.available() == 4) {  // kun serialissa on luettavissa 4 numeroa menee aliohjelmaan
    serial2();
   }

   
}

void serial2() {
    
    
    String pin = Serial2.readString(); // lukee pin koodin ja tekee siitä 4 numeroisen charin muutamalla funktiolla
    int str_len = pin.length() + 1;
    char pinni[str_len];
    pin.toCharArray(pinni, str_len);
    k = pin.toFloat();
    char juoma[7] = "juoma"; // määrittää charin joka on "juoma"
    strcat(pinni , "/");
    strcat(pinni , juoma); // tehdään polku xxxx/juoma
   
    Serial.println(pinni);
    
    c = Firebase.getFloat(pinni); // otetaan c:lle numero databasesta
    // jos ei löydy c vastinetta c: arvo pysyy 0:na mutta jos löytyy se on eri kuin nolla
    if (c == 0) { // jos ei löydy = käyttäjää ei löydy
      a = 2;
     
      Serial2.print(a); // printtaa 2 arduinolle
    
    }

    if (c != 0) { // löytyy käyttäjä löytyi
        a = 1;
  
        Serial2.print(a); // printtaa 1 arduinolle
        while (c != 0) { // pysäytetään ohjelma odotetaan minkä juoman käyttäjä haluaa

            if (Serial2.available() > 0) { // kun juoma on luettavissa
           char tilaus = Serial2.read(); // lukee sen char muotoon
            if (tilaus == '1'){ // jos se tilaus on yksi 
           strcat(pinni , "1_1"); //tekee pinnistä = xxxx(käyttäjä)/juoma1_1
           float juom1;
           juom1 = Firebase.getFloat(pinni); // etsii firebasesta juoman kertoimen ja lähettää sen arduinolle
           int drink1 = juom1; // muutetaan float int:iksi
           Serial2.print(drink1); // lähettää tässä
           int palaute = 0;
           while (palaute == 0){ // pysäytetään ohjelma while loopilla ja odotetaan antaako käyttäjä palautetta.
              if (Serial2.available()){ // jos serialissa on luettavaa.
                 String annettuPalaute = Serial2.readString(); // lukee palautteen stringiksi 
                 int pallaute = annettuPalaute.toInt(); // muuttaa stringin intiksi
                   if (pallaute==1){ // jos pallaute on 1 käyttäjä haluaa kertoimen pienemmäksi
                     float juomanPalaute = Firebase.getFloat(pinni); // haetaan kerroin uudestaan
                     delay(1000);
                     juomanPalaute--; // lasketaan sitä ythdellä
                     Firebase.setFloat(pinni, juomanPalaute); // kirjoitetaan se uudestaan firebaseen
                     palaute++; // puretaan whileloop
                    }
                    else if (pallaute==2){ // vahvenpaa
                     float juomanPalaute = Firebase.getFloat(pinni); // tehdään samat kuin edellä
                     delay(1000);
                     juomanPalaute++;
                     Firebase.setFloat(pinni, juomanPalaute);
                     palaute++;
                    }  
                    else if (pallaute==3){ // jos ei halua antaa palautetta niin purkaa vain while loopin
                      palaute++; 
                    }                   
                                    
                }
              
            }
           c++;          
           return;
          // SAMAT kommentit kaikissa tilauksissa
           }

           if (tilaus == '2'){
           char pinni2[15];  
           strcat(pinni , "2_1");
           Serial.println(pinni);
           float juom1, juom2;
           juom1 = Firebase.getFloat(pinni);
           int drink1 = juom1;
           Serial2.print(drink1);
           int palaute = 0;
           while (palaute == 0){
              if (Serial2.available()){
                 String annettuPalaute = Serial2.readString();
                 int pallaute = annettuPalaute.toInt();
                   if (pallaute==1){
                     float juomanPalaute = Firebase.getFloat(pinni);
                     delay(1000);
                     juomanPalaute--;
                     Firebase.setFloat(pinni, juomanPalaute);
                     palaute++;
                    }
                    else if (pallaute==2){
                     float juomanPalaute = Firebase.getFloat(pinni);
                     delay(1000);
                     juomanPalaute++;
                     Firebase.setFloat(pinni, juomanPalaute);
                     palaute++;
                    }  
                    else if (pallaute==3){
                      palaute++;
                    }                   
                                    
                }
              
            }
           c++;          
           return;
         
           }

           if (tilaus =='3'){
           char pinni2[15]; 
           strcat(pinni , "3_1");
           float juom1;
           juom1 = Firebase.getFloat(pinni);
           int drink1 = juom1;
           Serial2.print(drink1);
           c++;
           int palaute = 0;
           while (palaute == 0){
              if (Serial2.available()){
                 String annettuPalaute = Serial2.readString();
                 int pallaute = annettuPalaute.toInt();
                   if (pallaute==1){
                     float juomanPalaute = Firebase.getFloat(pinni);
                     delay(1000);
                     juomanPalaute--;
                     Firebase.setFloat(pinni, juomanPalaute);
                     palaute++;
                    }
                    else if (pallaute==2){
                     float juomanPalaute = Firebase.getFloat(pinni);
                     delay(1000);
                     juomanPalaute++;
                     Firebase.setFloat(pinni, juomanPalaute);
                     palaute++;
                    }  
                    else if (pallaute==3){
                      palaute++;
                    }                   
                                    
                }
              
            }
                   
           return;
          
           }
           
           if (tilaus == '4'){
           char pinni2[15];  
           strcat(pinni , "4_1");
           float juom1;
           juom1 = Firebase.getFloat(pinni);
           Serial2.print(drink1);
           int palaute = 0;
           while (palaute == 0){
          
              if (Serial2.available()){
             
                 String annettuPalaute = Serial2.readString();
                 int pallaute = annettuPalaute.toInt();
                   if (pallaute==1){
                     float juomanPalaute = Firebase.getFloat(pinni);
                     delay(1000);
                     juomanPalaute--;
                     Firebase.setFloat(pinni, juomanPalaute);
                     palaute++;
                    }
                    else if (pallaute==2){
                     float juomanPalaute = Firebase.getFloat(pinni);
                     delay(1000);
                     juomanPalaute++;
                     Firebase.setFloat(pinni, juomanPalaute);
                     palaute++;
                    }  
                    else if (pallaute==3){
                      palaute++;
                    }                   
                                    
                }
              
            }           
           c++;          
           return;
           
           }        
              
              
              }}
              }}
