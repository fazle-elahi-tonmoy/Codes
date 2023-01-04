void alg1()
{
    while(1)
    {
        //display_cube();
        if(U[0][1]==U[1][1] && U[1][0]==U[1][1] && U[2][1]==U[1][1] && U[1][2]==U[1][1] && L[2][1]==L[1][1] && R[0][1]==R[1][1] && F[1][0]==F[1][1] && B[1][2]==B[1][1])
            break;
        else if(F[1][1]==F[1][2] && D[1][2]==U[1][1])
        {
            f_clock();
            f_clock();
            break;
        }
        else if(R[1][1]==R[2][1] && D[0][1]==U[1][1])
        {
            r_clock();
            r_clock();
            break;
        }

        else if(B[1][1]==B[1][0] && D[1][0]==U[1][1])
        {
            b_clock();
            b_clock();
            break;
        }
        else if(L[1][1]==L[0][1] && D[2][1]==U[1][1])
        {
            l_clock();
            l_clock();
            break;
        }
        else
            d_anti_clock();
    }
}

void alg2()
{
b:
    if(U[0][0]==U[1][1] && U[0][2]==U[1][1] && U[2][0]==U[1][1] && U[2][2]==U[1][1] && L[2][0]==L[1][1] && L[2][2]==L[1][1] && R[0][0]==R[1][1] && R[0][2]==R[1][1] && B[0][2]==B[1][1] && B[2][2]==B[1][1] && F[0][0]==F[1][1] && F[2][0]==F[1][1])
        return;
    else if(L[1][1]==L[0][2] && F[0][2]==U[1][1])
    {
        d_anti_clock();
        l_clock();
        d_clock();
        l_anti_clock();
    }

    else if(L[1][1]==L[0][0] && B[0][0]==U[1][1])
    {
        d_clock();
        l_anti_clock();
        d_anti_clock();
        l_clock();
    }
    else if(R[1][1]==R[2][0] && B[2][0]==U[1][1])
    {
        d_anti_clock();
        r_clock();
        d_clock();
        r_anti_clock();
    }
    else if(R[1][1]==R[2][2] && F[2][2]==U[1][1])
    {
        d_clock();
        r_anti_clock();
        d_anti_clock();
        r_clock();
    }
    else if(B[1][1]==B[0][0] && L[0][0]==U[1][1])
    {
        d_anti_clock();
        b_anti_clock();
        d_clock();
        b_clock();
    }
    else if(B[1][1]==B[2][0] && R[2][0]==U[1][1])
    {
        d_clock();
        b_clock();
        d_anti_clock();
        b_anti_clock();
    }
    else if(F[1][1]==F[2][2] && R[2][2]==U[1][1])
    {
        d_anti_clock();
        f_clock();
        d_clock();
        f_anti_clock();
    }
    else if(F[1][1]==F[0][2] && L[0][2]==U[1][1])
    {
        d_clock();
        f_anti_clock();
        d_anti_clock();
        f_clock();
    }
    else if(F[0][2]==L[1][1] && L[0][2]==F[1][1])
    {
        for(int i=1; i<=3; i++)
        {
            f_anti_clock();
            d_clock();
            f_clock();
            d_anti_clock();
        }
    }
    else if(F[2][2]==R[1][1] && R[2][2]==F[1][1])
    {
        for(int i=1; i<=3; i++)
        {
            r_anti_clock();
            d_clock();
            r_clock();
            d_anti_clock();
        }
    }
    else if(B[2][0]==R[1][1] && R[2][0]==B[1][1])
    {
        for(int i=1; i<=3; i++)
        {
            b_clock();
            d_clock();
            b_anti_clock();
            d_anti_clock();
        }
    }
    else if(B[0][0]==L[1][1] && L[0][0]==B[1][1])
    {
        for(int i=1; i<=3; i++)
        {
            l_anti_clock();
            d_clock();
            l_clock();
            d_anti_clock();
        }
    }
    else
    {
        d_clock();
        goto b;
    }
}

void alg3()
{
    int t=0;
    while(t<4)
    {
        //display_cube();
        if(L[1][0]==L[1][1] && L[1][2]==L[1][1] && F[0][1]==F[1][1] && F[2][1]==F[1][1] && R[1][2]==R[1][1] && R[1][0]==R[1][1] && B[2][1]==B[1][1] && B[0][1]==B[1][1])
            break;
        else if(F[1][2]==F[1][1] && D[1][2]!=D[1][1])
        {
            if(D[1][2]==L[1][1])
            {
                d_anti_clock();
                l_clock();
                d_clock();
                l_anti_clock();
                alg2();
            }
            else if(D[1][2]==R[1][1])
            {
                d_clock();
                r_anti_clock();
                d_anti_clock();
                r_clock();
                alg2();
            }
            break;
        }
        else if(R[2][1]==R[1][1] && D[0][1]!=D[1][1])
        {
            if(D[0][1]==B[1][1])
            {
                d_clock();
                b_clock();
                d_anti_clock();
                b_anti_clock();
                alg2();
            }
            else if(D[0][1]==F[1][1])
            {
                d_anti_clock();
                f_clock();
                d_clock();
                f_anti_clock();
                alg2();
            }
            break;
        }
        else if(L[0][1]==L[1][1] && D[2][1]!=D[1][1])
        {
            if(D[2][1]==F[1][1])
            {
                d_clock();
                f_anti_clock();
                d_anti_clock();
                f_clock();
                alg2();
            }
            else if(D[2][1]==B[1][1])
            {
                d_anti_clock();
                b_anti_clock();
                d_clock();
                b_clock();
                alg2();
            }
            break;
        }
        else if(B[1][0]==B[1][1] && D[1][0]!=D[1][1])
        {
            if(D[1][0]==L[1][1])
            {
                d_clock();
                l_anti_clock();
                d_anti_clock();
                l_clock();
                alg2();
            }
            else if(D[1][0]==R[1][1])
            {
                d_anti_clock();
                r_clock();
                d_clock();
                r_anti_clock();
                alg2();
            }
            break;
        }
        else d_clock();
        t++;
    }
}

void alg4()
{
    r_clock();
    f_clock();
    d_anti_clock();
    f_anti_clock();
    d_clock();
    r_anti_clock();
}

void alg5()
{
    f_clock();
    d_anti_clock();
    f_anti_clock();
    d_anti_clock();
    f_clock();
    d_anti_clock();
    d_anti_clock();
    f_anti_clock();
}

void alg6()
{
    f_anti_clock();
    r_clock();
    f_anti_clock();
    l_clock();
    l_clock();
    f_clock();
    r_anti_clock();
    f_anti_clock();
    l_clock();
    l_clock();
    f_clock();
    f_clock();
}

void alg7(int a)
{
    r_clock();
    r_clock();
    if(a==1) d_anti_clock();
    else if(a==2) d_clock();
    b_anti_clock();
    f_anti_clock();
    r_clock();
    r_clock();
    b_clock();
    f_clock();
    if(a==1) d_anti_clock();
    else if(a==2) d_clock();
    r_clock();
    r_clock();
}
