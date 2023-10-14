#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX_ELEMENTS 80
#define MAX_SIMBOLS 16

/**********************************************************
LlegirExpressio.
Accio que, donat un fitxer de text, es capaz de llegir una
expressi� continguda en aquest fitxer (corresponent a una
l�nia del fitxer) i emmagatzemarla en una taula de
car�cters per al seu tractament posterior.
Par�metres:
    Expressio: Taula de car�cters que emmagatzemar�
        l'expressi�.
    proves: Fitxer que cont� totes les expressions a
        tractar en el programa.
    caracter: Variable de suport que permetr� evaluar cada
        car�cter abans d'emmagatzemar-lo a la taula per a
        saber si s'ha arribat al final de l'expressi�.
Retorn: L'acci� no retorna res.
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
Funci� que evalua si els s�mbols d'una expressi� son
v�lids, �s a dir, si es troben els preseleccionats per a la
realitzaci� del programa.
Par�metres:
    Expressi�: Taula de car�cters que emmagatzemar�
        l'expressi� a tractar.
    Simbols: Taula de car�cters que emmagatzema tots els
        s�mbols preseleccionats com a v�lids per a la
        realitzaci� del programa.
Retorn: La funci� retorna si tots els s�mbols de l'expressi�
son v�lids o no.
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
Funci� que determina si els par�ntesis de l'expressi� son
coherents, �s a dir, si el nombre de parentesis oberts es
correspon amb el nombre de par�ntesis tancats.
Par�metres:
    Expressi�: Taula de car�cters que emmagatzema
        l'expressi� a tractar.
Retorn: La funci� retorna si els pare�ntesis de l'expressi�
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
Funci� que permet rec�rrer un subconjunt qualsevol del
conjunt de s�mbols preseleccionats com a v�lids per a la
realitzaci� del programa per a saber si un determinat
element de l'expressi� es troba entre ells.
Par�metres:
    Expressi�: Taula de car�cters que emmagatzema
        l'expressi� a tractar.
    Simbols: Taula de car�cters que emmagatzema tots els
        s�mbols preseleccionats com a v�lids per a la
        realitzaci� del programa.
    i: Posici� de la taula Expressi� en la que es troba
        l'element que es vol saber si forma part d'un
        subconjunt.
    j: Posici� inicial del subconjunt de s�mbols del qual
        es vol saber si l'element en forma part.
    max: Posici� final del subconjunt de s�mbols del qual
        es vol saber si l'element en forma part.
Retorn: La funci� retorna si l'element a tractar forma part
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
Funci� que permet utilitzar la funci� Comparar per a
evaluar si dos elements consecutius formen part d'un
determinat subconjunt del conjunt de s�mbols preseleccionats
com a v�lids. Tot i que estructuralment pot semblar
lleugerament diferent a la funci� Comparar, a nivell
funcional es comparta de manera gaireb� id�ntica.
Par�metres:
    Expressi�: Taula de car�cters que emmagatzema
        l'expressi� a tractar.
    Simbols: Taula de car�cters que emmagatzema tots els
        s�mbols preseleccionats com a v�lids per a la
        realitzaci� del programa.
    i: Posici� de la taula Expressi� en la que es troba
        l'element que es vol saber si forma part d'un
        subconjunt.
    j: Posici� inicial del subconjunt de s�mbols del qual
        es vol saber si l'element en forma part.
    max: Posici� final del subconjunt de s�mbols del qual
        es vol saber si l'element en forma part.
Retorn: La funci� retorna si els dos elements consecutius a
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
Funci� que permet determinar si el veinatge dels s�mbols
�s correcte. En concret permetr� seleccionar com a
incorrectes aquelles expressions que comencin amb un
parentesi tancat, que acabin amb un par�ntesi obert, que
comencin o acabin amb un operador, que presentin dos
operadors consecutius, que presentin un n�mero abans de un
par�ntesi obert o que presentin un n�mero despr�s d'un
par�ntesi tancat. La detecci� de la major part d'aquests
cassos es portar� a terme mitjan�ant crides a les funcions
Comparar i Precomparar. Aquesta funci� presenta una gran
quantitat de comentaris degut a que el seu funcionament �s
m�s complexe que el de la resta de codis.
Par�metres:
    Expressi�: Taula de car�cters que emmagatzema
        l'expressi� a tractar.
    Simbols: Taula de car�cters que emmagatzema tots els
        s�mbols preseleccionats com a v�lids per a la
        realitzaci� del programa.
Retorn: La funci� retorna si el veintage de s�mbols �s
correcte o no.
**********************************************************/
bool VeinatgeValid(char Expressio[], char Simbols[])
{
     int i=0;
     bool valida=true;

     if (Expressio[i]==')') {       //Es comproba que la funci� no comenci amb par�ntesi tancat.
        valida=false;
     }
     if (valida) {
        valida=Comparar(Expressio, Simbols, i, 12, 16);         //Es comproba que la funci� no comenci amb un operador.
     }
     while ((valida)&&(Expressio[i]!='\0')) {
        valida=PreComparar(Expressio, Simbols, i, 12, 16);     //Es comproba que no hi hagi dos operadors conecutius.
        if ((valida)&&(Expressio[i]=='(')) {
            if (i>0) {
                valida=Comparar(Expressio, Simbols, i-1, 0, 10);     //Es comproba que no hi hagi un n�mero immediatament abans de un par�ntesi obert.
            }
            if ((valida)&&(Expressio[i+1]!='\0')) {
                valida=Comparar(Expressio, Simbols, i+1, 11, 16);     //Es comproba que no hi hagi un operador o un par�ntesi tanacat immediatament despr�s d'un par�ntesi obert.
            }
        }
        if ((valida)&&(Expressio[i]==')')) {
            if (Expressio[i+1]!='\0') {
                valida=Comparar(Expressio, Simbols, i+1, 0, 11);      //Es comproba que no hi hagi un n�mero o un par�ntesi obert immediatament despr�s de un par�ntesi tancat.
            }
            if ((valida)&&(i>0)) {
                valida=Comparar(Expressio, Simbols, i-1, 12, 16);     //Es comproba que no hi hagi un operador immediatament abans de un par�ntesi tancat.
            }
        }
        if ((valida)&&(i>0)&&(Expressio[i+1]!='\0')&&(!Comparar(Expressio, Simbols, i, 0, 10))&&(Expressio[i-1]=='(')&&(Expressio[i+1]==')')) {     //Es comproba que no hi hagi a la vegada un par�ntesi obert abans d'un n�mero i un par�ntesi tancat despr�s d'aquest mateix n�mero.
            valida=false;
        }
        i++;
     }
     if ((valida)&&(Expressio[i-1]=='(')) {         //Es comproba que l'expressi� no acabi amb un par�ntesi obert.
        valida=false;
     }
     if (valida) {
        valida=Comparar(Expressio, Simbols, i-1, 12, 16);       //Es comproba que l'expressi� no acabi amb un operador.
     }
     return valida;
}

