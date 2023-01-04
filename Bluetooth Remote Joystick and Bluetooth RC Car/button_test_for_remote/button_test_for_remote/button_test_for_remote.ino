byte lt, rt, lu, ld, ru, rd;
int jl, jr, i=0, j=0;




void setup() {
  pinMode(7, OUTPUT);
  pinMode(6, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  digitalWrite(7, HIGH);
  Serial.begin(9600);


}

void loop() {
  lu = digitalRead(8);
  ru = digitalRead(10);
  ld = digitalRead(6);
  rd = digitalRead(9);
  lt = digitalRead(11);
  rt = digitalRead(12);
  jl = analogRead(A1);
  jr = analogRead(A2);

//    Serial.print(lu);
//    Serial.print(" ");
//    Serial.print(ld);
//    Serial.print(" ");
//    Serial.print(ru);
//    Serial.print(" ");
//    Serial.print(rd);
//    Serial.print(" ");
//    Serial.print(lt);
//    Serial.print(" ");
//    Serial.print(rt);
//    Serial.print("  ");
//    Serial.print(jl);
//    Serial.print(" ");
//    Serial.println(jr);


  if (jl<350 && jr>350 && jr<650)      Serial.write('F');
  else if (jl>650 && jr>350 && jr<650) Serial.write('B');
  else if (jr<350 && jl>350 && jl<650) Serial.write('L');
  else if (jr>650 && jl>350 && jl<650) Serial.write('R');
//  else if (jl<350 && jr<350) Serial.write('G');
//  else if (jl<350 && jr>650) Serial.write('I');
//  else if (jl>650 && jr<350) Serial.write('H');
//  else if (jl>650 && jr>650) Serial.write('J');
//  
//  else if (lu==1 && ru==1) Serial.write('F');
//  else if (ld==1 && rd==1) Serial.write('B');
//  else if (lu==1 && rd==1) Serial.write('L');
//  else if (ld==1 && ru==1) Serial.write('R');
  else if (lu==1) Serial.write('G');
  else if (ru==1) Serial.write('I');
  else if (ld==1) Serial.write('H');
  else if (rd==1) Serial.write('J');
  
  
  else if (lt==1) {
    if(i==0) {
      Serial.write('W');
      i=1;
      delay(1000);
    }
    else {
      Serial.write('w');
      i=0;
      delay(1000);
    }
  }
  else if (rt==1) {
    if(j==0) {
      Serial.write('U');
      j=1;
      delay(1000);
    }
    else {
      Serial.write('u');
      j=0;
      delay(1000);
    }
  }

  else Serial.write('S');


}
