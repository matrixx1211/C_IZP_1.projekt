/*                            IZP projekt č.1                                */
/*                            Marek Bitomský                                 */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*      Cílem projektu je vytvořit tabulkový editor na příkazové řádce.      */

//Hlavičkové soubory
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

//maximální délka řádku == 10kiB => (1024 x 10) = 10240
#define ROWLENGTH 10240

/* Funkce usage pro vypsání jak by měl být program správně spuštěn v případě, 
že byl spuštěn nesprávně. */
int usage()
{
    printf("Program byl spusten spatne. Pro spravne spusteny zadej:\n"
    "V pripade OS Linux: \n"
    "./sheet [-d DELIM] [Prikazy pro upravu tabulky]\n"
    "./sheet [-d DELIM] [Selekce radku] [Prikaz pro zpracovani dat]\n"
    "V pripade OS Windows: \n"
    "sheet.exe [-d DELIM] [Prikazy pro upravu tabulky]\n"
    "sheet.exe [-d DELIM] [Selekce radku] [Prikaz pro zpracovani dat]\n"
    "--------------------------------------------------------------------------------\n"
    "                                   [-d DELIM]\n"
    "--------------------------------------------------------------------------------\n"
    "Argument -d specifikuje, jake znaky lze interpretovat jako oddelovace bunek.\n"
    "Ve vychozim nastaveni je DELIM retezec obsahujici mezeru.\n"
    "Prvni znak z retezce DELIM bude pouzit jako oddelovac vystupnich hodnot.\n"
    "--------------------------------------------------------------------------------\n"
    "                         [Prikazy pro upravu tabulky]\n"
    "--------------------------------------------------------------------------------\n"
    "irow R - vlozi radek tabulky pred radek R > 0 (insert-row).\n"
    "arow - prida novy radek tabulky na konec tabulky (append-row).\n"
    "drow R - odstrani radek cislo R > 0 (delete-row).\n"
    "drows N M - odstrani radky N az M (N <= M).\n"
    "\tV pripade N=M se prikaz chova stejne jako drow N.\n"
    "icol C - vlozi prazdny sloupec pred sloupec dany cislem C.\n"
    "acol - prida prazdny sloupec za posledni sloupec.\n"
    "dcol C - odstrani sloupec cislo C.\n"
    "dcols N M - odstrani sloupce N az M (N <= M).\n"
    "\tV pripade N=M se prikaz chova stejne jako dcol N.\n"
    "--------------------------------------------------------------------------------\n"
    "                         [Prikaz pro zpracovani dat]\n"
    "--------------------------------------------------------------------------------\n"
    "cset C STR - do bunky ve sloupci C bude nastaven retezec STR.\n"
    "tolower C - retezec ve sloupci C bude preveden na mala pismena.\n"
    "toupper C - retezec ve sloupce C bude preveden na velka pismena.\n"
    "round C - ve sloupci C zaokrouhli cislo na cele cislo.\n"
    "int C - odstrani desetinnou cast cisla ve sloupci C.\n"
    "copy N M - prepise obsah bunek ve sloupci M hodnotami ze sloupce N.\n"
    "swap N M - zameni hodnoty bunek ve sloupcich N a M.\n"
    "move N M - presune sloupec N pred sloupec M.\n"
    "--------------------------------------------------------------------------------\n"
    "                                [Selekce radku]\n"
    "--------------------------------------------------------------------------------\n"
    "rows N M - procesor bude zpracovavat pouze radky N az M vcetne (N <= M).\n"
    "\tN=1 znamena zpracovani od prvniho radku.\n "
    "\tPokud je misto cisla M zadan znak - (pomlcka),\n "
    "\tta reprezentuje posledni radek vstupniho souboru.\n "
    "\tPokud je pomlcka take misto sloupce N, mysli se tim vyber pouze posledniho radku.\n"
    "\tPokud neni tento prikaz zadan, uvazuje se implicitne o vsech radcich.\n"
    "beginswith C STR - procesor bude zpracovavat pouze ty radky,\n"
    "\tjejichz obsah bunky ve sloupci C zacina retezcem STR.\n"
    "contains C STR - procesor bude zpracovavat pouze ty radky,\n" 
    "\tjejichz bunky ve sloupci C obsahuji retezec STR.\n\n");
}

/* Volání funkce podle zadanéo argumentu */
//Příkazy pro úpravu tabulky
/* Vloží řádek před zadaný řádek R > 0 */
void iRow(int R)
{
}

/* Vloží nový řádek na konec */
void aRow()
{
}

/* Odstraní řádek R > 0 */
void dRow(int R)
{
}

/* Odstraní řádky N-M, N<=M, N=M => odstraní N */
void dRows(int N, int M)
{
}

/* Vloží prázdný sloupec před sloupec C */
void iCol(int C)
{
}

/* Vloží prázdný sloupec na konec */
void aCol()
{
}

/* Odstraní sloupec číslo C */
void dCol(int C)
{
}

/* Odstraní sloupce N-M, N<=M, N=M => odstraní N */
void dCols(int N, int M)
{
}

//Příkazy pro zpracování dat - povinné
/* Do buňky C nastavit řetezec STR */
void cSet(int C, char const *STR)
{
}

