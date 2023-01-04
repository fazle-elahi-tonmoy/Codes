#include<stdio.h>

char F[3][3]= {{'G','G','G'},{'G','G','G'},{'G','G','G'}};
char B[3][3]= {{'B','B','B'},{'B','B','B'},{'B','B','B'}};
char U[3][3]= {{'W','W','W'},{'W','W','W'},{'W','W','W'}};
char D[3][3]= {{'Y','Y','Y'},{'Y','Y','Y'},{'Y','Y','Y'}};
char L[3][3]= {{'O','O','O'},{'O','O','O'},{'O','O','O'}};
char R[3][3]= {{'R','R','R'},{'R','R','R'},{'R','R','R'}};
char T[3];
int i,j;
int count=0;

int main()
{
    display_cube();
    getch();
    for(int i=0; i<20; i++){
        int x= rand()/2730;
        if(x==0) r_clock();
        else if(x==1) f_clock();
        else if(x==2) d_clock();
        else if(x==3) l_clock();
        else if(x==4) u_clock();
        else if(x==5) b_clock();
        else if(x==6) r_anti_clock();
        else if(x==7) f_anti_clock();
        else if(x==8) d_anti_clock();
        else if(x==9) l_anti_clock();
        else if(x==10) u_anti_clock();
        else if(x==11) b_anti_clock();
    }
    display_cube();
    getch();
    first_step(); //cross matching
    display_cube();
    second_step(); //corner matching
    display_cube();
    third_step();  //edge matching....2nd layer complete
    display_cube();
    fourth_step(); // down side cross matching
    display_cube();
    fifth_step(); //down side full matching
    display_cube();
    sixth_step(); //OLL algorithm
    display_cube();
    seventh_step(); //PLL algorithm and final solving
    display_cube();
    printf("\n\n\t\t total movement done : %d \n\n",count);
    //cube solving done!!
}

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

void display_cube()
{
    printf("\n");
    for(j=0; j<=2; j++)
    {
        printf("          ");
        for(i=0; i<=2; i++)
            printf("%c ",B[i][j]);
        printf("\n");
    }
    printf("\n  ");
    for(j=0; j<=2; j++)
    {
        for(i=0; i<=2; i++)
            printf("%c ",L[i][j]);
        printf("  ");
        for(i=0; i<=2; i++)
            printf("%c ",U[i][j]);
        printf("  ");
        for(i=0; i<=2; i++)
            printf("%c ",R[i][j]);
        printf("  ");
        for(i=0; i<=2; i++)
            printf("%c ",D[i][j]);
        printf("\n  ");
    }
    printf("\n");
    for(j=0; j<=2; j++)
    {
        printf("          ");
        for(i=0; i<=2; i++)
            printf("%c ",F[i][j]);
        printf("\n");
    }
    printf("\n-------------------------------------------------------------------------\n");
}


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
