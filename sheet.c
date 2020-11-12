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
#include <math.h>

//maximální délka řádku == 10kiB => (1024 x 10) = 10240
#define ROWLENGTH 10240
#define CELLLENGTH 100

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

//Příkazy pro úpravu tabulky
/* Vloží řádek před zadaný řádek R > 0 */
void iRow(int R, int colCount, int currentRow, char delim)
{
    if (R > 0)
    {
        if (R == currentRow)
        {
            for (int i = 0; i < colCount; i++)
            {
                printf("%c", delim);
            }
            printf("\n");
        }
    }
}

/* Vloží nový řádek na konec */
void aRow(int colCount, char delim, char *row)
{
    sprintf(row, "%s\n", row);
    for (int i = 0; i < colCount; i++)
    {
        sprintf(row, "%s%c", row, delim);
    }
}

/* Odstraní řádek R > 0 */
void dRow(int R, char *row, int currentRow)
{
    int i = 0;
    if (R > 0)
    {
        if (R == currentRow)
        {
            while (row[i] != '\n')
            {
                row[i] = '\0';
                i++;
            }
        }
    }
}

/* Odstraní řádky N-M, N<=M, N=M => odstraní N */
void dRows(int N, int M, char *row, int currentRow)
{
    int i = 0;
    if (N > 0)
    {
        if ((currentRow >= N) && (currentRow <= M))
        {
            while (row[i] != '\n')
            {
                row[i] = '\0';
                i++;
            }
        }
    }
}

/* Vloží prázdný sloupec před sloupec C */
void iCol(int C)
{
}

/* Vloží prázdný sloupec na konec */
void aCol(char *row, char delim)
{
    int i = 0;
    while (row[i] != '\n')
    {
        if (row[i + 1] == '\n')
        {
            row[i + 1] = delim;
            row[i + 2] = '\n';
            break;
        }
        i++;
    }
}

/* Odstraní sloupec číslo C */
void dCol(int C)
{
    if (C > 0)
    {
    }
}

/* Odstraní sloupce N-M, N<=M, N=M => odstraní N */
void dCols(int N, int M)
{
}

//Příkazy pro zpracování dat - povinné
/* Do buňky C nastavit řetezec STR */
void cSet(int C, const char *STR)
{
}

/* Řetězec ve sloupci C bude převeden na malá písmena */
void myToLower(int C, char *row, int colCount, char delim)
{
    int currentCol = 0;
    if (C <= (colCount + 1))
    {
        int i = 0;
        while (row[i] != '\n')
        {
            if ((currentCol + 1) == C)
            {
                row[i] = tolower(row[i]);
            }

            if (row[i] == delim)
            {
                currentCol++;
            }
            i++;
        }
    }
}

/* Řetězec ve sloupci C bude převeden na velká písmena */
void myToUpper(int C, char *row, int colCount, char delim)
{
    int currentCol = 0;
    if (C <= (colCount + 1))
    {
        int i = 0;
        while (row[i] != '\n')
        {
            if ((currentCol + 1) == C)
            {
                row[i] = toupper(row[i]);
            }

            if (row[i] == delim)
            {
                currentCol++;
            }
            i++;
        }
    }
}

/* Složí buňky zpět do řádku */
void putIntoRow(char *row, int colCount, char rowToCells[colCount + 1][CELLLENGTH], char delim)
{
    //vynuluju pole
    for (int i = 0; i < strlen(row); i++)
        row[i] = '\0';
    //
    for (int i = 0; i < (colCount + 1); i++)
    {
        if (i != (colCount))
        {
            sprintf(row, "%s%s:", row, rowToCells[i]);
        }
        else
        {
            sprintf(row, "%s%s\n", row, rowToCells[i]);
        }
    }
}

/* Rozdělí řádek do buněk*/
void divideToCells(char *row, int colCount, char rowToCells[colCount + 1][CELLLENGTH], char delim)
{
    int c = 0,
        currentCol = 0;

    for (int i = 0; i <= (strlen(row)); i++)
    {
        if (row[i] == delim)
        {
            rowToCells[currentCol][c] = '\0';
            c = 0;
            currentCol++;
        }
        else if (row[i] != '\n')
        {
            rowToCells[currentCol][c] = row[i];
            c++;
        }
    }
}

