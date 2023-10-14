#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_ALGORISMES 5
#define MAX_LLARGADES_VECTORS 10
#define MAX_PROVES 5

/***********************************************
ObtenirNumeroAleatori
Funci� que permet obtenir un n�mero aleatori
localitzat entre un rang qualsevol de valors
determinat per par�metre utilitzant la funci�
rand() de la llibreria est�ndard.
Par�metres:
    rand_min: �s el valor m�nim del rang.
    rand_max: �s el valor m�xim del rang.
Retorn: Retorna un n�mero aleatori entre el rang
determinat per par�metre.
***********************************************/
int ObtenirNumeroAleatori(int rand_min, int rand_max)
{
    return(rand()%(rand_max-rand_min+1)+rand_min);
}

/***********************************************
OrdSelecci�
Funci� que ordena tots els elements d'un vector
d'enters del m�s petit al m�s gran mitjan�ant
l'algorisme d'ordenaci� per selecci�.
Par�metres:
    v: Vector d'enters per ordenar.
    nelem: Nombre d'elements del vector.
Retorn: No retorna res. El vector d'enters
es passa per refer�ncia i, per tant, quan
es surti de la funci�, ja estar� modificat.
***********************************************/
void OrdSeleccio(int v[], int nelem)
{
    int i, j, pos, minim;

    for (i=0; i<nelem-1; i++) {
        minim=v[i];
        pos=i;
        for (j=i+1; j<nelem; j++) {
            if (v[j]<minim) {
                minim=v[j];
                pos=j;
            }
        }
        v[pos]=v[i];
        v[i]=minim;
    }
}

/***********************************************
OrdBombolla
Funci� que ordena tots els elements d'un vector
d'enters del m�s petit al m�s gran mitjan�ant
l'algorisme d'ordenaci� per bombolla.
Par�metres:
    v: Vector d'enters per ordenar.
    nelem: Nombre d'elements del vector.
Retorn: No retorna res. El vector d'enters
es passa per refer�ncia i, per tant, quan
es surti de la funci�, ja estar� modificat.
************************************************/
void OrdBombolla(int v[], int nelem)
{
    int i=1, j, aux;
    bool ordenat=false;

    while (!ordenat) {
        ordenat=true;
        for (j=0; j<nelem-i; j++) {
            if (v[j]>v[j+1]) {
                aux=v[j];
                v[j]=v[j+1];
                v[j+1]=aux;
                ordenat=false;
            }
        }
        i++;
    }
}

/************************************************
OrdInserci�
Funci� que ordena tots els elements d'un vector
d'enters del m�s petit al m�s gran mitjan�ant
l'algorisme d'ordenaci� per inserci�.
Par�metres:
    v: Vector d'enters per ordenar.
    nelem: Nombre d'elements del vector.
Retorn: No retorna res. El vector d'enters
es passa per refer�ncia i, per tant, quan
es surti de la funci�, ja estar� modificat.
************************************************/
void OrdInsercio(int v[], int nelem)
{
    int i, j, aux;

    for (i=1; i<nelem; i++) {
        aux=v[i];
        j=i-1;
        while ((j>=0)&&(aux<v[j])) {
            v[j+1]=v[j];
            j--;
        }
        v[j+1]=aux;
    }
}

/************************************************
Merge
Funcio que, donat un vector ordenat des de la
posici� intermitja cap a baix i des de la
posici� intermitja cap amunt, retorna el vector
completament ordenat.
Par�metres:
    v: Vector d'enters.
    ini: Posici� inicial del vector.
    mig: Posici� intermitja del vector.
    fin: Posici� final del vector.
Retorn: No retorna res. El vector d'enters
es passa per refer�ncia i, per tant, quan
es surti de la funci�, ja estar� modificat.
************************************************/
void Merge(int v[], int ini, int mig, int fin)
{
    int i=ini, j=mig+1, k, mida=fin-ini, aux[mida];

    for (k=0; k<=mida; k++) {
        if (((j>fin)||(v[i]<=v[j]))&&(i<=mig)) {
            aux[k]=v[i];
            i++;
        }
        else {
            aux[k]=v[j];
            j++;
        }
    }
    for (k=0, i=ini; k<=mida; k++, i++) {
        v[i]=aux[k];
    }
}

/************************************************
MergeSort
Funci� que ordena tots els elements d'un vector
d'enters del m�s petit al m�s gran mitjan�ant
l'algorisme d'ordenaci� MergeSort.
Par�metres:
    v: Vector d'enters per ordenar.
    ini: Posici� inicial del vector.
    fin: Posici� final del vector.
Retorn: No retorna res. El vector d'enters
es passa per refer�ncia i, per tant, quan
es surti de la funci�, ja estar� modificat.
************************************************/
void MergeSort(int v[], int ini, int fin)
{
    int mig;

    //Al cas directe no es fa res.
    if (ini<fin) {           //Cas recursiu.
        mig=(ini+fin)/2;
        MergeSort(v, ini, mig);
        MergeSort(v, mig+1, fin);
        Merge(v, ini, mig, fin);
    }
}

