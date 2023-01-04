void display_cube()
{
  Serial.println("");
  for (j = 0; j <= 2; j++)
  {
    Serial.print("          ");
    for (i = 0; i <= 2; i++) {
      Serial.print(B[i][j]);
      Serial.print(" ");
    }
    Serial.print("\n");
  }
  Serial.print("\n  ");
  for (j = 0; j <= 2; j++)
  {
    for (i = 0; i <= 2; i++){
      Serial.print(L[i][j]);
      Serial.print(" ");
    }
    Serial.print("  ");
    for (i = 0; i <= 2; i++){
      Serial.print(U[i][j]);
      Serial.print(" ");
    }
    Serial.print("  ");
    for (i = 0; i <= 2; i++){
      Serial.print(R[i][j]);
      Serial.print(" ");
    }
    Serial.print("  ");
    for (i = 0; i <= 2; i++){
      Serial.print(D[i][j]);
      Serial.print(" ");
    }
    Serial.print("\n  ");
  }
  Serial.print("\n");
  for (j = 0; j <= 2; j++)
  {
    Serial.print("          ");
    for (i = 0; i <= 2; i++){
      Serial.print(F[i][j]);
      Serial.print(" ");
    }
    Serial.print("\n");
  }
  Serial.print("\n-------------------------------------------------------------------------\n");
}