/* Ve sloupci C zaokrouhlí na celé číslo */
void myRound(int C, char *row, int colCount, char delim)
{
    bool floatNum = false;
    int rounded;
    if (C <= (colCount + 1))
    {
        char rowToCells[colCount + 1][CELLLENGTH];
        divideToCells(row, colCount, rowToCells, delim);
        for (int i = 0; i < strlen(rowToCells[C - 1]); i++)
        {
            if ((isdigit(rowToCells[C - 1][i])) || (rowToCells[C - 1][i] == '.') || (rowToCells[C - 1][i] == ','))
            {
                if (rowToCells[C - 1][i] == ',')
                {
                    rowToCells[C - 1][i] = '.';
                }
                floatNum = true;
            }
            else
            {
                floatNum = false;
                break;
            }
        }
        //Nalezené číslo převedu na float
        if (floatNum == true)
        {
            rounded = (int)round(atof(rowToCells[C - 1]));
            sprintf(rowToCells[C - 1], "%d", rounded);
        }
        putIntoRow(row, colCount, rowToCells, delim);
    }
}

/* Odstraní desetinnou část čísla ve sloupci C */
void toInt(int C, char *row, int colCount, char delim)
{
    bool floatNum = false;
    int rounded;
    if (C <= (colCount + 1))
    {
        char rowToCells[colCount + 1][CELLLENGTH];
        divideToCells(row, colCount, rowToCells, delim);
        for (int i = 0; i < strlen(rowToCells[C - 1]); i++)
        {
            if ((isdigit(rowToCells[C - 1][i])) || (rowToCells[C - 1][i] == '.') || (rowToCells[C - 1][i] == ','))
            {
                if (rowToCells[C - 1][i] == ',')
                {
                    rowToCells[C - 1][i] = '.';
                }
                floatNum = true;
            }
            else
            {
                floatNum = false;
                break;
            }
        }
        //Nalezené číslo převedu na float
        if (floatNum == true)
        {
            rounded = (int)floor(atof(rowToCells[C - 1]));
            sprintf(rowToCells[C - 1], "%d", rounded);
        }
        putIntoRow(row, colCount, rowToCells, delim);
    }
}

/* Přepíše obsah buňek ve sloupci M hodnozami ze sloupce N */
void copy(int N, int M)
{
    /* TODO: 3 stejné funkce skoro, COPY, SWAP a MOVE */
}

/* Zamění hodnoty buňek ve sloupcích N a M */
void swap(int N, int M)
{
    /* TODO: 3 stejné funkce skoro, COPY, SWAP a MOVE */
}

/* Přesune sloupec N před sloupec M */
void move(int N, int M)
{
    /* TODO: 3 stejné funkce skoro, COPY, SWAP a MOVE */
}

//Příkazy pro selekci
/* Zpracuje řádky N až M, N<=M, 
při zadání například (N = 1) (M = 2) od prvního do druhého včetně
při (N = 1) (M = -) od prvního do posledního řádku, 
při (N = -) (M = -) zpracuje se pouze poslední řádku, 
při nezadání se zpracuje vše */
int rows(const char *N, const char *M, int *all, int currentRow, bool endOfFile)
{
    *all = 0;
    if ((isdigit(*N)) && (isdigit(*M)))
    {
        if ((currentRow >= atoi(N)) && (currentRow <= atoi(M)))
        {
            return 1;
        }
    }
    else if ((isdigit(*N)) && (!isdigit(*M)))
    {
        if (currentRow >= atoi(N))
        {
            return 1;
        }
    }
    else if (((!isdigit(*N)) && (!isdigit(*M))) && (endOfFile))
    {
        return 1;
    }
    return 0;
}

/* Zpracuje se pouze řádek, který ve sloupci C začína řetezcem STR */
int beginsWith(int C, char const *STR, int *all)
{
    *all = 0;
    return 1;
}