/**********************************************************
ConvertirCaracterANumero.
Funci� que permet que, quan es detecta un car�cter que
representa un d�git en la expressi�, obtenir aquest d�git i
tots els car�cters consecutius que tamb� representen d�gits
i transformarles en un �nic n�mero amb tantes xifres com
car�cters consecutius que representin d�gits s'hagin
trobat.
Par�metres:
    Expressi�: Taula de car�cters que emmagatzema
        l'expressi� a tractar.
    i: Posici� de la taula Expressi� en la que es troba
        el primer car�cter que representa un d�git, es a
        dir, el car�cter a partir del qual s'ha de comen�ar
        a fer la cerca de car�cters que representin d�gits.
        Aquesta variable es pasa per ref�rencia per a que
        al retornar a la funci� recursiva, l'�ndex que
        recorre l'expressi� estigui sempre actualitzat.
Retorn: El n�mero format pel conjunt de car�cter consecutius
que representen d�gits.
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
Operaci�.
Funci� que, segons el valor d'un determinat operador,
es realitza el c�lcul d'una operaci� concreta entre dos
n�meros.
Par�metres:
    a: Primer n�mero.
    op: Operador.
    b: Segon n�mero.
Retorn: El resultat de l'operaci�.
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
                resultat=-1000000;      //L'elecci� d'aquest valor �s completament arbitr�ria com indicador de que no es pot calcular el resultat de l'expressi� �s completament arbitr�ria.
            }
            break;
        default:
            break;
    }
    return resultat;
}

/**********************************************************
Calcula.
Funci� recursiva que, donada una expressi�, es a dir, un
conjunt d'operacions matem�ticas l'ordre de prioritat de
les quals ve determinat per par�ntesis, en calcula el
resultat. Aquest proc�s es porta a terme mitjan�ant la
crida recursiva a la pr�pia funci� cada vegada que es
detecta un par�ntesi obert (dintre del qual i haur� una
nova operaci� o expressi�).
Par�metres:
    Expressi�: Taula de car�cters que emmagatzema
        l'expressi� a tractar.
    i: �ndex que permetr� rec�rrer la taula que cont�
        la expressi� per anar evaluant cada element
        d'aquesta expressi�.
Retorn: Aquesta funci� retorna, en la primera crida, el
resultat final de l'expressi� i, en cada crida recursiva,
el resultat parcial de cada operaci� o conjunt d'operacions
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
TractarExpressi�.
Acci� que, donada una expressi�, s'encarrega de tractar
aquesta expressi�. Aquest tractament consisteix en la crida
a les diferents funcions que s'encarregan d'evaluar la
correctesa de les dades i, en cas de que l'expressi� sigui
correcta, de la crida a la funci� recursiva que
s'encarregar� de calcular el resultat de l'expressi�.
Par�metres:
    Expressi�: Taula de car�cters que emmagatzema
        l'expressi� a tractar.
    cont_expressions: �s un contador del n�mero
        d'expressions que s'han evaluat. Permet saber quina
        expressi� s'est� evaluant en cada crida a l'acci�.
Retorn: Aquesta acci� no retorna res.
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
