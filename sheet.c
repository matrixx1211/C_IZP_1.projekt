/*                            IZP projekt č.1                                */
/*                            Marek Bitomský                                 */
/*                                 2020                                      */
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
//maximální délka buňky
#define CELLLENGTH 100

/* Funkce usage pro vypsání jak by měl být program správně spuštěn v případě, 
že byl spuštěn nesprávně. */
void usage()
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

/* Složí buňky zpět do řádku */
void putIntoRow(char *row, int delimCount, char rowToCells[delimCount + 1][CELLLENGTH], char delim)
{
    //vynuluju pole
    for (unsigned int i = 0; i < strlen(row); i++)
        row[i] = '\0';
    //postupně skládá buňky do řádku
    for (int i = 0; i < (delimCount + 1); i++)
    {
        if (strcmp(rowToCells[i], " "))
        {
            if (i != (delimCount))
            {
                sprintf(row, "%s%s%c", row, rowToCells[i], delim);
            }
            else
            {
                sprintf(row, "%s%s\n", row, rowToCells[i]);
            }
        }
    }
    //pokud byl smazán poslední sloupec
    if ((!strcmp(rowToCells[delimCount], " ")))
    {
        row[strlen(row) - 1] = '\0';
        sprintf(row, "%s\n", row);
    }
}

