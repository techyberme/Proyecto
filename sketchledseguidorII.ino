     
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
       restaz=max(abs(resta1),abs(resta2));
      if(abs(resta1)==restaz){
        restaz=resta1;
      }
      else if(abs(resta2)==restaz){
        restaz=resta2;
      }
      resta3=valora-valorc;
      resta4=valorb-valord;
      restax=max(abs(resta3),abs(resta4));
      if(abs(resta3)==restax){
        restax=resta3;
      }
      else if(abs(resta4)==restax){
        restax=resta4;
      }
      if (abs(stepper2.currentPosition())<1024){
      if(restaz<-50 || restaz>50){
      if(restaz>600 || restaz<-600){
      stepper2.stop();
    }
       else if (restaz>0){
        stepper2.setSpeed(200);
        stepper2.runSpeed();
        encender();
       }
       else if (restaz<0){
        stepper2.setSpeed(-200);
      stepper2.runSpeed();
      encender();
    }
      }  
    }
    if (abs(stepper.currentPosition())<512){
    if (restax<-50 || restax>50){  //este es para el  de arriba a ab
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
       
     if (abs(stepper2.currentPosition())>=1024){
      if (stepper2.currentPosition()>0){
        if(restaz<0){
           stepper2.setSpeed(-200);
          stepper2.runSpeed();
          encender();
        }
      else if(restaz>0){
               stepper2.setSpeed(0);
               stepper2.runSpeed();
               
        }

      }
       else if (stepper2.currentPosition()<0){
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
      if (abs(stepper.currentPosition())>=512){
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
      void encender(){
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

       
    
