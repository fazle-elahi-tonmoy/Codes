void maze_scanner()
{
  check();


  if(sum==0){
 
 
  if(mov==1 ){
  if(k90==1){
   digitalWrite(d90, HIGH);
      motorSpeedB(10*sp,10*sp);
    delay(50);

    while(bin!=12){
      check();
          motorSpeedR(6*sp,6*sp);
      
    }
    motorSpeedL(6*sp,6*sp);
    delay(40);
    k90=0; 
    mov=0; 
 
     digitalWrite(d90, LOW);
 }
 
    
  }

  
  else if(mov==2){
     if(k90==2){
     digitalWrite(d90, HIGH);
      motorSpeedB(10*sp,10*sp);
      delay(100);

    while(bin!=12){
      check();
          motorSpeedL(6*sp,6*sp);
    }
    motorSpeedR(6*sp,6*sp);
    delay(40);
      //  motorSpeed(10*sp, 10*sp);
   // delay(100);  
     k90=0;
     mov=0; 
 
      digitalWrite(d90, LOW);
   }
   else if(k90==0){
    digitalWrite(d90, HIGH);
    motorSpeedB(10*sp,10*sp);
    delay(100);

    while(bin!=12){
      check();
          motorSpeedR(6*sp,6*sp);
    }
    motorSpeedL(6*sp,6*sp);
    delay(40);
     k90=0;
     mov=0;
     cross=0; 
     prob[ii]=1;
 
      digitalWrite(d90, LOW);
    
   }
    
  }
  else if(mov==0){
    delay(100);
    digitalWrite(d90, HIGH);
    motorSpeedB(10*sp,10*sp);
    delay(50);

    while(bin!=12){
      check();
          motorSpeedR(6*sp,6*sp);
      
    }
    motorSpeedL(6*sp,6*sp);
    delay(40);
    k90=0; 
    mov=0; 
    cross=0;
    prob[ii]=4;
 
     digitalWrite(d90, LOW);
    
  }
  
  




  
}//end of sum 0 


else if(sum==1|| sum==2){

if(cross==1){
    cross=0;
    digitalWrite(d90, HIGH);
    motorSpeedB(10*sp,10*sp);
    delay(100);

    while(sensor[2]==1||sensor[3]==1||sensor[4]==1||sensor[1]==1){
      check();
          motorSpeedR(6*sp,6*sp);
      
    }
    while(bin!=12){
      check();
          motorSpeedR(6*sp,6*sp);
      
    }
    motorSpeedL(6*sp,6*sp);
    delay(40);
    k90=0; 
    mov=0;
    prob[ii]=1; 
 
   digitalWrite(d90, LOW);
  }
else if(bin==12){
  if(k>0){
    motorSpeedR(10*sp, 10*sp);
    delay(dt);
    
  }
  else if(k<0){
    motorSpeedL(10*sp, 10*sp);
    delay(dt);
  }
  k=0;
  mos(10*sp, 10*sp);
}
else if (bin==4){mos(9*sp, 10*sp);}
else if (bin==8){mos(10*sp, 9*sp); }

else if(bin==6){
  if(k<2){
    motorSpeedR(10*sp, 10*sp);
    delay(dt);
    k=2;
}
  mos(7*sp, 10*sp);
}

else if(bin==2){
  if(k<3){
    motorSpeedR(10*sp, 10*sp);
    delay(dt);
    k=3;
}
  mos(4.5*sp, 10*sp);
}

else if(bin==3){
  if(k<4){
    motorSpeedR(10*sp, 10*sp);
    delay(dt);
    k=4;
}
  mos(-3*sp, 10*sp);
}
else if(bin==1){
  if(k<5){
    motorSpeedR(10*sp, 10*sp);
    delay(dt);
    k=5;
}
  mos(-5*sp, 10*sp);
}

// dan side shesh 


// bam side shuru 

else if(bin==24){
  if(k>-2){
    motorSpeedL(10*sp, 10*sp);
    delay(dt);
    k=-2;
}
  mos(10*sp, 7*sp);
}
else if(bin==16){
  if(k>-3){
    motorSpeedL(10*sp, 10*sp);
    delay(dt);
    k=-3;
}
  mos(10*sp, 4.5*sp);
}

else if(bin==48){
  if(k>-4){
    motorSpeedL(10*sp, 10*sp);
    delay(dt);
    k=-4;
}
  mos(10*sp, -3*sp);
}
else if(bin==32){
  if(k>-5){
    motorSpeedL(10*sp, 10*sp);
    delay(dt);
    k=-5;
}
  mos(10*sp, -5*sp);
}

  
}//end sum 1


else if(sum==3||sum==4){

if(  bin==15 || bin==7 ){
k90=1;
mov=1;
m81=m82= millis();
while(sum==4 || sum==3 || sum==1 || sum==2){
  check();
  m82=millis();
 if(m82-m81>=70){
    cross=1;
    break;
   }
}
} 

if(  bin==60 || bin==56 ){
k90=2;
mov=2;
m81=m82= millis();
while(sum==4 || sum==3 || sum==1 || sum==2){
  check();
  m82=millis();
 if(m82-m81>=70){
    k90=0;
    mov=0;
    cross=0;
    prob[ii]=2;
    break;
   }
}

}


}// end of sum 3



else if(sum==6){

    cross=1;
    mov=2;
    k30=0;
    k90=0;
   m81=m82= millis();
   while (sum==5||sum==6||sum==4||sum==3){ 
    digitalWrite(22, 1);
    check();
    m82=millis();
    if(m82-m81>=100){
    motorSpeedB(200,200);
    delay(50);
    motorSpeedS();
    //delay(2000);
    prob[ii]=5;
    algorithm();
    break;
   }
   
   }
   
}



}

