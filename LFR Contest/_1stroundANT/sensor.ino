void sensor()
{
  v6 = analogRead(A0);
  v5 = analogRead(A1);
  v4 = analogRead(A2);
  v3 = analogRead(A3);
  v2 = analogRead(A4);
  v1 = analogRead(A5);

  if(a==0||a==2){
    if (v1 > th) v1 = 1;
    else v1 = 0;
    if (v2 > th) v2 = 1;
    else v2 = 0;
    if (v3 > th) v3 = 1;
    else v3 = 0;
    if (v4 > th) v4 = 1;
    else v4 = 0;
    if (v5 > th) v5 = 1;
    else v5 = 0;
    if (v6 > th) v6 = 1;
    else v6 = 0;
  }
  if(a==1){
    if (v1 < th) v1 = 1;
    else v1 = 0;
    if (v2 < th) v2 = 1;
    else v2 = 0;
    if (v3 < th) v3 = 1;
    else v3 = 0;
    if (v4 < th) v4 = 1;
    else v4 = 0;
    if (v5 < th) v5 = 1;
    else v5 = 0;
    if (v6 < th) v6 = 1;
    else v6 = 0;

  }

  

}

