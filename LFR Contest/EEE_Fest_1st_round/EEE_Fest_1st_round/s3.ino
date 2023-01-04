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







}// end of logic 













