const int lecture_Vpin = A0; // Lecture de la tension
const int lecture_Ipin  = A1; // Lecture du courant 
const int PWM_filtree = A2;
const int PWMpin = 3;


//Reglage sinus
int index = 0;
const int numSteps = 20; // Nombre d'etapes dans la sinusoïde
const int sinValues[numSteps] ={0,3,11,23,38,54,70,84,
94,99,99,94,84,70,54,38,23,11,3,0};
int dataVpin;
int dataIpin;
int dataPWM_filtree;
int time = 0;

void setup() {
  Serial.begin(9600) ; // Ouverture port série avec baudrate de 9600 (augmenter si besoin)
  pinMode(lecture_Vpin, INPUT); // Entree des valeurs analogiques
  pinMode(lecture_Ipin, INPUT);
  
  pinMode(3, OUTPUT);//Pin PWM

  //TIMER 2 : PWM variable à valeur moyenne sinusoidale à 1KHz
  TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20); 
  TCCR2B = _BV(CS21) |_BV(WGM22);
  OCR2A = 99;
  OCR2B  = 20; 
  TIMSK2 |= _BV(OCIE2A);
  sei(); // Activation des interruptions globales  interupts(); 
}

void loop() {
  dataVpin = analogRead(lecture_Vpin);
  dataIpin = analogRead(lecture_Ipin);
  dataPWM_filtree = analogRead(PWM_filtree);
  Serial.println(String(dataVpin) + ';' + String(dataIpin) + ';' + String(dataPWM_filtree) + ';' + String(time));
  delay(10);
  time += 1;
  Serial.flush();
}

//Interuption Timer 2
ISR(TIMER2_COMPA_vect) {
  OCR2B=sinValues[index];
  if (index < numSteps - 1)
    index++;
  else
    index=0;
    } 