/* Zpracuje se pouze řádek, který ve sloupci C obsahuje řetezec STR */
int contains(int C, char const *STR, int *all)
{
    *all = 0;
    return 1;
}

/* Kontrola spuštění - buď [Selekce radku] [Prikaz pro zpracovani dat] a nebo [Prikazy pro upravu tabulky] */
int selectedMode(int argCount, char const **pArg)
{
    //Vráti hodnotu 1 v případě, že je zadán mód
    //pro úpravu tabulky nebo případně mód
    //pro zpracování dat
    bool fM = false, sM = false;
    int x = 8, y = 11;
    char firstMode[8][6] = {"irow", "arow", "drow", "drows", "icol", "acol", "dcol", "dcols"};
    char secondMode[11][11] = {"cset", "tolower", "toupper", "round", "int", "copy", "swap", "move",
                               "rows", "beginswith", "contains"};

    for (int i = 1; i < argCount; i++)
    {
        for (int ix = 0; ix < x; ix++)
        {
            if (!strcmp(pArg[i], firstMode[ix]))
            {
                fM = true;
            }
        }

        for (int iy = 0; iy < y; iy++)
        {
            if (!strcmp(pArg[i], secondMode[iy]))
            {
                sM = true;
            }
        }
    }
    if ((fM == true) && (sM == true))
    {
        return 0;
    }
    else if ((fM == true) && (sM == false))
    {
        return 1;
    }
    else
    {
        return 1;
    }
}

/* Počítadlo kolik má program očekávat zadaných parametrů */
int expectedArqsCount(int argCount, char const **pArg)
{
    //x - počet funkcí bez argumentu, y - počet funkcí s jedním argumentem, z - počet funkcí s dvěma argumenty
    int x = 2, y = 9, z = 9;
    char zeroParamFun[2][5] = {"arow", "acol"};
    char oneParamFun[9][8] = {"irow", "drow", "icol", "dcol", "tolower", "toupper", "round", "int", "-d"};
    char twoParamFun[9][11] = {"drows", "dcols", "cset", "copy", "swap", "move", "rows", "beginswith", "contains"};

    int expectedArgs = 0;
    for (int i = 1; i < argCount; i++)
    {
        for (int ix = 0; ix < x; ix++)
        {
            if (!strcmp(pArg[i], zeroParamFun[ix]))
            {
                expectedArgs += 1;
            }
        }

        for (int iy = 0; iy < y; iy++)
        {
            if (!strcmp(pArg[i], oneParamFun[iy]))
            {
                expectedArgs += 2;
            }
        }

        for (int iz = 0; iz < z; iz++)
        {
            if (!strcmp(pArg[i], twoParamFun[iz]))
            {
                expectedArgs += 3;
            }
        }
    }
    return expectedArgs;
}

/* Prototyp funkce readRow */
void readRow(int argCount, const char **pArg, char delim, int rowCount, bool endOfFile);