/* Řetězec ve sloupci C bude převeden na malá písmena */
void myToLower(int C, char *row) /* FIX ME - name of func */
{
    //Pro a-z udělá A-Z
    int i = 0;
    while (row[i] != '\n')
    {
        //FIX ME - udělat pro konkrétní sloupec
        row[i] = tolower(row[i]);
        i++;
    }
}

/* Řetězec ve sloupci C bude převeden na velká písmena */
void myToUpper(int C, char *row) /* FIX ME - name of func */
{
    //Pro a-z udělá A-Z
    int i = 0;
    while (row[i] != '\n')
    {
        //FIX ME - udělat pro konkrétní sloupec
        row[i] = toupper(row[i]);
        i++;
    }
}

/* Ve sloupci C zaokrouhlí na celé číslo */
void myRound(int C) /* FIX ME - name of func */
{
}

/* Odstraní desetinnou část čísla ve sloupci C */
void toInt(int C)
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

//Příkazy pro selekci
/* Zpracuje řádky N až M, N<=M, 
při zadání například (N = 1) (M = 2) od prvního do druhého včetně
při (N = 1) (M = -) od prvního do posledního sloupce, 
při (N = -) (M = -) zpracuje se pouze poslední sloupec, 
při nezadání se zpracuje vše */
void rows(int N, int M)
{
}
/* Zpracuje se pouze řádek, který ve sloupci C začína řetezcem STR */
void beginsWith(int C, char const *STR)
{
}
/* Zpracuje se pouze řádek, který ve sloupci C obsahuje řetezec STR */
void contains(int C, char const *STR)
{
}

/* Prototyp funkce readRow */
void readRow(int argCount, char const **pArg, char delim);

/* Zpracování argumentu */
void argsProcessing(int argCount, char const **pArg, char delim, char *row)
{
    //Podle argumentů v příkazové řádce volá funkce programu
    /* FIX ME: přidat funkce na kontrolu kolik bylo zadáno argumentu v případě, 
    že bylo zadáno míň argumentů než je potřeba vrátit se do MAIN a vypsat USAGE */
    if (argCount > 1)
    {
        for (int i = 0; i < argCount; i++)
        {
            if (!strcmp("irow", pArg[i]))
                iRow(*pArg[i + 1]);
            if (!strcmp("arow", pArg[i]))
                aRow();
            if (!strcmp("drow", pArg[i]))
                dRow(*pArg[i + 1]);
            if (!strcmp("drows", pArg[i]))
                dRows(*pArg[i + 1], *pArg[i + 2]);
            if (!strcmp("icol", pArg[i]))
                iCol(*pArg[i + 1]);
            if (!strcmp("acol", pArg[i]))
                aCol();
            if (!strcmp("dcol", pArg[i]))
                dCol(*pArg[i + 1]);
            if (!strcmp("dcols", pArg[i]))
                dCols(*pArg[i + 1], *pArg[i + 2]);
            if (!strcmp("cset", pArg[i]))
                cSet(*pArg[i + 1], pArg[i + 2]);
            if (!strcmp("tolower", pArg[i]))
                myToLower(*pArg[i + 1], row);
            if (!strcmp("toupper", pArg[i]))
                myToUpper(*pArg[i + 1], row);
            if (!strcmp("round", pArg[i]))
                myRound(*pArg[i + 1]);
            if (!strcmp("int", pArg[i]))
                toInt(*pArg[i + 1]);
            if (!strcmp("copy", pArg[i]))
                copy(*pArg[i + 1], *pArg[i + 2]);
            if (!strcmp("swap", pArg[i]))
                swap(*pArg[i + 1], *pArg[i + 2]);
            if (!strcmp("move", pArg[i]))
                move(*pArg[i + 1], *pArg[i + 2]);
            if (!strcmp("move", pArg[i]))
                rows(*pArg[i + 1], *pArg[i + 2]);
            if (!strcmp("move", pArg[i]))
                beginsWith(*pArg[i + 1], pArg[i + 2]);
            if (!strcmp("move", pArg[i]))
                contains(*pArg[i + 1], pArg[i + 2]);
            /* FIX ME: nutno přidat kontrolu jestli existuje *pArg[i+?], v případě že není zadáno error */
            //if (i == argCount) printRow();
        }
    }
    /* Výpis jednoho zpracovaného řádku */
    printf("%s", row);
    /* Čtení dalšího řádku */
    readRow(argCount, pArg, delim);
}

char findDelim(int argCount, char const **pArg)
{
    //Horizontální tabulátor - ASCII = 9HEX = 9DEC
    char delim = '\t';
    /* FIX ME: Ošetřit jestli to bylo zadáno nebo ne */
    if (argCount > 1)
    {
        if (!strcmp(pArg[1], "-d"))
            delim = pArg[2][0];
    }
    return delim;
}

void readRow(int argCount, char const **pArg, char delim)
{
    char row[ROWLENGTH];
    while (fgets(row, ROWLENGTH, stdin) != NULL)
    {
        argsProcessing(argCount, pArg, delim, row);
    }
}

int main(int argc, char const **argv)
{
    //Nalezení oddělovače DELIM
    char delim = findDelim(argc, argv);
    usage();
    //printf("Oddelovac je -> %c\n", delim);
    readRow(argc, argv, delim);
    return 0;
}
