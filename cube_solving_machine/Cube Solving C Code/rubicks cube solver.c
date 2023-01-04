#include<stdio.h>
/*char F[3][3]= {{'1','4','7'},{'2','5','8'},{'3','6','9'}};
char B[3][3]= {{'S','V','Y'},{'T','W','Z'},{'U','X','z'}};
char U[3][3]= {{'a','d','g'},{'b','e','h'},{'c','f','i'}};
char D[3][3]= {{'j','m','p'},{'k','n','q'},{'l','o','r'}};
char L[3][3]= {{'A','D','G'},{'B','E','H'},{'C','F','I'}};
char R[3][3]= {{'J','M','P'},{'K','N','Q'},{'L','O','R'}};*/

char F[3][3]= {{'G','G','G'},{'G','G','G'},{'G','G','G'}};
char B[3][3]= {{'B','B','B'},{'B','B','B'},{'B','B','B'}};
char U[3][3]= {{'W','W','W'},{'W','W','W'},{'W','W','W'}};
char D[3][3]= {{'Y','Y','Y'},{'Y','Y','Y'},{'Y','Y','Y'}};
char L[3][3]= {{'O','O','O'},{'O','O','O'},{'O','O','O'}};
char R[3][3]= {{'R','R','R'},{'R','R','R'},{'R','R','R'}};
char T[3],temp;
int i,j;

void main()
{
    r_clock();
    f_clock();
    d_clock();
    l_clock();
    u_clock();
    b_clock();
    r_anti_clock();
    f_anti_clock();
    d_anti_clock();
    l_anti_clock();
    u_anti_clock();
    b_anti_clock();
    //b_anti_clock();
    //input_scrambled_value();
    display_cube();
    first_step(); //cross matching
    display_cube();
    second_step();
    display_cube();
}

void input_scrambled_value()
{
    for(j=0; j<=2; j++)
        for(i=0; i<=2; i++)
        {
            printf("enter the pattern for back side %d %d : ",i,j);
            scanf(" %c",&B[i][j]);
        }
    for(j=0; j<=2; j++)
        for(i=0; i<=2; i++)
        {
            printf("enter the pattern for left side %d %d : ",i,j);
            scanf(" %c",&L[i][j]);
        }
    for(j=0; j<=2; j++)
        for(i=0; i<=2; i++)
        {
            printf("enter the pattern for upper side %d %d : ",i,j);
            scanf(" %c",&U[i][j]);
        }
    for(j=0; j<=2; j++)
        for(i=0; i<=2; i++)
        {
            printf("enter the pattern for right side %d %d : ",i,j);
            scanf(" %c",&R[i][j]);
        }
    for(j=0; j<=2; j++)
        for(i=0; i<=2; i++)
        {
            printf("enter the pattern for down side %d %d : ",i,j);
            scanf(" %c",&D[i][j]);
        }
    for(j=0; j<=2; j++)
        for(i=0; i<=2; i++)
        {
            printf("enter the pattern for front side %d %d : ",i,j);
            scanf(" %c",&F[i][j]);
        }
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
}

void first_step()
{
a:
    if(D[0][1]=='W' || D[1][0]=='W' || D[2][1]=='W' || D[1][2]=='W')
        alg1();

    if(U[0][1]=='W' && L[2][1] != L[1][1])
    {
        l_clock();
        l_clock();
        alg1(); //down rotation matching
    }

    if(U[1][0]=='W' && B[1][2] != B[1][1])
    {
        b_clock();
        b_clock();
        alg1();
    }
    if(U[2][1]=='W' && R[0][1] != R[1][1])
    {
        r_clock();
        r_clock();
        alg1();
    }
    if(U[1][2]=='W' && F[1][0] != F[1][1])
    {
        r_clock();
        r_clock();
        alg1();
    }
    //.....................................left portion
    if(L[1][0]=='W')
    {
        b_anti_clock();
        d_anti_clock();
        b_clock();
        alg1();
    }
    if(L[2][1]=='W')
    {
        l_anti_clock();
        b_anti_clock();
        d_anti_clock();
        b_clock();
        alg1();
    }
    if(L[1][2]=='W')
    {
        f_anti_clock();
        d_clock();
        f_clock();
        alg1();
    }
    if(L[0][1]=='W')
    {
        l_clock();
        b_anti_clock();
        d_anti_clock();
        d_anti_clock();
        b_clock();
        l_anti_clock();
        alg1();
    }

    //................................................right portion
    if(R[1][0]=='W')
    {
        b_clock();
        d_clock();
        b_anti_clock();
        alg1();
    }
    if(R[0][1]=='W')
    {
        r_clock();
        b_clock();
        d_clock();
        b_anti_clock();
        alg1();
    }
    if(R[1][2]=='W')
    {
        f_clock();
        d_anti_clock();
        f_anti_clock();
        alg1();
    }
    if(R[2][1]=='W')
    {
        r_clock();
        f_clock();
        d_anti_clock();
        d_anti_clock();
        f_anti_clock();
        r_anti_clock();
        alg1();
    }

    //..........................................front portion
    if(F[0][1]=='W')
    {
        l_clock();
        d_anti_clock();
        l_anti_clock();
        alg1();
    }
    if(F[1][0]=='W')
    {
        f_anti_clock();
        l_clock();
        d_anti_clock();
        l_anti_clock();
        alg1();
    }
    if(F[2][1]=='W')
    {
        r_anti_clock();
        d_clock();
        r_clock();
        alg1();
    }
    if(F[1][2]=='W')
    {
        f_anti_clock();
        r_anti_clock();
        d_anti_clock();
        d_anti_clock();
        r_clock();
        f_clock();
        alg1();
    }

    //.............................................................back portion
    if(B[0][1]=='W')
    {
        l_anti_clock();
        d_clock();
        l_clock();
        alg1();
    }
    if(B[1][2]=='W')
    {
        b_anti_clock();
        l_anti_clock();
        d_clock();
        l_clock();
        alg1();
    }
    if(B[2][1]=='W')
    {
        r_clock();
        d_anti_clock();
        r_anti_clock();
        alg1();
    }
    if(B[1][0]=='W')
    {
        b_anti_clock();
        r_clock();
        d_anti_clock();
        d_anti_clock();
        r_anti_clock();
        b_clock();
        alg1();
    }

    if(U[0][1]!='W' || U[1][0]!='W' || U[2][1]!='W' || U[1][2]!='W' || L[2][1]!=L[1][1] || R[0][1]!=R[1][1] || F[1][0]!=F[1][1]|| B[1][2]!=B[1][1])
        goto a;

}

