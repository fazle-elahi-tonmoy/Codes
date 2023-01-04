void line_follow() 
{
    sr = sonarr.ping_cm();
    check();

    if(sum==0){
 
 if(sr<=18 && sr!=0) wall_function();
 
 else if(mov==1 ){
    if(k30==1){
     motorSpeedB(10*sp,10*sp);
    delay(100);


    while(bin!=1&&bin!=3){
      check();
          motorSpeedR(6*sp,6*sp);
    }
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
     k90=0;
     mov=0; 
 
      digitalWrite(d90, LOW);
   }
    
  }
  
  




  
}//end of sum 0 
  else if(sum==1|| sum==2){


if(bin==12){   //  001100
  if(k>0){
    motorSpeedR(9*sp, 9*sp);  // 250,250
    delay(dt);
    
  }
  else if(k<0){
    motorSpeedL(9*sp, 9*sp);
    delay(dt);
  }
  k=0;                        //????????????????????????????????
  mos(9*sp, 9*sp);          
}
else if (bin==4){mos(8*sp, 9*sp);} // 001000 225,250
else if (bin==8){mos(9*sp, 8*sp); } //000100 250,225

else if(bin==6){   //011000 
  if(k<2){
    motorSpeedR(10*sp, 10*sp);
    delay(dt);
    k=2;                  // k=0 jokon tokon seta bracket er baire silo ata te vitore kano??????????????????????
}
  mos(6*sp, 9*sp);
}

else if(bin==2){       // 010000
  if(k<3){           
    motorSpeedR(10*sp, 10*sp);
    delay(dt);
    k=3;
}
  mos(3.5*sp, 9*sp);  // 112.5,250
}

else if(bin==3){      // 110000 
  if(k<4){
    motorSpeedR(10*sp, 10*sp);
    delay(dt);
    k=4;
}
  mos(-3*sp, 9*sp);  //-75,250
}
else if(bin==1){      //100000
  if(k<5){
    motorSpeedR(10*sp, 10*sp);
    delay(dt);
    k=5;
}
  mos(-4.5*sp, 9*sp);   //125,250
}

// dan side shesh 


// bam side shuru 

else if(bin==24){   //000110
  if(k>-2){
    motorSpeedL(10*sp, 10*sp);
    delay(dt);
    k=-2;
}
  mos(9*sp, 6*sp);
}
else if(bin==16){  //000010
  if(k>-3){
    motorSpeedL(10*sp, 10*sp);
    delay(dt);
    k=-3;
}
  mos(9*sp, 3.5*sp);
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
if(bin==9||  bin==11|| bin==13    ){  // bin er man 9 kamne hoy 7 hobe na?? 111000 hole tho 7 ase?????????????????
 // motorSpeed(5*sp,5*sp);           // (   || 110100 || 1011000)
  k30=1; 
  mov=1;
}
 
if( bin==52||  bin==36|| bin==44  ){  // (001011 ||     ||0001101)
 // motorSpeed(5*sp,5*sp);   // bin er man 36 kivabe ase????? 001001 hole ase.. kintu tokon tho sum er man 2 hobe????????????????
  k30=2;
  mov =2;
}




if(  bin==15 || bin==7 ){ //(111100 ||111000)
k90=1;
mov=1;
//delay(50);
}
// bin==7 bad disi 

if(  bin==60 || bin==56 ){ //(001111 || 000111)
k90=2;
mov=2;
 // delay(50);
}
//bin==224  bad disi 



//check();


if(mov!=0){
  mi1=millis();
}

}// end of sum 3


else if(sum==6){
   m81=m82= millis();
   while (sum==5||sum==6||sum==4||sum==3){
    check();
    m82=millis();
    if(m82-m81>=70){
    motorSpeedB(200,200);
    delay(100);
    motorSpeedS();
    delay(3000);
    break;
   }
   
   }
   mov=0;
   k90=0;
   k30=0;
   
   
}

mi2=millis();
if(mi2-mi1>=300)mov=0;
  
}// end of loop :) 











