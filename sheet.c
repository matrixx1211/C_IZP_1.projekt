/*                            IZP projekt č.1                                */
/*                            Marek Bitomský                                 */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*      Cílem projektu je vytvořit tabulkový editor na příkazové řádce.      */

#include <stdio.h>
#include <string.h>

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
int main(int argc, char const *argv[])
{
    for (int i = 0; (i = getchar()) != EOF;)
    {
        printf("%c", i);
    }
    
    return 0;
}
