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
void cset(int C, char const *STR)
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

/* Prototyp funkce readrow */
void readrow(int argCount, char const **pArg);

/* Zpracování argumentu */
void argsProcessing(int argCount, char const **pArg)
{
    //Podle argumentů v příkazové řádce volá funkce programu
    for (int i = 0; i < argCount; i++)
    {
        if (strcmp("irow", pArg[i]) == 0) irow(*pArg[i+1]);
        if (strcmp("arow", pArg[i]) == 0) arow();
        if (strcmp("drow", pArg[i]) == 0) drow(*pArg[i+1]);
        if (strcmp("drows", pArg[i]) == 0) drows(*pArg[i+1], *pArg[i+2]);
        if (strcmp("icol", pArg[i]) == 0) icol(*pArg[i+1]);
        if (strcmp("acol", pArg[i]) == 0) acol();
        if (strcmp("dcol", pArg[i]) == 0) dcol(*pArg[i+1]);
        if (strcmp("dcols", pArg[i]) == 0) dcols(*pArg[i+1], *pArg[i+2]);
        if (strcmp("cset", pArg[i]) == 0) cset(*pArg[i+1], pArg[i+2]);
        if (strcmp("tolower", pArg[i]) == 0) mytolower(*pArg[i+1]);
        if (strcmp("toupper", pArg[i]) == 0) mytoupper(*pArg[i+1]);
        if (strcmp("round", pArg[i]) == 0) myround(*pArg[i+1]);
        if (strcmp("int", pArg[i]) == 0) toint(*pArg[i+1]);
        if (strcmp("copy", pArg[i]) == 0) copy(*pArg[i+1], *pArg[i+2]);
        if (strcmp("swap", pArg[i]) == 0) swap(*pArg[i+1], *pArg[i+2]);
        if (strcmp("move", pArg[i]) == 0) move(*pArg[i+1], *pArg[i+2]);
        /* FIX ME: nutno přidat kontrolu jestli existuje *pArg[i+?], v případě že není zadáno error */
    }
    readrow(argCount, pArg);
}

void readrow(int argCount, char const **pArg)
{
    int inC;
    while ((inC = getchar()) != EOF)
    {
        printf("%c", inC);
        if (inC == '\n')
        {
            //pokud konec řádku zavolej funkci, která udělá pro řádek
            argsProcessing(argCount, pArg);
            break; /* Musíš tu být ??? */
        }
    }
    return;
}

int main(int argc, char const **argv)
{
    readrow(argc, argv);
    return 0;
}
