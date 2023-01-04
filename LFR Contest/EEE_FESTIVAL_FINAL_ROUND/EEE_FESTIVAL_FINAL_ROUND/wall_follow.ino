void wall_function()
{
  while(sum==0){
  sonar();
  check();
  if(sr>=16 && sl<=12) motorSpeed(0,150);
  else if(sl>=16 && sr<=12) motorSpeed(150,0);
  else motorSpeed(120,120); 
    
  }
  robot=1;
  return;
  
}
