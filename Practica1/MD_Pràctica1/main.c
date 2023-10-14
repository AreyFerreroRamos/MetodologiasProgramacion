#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX_ELEMENTS 80
#define MAX_SIMBOLS 16

/**********************************************************
LlegirExpressio.
Accio que, donat un fitxer de text, es capaz de llegir una
expressió continguda en aquest fitxer (corresponent a una
línia del fitxer) i emmagatzemarla en una taula de
caràcters per al seu tractament posterior.
Paràmetres:
    Expressio: Taula de caràcters que emmagatzemarà
        l'expressió.
    proves: Fitxer que conté totes les expressions a
        tractar en el programa.
    caracter: Variable de suport que permetrà evaluar cada
        caràcter abans d'emmagatzemar-lo a la taula per a
        saber si s'ha arribat al final de l'expressió.
Retorn: L'acció no retorna res.
**********************************************************/
void LlegirExpressio(char Expressio[], FILE *proves, char *caracter)
{
    int i=0;

    while ((!feof(proves))&&(*caracter!='\n')) {
        Expressio[i]=*caracter;
        i++;
        fscanf(proves, "%c", &(*caracter));
    }
    Expressio[i]='\0';
}

/**********************************************************
SimbolsValids.
Funció que evalua si els símbols d'una expressió son
vàlids, és a dir, si es troben els preseleccionats per a la
realització del programa.
Paràmetres:
    Expressió: Taula de caràcters que emmagatzemarà
        l'expressió a tractar.
    Simbols: Taula de caràcters que emmagatzema tots els
        símbols preseleccionats com a vàlids per a la
        realització del programa.
Retorn: La funció retorna si tots els símbols de l'expressió
son vàlids o no.
**********************************************************/
bool SimbolsValids (char Expressio[], char Simbols[])
{
    int i=0, j;
    bool valida=true;

    while ((valida)&&(Expressio[i]!='\0')) {
        valida=false;
        j=0;
        while ((!valida)&&(j<MAX_SIMBOLS)) {
            if (Expressio[i]==Simbols[j]) {
                valida=true;
            }
            else {
                j++;
            }
        }
        i++;
    }
    return valida;
}


/**********************************************************
ParentesisValids.
Funció que determina si els parèntesis de l'expressió son
coherents, és a dir, si el nombre de parentesis oberts es
correspon amb el nombre de parèntesis tancats.
Paràmetres:
    Expressió: Taula de caràcters que emmagatzema
        l'expressió a tractar.
Retorn: La funció retorna si els pareèntesis de l'expressió
son coherents o no.
**********************************************************/
bool ParentesisValids(char Expressio[])
{
    int cont_parentesis=0, i=0;

    while (Expressio[i]!='\0') {
        if (Expressio[i]=='(') {
            cont_parentesis++;
        }
        else {
            if (Expressio[i]==')') {
                cont_parentesis--;
            }
        }
        i++;
    }
    return (cont_parentesis==0);
}

/**********************************************************
Comparar.
Funció que permet recòrrer un subconjunt qualsevol del
conjunt de símbols preseleccionats com a vàlids per a la
realització del programa per a saber si un determinat
element de l'expressió es troba entre ells.
Paràmetres:
    Expressió: Taula de caràcters que emmagatzema
        l'expressió a tractar.
    Simbols: Taula de caràcters que emmagatzema tots els
        símbols preseleccionats com a vàlids per a la
        realització del programa.
    i: Posició de la taula Expressió en la que es troba
        l'element que es vol saber si forma part d'un
        subconjunt.
    j: Posició inicial del subconjunt de símbols del qual
        es vol saber si l'element en forma part.
    max: Posició final del subconjunt de símbols del qual
        es vol saber si l'element en forma part.
Retorn: La funció retorna si l'element a tractar forma part
del subconjunt seleccionat.
**********************************************************/

bool Comparar (char Expressio[], char Simbols[], int i, int j, int max)
{
    bool valida=true;

    while ((valida)&&(j<max)) {
        if (Expressio[i]==Simbols[j]) {
            valida=false;
        }
        else {
            j++;
        }
    }
    return valida;
}

