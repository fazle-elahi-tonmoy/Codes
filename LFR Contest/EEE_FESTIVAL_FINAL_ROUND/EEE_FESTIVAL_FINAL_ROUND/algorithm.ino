void algorithm(){

    ii=0;
    aa=0;
    while(1)
    {
        if(prob[aa+1]==4)
        {
            prob[ii]=prob[ii]+prob[aa+2];
            aa+=2;
        }
        if(prob[ii]==4)
        {
            prob[ii-1]=prob[ii-1]+prob[aa+1];
            aa++;
            ii--;
        }
        else
        {
            ii++;
            aa++;
            prob[ii]=prob[aa];
        }
        if(prob[ii]==5) break;
    }


    
    while(1)
    {
        if(prob[bb]==1) prob[bb]=3;
        else if(prob[bb]==3) prob[bb]=1;
        else if(prob[bb]==5) break;
        bb++;
    }


    EEPROM.write(cc+9, bb);
    for (int cc = 0;; cc++) {
    EEPROM.write(cc+10, prob[cc]);
    delay(10);
    if(prob[cc]==5) break;

  }
    
    robot=2;
    cc=0;
    

}
