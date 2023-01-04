if(sum==0){
 
 if(sr<=18 && sr!=0){
    motorSpeedB(200,200);
    delay(100);
    motorSpeedS();
    delay(3000);
 }
 
 else if(mov==1 ){
    if(k30==1){
     motorSpeedB(10*sp,10*sp);
    delay(100);


    while(bin!=1&&bin!=3){
      check();
          motorSpeedR(6*sp,6*sp);
    }
//    motorSpeedL(6*sp,6*sp);
//    delay(70);
   // motorSpeed(10*sp, 10*sp);
   // delay(100);
    k30=0;
    mov=0; 
    }

 else if(k90==1){
   digitalWrite(d90, HIGH);
      motorSpeedB(10*sp,10*sp);
    delay(90);

    while(bin!=12){
      check();
          motorSpeedR(5*sp,5*sp);
      
    }
    motorSpeedL(5*sp,5*sp);
    delay(40);
  //  motorSpeed(10*sp,10*sp);
  //  delay(100);
    k90=0; 
    mov=0; 
 
     digitalWrite(d90, LOW);
 }
    
  }

  
  else if(mov==2){

    if(k30==2){
   motorSpeedB(10*sp,10*sp);
    delay(100);

    while(bin!=48&&bin!=32){
      check();
          motorSpeedL(6*sp,6*sp);
    }
//    motorSpeedR(6*sp,6*sp);
//      delay(70); 
    k30=0;
    mov=0;  
    }
   else if(k90==2){
     digitalWrite(d90, HIGH);
      motorSpeedB(10*sp,10*sp);
    delay(90);

    while(bin!=12){
      check();
          motorSpeedL(5*sp,5*sp);
    }
    motorSpeedR(4.5*sp,4.5*sp);
    delay(20);
//     motorSpeedB(6*sp,6*sp);
//     delay(100); 
     k90=0;
     mov=0; 
 
      digitalWrite(d90, LOW);
   }
    
  }
  
  




  
}//end of sum 0 