/************************************************
Ordenar
Funci� que, donat un vector d'enters, selecciona
el primer element del vector com a pivot i ubica
aquest pivot en una posici� del vector de manera
que tots els elements m�s petit que aquest siguin
colocats a la seva esquerra i tots els elements
m�s grans siguin colocats a la seva dreta.
Par�metres:
    v: Vector d'enters.
    ini: Posici� inicial del vector.
    fin: Posici� final del vector.
Retorn: Retorna la posici� del vector en la
que es localitza el pivot.
************************************************/
int Ordenar(int v[], int ini, int fin)
{
    int pivot=v[ini], i=ini+1, j=fin, aux;

    while (i<j) {
        if (v[i]>pivot) {
            if (v[j]<=pivot) {
                aux=v[i];
                v[i]=v[j];
                v[j]=aux;
                i++;
            }
            j--;
        }
        else {
            i++;
        }
    }
    if (v[i]<pivot) {
        aux=v[i];
        v[i]=pivot;
        v[ini]=aux;
    }
    return i-1;
}

/************************************************
QuickSort
Funci� que ordena tots els elements d'un vector
d'enters del m�s petit al m�s gran mitjan�ant
l'algorisme d'ordenaci� QuickSort.
Par�metres:
    v: Vector d'enters per ordenar.
    ini: Posici� inicial del vector.
    fin: Posici� final del vector.
Retorn: No retorna res. El vector d'enters
es passa per refer�ncia i, per tant, quan
es surti de la funci�, ja estar� modificat.
************************************************/
void QuickSort(int v[], int ini, int fin)
{
    int mig;

    //Al cas directe no es far res.
    if (ini<fin) {        //Cas recursiu.
        mig=Ordenar(v, ini, fin);
        QuickSort(v, ini, mig);
        QuickSort(v, mig+1, fin);
    }
}

/************************************************
PerCadaLlargadaVector
Funci� que, per cada vector d'enters d'una
llargada determinada per par�metre, ordena tots
aquests enters mitjan�ant un algorisme d'ordenaci�
tamb� determinat per par�metre.
Par�metres:
    vector: vector d'enters desordenats.
    n: Llargada del vector
    algorisme: Lletra inicial de l'algorisme que
                es vol utilitzar per ordenar el
                vector.
    fitxer_sortida: Fitxer en el qual s'emmagatzemar�
                el temps d'ordenaci� del vector
                que s'avalua per a l'algorisme
                d'ordenaci� que s'avalua.
Retorn: No retorna res. El valor del temps
d'ordenaci� s'emmagatzema en un fitxer de text.
************************************************/
void PerCadaLlargadaVector(int n, char algorisme, FILE *fitxer_sortida)
{
    clock_t clocks_inicials, clocks_finals;
    double promig_temps=0;
    int i, j, *vector=(int*)malloc(n*sizeof(int));

    for (i=0; i<MAX_PROVES; i++) {
        for (j=0; j<n; j++) {
            vector[j]=ObtenirNumeroAleatori(-100, 100);
        }
        clocks_inicials=clock();
        switch (algorisme) {
            case 'B':
                OrdBombolla(vector, n);
                break;
            case 'I':
                OrdInsercio(vector, n);
                break;
            case 'S':
                OrdSeleccio(vector, n);
                break;
            case 'M':
                MergeSort(vector, 0, n-1);
                break;
            case 'Q':
                QuickSort(vector,0, n-1);
                break;
            default:
                break;
        }
        clocks_finals=clock();
        promig_temps=promig_temps+(double)(clocks_finals-clocks_inicials)/CLOCKS_PER_SEC;
    }
    promig_temps=promig_temps/i;
    fprintf(fitxer_sortida, "%c\t%i\t%.6f\n", algorisme, n, promig_temps);
    printf("%c\t%i\t%.6f\n", algorisme, n, promig_temps);
    free(vector);
}

/************************************************
PerCadaAlgorismeOrdenacio
Funci� que, per cada algorisme d'ordenaci�, crida
a una funci� per a cada vector d'una llargada
determinada que s'encarregar� d'ordenar aquest
vector mitjan�ant l'algorisme d'ordenaci�
determinat per par�metre.
Par�metres:
    algorisme: Lletra inicial de l'algorisme que
                es vol utilitzar per ordenar el
                vector.
    fitxer_sortida: Fitxer en el qual s'emmagatzemaran
                tots els temps d'ordenaci� de
                cada vector per a l'algorisme
                d'ordenaci� que s'avalua.
Retorn: No retorna res.
************************************************/
void PerCadaAlgorismeOrdenacio(char algorisme, FILE *fitxer_sortida)
{
    int llargades_vectors[MAX_LLARGADES_VECTORS]={100, 500, 1000, 5000, 10000, 50000, 100000, 200000, 300000, 400000}, i;

    for (i=0; i<MAX_LLARGADES_VECTORS; i++) {
        PerCadaLlargadaVector(llargades_vectors[i], algorisme, fitxer_sortida);
    }
    fprintf(fitxer_sortida, "\n");
    printf("\n");
}

int main()
{
    FILE *fitxer_sortida;
    char algorismes[MAX_ALGORISMES]={'B', 'I', 'S', 'M', 'Q'};
    int i;

    fitxer_sortida=fopen("fitxer_sortida.txt","w");
    srand(time(NULL));

    fprintf(fitxer_sortida, "#GRUP BOSCA, CA�ELLES, FERRERO\n#Metode\tN\ttemps(s)\n");

    for (i=0; i<MAX_ALGORISMES; i++) {
        PerCadaAlgorismeOrdenacio(algorismes[i], fitxer_sortida);
    }

    fclose(fitxer_sortida);

    return 0;
}
