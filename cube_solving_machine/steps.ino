void first_step()
{
    while(1)
    {
        if(U[0][1]==U[1][1] && U[1][0]==U[1][1] && U[2][1]==U[1][1] && U[1][2]==U[1][1] && L[2][1]==L[1][1] && R[0][1]==R[1][1] && F[1][0]==F[1][1] && B[1][2]==B[1][1])
            break;
        else if(U[0][1]==U[1][1] && L[2][1] != L[1][1])
        {
            l_clock();
            l_clock();
        }

        else if(U[1][0]==U[1][1] && B[1][2] != B[1][1])
        {
            b_clock();
            b_clock();
        }
        else if(U[2][1]==U[1][1] && R[0][1] != R[1][1])
        {
            r_clock();
            r_clock();
        }
        else if(U[1][2]==U[1][1] && F[1][0] != F[1][1])
        {
            f_clock();
            f_clock();
        }
        //.....................................left portion
        else if(L[1][0]==U[1][1])
        {
            b_anti_clock();
            d_anti_clock();
            b_clock();
        }
        else if(L[2][1]==U[1][1])
        {
            l_anti_clock();
            b_anti_clock();
            d_anti_clock();
            b_clock();
        }
        else if(L[1][2]==U[1][1])
        {
            f_anti_clock();
            d_clock();
            f_clock();
        }
        else if(L[0][1]==U[1][1])
        {
            l_clock();
            b_anti_clock();
            d_anti_clock();
            d_anti_clock();
            b_clock();
            l_anti_clock();
        }
        //................................................right portion
        else if(R[1][0]==U[1][1])
        {
            b_clock();
            d_clock();
            b_anti_clock();
        }
        else if(R[0][1]==U[1][1])
        {
            r_clock();
            b_clock();
            d_clock();
            b_anti_clock();
        }
        else if(R[1][2]==U[1][1])
        {
            f_clock();
            d_anti_clock();
            f_anti_clock();
        }
        else if(R[2][1]==U[1][1])
        {
            r_clock();
            f_clock();
            d_anti_clock();
            d_anti_clock();
            f_anti_clock();
            r_anti_clock();
        }

        //..........................................front portion
        else if(F[0][1]==U[1][1])
        {
            l_clock();
            d_anti_clock();
            l_anti_clock();
        }
        else if(F[1][0]==U[1][1])
        {
            f_anti_clock();
            l_clock();
            d_anti_clock();
            l_anti_clock();
        }
        else if(F[2][1]==U[1][1])
        {
            r_anti_clock();
            d_clock();
            r_clock();
        }
        else if(F[1][2]==U[1][1])
        {
            f_anti_clock();
            r_anti_clock();
            d_anti_clock();
            d_anti_clock();
            r_clock();
            f_clock();
        }
        //.............................................................back portion
        else if(B[0][1]==U[1][1])
        {
            l_anti_clock();
            d_clock();
            l_clock();
        }
        else if(B[1][2]==U[1][1])
        {
            b_anti_clock();
            l_anti_clock();
            d_clock();
            l_clock();
        }
        else if(B[2][1]==U[1][1])
        {
            r_clock();
            d_anti_clock();
            r_anti_clock();
        }
        else if(B[1][0]==U[1][1])
        {
            b_anti_clock();
            r_clock();
            d_anti_clock();
            d_anti_clock();
            r_anti_clock();
            b_clock();
        }
        //display_cube();
        alg1();
    }
}

