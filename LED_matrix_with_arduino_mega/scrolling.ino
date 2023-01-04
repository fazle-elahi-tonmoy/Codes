void scrolling(char a[255], int t) {
  int x, s = 0;
  x = strlen(a);
  while ( s <= x * 6) {
    m2 = millis();
    if (m2 - m1 > t) {
      m1 = m2;
      for (int p = 0 ; p < x ; p++)
        for (int i = 0; i < 7 ; i++)
          for (int j = 0; j < 5; j++) {
            if (j + p * 6 - s + 20 < 0) continue;
            disp[i][j + p * 6 - s + 21] = 0;
            if (a[p] == 'A') disp[i][j + p * 6 - s + 20] = A[i][j];
            else if (a[p] == 'B') disp[i][j + p * 6 - s + 20] = B[i][j];
            else if (a[p] == 'C') disp[i][j + p * 6 - s + 20] = C[i][j];
            else if (a[p] == 'D') disp[i][j + p * 6 - s + 20] = D[i][j];
            else if (a[p] == 'E') disp[i][j + p * 6 - s + 20] = E[i][j];
            else if (a[p] == 'F') disp[i][j + p * 6 - s + 20] = F[i][j];
            else if (a[p] == 'G') disp[i][j + p * 6 - s + 20] = G[i][j];
            else if (a[p] == 'H') disp[i][j + p * 6 - s + 20] = H[i][j];
            else if (a[p] == 'I') disp[i][j + p * 6 - s + 20] = I[i][j];
            else if (a[p] == 'J') disp[i][j + p * 6 - s + 20] = J[i][j];
            else if (a[p] == 'K') disp[i][j + p * 6 - s + 20] = K[i][j];
            else if (a[p] == 'L') disp[i][j + p * 6 - s + 20] = L[i][j];
            else if (a[p] == 'M') disp[i][j + p * 6 - s + 20] = M[i][j];
            else if (a[p] == 'N') disp[i][j + p * 6 - s + 20] = N[i][j];
            else if (a[p] == 'O') disp[i][j + p * 6 - s + 20] = O[i][j];
            else if (a[p] == 'P') disp[i][j + p * 6 - s + 20] = P[i][j];
            else if (a[p] == 'Q') disp[i][j + p * 6 - s + 20] = Q[i][j];
            else if (a[p] == 'R') disp[i][j + p * 6 - s + 20] = R[i][j];
            else if (a[p] == 'S') disp[i][j + p * 6 - s + 20] = S[i][j];
            else if (a[p] == 'T') disp[i][j + p * 6 - s + 20] = T[i][j];
            else if (a[p] == 'U') disp[i][j + p * 6 - s + 20] = U[i][j];
            else if (a[p] == 'V') disp[i][j + p * 6 - s + 20] = V[i][j];
            else if (a[p] == 'W') disp[i][j + p * 6 - s + 20] = W[i][j];
            else if (a[p] == 'X') disp[i][j + p * 6 - s + 20] = X[i][j];
            else if (a[p] == 'Y') disp[i][j + p * 6 - s + 20] = Y[i][j];
            else if (a[p] == 'Z') disp[i][j + p * 6 - s + 20] = Z[i][j];
            else disp[i][j + p * 6 - s + 20] = nil[i][j];
          }
      s++;
    }
    showing();
  }


  s = 0;
  while (s < 20) {
    m2 = millis();
    if (m2 - m1 > t) {
      m1 = m2;
      for (int i = 0; i < 7 ; i++)
        for (int j = 0; j < 19 ; j++)
          disp[i][j] = disp[i][j + 1];
      for (int i = 0 ; i < 7 ; i++) disp[i][19] = 0;
      s++;
    }
    showing();
  }
}
