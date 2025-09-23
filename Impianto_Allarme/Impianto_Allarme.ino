#include <SPI.h>
#include <RFID.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>

#define SDA_PIN 10
#define RST_PIN 9
// 41, 111, 83, 178, 167 

#define masnum0 41
#define masnum1 111
#define masnum2 83
#define masnum3 178
#define masnum4 167


#define pir 8
#define ledV 4
#define ledR 3
#define ledG 5
#define resetkey 6
#define pausa 1000
RFID rfid(SDA_PIN, RST_PIN); 
LiquidCrystal lcd( A0, A1, A2, A3, A4, A5);

boolean antiON = 0;
boolean allarm = 0; 
boolean cardmas = 0; 
int slave; 

int sernum0;
int sernum1;
int sernum2;
int sernum3;
int sernum4;

void setup()
{ 
  lcd.begin(16, 2);
  SPI.begin(); 
  rfid.init();
  pinMode(ledR, OUTPUT);
  pinMode(ledV, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(resetkey, INPUT);
  digitalWrite(7,HIGH);
  lcd.print("Made by Andrea");
  delay(5000);
 }

void loop() {
 slave = EEPROM.read(0);
  
   if (rfid.isCard()) {
   if(rfid.readCardSerial()){  
        sernum0 = rfid.serNum[0];
        sernum1 = rfid.serNum[1];
        sernum2 = rfid.serNum[2];
        sernum3 = rfid.serNum[3];
        sernum4 = rfid.serNum[4];
     

                if (sernum0 == masnum0
                && sernum1 == masnum1
                && sernum2 == masnum2
                && sernum3 == masnum3
                && sernum4 == masnum4
             ) {
                if (cardmas==0) {
                  lcd.clear();
                  lcd.print("CARD MASTER");      
                  delay(1500);                        
                  lcd.clear();                     
                  lcd.print("GESTIONE"); 
                  lcd.setCursor(0,1); 
                  lcd.print("CHIAVI"); 
                  lcd.clear(); 
                cardmas = 1;                  
                lcd.setCursor(1, 0);              
                lcd.print("Chiavi slave: ");
                lcd.setCursor(15,1);
                lcd.print(slave);
                delay(2000);
                }  else { cardmas = 0;        
                  lcd.setCursor(0, 1);
                  lcd.print("Annullato");
                delay(3000);
                }
                }
else if ((sernum0 == EEPROM.read(1) && sernum1 == EEPROM.read(2) && sernum2 == EEPROM.read(3) && sernum3 == EEPROM.read(4) && sernum4 == EEPROM.read(5))|| (sernum0 == EEPROM.read(6) && sernum1 == EEPROM.read(7) && sernum2 == EEPROM.read(8) && sernum3 == EEPROM.read(9) && sernum4 == EEPROM.read(10))  || (sernum0 == EEPROM.read(11) && sernum1 == EEPROM.read(12) && sernum2 == EEPROM.read(13) && sernum3 == EEPROM.read(14) && sernum4 == EEPROM.read(15))) {
         if (antiON == 1) {  
                             antiON =0 ;
                             lcd.clear();
                             lcd.print("lettura chiave");
                             delay(1500);
                             lcd.clear();
                             lcd.print("ANTIFURTO");
                             lcd.setCursor(0, 1);                             
                             lcd.print("INSERITO");
                             delay(8000);
                             digitalWrite(ledR,LOW);                            
                             pinMode(pir,LOW);
                              digitalWrite(7,LOW);
                             digitalWrite(ledV,HIGH);
                             } 
                              else {
                                   antiON = 1;
                                   allarm = 0;
                                   digitalWrite(ledR,HIGH);
                                   digitalWrite(ledV,LOW);
                                   lcd.clear();
                                   lcd.print("lettura chiave");
                                   delay(500);
                                   lcd.clear();
                                   lcd.print("antifurto");
                                   lcd.setCursor(0, 1);
                                   lcd.print("disinserito");
                                   pinMode(pir,HIGH);
                                   digitalWrite(7,HIGH);
                                   
                                   } 
                }
  // memororizzazione chiave slave
  
else if (cardmas == 1 && slave == 0) {
                    lcd.clear();
                    lcd.print("Chiave rilevata!");
                    EEPROM.write(0, 1);
                    EEPROM.write(1, sernum0);
                    EEPROM.write(2, sernum1);
                    EEPROM.write(3, sernum2);
                    EEPROM.write(4, sernum3);
                    EEPROM.write(5, sernum4);
                    cardmas = 0;
                    delay(1000);
                    lcd.setCursor(0, 1);
                    lcd.print("Slave 1 salvata!");
                    delay(3000);
                    }
                    
    } 
                 

   }

     // letture da parte del pir 
     /* se il pir non rileva il movimento il led Giallo e il buzzer si troveranno allo stato SPENTO*/ 
       if (digitalRead(pir) == HIGH) {
                                   digitalWrite(ledG,LOW);
                                   digitalWrite(7,LOW);
                                  
      /*se il pir rileva il movimento il led Giallo e il buzzer si troveranno allo stato ACCESO*/                             } 
          else {
          digitalWrite(ledG,HIGH);
          digitalWrite(7,HIGH);
          
   }  
  
if (digitalRead(pir) == HIGH && antiON == 0 && allarm == 0){
         
          lcd.clear();
          lcd.print("ALLARME IN CORSO");     
               
         }
      if (digitalRead(pir) == LOW && antiON == 0 && allarm == 0){
         lcd.clear();
         lcd.print("ANTIFURTO");
         lcd.setCursor(0,1);
         lcd.print("INSERITO");
         }
 // reset chiave slave
 
if (digitalRead(resetkey) == HIGH && cardmas ==0) {
         cardmas = 1;
         for (int i=0; i<16; i++){
           EEPROM.write(i, 0);
             } 
         lcd.clear();
         lcd.print("Reset chiavi...");
         delay(3000);
         } 
        
rfid.halt();
}     
 
