void displayletter(char letter, int pos) {
    for (int i = 0; i < 7 ; i++)
      for (int j = 0; j < 5; j++) {
        if (letter == 'A') disp[i][j + pos] = A[i][j];
        else if (letter == 'B') disp[i][j + pos] = B[i][j];
        else if (letter == 'C') disp[i][j + pos] = C[i][j];
        else if (letter == 'D') disp[i][j + pos] = D[i][j];
        else if (letter == 'E') disp[i][j + pos] = E[i][j];
        else if (letter == 'F') disp[i][j + pos] = F[i][j];
        else if (letter == 'G') disp[i][j + pos] = G[i][j];
        else if (letter == 'H') disp[i][j + pos] = H[i][j];
        else if (letter == 'I') disp[i][j + pos] = I[i][j];
        else if (letter == 'J') disp[i][j + pos] = J[i][j];
        else if (letter == 'K') disp[i][j + pos] = K[i][j];
        else if (letter == 'L') disp[i][j + pos] = L[i][j];
        else if (letter == 'M') disp[i][j + pos] = M[i][j];
        else if (letter == 'N') disp[i][j + pos] = N[i][j];
        else if (letter == 'O') disp[i][j + pos] = O[i][j];
        else if (letter == 'P') disp[i][j + pos] = P[i][j];
        else if (letter == 'Q') disp[i][j + pos] = Q[i][j];
        else if (letter == 'R') disp[i][j + pos] = R[i][j];
        else if (letter == 'S') disp[i][j + pos] = S[i][j];
        else if (letter == 'T') disp[i][j + pos] = T[i][j];
        else if (letter == 'U') disp[i][j + pos] = U[i][j];
        else if (letter == 'V') disp[i][j + pos] = V[i][j];
        else if (letter == 'W') disp[i][j + pos] = W[i][j];
        else if (letter == 'X') disp[i][j + pos] = X[i][j];
        else if (letter == 'Y') disp[i][j + pos] = Y[i][j];
        else if (letter == 'Z') disp[i][j + pos] = Z[i][j];
        else disp[i][j + pos] = nil[i][j];
      }
}