/* Rozdělí řádek do buněk*/
void divideToCells(char *row, int delimCount, char rowToCells[delimCount + 1][CELLLENGTH], char delim)
{
    int c = 0,
        currentCol = 0;
    //postupně rozkládá řádek
    for (unsigned int i = 0; i <= (strlen(row)); i++)
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

//Příkazy pro úpravu tabulky
/* Vloží řádek před zadaný řádek R > 0 */
void iRow(int R, int argCount, const char **pArg, int delimCount, int currentRow, char delim)
{
    //ověření zda bylo správně zadáno R
    if (R > 0)
    {
        int dcolsPos = 0, dcolPos = 0, irowPos = 0, newDelimCount = delimCount;
        //pokud bylo zadáno dcol nebo dcols společně s irow, tak se uloží jejich pozice
        for (int i = 1; i < argCount; i++)
        {
            if (!strcmp(pArg[i], "dcol"))
                dcolPos = i;
            if (!strcmp(pArg[i], "dcols"))
                dcolsPos = i;
            if (!strcmp(pArg[i], "irow"))
                irowPos = i;
        }

        //změna počtu delimů -> počtu sloupců
        //při zadání dcol
        if (irowPos > 0 && dcolPos > 0)
            if (irowPos < dcolPos)
            {
                newDelimCount = newDelimCount - 1;
            }
        //při zadání dcols
        if (irowPos > 0 && dcolsPos > 0)
            if (irowPos < dcolsPos)
            {
                if (atoi(pArg[dcolsPos + 1]) <= atoi(pArg[dcolsPos + 2]))
                    newDelimCount = newDelimCount - (atoi(pArg[dcolsPos + 2]) - atoi(pArg[dcolsPos + 1]) + 1);
            }

        //vkládání nového řádku
        if (R == currentRow)
        {
            for (int i = 0; i < newDelimCount; i++)
            {
                printf("%c", delim);
            }
            printf("\n");
        }
    }
}

/* Vloží nový řádek na konec */
void aRow(int delimCount, char delim, char *row)
{
    //k řetězci row přidám další prázdný řádek
    sprintf(row, "%s\n", row);
    for (int i = 0; i < delimCount; i++)
    {
        sprintf(row, "%s%c", row, delim);
    }
}

/* Odstraní řádek R > 0 */
void dRow(int R, char *row, int currentRow)
{
    int i = 0;
    //ověření zda bylo správně zadáno R
    if (R > 0)
    {
        //pokud načtený řádek je ten, který se má smazat, tak se vynuluje
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
    //ověření zda bylo správně zadáno N a M
    if (N <= M)
    {
        if (N > 0)
        {
            //pokud načtený řádek je ten, který se má smazat, tak se vynuluje
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
}

/* Vloží prázdný sloupec před sloupec C */
void iCol(int C, char *row, int delimCount, char delim)
{
    //rozdělí do buněk
    char rowToCells[delimCount + 1][CELLLENGTH];
    char tempCell[CELLLENGTH];
    divideToCells(row, delimCount, rowToCells, delim);
    //zkopíruje obsah buňky z rowToCells do dočasné tempCell
    strcpy(tempCell, rowToCells[C - 1]);
    //do buňky rowToCells vloží dělič a dočasnou tempCell a následně vše poskládá zpět do řádku
    sprintf(rowToCells[C - 1], "%c%s", delim, tempCell);
    putIntoRow(row, delimCount, rowToCells, delim);
}

/* Vloží prázdný sloupec na konec */
void aCol(char *row, char delim)
{
    int i = 0;
    //prochází řádek row
    while (row[i] != '\n')
    {
        //jestli nalezne znak konce řádku na pozici i+1
        if (row[i + 1] == '\n')
        {
            //tak na i+1 vloží dělič a za něj znak konec řádku
            row[i + 1] = delim;
            row[i + 2] = '\n';
            break;
        }
        i++;
    }
}

/* Odstraní sloupec číslo C */
void dCol(int C, char *row, int *delimCount, char delim)
{
    //ověření zda bylo správně zadáno C
    if (C > 0)
    {
        //rozdělí do buněk
        char rowToCells[*delimCount + 1][CELLLENGTH];
        divideToCells(row, *delimCount, rowToCells, delim);
        //do zadaného sloupce v buňce se vloží mezera
        sprintf(rowToCells[C - 1], " ");
        //složí zpět do řádku
        putIntoRow(row, *delimCount, rowToCells, delim);
        //počet děličů/sloupců-1 se nastaví na nový počet
        *delimCount = *delimCount - 1;
    }
}

/* Odstraní sloupce N-M, N<=M, N=M => odstraní N */
void dCols(int N, int M, char *row, int *delimCount, char delim)
{
    //ověření zda bylo správně zadáno N a M
    if (N <= M && N > 0)
    {
        //rozdělí do buněk
        char rowToCells[*delimCount + 1][CELLLENGTH];
        divideToCells(row, *delimCount, rowToCells, delim);
        //do zadaných sloupců v buňce se vloží mezera
        for (int i = 0; i < (*delimCount + 1); i++)
        {
            if ((i >= (N - 1)) && (i <= (M - 1)))
                sprintf(rowToCells[i], " ");
        }
        //složí zpět do řádku
        putIntoRow(row, *delimCount, rowToCells, delim);
        //počet děličů/sloupců-1 se nastaví na nový počet
        *delimCount = *delimCount - (M - N + 1);
    }
}

//Příkazy pro zpracování dat - povinné
/* Do buňky C nastavit řetezec STR */
void cSet(int C, const char *STR, char *row, int delimCount, char delim)
{
    //rozdělí do buněk
    char rowToCells[delimCount + 1][CELLLENGTH];
    divideToCells(row, delimCount, rowToCells, delim);
    //na zadaný sloupec v buňce vloží zadanou hodnotu
    sprintf(rowToCells[C - 1], "%s", STR);
    //složí zpět do řádku
    putIntoRow(row, delimCount, rowToCells, delim);
}

/* Řetězec ve sloupci C bude převeden na malá písmena */
void myToLower(int C, char *row, int delimCount, char delim)
{
    //ověření zda bylo správně zadáno C
    if (C <= (delimCount + 1) && C > 0)
    {
        int currentCol = 0;
        int i = 0;
        //pokud jsem na zadaném sloupci, tak znak po znaku se zmenší
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
void myToUpper(int C, char *row, int delimCount, char delim)
{
    //ověření zda bylo správně zadáno C
    if (C <= (delimCount + 1) && C > 0)
    {
        int currentCol = 0;
        int i = 0;
        //pokud jsem na zadaném sloupci, tak znak po znaku se zvětší
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

/* Ve sloupci C zaokrouhlí na celé číslo */
void myRound(int C, char *row, int delimCount, char delim)
{
    //ověření zda bylo správně zadáno C
    if (C <= (delimCount + 1) && C > 0)
    {
        bool floatNum = false;
        int rounded;
        //rozdělí do buněk
        char rowToCells[delimCount + 1][CELLLENGTH];
        divideToCells(row, delimCount, rowToCells, delim);
        //kontrola jestli v buňce je číslo
        for (unsigned int i = 0; i < strlen(rowToCells[C - 1]); i++)
        {
            //kontrola jestli je číslo, "." nebo ","
            if ((isdigit(rowToCells[C - 1][i])) || (rowToCells[C - 1][i] == '.') || (rowToCells[C - 1][i] == ','))
            {
                //pokud je zadaná ",", tak převedu na .
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
        //nalezené číslo se převede na float a přičte 0,5
        if (floatNum == true)
        {
            rounded = (int)(atof(rowToCells[C - 1]) + 0.5);
            sprintf(rowToCells[C - 1], "%d", rounded);
        }
        //složí zpět do řádku
        putIntoRow(row, delimCount, rowToCells, delim);
    }
}

/* Odstraní desetinnou část čísla ve sloupci C */
void toInt(int C, char *row, int delimCount, char delim)
{
    //ověření zda bylo správně zadáno C
    if (C <= (delimCount + 1) && C > 0)
    {
        bool floatNum = false;
        int rounded;
        //rozdělí do buněk
        char rowToCells[delimCount + 1][CELLLENGTH];
        divideToCells(row, delimCount, rowToCells, delim);
        //kontrola jestli v buňce je číslo
        for (unsigned int i = 0; i < strlen(rowToCells[C - 1]); i++)
        {
            if ((isdigit(rowToCells[C - 1][i])) || (rowToCells[C - 1][i] == '.') || (rowToCells[C - 1][i] == ','))
            {
                //pokud je zadaná ",", tak převedu na .
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
        //nalezené číslo převede na float a přetypuje na celé číslo
        if (floatNum == true)
        {
            rounded = (int)(atof(rowToCells[C - 1]));
            sprintf(rowToCells[C - 1], "%d", rounded);
        }
        //složí zpět do řádku
        putIntoRow(row, delimCount, rowToCells, delim);
    }
}

/* Přepíše obsah buňek ve sloupci M hodnozami ze sloupce N */
void copy(int N, int M, char *row, int delimCount, char delim)
{
    //pokud není zadáno M nebo N mimo rozsah
    if (!(M >= (delimCount + 2) || N >= (delimCount + 2)))
    {
        //rozdělí do buněk
        char rowToCells[delimCount + 1][CELLLENGTH];
        divideToCells(row, delimCount, rowToCells, delim);
        //překopíruje hodnotu z N do M
        strcpy(rowToCells[M - 1], rowToCells[N - 1]);
        //složí zpět do řádku
        putIntoRow(row, delimCount, rowToCells, delim);
    }
}

/* Zamění hodnoty buňek ve sloupcích N a M */
void swap(int N, int M, char *row, int delimCount, char delim)
{
    //pokud není zadáno M nebo N mimo rozsah
    if (!(M >= (delimCount + 2) || N >= (delimCount + 2)))
    {
        char tempCell[CELLLENGTH];
        //rozdělí do buněk
        char rowToCells[delimCount + 1][CELLLENGTH];
        divideToCells(row, delimCount, rowToCells, delim);
        //provede výměnu buněk N a M
        //tempCell = N (aby nedošlo ke ztrátě dat z buňky N)
        strcpy(tempCell, rowToCells[N - 1]);
        //N = M
        strcpy(rowToCells[N - 1], rowToCells[M - 1]);
        //M = tempCell
        strcpy(rowToCells[M - 1], tempCell);
        //složí zpět do řádku
        putIntoRow(row, delimCount, rowToCells, delim);
    }
}

/* Přesune sloupec N před sloupec M */
void move(int N, int M, char *row, int delimCount, char delim)
{
    //pokud není zadáno M nebo N mimo rozsah
    if (!(M >= (delimCount + 2) || N >= (delimCount + 2)))
    {
        char tempCell[CELLLENGTH];
        //rozdělí do buněk
        char rowToCells[delimCount + 1][CELLLENGTH];
        divideToCells(row, delimCount, rowToCells, delim);
        //zkopíruje obsah buňky do dočasné proměnné
        strcpy(tempCell, rowToCells[N - 1]);
        //pokud je N před M
        if (N < M)
        {
            //posouvá řádky
            for (int i = (N - 1); i < (M - 1) - 1; i++)
            {
                strcpy(rowToCells[i], rowToCells[i + 1]);
            }
            strcpy(rowToCells[M - 2], tempCell);
        }
        //pokud je M před N
        else if ((N > M) && (M > 1))
        {
            //posouvá rádky
            for (int i = (N - 1); i > (M - 1) - 1; i--)
            {
                strcpy(rowToCells[i], rowToCells[i - 1]);
            }
            strcpy(rowToCells[(M - 1) - 1], tempCell);
        }
        //složí zpět do řádku
        putIntoRow(row, delimCount, rowToCells, delim);
    }
}

//Příkazy pro selekci
/* Zpracuje řádky N až M, N<=M, 
při zadání například (N = 1) (M = 2) od prvního do druhého včetně
při (N = 1) (M = -) od prvního do posledního řádku, 
při (N = -) (M = -) zpracuje se pouze poslední řádku, 
při nezadání se zpracuje vše */
int rows(const char *N, const char *M, int *all, int currentRow, bool endOfFile)
{
    //určuje jestli se provede pro všechny řádky
    *all = 0;
    //při zadání čísel N i M
    if ((isdigit(*N)) && (isdigit(*M)))
    {
        //pokud je současný řádek v rozsahu N a M
        if ((currentRow >= atoi(N)) && (currentRow <= atoi(M)))
        {
            return 1;
        }
    }
    //při zadání čísla N a -
    else if ((isdigit(*N)) && (!isdigit(*M)))
    {
        //pokud je současný řádek v rozsahu N až konec
        if (currentRow >= atoi(N))
        {
            return 1;
        }
    }
    //při zadání - a - a zároveň pokud je na posledním řádku
    else if (((!isdigit(*N)) && (!isdigit(*M))) && (endOfFile))
    {
        return 1;
    }
    return 0;
}

/* Zpracuje se pouze řádek, který ve sloupci C začína řetezcem STR */
int beginsWith(int C, char const *STR, int *all, char *row, int delimCount, char delim)
{
    //určuje jestli se provede pro všechny řádky
    *all = 0;
    bool cellBeginsWith = false;
    //rozdělí do buněk
    char rowToCells[delimCount + 1][CELLLENGTH];
    divideToCells(row, delimCount, rowToCells, delim);
    //kontroluje jestli i-tý znak od prvního z buňky je rovný i-tému znaku ze zadaného řetězce
    for (unsigned int i = 0; i < strlen(STR); i++)
    {
        if (rowToCells[C - 1][i] == STR[i])
        {
            cellBeginsWith = true;
        }
        else
        {
            cellBeginsWith = false;
            break;
        }
    }

    //pokud buňka začína zadaným řetězcem, tak vrací 1 jinak 0
    if (cellBeginsWith)
        return 1;
    else
        return 0;
}

/* Zpracuje se pouze řádek, který ve sloupci C obsahuje řetezec STR */
int contains(int C, char const *STR, int *all, char *row, int delimCount, char delim)
{
    //určuje jestli se provede pro všechny řádky
    *all = 0;
    //rozdělí do buněk
    char rowToCells[delimCount + 1][CELLLENGTH];
    divideToCells(row, delimCount, rowToCells, delim);
    //pokud funkce vrátí nenulový ukazatel, tak buňka obsahuje zadaný řetězec
    if (strstr(rowToCells[C - 1], STR) != NULL)
        return 1;
    else
        return 0;
}

/* Kontrola spuštění - buď [Selekce radku] [Prikaz pro zpracovani dat] a nebo [Prikazy pro upravu tabulky] */
int selectedMode(int argCount, char const **pArg)
{
    //Vrací hodnotu 1 v případě, že je zadán mód
    //pro úpravu tabulky nebo případně mód
    //pro zpracování dat
    bool fM = false, sM = false;
    int x = 8,
        y = 11;
    //funkce prvního módu
    char firstMode[8][6] = {"irow", "arow", "drow", "drows", "icol", "acol", "dcol", "dcols"};
    //funkce druhého módu
    char secondMode[11][11] = {"cset", "tolower", "toupper", "round", "int", "copy", "swap", "move",
                               "rows", "beginswith", "contains"};

    //kontroluje, jaké argumenty byli zadány
    for (int i = 1; i < argCount; i++)
    {
        for (int ix = 0; ix < x; ix++)
        {
            //pokud byl zadán argument z prvního módu, tak vrací proměnnou s hodnotou true
            if (!strcmp(pArg[i], firstMode[ix]))
            {
                fM = true;
            }
        }

        for (int iy = 0; iy < y; iy++)
        {
            //pokud byl zadán argument z druhého módu, tak vrací proměnnou s hodnotou true
            if (!strcmp(pArg[i], secondMode[iy]))
            {
                sM = true;
            }
        }
    }
    //podle hodnot proměnných vrací 0 v případě špatného zadání
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
    //kontroluje jaké argumenty byli zadány na příkazové řádce
    for (int i = 1; i < argCount; i++)
    {
        //pokud byli zadány takové, které nemají další argument
        for (int ix = 0; ix < x; ix++)
        {
            //počet očekávaných argumentů se navýší o 1
            if (!strcmp(pArg[i], zeroParamFun[ix]))
            {
                expectedArgs += 1;
            }
        }
        //pokud byli zadány takové, které mají jeden další argument
        for (int iy = 0; iy < y; iy++)
        {
            //počet očekávaných argumentů se navýší o 2
            if (!strcmp(pArg[i], oneParamFun[iy]))
            {
                expectedArgs += 2;
            }
        }
        //pokud byli zadány takové, které mají dva další argumenty
        for (int iz = 0; iz < z; iz++)
        {
            //počet očekávaných argumentů se navýší o 3
            if (!strcmp(pArg[i], twoParamFun[iz]))
            {
                expectedArgs += 3;
            }
        }
    }
    //vrací počet očekávaných argumentů
    return expectedArgs;
}

/* Prototyp funkce readRow */
void readRow(int argCount, const char **pArg, char delim, int rowCount, bool endOfFile);

/* Zpracování argumentu */
void argsProcessing(int argCount, const char **pArg, char delim, char *row, int delimCount, int rowCount, bool endOfFile)
{
    int all = 1, rowsSet = 0, beginsWithSet = 0, containsSet = 0;
    //kontrola jestli byl zadán nějaký argument
    if (argCount > 1)
    {
        //podle argumentů na příkazové řádce volá funkce programu
        for (int i = 0; i < argCount; i++)
        {
            //Příkazy pro úpravu tabulky
            if (!strcmp("irow", pArg[i]))
                iRow(atoi(pArg[i + 1]), argCount, pArg, delimCount, rowCount, delim);
            //arow přesunuto do main - FIXME: chtěl bych ho zde
            if ((!strcmp("arow", pArg[i])) && endOfFile)
                aRow(delimCount, delim, row);
            if (!strcmp("drow", pArg[i]))
                dRow(atoi(pArg[i + 1]), row, rowCount);
            if (!strcmp("drows", pArg[i]))
                dRows(atoi(pArg[i + 1]), atoi(pArg[i + 2]), row, rowCount);
            if (!strcmp("icol", pArg[i]))
                iCol(atoi(pArg[i + 1]), row, delimCount, delim);
            if (!strcmp("acol", pArg[i]))
                aCol(row, delim);
            if (!strcmp("dcol", pArg[i]))
                dCol(atoi(pArg[i + 1]), row, &delimCount, delim);
            if (!strcmp("dcols", pArg[i]))
                dCols(atoi(pArg[i + 1]), atoi(pArg[i + 2]), row, &delimCount, delim);

            //selekce řádků
            //tyto funkce vrací 1 pokud se má zpracovat konkrétní řádek
            if (!strcmp("rows", pArg[i]))
                rowsSet = rows(pArg[i + 1], pArg[i + 2], &all, rowCount, endOfFile);
            if (!strcmp("beginswith", pArg[i]))
                beginsWithSet = beginsWith(atoi(pArg[i + 1]), pArg[i + 2], &all, row, delimCount, delim);
            if (!strcmp("contains", pArg[i]))
                containsSet = contains(atoi(pArg[i + 1]), pArg[i + 2], &all, row, delimCount, delim);

            //příkazy pro zpracování dat
            //pokud nějaká z hodnot bude 1, tak se provede
            if (rowsSet || beginsWithSet || containsSet || all)
            {
                if (!strcmp("cset", pArg[i]))
                    cSet(atoi(pArg[i + 1]), pArg[i + 2], row, delimCount, delim);
                if (!strcmp("tolower", pArg[i]))
                    myToLower(atoi(pArg[i + 1]), row, delimCount, delim);
                if (!strcmp("toupper", pArg[i]))
                    myToUpper(atoi(pArg[i + 1]), row, delimCount, delim);
                if (!strcmp("round", pArg[i]))
                    myRound(atoi(pArg[i + 1]), row, delimCount, delim);
                if (!strcmp("int", pArg[i]))
                    toInt(atoi(pArg[i + 1]), row, delimCount, delim);
                if (!strcmp("copy", pArg[i]))
                    copy(atoi(pArg[i + 1]), atoi(pArg[i + 2]), row, delimCount, delim);
                if (!strcmp("swap", pArg[i]))
                    swap(atoi(pArg[i + 1]), atoi(pArg[i + 2]), row, delimCount, delim);
                if (!strcmp("move", pArg[i]))
                    move(atoi(pArg[i + 1]), atoi(pArg[i + 2]), row, delimCount, delim);
            }
        }
    }
    //pokud současný řádek je poslední tak na místo konce řádku vložím \0
    if (endOfFile)
        row[strlen(row) - 1] = '\0';
    //výpis jednoho zpracovaného řádku
    printf("%s", row);

    //čtení dalšího řádku
    readRow(argCount, pArg, delim, rowCount, endOfFile);
}

/* Čtení řádku */
void readRow(int argCount, char const **pArg, char delim, int rowCount, bool endOfFile)
{
    char row[ROWLENGTH];
    int delimCount = 0, i = 0;
    //načtení celého řádku do row ze stdin s maximální délkou ROWLENGTH
    while (fgets(row, ROWLENGTH, stdin) != NULL)
    {
        //počítání počtu děliču, tudiž sloupců bez jednoho
        while (row[i] != '\n')
        {
            if (row[i] == delim)
            {
                delimCount++;
            }
            i++;
        }
        rowCount++;
        //pokud je současný řádek poslední, tak do proměnné uložím true
        if (feof(stdin))
            endOfFile = true;
        //zpracování přečteného řádku podle zadaných argumentů
        argsProcessing(argCount, pArg, delim, row, delimCount, rowCount, endOfFile);
    }
}

int main(int argc, char const **argv)
{
    //očekávaný počet argumentů
    int expectedArgs = expectedArqsCount(argc, argv);
    int rowCount = 0;
    bool endOfFile = false;

    //pokud je počet argumentu větší nebo roven 3 
    char delim = ' ';
    if (argc >= 3)
    {
        //a první zadaný argument je -d, tak nastaví dělič na první znak z druhého argumentu
        if (!strcmp(argv[1], "-d"))
            delim = argv[2][0];
    }
    //kontrola počtu očekávaných argumentů (sheet.exe)
    //kontrola jaký mód spuštění byl zadán, jestli editace tabulky nebo zpracování dat
    if ((expectedArgs == (argc - 1)) && (selectedMode(argc, argv)))
    {
        readRow(argc, argv, delim, rowCount, endOfFile);
        return 0;
    }
    else
    {
        //pokud byl program spuštěn zavolá funkci usage, která vypíše, jak by měl být spuštěn 
        usage();
        return 1;
    }
}