/* Zpracování argumentu */
void argsProcessing(int argCount, const char **pArg, char delim, char *row, int colCount, int rowCount, bool endOfFile)
{
    int all = 1, rowsSet = 0, beginsWithSet = 0, containsSet = 0;
    //Podle argumentů v příkazové řádce volá funkce programu
    /* IF TODO: rows ... zpracuj pokud row je ze zadaných row */
    /* TODO: beginswith ... zavolá funkci a pokud se nalezne v daném sloupci na začátku to co chci tak vráti hodnotu a potom se provede to co bylo zadáno  */
    /* TODO: contains ... obdobně jako u beginswith, ale může být kdekoliv daný STR*/
    if (argCount > 1)
    {
        for (int i = 0; i < argCount; i++)
        {
            //Příkazy pro úpravu tabulky
            if (!strcmp("irow", pArg[i]))
                iRow(atoi(pArg[i + 1]), colCount, rowCount, delim);
            //arow přesunuto do main - FIXME: chtěl bych ho zde
            if ((!strcmp("arow", pArg[i])) && endOfFile)
                aRow(colCount, delim, row);
            if (!strcmp("drow", pArg[i]))
                dRow(atoi(pArg[i + 1]), row, rowCount);
            if (!strcmp("drows", pArg[i]))
                dRows(atoi(pArg[i + 1]), atoi(pArg[i + 2]), row, rowCount);
            if (!strcmp("icol", pArg[i]))
                iCol(*pArg[i + 1]);
            if (!strcmp("acol", pArg[i]))
                aCol(row, delim);
            if (!strcmp("dcol", pArg[i]))
                dCol(*pArg[i + 1]);
            if (!strcmp("dcols", pArg[i]))
                dCols(*pArg[i + 1], *pArg[i + 2]);

            //Selekce řádků
            if (!strcmp("rows", pArg[i]))
                rowsSet = rows(pArg[i + 1], pArg[i + 2], &all, rowCount, endOfFile);
            if (!strcmp("beginswith", pArg[i]))
                beginsWithSet = beginsWith(atoi(pArg[i + 1]), pArg[i + 2], &all);
            if (!strcmp("contains", pArg[i]))
                containsSet = contains(atoi(pArg[i + 1]), pArg[i + 2], &all);

            //Příkazy pro zpracování dat
            //TODO: pokud nějaký z hodnot bude 1, tak se provede
            if (rowsSet || beginsWithSet || containsSet || all)
            {
                if (!strcmp("cset", pArg[i]))
                    cSet(*pArg[i + 1], pArg[i + 2]);
                if (!strcmp("tolower", pArg[i]))
                    myToLower(atoi(pArg[i + 1]), row, colCount, delim);
                if (!strcmp("toupper", pArg[i]))
                    myToUpper(atoi(pArg[i + 1]), row, colCount, delim);
                if (!strcmp("round", pArg[i]))
                    myRound(atoi(pArg[i + 1]), row, colCount, delim);
                if (!strcmp("int", pArg[i]))
                    toInt(atoi(pArg[i + 1]), row, colCount, delim);
                if (!strcmp("copy", pArg[i]))
                    copy(*pArg[i + 1], *pArg[i + 2]);
                if (!strcmp("swap", pArg[i]))
                    swap(*pArg[i + 1], *pArg[i + 2]);
                if (!strcmp("move", pArg[i]))
                    move(*pArg[i + 1], *pArg[i + 2]);
            }
        }
        //printf("\nH- %d,%d,%d,%d\n", all, rowsSet, beginsWithSet, containsSet);
    }
    //Výpis jednoho zpracovaného řádku
    printf("%s", row);
    //Čtení dalšího řádku
    readRow(argCount, pArg, delim, rowCount, endOfFile);
}

/* Čtení řádku */
void readRow(int argCount, char const **pArg, char delim, int rowCount, bool endOfFile)
{
    char row[ROWLENGTH];
    int colCount = 0, i = 0;
    //Načtení celého řádku do row ze stdin s maximální délkou ROWLENGTH
    while (fgets(row, ROWLENGTH, stdin) != NULL)
    {
        //Počítání počtu děliču, tudiž sloupců bez jednoho
        while (row[i] != '\n')
        {
            if (row[i] == delim)
            {
                colCount++;
            }
            i++;
        }
        rowCount++;
        //printf("%d", rowCount);
        //tady mi to vráti konec, ale je na začátku posledního řádku
        if (feof(stdin))
            endOfFile = true;
        argsProcessing(argCount, pArg, delim, row, colCount, rowCount, endOfFile);
    }
}

int main(int argc, char const **argv)
{
    //Očekávaný počet argumentů
    int expected = expectedArqsCount(argc, argv);
    //Počet řádků
    int rowCount = 0;
    //Konec řádku
    bool endOfFile = false;

    /* Nalezení oddělovače DELIM */
    char delim = ' ';
    if (argc >= 3)
    {
        if (!strcmp(argv[1], "-d"))
            delim = argv[2][0];
    }
    //Počet očekávaných arg musí být roven počtu arg bez prvního (sheet.exe)
    //Mód spuštění buď edit tabulky nebo edit dat
    if ((expected == (argc - 1)) && (selectedMode(argc, argv)))
    {
        readRow(argc, argv, delim, rowCount, endOfFile);
        return 0;
    }
    else
    {
        usage();
        return 1;
    }
}