/**********************************************************
PreComparar.
Funció que permet utilitzar la funció Comparar per a
evaluar si dos elements consecutius formen part d'un
determinat subconjunt del conjunt de símbols preseleccionats
com a vàlids. Tot i que estructuralment pot semblar
lleugerament diferent a la funció Comparar, a nivell
funcional es comparta de manera gairebé idéntica.
Paràmetres:
    Expressió: Taula de caràcters que emmagatzema
        l'expressió a tractar.
    Simbols: Taula de caràcters que emmagatzema tots els
        símbols preseleccionats com a vàlids per a la
        realització del programa.
    i: Posició de la taula Expressió en la que es troba
        l'element que es vol saber si forma part d'un
        subconjunt.
    j: Posició inicial del subconjunt de símbols del qual
        es vol saber si l'element en forma part.
    max: Posició final del subconjunt de símbols del qual
        es vol saber si l'element en forma part.
Retorn: La funció retorna si els dos elements consecutius a
tractar formen part del subconjunt seleccionat.
**********************************************************/
bool PreComparar (char Expressio[], char Simbols[], int i, int j, int max)
{
    bool valida=true;

    while (!(Expressio[i]==Simbols[j])&&(j<max)) {
        j++;
    }
    if (Expressio[i]==Simbols[j]) {
        valida=Comparar(Expressio, Simbols, i+1, 12, max);
    }
    return valida;
}

/**********************************************************
VeinatgeValid.
Funció que permet determinar si el veinatge dels símbols
és correcte. En concret permetrà seleccionar com a
incorrectes aquelles expressions que comencin amb un
parentesi tancat, que acabin amb un parèntesi obert, que
comencin o acabin amb un operador, que presentin dos
operadors consecutius, que presentin un número abans de un
parèntesi obert o que presentin un número després d'un
parèntesi tancat. La detecció de la major part d'aquests
cassos es portarà a terme mitjançant crides a les funcions
Comparar i Precomparar. Aquesta funció presenta una gran
quantitat de comentaris degut a que el seu funcionament és
més complexe que el de la resta de codis.
Paràmetres:
    Expressió: Taula de caràcters que emmagatzema
        l'expressió a tractar.
    Simbols: Taula de caràcters que emmagatzema tots els
        símbols preseleccionats com a vàlids per a la
        realització del programa.
Retorn: La funció retorna si el veintage de símbols és
correcte o no.
**********************************************************/
bool VeinatgeValid(char Expressio[], char Simbols[])
{
     int i=0;
     bool valida=true;

     if (Expressio[i]==')') {       //Es comproba que la funció no comenci amb parèntesi tancat.
        valida=false;
     }
     if (valida) {
        valida=Comparar(Expressio, Simbols, i, 12, 16);         //Es comproba que la funció no comenci amb un operador.
     }
     while ((valida)&&(Expressio[i]!='\0')) {
        valida=PreComparar(Expressio, Simbols, i, 12, 16);     //Es comproba que no hi hagi dos operadors conecutius.
        if ((valida)&&(Expressio[i]=='(')) {
            if (i>0) {
                valida=Comparar(Expressio, Simbols, i-1, 0, 10);     //Es comproba que no hi hagi un número immediatament abans de un parèntesi obert.
            }
            if ((valida)&&(Expressio[i+1]!='\0')) {
                valida=Comparar(Expressio, Simbols, i+1, 11, 16);     //Es comproba que no hi hagi un operador o un parèntesi tanacat immediatament després d'un parèntesi obert.
            }
        }
        if ((valida)&&(Expressio[i]==')')) {
            if (Expressio[i+1]!='\0') {
                valida=Comparar(Expressio, Simbols, i+1, 0, 11);      //Es comproba que no hi hagi un número o un parèntesi obert immediatament després de un parèntesi tancat.
            }
            if ((valida)&&(i>0)) {
                valida=Comparar(Expressio, Simbols, i-1, 12, 16);     //Es comproba que no hi hagi un operador immediatament abans de un parèntesi tancat.
            }
        }
        if ((valida)&&(i>0)&&(Expressio[i+1]!='\0')&&(!Comparar(Expressio, Simbols, i, 0, 10))&&(Expressio[i-1]=='(')&&(Expressio[i+1]==')')) {     //Es comproba que no hi hagi a la vegada un parèntesi obert abans d'un número i un parèntesi tancat després d'aquest mateix número.
            valida=false;
        }
        i++;
     }
     if ((valida)&&(Expressio[i-1]=='(')) {         //Es comproba que l'expressió no acabi amb un parèntesi obert.
        valida=false;
     }
     if (valida) {
        valida=Comparar(Expressio, Simbols, i-1, 12, 16);       //Es comproba que l'expressió no acabi amb un operador.
     }
     return valida;
}

