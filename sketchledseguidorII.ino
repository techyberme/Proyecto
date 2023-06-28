     
    #include <AccelStepper.h>.  //incluimos la librería del motor por pasos.
    
   //definición de los pines del motor:
    #define motorPin1  8       //IN1 del motor que va a girar en el eje x
    #define motorPin2  9      // IN2 del motor que va a girar en el eje x
    #define motorPin3  10     // IN3 del motor que va a girar en el eje x
    #define motorPin4  11     // IN4 del motor que va a girar en el eje x
    #define motorPin5  4      // IN1 del motor que va a girar en el eje z
    #define motorPin6  5      // IN2 del motor que va a girar en el eje z
    #define motorPin7  6      //IN3 del motor que va a girar en el eje z
    #define motorPin8  7     // IN4 del motor que va a girar en el eje z
    #define a A0            //definición del puerto para la medida a
    #define b A1            //definición del puerto para la medida b
    #define c A2            //definición del puerto para la medida c
    #define d A3            //definición del puerto para la medida d   
    // Definición del tipo de motor
    #define MotorInterfaceType 8
    #define LED 52          //definimos el pin del led
    unsigned long timerOne = 0; //variable to subtract from millis()
    
    //definimos los pines correspondientes a cada motor
    AccelStepper stepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);    //motorx
    AccelStepper stepper2 = AccelStepper(MotorInterfaceType, motorPin5, motorPin7, motorPin6, motorPin8);   //motorz
    //definición de variables
    int valora;   
    int valorb;
    int valorc;
    int valord;
    int resta1;
    int resta2;
    int resta3;
    int resta4;
    int restaz;
    int restax;
    void setup() {
      Serial.begin(9600);              //inicialización del puerto serie
      pinMode(LED,OUTPUT);             //ponemos el pin del LED como salida
      pinMode(53,OUTPUT); 
      stepper.setMaxSpeed(1000);      //selección de la velocidad máxima de los motores
      stepper2.setMaxSpeed(1000);
      stepper.setCurrentPosition(-512);   //selección de la posición inicial de los motores
      stepper2.setCurrentPosition(0);
    }
    
    void loop() {
       valora=analogRead(a);            //lectura de los puertos analógicos
       valorb=analogRead(b);
       valorc=analogRead(c);
       valord=analogRead(d);
       resta1=valora-valorb;            
       resta2=valorc-valord;
       restaz=max(abs(resta1),abs(resta2)); //guardamos el valor máximo absoluto
      if(abs(resta1)==restaz){ //como hemos guardado el absoluto y queremos conocer el signo de la resta máxima, igualamos restaz a la resta más grande
        restaz=resta1;
      }
      else if(abs(resta2)==restaz){
        restaz=resta2;
      }
      resta3=valora-valorc;          //realizamos lo mismo pero para el eje x
      resta4=valorb-valord;
      restax=max(abs(resta3),abs(resta4));
      if(abs(resta3)==restax){
        restax=resta3;
      }
      else if(abs(resta4)==restax){
        restax=resta4;
      }
      if (abs(stepper2.currentPosition())<1024){     //si el motor 2 está entre -45º y 45º
      if(restaz<-50 || restaz>50){
      if(restaz>600 || restaz<-600){          //en caso de que sea muy pequeña o muy grande restaz
      stepper2.stop();                         //paramos motor
    }
       else if (restaz>0){                    //si no y es positiva
        stepper2.setSpeed(200);                //velocidad en sentido horario
        stepper2.runSpeed();
        encender();
       }
       else if (restaz<0){                    //si no y es negativa
        stepper2.setSpeed(-200);              //velocidad en sentido antihorario
      stepper2.runSpeed();
      encender();                              //ponemos la secuencia de leds en funcionamineto
    }
      }  
    }
    if (abs(stepper.currentPosition())<512){
    if (restax<-50 || restax>50){  
    if(restax>600 || restax<-600){
      encender();
    }
    else if (restax>0){
        stepper.setSpeed(200);
        stepper.runSpeed();
        encender();
       }
       else if (restax<0){
        stepper.setSpeed(-200);
        stepper.runSpeed();
        encender();
    }
    
    }
    } 
       
     if (abs(stepper2.currentPosition())>=1024){          //en el caso que el motor2 este fuera del rango de -45 y 45º
      if (stepper2.currentPosition()>0){                  //si está en 90º
        if(restaz<0){                                     //solo puede girar hacia en sentido antihorario
           stepper2.setSpeed(-200);
          stepper2.runSpeed();
          encender();
        }
      else if(restaz>0){                                   
               stepper2.setSpeed(0);                       //no puede girar en sentido horario
               stepper2.runSpeed();                        
               
        }

      }
       else if (stepper2.currentPosition()<0){             //si está a -90º, lo contrarior
        if(restaz>0){
           stepper2.setSpeed(200);
           stepper2.runSpeed();
           encender();
        }
        else if(restaz<0){
               stepper2.setSpeed(0);
               stepper2.runSpeed();
        }

      }
      }
      if (abs(stepper.currentPosition())>=512){             //Para el eje z, lo mismo pero para 45º
      if (stepper.currentPosition()>0){
        if(restax<0){
           stepper.setSpeed(-200);
          stepper.runSpeed();
        }
      else if(restax>0){
               stepper.setSpeed(0);
               stepper.runSpeed();
        }

      }
       else if (stepper.currentPosition()<0){
        if(restax>0){
           stepper.setSpeed(200);
           stepper.runSpeed();
        }
        else if(restax<0){
               stepper.setSpeed(0);
               stepper.runSpeed();
        }

      }
      }
      
      Serial.println(restaz);
       
      }  
      void encender(){                    //función para encender y apagar leds
        if (millis() - timerOne > 350) {
      digitalWrite(52, LOW);
      digitalWrite(53,HIGH);
      timerOne = millis();  
    }  
    else if (millis() - timerOne > 100) {
      digitalWrite(52, HIGH);
      digitalWrite(53,LOW);
    }
      }

       
    