void second_step()
{
    while(1)
    {
        //display_cube();
        //if(U[0][0]==U[0][2]==U[2][0]==U[2][2]==U[1][1] && L[2][0]==L[2][2]==L[1][1] && R[0][0]==R[0][2]==R[1][1] && B[0][2]==B[2][2]==B[1][1] && F[0][0]==F[2][0]==F[1][1])
        if(U[0][0]=='W' && U[0][2]=='W' && U[2][0]=='W' && U[2][2]=='W' && L[2][0]=='O' && L[2][2]=='O' && R[0][0]=='R' && R[0][2]=='R' && B[0][2]=='B' && B[2][2]=='B' && F[0][0]=='G' && F[2][0]=='G')
            break;
        else if((L[1][1]!=L[2][0] && U[0][0]==U[1][1]) || U[1][1]==L[2][0] || U[1][1]==B[0][2])
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
            b_clock();
            alg2();
        }
        else
            alg2();
    }
}


void alg1()
{
    while(1)
    {
        if(F[1][1]==F[1][2] && D[1][2]=='W')
        {
            f_clock();
            f_clock();
            break;
        }
        else if(R[1][1]==R[2][1] && D[0][1]=='W')
        {
            r_clock();
            r_clock();
            break;
        }

        else if(B[1][1]==B[1][0] && D[1][0]=='W')
        {
            b_clock();
            b_clock();
            break;
        }
        else if(L[1][1]==L[0][1] && D[2][1]=='W')
        {
            l_clock();
            l_clock();
            break;
        }
        else
            d_anti_clock();
        //display_cube();
    }
    return;
}

void alg2()
{
b:
        if(U[0][0]=='W' && U[0][2]=='W' && U[2][0]=='W' && U[2][2]=='W' && L[2][0]=='O' && L[2][2]=='O' && R[0][0]=='R' && R[0][2]=='R' && B[0][2]=='B' && B[2][2]=='B' && F[0][0]=='G' && F[2][0]=='G')
            return;
        else if(L[1][1]==L[0][2] && F[0][2]=='W')
        {
            d_anti_clock();
            l_clock();
            d_clock();
            l_anti_clock();
        }

        else if(L[1][1]==L[0][0] && B[0][0]=='W')
        {
            d_clock();
            l_anti_clock();
            d_anti_clock();
            l_clock();
        }
        else if(R[1][1]==R[2][0] && B[2][0]=='W')
        {
            d_anti_clock();
            r_clock();
            d_clock();
            r_anti_clock();
        }
        else if(R[1][1]==R[2][2] && F[2][2]=='W')
        {
            d_clock();
            r_anti_clock();
            d_anti_clock();
            r_clock();
        }
        else if(B[1][1]==B[0][0] && L[0][0]=='W')
        {
            d_anti_clock();
            b_anti_clock();
            d_clock();
            b_clock();
        }
        else if(B[1][1]==B[2][0] && R[2][0]=='W')
        {
            d_clock();
            b_clock();
            d_anti_clock();
            b_anti_clock();
        }
        else if(F[1][1]==F[2][2] && R[2][2]=='W')
        {
            d_anti_clock();
            f_clock();
            d_clock();
            f_anti_clock();
        }
        else if(F[1][1]==F[0][2] && L[0][2]=='W')
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
        //display_cube();
}
