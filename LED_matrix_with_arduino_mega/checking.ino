void checking(char a[], int b, int pos) {
  for (int p = b * 4 ; p < 4 + b * 4; p++)
    for (int i = 0; i < 7 ; i++)
      for (int j = 0; j < 5; j++) {
        if (a[p] == 'A') disp[i][j + (p - b * 4) * 5 + pos] = A[i][j];
        else if (a[p] == 'B') disp[i][j + (p - b * 4) * 5 + pos] = B[i][j];
        else if (a[p] == 'C') disp[i][j + (p - b * 4) * 5 + pos] = C[i][j];
        else if (a[p] == 'D') disp[i][j + (p - b * 4) * 5 + pos] = D[i][j];
        else if (a[p] == 'E') disp[i][j + (p - b * 4) * 5 + pos] = E[i][j];
        else if (a[p] == 'F') disp[i][j + (p - b * 4) * 5 + pos] = F[i][j];
        else if (a[p] == 'G') disp[i][j + (p - b * 4) * 5 + pos] = G[i][j];
        else if (a[p] == 'H') disp[i][j + (p - b * 4) * 5 + pos] = H[i][j];
        else if (a[p] == 'I') disp[i][j + (p - b * 4) * 5 + pos] = I[i][j];
        else if (a[p] == 'J') disp[i][j + (p - b * 4) * 5 + pos] = J[i][j];
        else if (a[p] == 'K') disp[i][j + (p - b * 4) * 5 + pos] = K[i][j];
        else if (a[p] == 'L') disp[i][j + (p - b * 4) * 5 + pos] = L[i][j];
        else if (a[p] == 'M') disp[i][j + (p - b * 4) * 5 + pos] = M[i][j];
        else if (a[p] == 'N') disp[i][j + (p - b * 4) * 5 + pos] = N[i][j];
        else if (a[p] == 'O') disp[i][j + (p - b * 4) * 5 + pos] = O[i][j];
        else if (a[p] == 'P') disp[i][j + (p - b * 4) * 5 + pos] = P[i][j];
        else if (a[p] == 'Q') disp[i][j + (p - b * 4) * 5 + pos] = Q[i][j];
        else if (a[p] == 'R') disp[i][j + (p - b * 4) * 5 + pos] = R[i][j];
        else if (a[p] == 'S') disp[i][j + (p - b * 4) * 5 + pos] = S[i][j];
        else if (a[p] == 'T') disp[i][j + (p - b * 4) * 5 + pos] = T[i][j];
        else if (a[p] == 'U') disp[i][j + (p - b * 4) * 5 + pos] = U[i][j];
        else if (a[p] == 'V') disp[i][j + (p - b * 4) * 5 + pos] = V[i][j];
        else if (a[p] == 'W') disp[i][j + (p - b * 4) * 5 + pos] = W[i][j];
        else if (a[p] == 'X') disp[i][j + (p - b * 4) * 5 + pos] = X[i][j];
        else if (a[p] == 'Y') disp[i][j + (p - b * 4) * 5 + pos] = Y[i][j];
        else if (a[p] == 'Z') disp[i][j + (p - b * 4) * 5 + pos] = Z[i][j];
        else disp[i][j + (p - b * 4) * 5 + pos] = nil[i][j];
      }
}
