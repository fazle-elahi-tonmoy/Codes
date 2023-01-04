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