void second_step()
{
    while(1)
    {
        //display_cube();
        //if(U[0][0]==U[0][2]==U[2][0]==U[2][2]==U[1][1] && L[2][0]==L[2][2]==L[1][1] && R[0][0]==R[0][2]==R[1][1] && B[0][2]==B[2][2]==B[1][1] && F[0][0]==F[2][0]==F[1][1])
        if(U[0][0]==U[1][1] && U[0][2]==U[1][1] && U[2][0]==U[1][1] && U[2][2]==U[1][1] && L[2][0]==L[1][1] && L[2][2]==L[1][1] && R[0][0]==R[1][1] && R[0][2]==R[1][1] && B[0][2]==B[1][1] && B[2][2]==B[1][1] && F[0][0]==F[1][1] && F[2][0]==F[1][1])
            break;
        else if((L[2][0]!=L[1][1] && U[0][0]==U[1][1]) || L[2][0]==U[1][1] || U[1][1]==B[0][2])
        {
            b_anti_clock();
            d_clock();
            b_clock();
            alg2();
        }
        else if((L[1][1]!=L[2][2] && U[0][2]==U[1][1]) || U[1][1]==L[2][2] || F[0][0]==U[1][1])
        {
            f_anti_clock();
            d_anti_clock();
            f_clock();
            alg2();
        }
        else if((F[2][0]!=F[1][1] && U[2][2]==U[1][1]) || F[2][0]==U[1][1] || R[0][2]==U[1][1])
        {
            f_clock();
            d_clock();
            f_anti_clock();
            alg2();
        }
        else if((B[2][2]!=B[1][1] && U[2][0]==U[1][1]) || B[2][2]==U[1][1] || R[0][0]==U[1][1])
        {
            b_clock();
            d_anti_clock();
            b_anti_clock();
            alg2();
        }
        else
            alg2();
    }
}

void third_step()
{
    while(1)
    {
        //display_cube();
        if(L[1][0]==L[1][1] && L[1][2]==L[1][1] && F[0][1]==F[1][1] && F[2][1]==F[1][1] && R[1][2]==R[1][1] && R[1][0]==R[1][1] && B[2][1]==B[1][1] && B[0][1]==B[1][1])
            break;
        else if(L[1][0]!=D[1][1] && B[0][1]!=D[1][1] && (L[1][0]!=L[1][1] || B[0][1]!=B[1][1]))
        {
            b_anti_clock();
            d_clock();
            b_clock();
            alg2();
            alg3();
        }
        else if(L[1][2]!=D[1][1] && F[0][1]!=D[1][1] && (L[1][2]!=L[1][1] || F[0][1]!=F[1][1]))
        {
            f_anti_clock();
            d_anti_clock();
            f_clock();
            alg2();
            alg3();
        }
        else if(F[2][1]!=D[1][1] && R[1][2]!=D[1][1] && (F[2][1]!=F[1][1] || R[1][2]!=R[1][1]))
        {
            f_clock();
            d_clock();
            f_anti_clock();
            alg2();
            alg3();
        }
        else if(R[1][0]!=D[1][1] && B[2][1]!=D[1][1] && (R[1][0]!=R[1][1] || B[2][1]!=B[1][1]))
        {
            b_clock();
            d_anti_clock();
            b_anti_clock();
            alg2();
            alg3();
        }
        else alg3();
    }
}

void fourth_step()
{
    if(D[0][1]==D[1][1] && D[1][0]==D[1][1] && D[2][1]==D[1][1] && D[1][2]==D[1][1])
        return;
    int t=0;
    while(1)
    {
        if(t==4)
        {
            alg4();
            d_clock();
            d_clock();
            alg4();
            alg4();
            break;
        }
        if(D[1][0]==D[1][1] && D[2][1]==D[1][1] && D[1][2]==D[1][1] && D[0][1]==D[1][1])
            break;
        else if(D[1][0]==D[1][1] && D[2][1]==D[1][1])
        {
            alg4();
            alg4();
            break;
        }
        else if(D[1][0]==D[1][1] && D[1][2]==D[1][1])
        {
            alg4();
            break;
        }
        else
            d_clock();
        t++;

    }
}