/**********************************************************
ConvertirCaracterANumero.
Funció que permet que, quan es detecta un caràcter que
representa un dígit en la expressió, obtenir aquest dígit i
tots els caràcters consecutius que també representen dígits
i transformarles en un únic número amb tantes xifres com
caràcters consecutius que representin dígits s'hagin
trobat.
Paràmetres:
    Expressió: Taula de caràcters que emmagatzema
        l'expressió a tractar.
    i: Posició de la taula Expressió en la que es troba
        el primer caràcter que representa un dígit, es a
        dir, el caràcter a partir del qual s'ha de començar
        a fer la cerca de caràcters que representin dígits.
        Aquesta variable es pasa per refèrencia per a que
        al retornar a la funció recursiva, l'índex que
        recorre l'expressió estigui sempre actualitzat.
Retorn: El número format pel conjunt de caràcter consecutius
que representen dígits.
**********************************************************/
int ConvertirCaractersANumero (char Expressio[], int *i)
{
    char Numero[MAX_ELEMENTS];
    int j=0, max, acum=0;

    while ((Expressio[*i]>='0')&&(Expressio[*i]<='9')&&(*i<MAX_ELEMENTS)) {
        Numero[j]=Expressio[*i];
        j++;
        (*i)++;
    }
    max=j;
    for (j=0; j<max; j++) {
        acum=acum+(Numero[j]-48)*round(pow(10, max-j-1));
    }
    return acum;

}

/**********************************************************
Operació.
Funció que, segons el valor d'un determinat operador,
es realitza el càlcul d'una operació concreta entre dos
números.
Paràmetres:
    a: Primer número.
    op: Operador.
    b: Segon número.
Retorn: El resultat de l'operació.
**********************************************************/
int Operacio(int a, char op, int b)
{
    int resultat;

    switch (op) {
        case '+':
            resultat=a+b;
            break;
        case '-':
            resultat=a-b;
            break;
        case '*':
            resultat=a*b;
            break;
        case '/':
            if (b!=0) {
                resultat=a/b;
            }
            else {
                resultat=-1000000;      //L'elecció d'aquest valor és completament arbitrària com indicador de que no es pot calcular el resultat de l'expressió és completament arbitrària.
            }
            break;
        default:
            break;
    }
    return resultat;
}

/**********************************************************
Calcula.
Funció recursiva que, donada una expressió, es a dir, un
conjunt d'operacions matemàticas l'ordre de prioritat de
les quals ve determinat per parèntesis, en calcula el
resultat. Aquest procés es porta a terme mitjançant la
crida recursiva a la pròpia funció cada vegada que es
detecta un parèntesi obert (dintre del qual i haurà una
nova operació o expressió).
Paràmetres:
    Expressió: Taula de caràcters que emmagatzema
        l'expressió a tractar.
    i: Índex que permetrà recòrrer la taula que conté
        la expressió per anar evaluant cada element
        d'aquesta expressió.
Retorn: Aquesta funció retorna, en la primera crida, el
resultat final de l'expressió i, en cada crida recursiva,
el resultat parcial de cada operació o conjunt d'operacions
evaluats abans d'arribar al resultat final.
**********************************************************/
int Calcula(char Expressio[], int *i)
{
    int a, b, resultat;
    char op;

    a=Expressio[*i];
    (*i)++;
    if (a!='(') {
        (*i)--;
        a=ConvertirCaractersANumero(Expressio, &(*i));
        op=Expressio[*i];
        (*i)++;
        b=Expressio[*i];
        (*i)++;
        if (b!='(') {
            (*i)--;
            b=ConvertirCaractersANumero(Expressio, &(*i));
            resultat=Operacio(a, op, b);
        }
        else {
            b=Calcula(Expressio, &(*i));
            resultat=Operacio(a, op, b);
        }
    }
    else {
        a=Calcula(Expressio, &(*i));
        op=Expressio[*i];
        (*i)++;
        b=Expressio[*i];
        (*i)++;
        if (b!='(') {
            (*i)--;
            b=ConvertirCaractersANumero(Expressio, &(*i));
            resultat=Operacio(a, op, b);
        }
        else {
            b=Calcula(Expressio, &(*i));
            resultat=Operacio(a, op, b);
        }
    }
    while (Expressio[*i]==')') {
        (*i)++;
    }
    return resultat;
}

