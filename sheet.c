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
#define ROWLENGTH 10240

//Příkazy pro úpravu tabulky
/* Vloží řádek před zadaný řádek R > 0 */
void irow(int R)
{
}

/* Vloží nový řádek na konec */
void arow()
{
}

/* Odstraní řádek R > 0 */
void drow(int R)
{
}

/* Odstraní řádky N-M, N<=M, N=M => odstraní N */
void drows(int N, int M)
{
}

/* Vloží prázdný sloupec před sloupec C */
void icol(int C)
{
}

/* Vloží prázdný sloupec na konec */
void acol()
{
}

/* Odstraní sloupec číslo C */
void dcol(int C)
{
}

/* Odstraní sloupce N-M, N<=M, N=M => odstraní N */
void dcols(int N, int M)
{
}

//Příkazy pro zpracování dat - povinné
/* Do buňky C nastavit řetezec STR */
void cset(int C, char STR)
{
}

/* Řetězec ve sloupci C bude převeden na malá písmena */
void mytolower(int C) /* FIX ME - name of func */
{
}

/* Řetězec ve sloupci C bude převeden na velká písmena */
void mytoupper(int C) /* FIX ME - name of func */
{
}

/* Ve sloupci C zaokrouhlí na celé číslo */
void myround(int C) /* FIX ME - name of func */
{
}

/* Odstraní desetinnou část čísla ve sloupci C */
void toint(int C)
{
}

/* Přepíše obsah buňek ve sloupci M hodnozami ze sloupce N */
void copy(int N, int M)
{
}

/* Zamění hodnoty buňek ve sloupcích N a M */
void swap(int N, int M)
{
}

/* Přesune sloupec N před sloupec M */
void move(int N, int M)
{
}

/* Volání funkce podle zadanéo argumentu */

/* Zpracování argumentu */
void argsProcessing(int argCount, char const **pArg)
{
    //Výčet funkcí podle počtů potřebných paramatrů
    /* typedef enum
    {

    } zeroParamFun;

    typedef enum
    {

    } oneParamFun;

    typedef enum
    {

    } twoParamFun; */



    for (int i = 0; i < argCount; i++)
    {
        printf("%s\n", pArg[i]);
        int irow = strcmp("irow", pArg[i]);
        if (irow == 0)
            printf("IROW zadano.");
    }
}

int main(int argc, char const **argv)
{
    //řádek - pole znaků
    char row[ROWLENGTH];
    int rowCount = 0, c = 0, inC;
    argsProcessing(argc, argv);

    return 0;
}
