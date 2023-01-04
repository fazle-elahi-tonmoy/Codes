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






void wall_function()
{
  while(sum==0){
  sonar();
  check();
  if(sr>=16 && sl<=12) motorSpeed(0,150);
  else if(sl>=16 && sr<=12) motorSpeed(150,0);
  else motorSpeed(120,120); 
    
  }
  return;
  
}




