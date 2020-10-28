/*                            IZP projekt č.1                                */
/*                            Marek Bitomský                                 */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*      Cílem projektu je vytvořit tabulkový editor na příkazové řádce.      */

//Hlavičkové soubory
#include <stdio.h>
#include <string.h>

//maximální délka řádku == 10kiB => (1024 x 10) = 10240
/* #define ROWLENGTH 10240 */

/* Volání funkce podle zadanéo argumentu */

/* Zpracování argumentu */
void argsProcessing(int argCount, char const **pArg)
{
    //Výčet funkcí podle počtů potřebných paramatrů
    enum zeroParamFun
    {
        arow,
    };

    enum oneParamFun
    {
        irow,
        drow,
        icol,
        dcol,
        tolower,
        toupper,
        round,
        int,
    };

    enum twoParamFun
    {

    };

    for (int i = 0; i < argCount; i++)
    {
        printf("%s\n", pArg[i]);
        int irow = strcmp("irow", pArg[i]);
        if (irow == 0)
            printf("IROW zadano.");
    }

    printf("%d", argCount);
}

//Prototyp funkce another
void another();

void readrow()
{
    int inC;
    while ((inC = getchar()) != EOF)
    {
        printf("%c", inC);
        if (inC == '\n')
        {
            //pokud konec řádku zavolej funkci, která udělá pro řádek
            another();
            break;
        }
    }
    return;
}

void another()
{
    printf("------------------\n");
    readrow();
    return;
}

int main(int argc, char const **argv)
{
    another();
    argsProcessing(argc, argv);

    return 0;
}