/**********************************************************
TractarExpressió.
Acció que, donada una expressió, s'encarrega de tractar
aquesta expressió. Aquest tractament consisteix en la crida
a les diferents funcions que s'encarregan d'evaluar la
correctesa de les dades i, en cas de que l'expressió sigui
correcta, de la crida a la funció recursiva que
s'encarregarà de calcular el resultat de l'expressió.
Paràmetres:
    Expressió: Taula de caràcters que emmagatzema
        l'expressió a tractar.
    cont_expressions: És un contador del número
        d'expressions que s'han evaluat. Permet saber quina
        expressió s'està evaluant en cada crida a l'acció.
Retorn: Aquesta acció no retorna res.
**********************************************************/
void TractarExpressio (char Expressio[], int cont_expressions)
{
    char Simbols[MAX_SIMBOLS]={"0123456789()+-*/"};
    int resultat, i=0;

    if (SimbolsValids(Expressio, Simbols)) {
        if (ParentesisValids(Expressio)) {
            if (VeinatgeValid(Expressio, Simbols)) {
                resultat=Calcula(Expressio, &i);
                if (resultat!=-1000000) {
                    printf("El resultat de l'expressio %i es: %i\n",cont_expressions+1,resultat);
                }
                else {
                    printf("El resultat de l'expressio %i no existeix.\n",cont_expressions+1);
                }
            }
            else {
                printf("L'expressio %i no es valida perque el veinatge dels simbols no es correcte.\n",cont_expressions+1);
            }
        }
        else {
            printf("L'expressio %i no es valida perque la distribucio dels parentesis no es coherent.\n",cont_expressions+1);
        }
    }
    else {
        printf("L'expressio %i no es valida perque els simbols de l'expressio no son valids.\n",cont_expressions+1);
    }
}

/**********************************************************
Programa principal.
**********************************************************/
int main()
{
    FILE *proves;
    int numero_expressions, cont_expressions=0;
    char Expressio[MAX_ELEMENTS], caracter;

    proves=fopen("proves.txt","r");

    if (proves!=NULL) {
        fscanf(proves, "%i", &numero_expressions);
        fscanf(proves, "%c", &caracter);
        while (caracter!='\n'); {
            fscanf(proves, "%c", &caracter);
        }
        while ((!feof(proves))&&(cont_expressions<numero_expressions-1)) {
            LlegirExpressio(Expressio, &(*proves), &caracter);
            TractarExpressio(Expressio, cont_expressions);
            cont_expressions++;
            fscanf(proves, "%c", &caracter);
        }
        if (!feof(proves)) {
            LlegirExpressio(Expressio, &(*proves), &caracter);
            TractarExpressio(Expressio, cont_expressions);
            cont_expressions++;
        }
        if (cont_expressions!=numero_expressions) {
            printf("\nEl nombre d'expressions donat al inici del programa es superior al nombre d'expressions que realment te el programa.\n");
        }
        else {
            if (caracter=='\n') {
                printf("\nEl nombre d'expressions donat al inici del programa es inferior al nombre d'expressions que realment te el programa.\n");
            }
        }
    }
    else {
        printf("El fitxer no existeix.\n");
    }
    fclose(proves);
    printf("\n");
    return 0;
}
