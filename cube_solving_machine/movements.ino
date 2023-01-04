void f_clock()
{
    for(i=0; i<=2; i++)
    {
        T[i]=L[i][2];
        L[i][2]=D[i][2];
        D[i][2]=R[i][2];
        R[i][2]=U[i][2];
        U[i][2]=T[i];
    }
    for(i=0; i<=1; i++)
    {
        T[i]=F[0][i];
        F[0][i]=F[i][2];
        F[i][2]=F[2][2-i];
        F[2][2-i]=F[2-i][0];
        F[2-i][0]=T[i];
    }
    count++;
}
void f_anti_clock()
{
    for(i=0; i<=2; i++)
    {
        T[i]=L[i][2];
        L[i][2]=U[i][2];
        U[i][2]=R[i][2];
        R[i][2]=D[i][2];
        D[i][2]=T[i];
    }
    for(i=0; i<=1; i++)
    {
        T[i]=F[0][i];
        F[0][i]=F[2-i][0];
        F[2-i][0]=F[2][2-i];
        F[2][2-i]=F[i][2];
        F[i][2]=T[i];
    }
    count++;
}
void b_clock()
{
    for(i=0; i<=2; i++)
    {
        T[i]=L[i][0];
        L[i][0]=D[i][0];
        D[i][0]=R[i][0];
        R[i][0]=U[i][0];
        U[i][0]=T[i];
    }
    for(i=0; i<=1; i++)
    {
        T[i]=B[0][i];
        B[0][i]=B[2-i][0];
        B[2-i][0]=B[2][2-i];
        B[2][2-i]=B[i][2];
        B[i][2]=T[i];
    }
    count++;
}
void b_anti_clock()
{
    for(i=0; i<=2; i++)
    {
        T[i]=L[i][0];
        L[i][0]=U[i][0];
        U[i][0]=R[i][0];
        R[i][0]=D[i][0];
        D[i][0]=T[i];
    }
    for(i=0; i<=1; i++)
    {
        T[i]=B[0][i];
        B[0][i]=B[i][2];
        B[i][2]=B[2][2-i];
        B[2][2-i]=B[2-i][0];
        B[2-i][0]=T[i];
    }
    count++;
}
void u_clock()
{
    for(i=0; i<=2; i++)
    {
        T[i]=L[2][i];
        L[2][i]=F[i][0];
        F[i][0]=R[0][2-i];
        R[0][2-i]=B[2-i][2];
        B[2-i][2]=T[i];
    }
    for(i=0; i<=1; i++)
    {
        T[i]=U[0][i];
        U[0][i]=U[i][2];
        U[i][2]=U[2][2-i];
        U[2][2-i]=U[2-i][0];
        U[2-i][0]=T[i];
    }
    count++;
}
void u_anti_clock()
{
    for(i=0; i<=2; i++)
    {
        T[i]=L[2][i];
        L[2][i]=B[2-i][2];
        B[2-i][2]=R[0][2-i];
        R[0][2-i]=F[i][0];
        F[i][0]=T[i];
    }
    for(i=0; i<=1; i++)
    {
        T[i]=U[0][i];
        U[0][i]=U[2-i][0];
        U[2-i][0]=U[2][2-i];
        U[2][2-i]=U[i][2];
        U[i][2]=T[i];
    }
    count++;
}
void d_anti_clock()
{
    for(i=0; i<=2; i++)
    {
        T[i]=L[0][i];
        L[0][i]=B[2-i][0];
        B[2-i][0]=R[2][2-i];
        R[2][2-i]=F[i][2];
        F[i][2]=T[i];
    }
    for(i=0; i<=1; i++)
    {
        T[i]=D[0][i];
        D[0][i]=D[i][2];
        D[i][2]=D[2][2-i];
        D[2][2-i]=D[2-i][0];
        D[2-i][0]=T[i];
    }
    count++;
}
void d_clock()
{
    for(i=0; i<=2; i++)
    {
        T[i]=L[0][i];
        L[0][i]=F[i][2];
        F[i][2]=R[2][2-i];
        R[2][2-i]=B[2-i][0];
        B[2-i][0]=T[i];
    }
    for(i=0; i<=1; i++)
    {
        T[i]=D[0][i];
        D[0][i]=D[2-i][0];
        D[2-i][0]=D[2][2-i];
        D[2][2-i]=D[i][2];
        D[i][2]=T[i];
    }
    count++;
}

void l_clock()
{
    for(i=0; i<=2; i++)
    {
        T[i]=B[0][i];
        B[0][i]=D[2][2-i];
        D[2][2-i]=F[0][i];
        F[0][i]=U[0][i];
        U[0][i]=T[i];
    }
    for(i=0; i<=1; i++)
    {
        T[i]=L[0][i];
        L[0][i]=L[i][2];
        L[i][2]=L[2][2-i];
        L[2][2-i]=L[2-i][0];
        L[2-i][0]=T[i];
    }
    count++;
}

void l_anti_clock()
{
    for(i=0; i<=2; i++)
    {
        T[i]=B[0][i];
        B[0][i]=U[0][i];
        U[0][i]=F[0][i];
        F[0][i]=D[2][2-i];
        D[2][2-i]=T[i];
    }
    for(i=0; i<=1; i++)
    {
        T[i]=L[0][i];
        L[0][i]=L[2-i][0];
        L[2-i][0]=L[2][2-i];
        L[2][2-i]=L[i][2];
        L[i][2]=T[i];
    }
    count++;
}

void r_clock()
{
    for(i=0; i<=2; i++)
    {
        T[i]=B[2][i];
        B[2][i]=U[2][i];
        U[2][i]=F[2][i];
        F[2][i]=D[0][2-i];
        D[0][2-i]=T[i];
    }
    for(i=0; i<=1; i++)
    {
        T[i]=R[0][i];
        R[0][i]=R[i][2];
        R[i][2]=R[2][2-i];
        R[2][2-i]=R[2-i][0];
        R[2-i][0]=T[i];
    }
    count++;
}

void r_anti_clock()
{
    for(i=0; i<=2; i++)
    {
        T[i]=B[2][i];
        B[2][i]=D[0][2-i];
        D[0][2-i]=F[2][i];
        F[2][i]=U[2][i];
        U[2][i]=T[i];
    }
    for(i=0; i<=1; i++)
    {
        T[i]=R[0][i];
        R[0][i]=R[2-i][0];
        R[2-i][0]=R[2][2-i];
        R[2][2-i]=R[i][2];
        R[i][2]=T[i];
    }
    count++;
}