void fifth_step()
{
    if(D[0][0]==D[1][1] && D[0][2]==D[1][1] && D[2][2]==D[1][1] && D[2][0]==D[1][1])
        return;
    else if(D[0][0]!=D[1][1] && D[0][2]!=D[1][1] && D[2][2]!=D[1][1] && D[2][0]!=D[1][1])
    {
        while(B[2][0]!=D[1][1] || F[2][2]!=D[1][1]) d_anti_clock();
        alg5();
        while (D[0][0]!=D[1][1]) d_anti_clock();
        alg5();
    }
    else
    {
        while(1)
        {
            if(D[0][0]!=D[1][1] && D[0][2]==D[1][1] && D[2][2]==D[1][1] && D[2][0]!=D[1][1])
            {
                alg5();
                if(D[0][0]==D[1][1] || D[0][2]==D[1][1] || D[2][2]==D[1][1] || D[2][0]==D[1][1])
                {
                    while (D[0][0]!=D[1][1]) d_anti_clock();
                    alg5();
                    while (D[0][0]!=D[1][1]) d_anti_clock();
                    alg5();
                }
                else
                {
                    while(B[2][0]!=D[1][1] || F[2][2]!=D[1][1]) d_anti_clock();
                    alg5();
                    while (D[0][0]!=D[1][1]) d_anti_clock();
                    alg5();
                }
                break;
            }

            else if(D[0][0]!=D[1][1] && D[0][2]==D[1][1] && D[2][2]!=D[1][1] && D[2][0]==D[1][1])
            {
                alg5();
                if(D[0][0]==D[1][1] || D[0][2]==D[1][1] || D[2][2]==D[1][1] || D[2][0]==D[1][1])
                {
                    while (D[0][0]!=D[1][1]) d_anti_clock();
                    alg5();
                    while (D[0][0]!=D[1][1]) d_anti_clock();
                    alg5();
                }
                else
                {
                    while(B[2][0]!=D[1][1] || F[2][2]!=D[1][1]) d_anti_clock();
                    alg5();
                    while (D[0][0]!=D[1][1]) d_anti_clock();
                    alg5();
                }
                break;
            }

            else if(D[0][0]==D[1][1] && D[0][2]!=D[1][1] && D[2][2]!=D[1][1] && D[2][0]!=D[1][1])
            {
                alg5();
                if(D[0][0]==D[1][1] && D[0][2]==D[1][1] && D[2][2]==D[1][1] && D[2][0]==D[1][1])
                    break;
                else
                {
                    while (D[0][0]!=D[1][1]) d_anti_clock();
                    alg5();
                    break;
                }
            }

            else d_anti_clock();
        }
    }
}

void sixth_step()
{
    if(B[0][0]==B[2][0] && R[2][0]==R[2][2] && F[2][2]==F[0][2] && L[0][2]==L[0][0])
        return;
    else
    {
        if(B[0][0]==B[2][0] || R[2][0]==R[2][2] || F[2][2]==F[0][2] || L[0][2]==L[0][0])
        {
            while(L[0][0]!=L[0][2]) d_anti_clock();
            alg6();
        }
        else
        {
            alg6();
            while(L[0][0]!=L[0][2]) d_anti_clock();
            alg6();
        }
    }
}

void seventh_step()
{
    if(B[0][0]==B[1][0] && B[2][0]==B[1][0] && R[2][0]==R[2][1] && R[2][2]==R[2][1] && F[0][2]==F[1][2] && F[1][2]==F[2][2] && L[0][0]==L[0][1] && L[0][1]==L[0][2])
    {
        while(B[1][0]!=B[1][1]) d_anti_clock();
        return;
    }
    else if((B[0][0]==B[1][0] && B[2][0]==B[1][0]) || (R[2][0]==R[2][1] && R[2][2]==R[2][1]) || (F[0][2]==F[1][2] && F[1][2]==F[2][2]) || (L[0][0]==L[0][1] && L[0][1]==L[0][2]))
    {
        while(L[0][0]!=L[0][1] || L[0][1]!=L[0][2]) d_anti_clock();
        if(R[2][1]==B[0][0]) alg7(1);
        else if(R[2][1]==F[2][2]) alg7(2);
        while(B[1][0]!=B[1][1]) d_anti_clock();
    }
    else
    {
        alg7(1);
        while(L[0][0]!=L[0][1] || L[0][1]!=L[0][2]) d_anti_clock();
        if(R[2][1]==B[0][0]) alg7(1);
        else if(R[2][1]==F[2][2]) alg7(2);
        while(B[1][0]!=B[1][1]) d_anti_clock();
    }
}
