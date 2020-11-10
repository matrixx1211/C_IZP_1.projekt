# C_fit-vut_projekt-1
## Spouštění programu
1. V pripade OS Linux: 
- **./sheet [-d DELIM] [Prikazy pro upravu tabulky]**
- **./sheet [-d DELIM] [Selekce radku] [Prikaz pro zpracovani dat]**
2. V pripade OS Windows: 
- **sheet.exe [-d DELIM] [Prikazy pro upravu tabulky]**
- **sheet.exe [-d DELIM] [Selekce radku] [Prikaz pro zpracovani dat]**

## Oddělovač buněk [-d DELIM]

Argument -d specifikuje, jake znaky lze interpretovat jako oddelovace bunek.
Ve vychozim nastaveni je DELIM retezec obsahujici mezeru.
Prvni znak z retezce DELIM bude pouzit jako oddelovac vystupnich hodnot.

## Popis příkazů pro úpravu tabulky [Prikazy pro upravu tabulky]

- irow R - vlozi radek tabulky pred radek R > 0 (insert-row).
- arow - prida novy radek tabulky na konec tabulky (append-row).
- drow R - odstrani radek cislo R > 0 (delete-row).
- drows N M - odstrani radky N az M (N <= M).
V pripade N=M se prikaz chova stejne jako drow N.
- icol C - vlozi prazdny sloupec pred sloupec dany cislem C.
- acol - prida prazdny sloupec za posledni sloupec.
- dcol C - odstrani sloupec cislo C.
- dcols N M - odstrani sloupce N az M (N <= M).
V pripade N=M se prikaz chova stejne jako dcol N.

## Popis příkazů pro zpracování dat [Prikaz pro zpracovani dat]

- cset C STR - do bunky ve sloupci C bude nastaven retezec STR.
- tolower C - retezec ve sloupci C bude preveden na mala pismena.
- toupper C - retezec ve sloupce C bude preveden na velka pismena.
- round C - ve sloupci C zaokrouhli cislo na cele cislo.
- int C - odstrani desetinnou cast cisla ve sloupci C.
- copy N M - prepise obsah bunek ve sloupci M hodnotami ze sloupce N.
- swap N M - zameni hodnoty bunek ve sloupcich N a M.
- move N M - presune sloupec N pred sloupec M.

## Popis příkazů pro selekci řádků [Selekce radku]

- rows N M - procesor bude zpracovavat pouze radky N az M vcetne (N <= M).
N=1 znamena zpracovani od prvniho radku. 
Pokud je misto cisla M zadan znak - (pomlcka), 
ta reprezentuje posledni radek vstupniho souboru. 
Pokud je pomlcka take misto sloupce N, mysli se tim vyber pouze posledniho radku.
Pokud neni tento prikaz zadan, uvazuje se implicitne o vsech radcich.
- beginswith C STR - procesor bude zpracovavat pouze ty radky,
jejichz obsah bunky ve sloupci C zacina retezcem STR.
- contains C STR - procesor bude zpracovavat pouze ty radky, 
jejichz bunky ve sloupci C obsahuji retezec STR.);