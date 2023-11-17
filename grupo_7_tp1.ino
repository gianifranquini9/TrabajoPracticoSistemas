// C++ code
// (descargar archivo ino)
// ingresar hora por monitor en serie
// informe y repositorio github + imagen del circuito + archivo ino
#include <LiquidCrystal.h>
int minutos = 0;
int segundos = 0;
int horas = 0 ;
int intervaloPerfume = 10000 ; // esta en 10k por la prueba
int variableMillis=0;
int led = 13;
int estadoBoton1 = 0;
const int botonPin1 = 2;
 
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte caritaA[8] =  {B00000,
                   B00000,
                   B00000,
                   B00000,
                   B00001,
                   B00010,
                   B11100,
                   B00000};
byte caritaB[8] = {B00000,
                   B00000,
                   B00000,
                   B00000,
                   B10000,
                   B01000,
                   B00111,
                   B00000};
byte caritaC[8] = {B00000,
                   B00000,
                   B00010,
                   B00010,
                   B00010,
                   B00000,
                   B00000,
                   B00000};
byte caritaD[8] = {B00000,
                   B00000,
                   B01000,
                   B01000,
                   B01000,
                   B00000,
                   B00000,
                   B00000};


void setup()
{
  // creo caracteres especiales
  lcd.createChar(0, caritaA);
  lcd.createChar(1, caritaB);
  lcd.createChar(2, caritaC);
  lcd.createChar(3, caritaD);

  //arranco comunicacion en serie
  Serial.begin(9600);
  while (!Serial) {
    ; // espero a que el puerto serie esté listo
  }
  lcd.begin(16, 2); 
  lcd.setCursor(0,0);
  
  // configuro el led
  pinMode(led, OUTPUT);     
  digitalWrite(led, HIGH);

   // configuro el pin del botón como entrada
  pinMode(botonPin1, INPUT);
  
}


void loop() {
 
  if (Serial.available()) {//datos qur se van a leer desde la comunicacion en serie
        delay(600);  //se asegura de que los caract se lean antes de intentar leerlos
        
        // utilizamos parseInt para leer un numero entero desde la comunicacion en serie.
        int nuevaHora = Serial.parseInt();
        int nuevosMin = Serial.parseInt();
        int nuevosSeg = Serial.parseInt();
        
        horas = nuevaHora;
        minutos = nuevosMin;
        segundos=nuevosSeg;
    }

  
   segundos++;
  if(segundos>59){
    minutos++;
    segundos=0;
  }
  if(minutos>59){
    horas++;
    minutos=0;
    segundos=0;
  }
  if(horas>=24)
  {
    horas=0;
    minutos=0;
    segundos=0;
  }
   
  lcd.clear();
  lcd.print("Hora:");
  lcd.print(" ");
  
  if(horas<10){
    lcd.print("0");
  }
  lcd.print(horas);
  lcd.print(":");
  if(minutos<10){
    lcd.print("0");
  }
  
  lcd.print(minutos);
  
  lcd.print(":");
  
  if(segundos<10){
    lcd.print("0");
  }
  lcd.print(segundos);
  lcd.setCursor(0,1);
  delay(1000); // error, comentar solución en el informe (millis)
  
  // activacion automatica cada 10 seg para probarlo
  
  if(segundos%10==0){
    mensajePerfume();
    activarPerfume();
  }
  
  // activacion manual
  estadoBoton1 = digitalRead(botonPin1);
  if (estadoBoton1 == HIGH) {
    mensajePerfume();
    activarPerfume();
  }
}

// funcion q envia el mensaje e imprime carita
void mensajePerfume(){
  lcd.clear();
  	lcd.setCursor(3,0);
  	lcd.print("Aromatizador");
  	lcd.setCursor(0,0);
  	lcd.write(byte(2));
  	lcd.setCursor(0,1);
  	lcd.write(byte(1));
  	lcd.setCursor(1,0);
  	lcd.write(byte(3));
  	lcd.setCursor(1,1);
  	lcd.write(byte(0));
 	lcd.setCursor(3,1);
  	lcd.print("activado.");
  	delay(500);
 }

// funcion que activa el aromatizador
void activarPerfume(){
  mensajePerfume();
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
}

 
     /*
PIN	FUNCIÓN
Analog 0	Button(select, up, right, down and left)
Digital 4	DB4
Digital 5	DB5
Digital 6	DB6
Digital 7	DB7
Digital 8	RS (Data or signal Display Selection)
Digital 9	Enable
Digital 10	Backlit Control
*/