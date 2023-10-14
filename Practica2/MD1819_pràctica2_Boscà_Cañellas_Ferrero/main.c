#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_ALGORISMES 5
#define MAX_LLARGADES_VECTORS 10
#define MAX_PROVES 5

/***********************************************
ObtenirNumeroAleatori
Funció que permet obtenir un número aleatori
localitzat entre un rang qualsevol de valors
determinat per paràmetre utilitzant la funció
rand() de la llibreria estàndard.
Paràmetres:
    rand_min: És el valor mínim del rang.
    rand_max: És el valor màxim del rang.
Retorn: Retorna un número aleatori entre el rang
determinat per paràmetre.
***********************************************/
int ObtenirNumeroAleatori(int rand_min, int rand_max)
{
    return(rand()%(rand_max-rand_min+1)+rand_min);
}

/***********************************************
OrdSelecció
Funció que ordena tots els elements d'un vector
d'enters del més petit al més gran mitjançant
l'algorisme d'ordenació per selecció.
Paràmetres:
    v: Vector d'enters per ordenar.
    nelem: Nombre d'elements del vector.
Retorn: No retorna res. El vector d'enters
es passa per referència i, per tant, quan
es surti de la funció, ja estarà modificat.
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
Funció que ordena tots els elements d'un vector
d'enters del més petit al més gran mitjançant
l'algorisme d'ordenació per bombolla.
Paràmetres:
    v: Vector d'enters per ordenar.
    nelem: Nombre d'elements del vector.
Retorn: No retorna res. El vector d'enters
es passa per referència i, per tant, quan
es surti de la funció, ja estarà modificat.
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
OrdInserció
Funció que ordena tots els elements d'un vector
d'enters del més petit al més gran mitjançant
l'algorisme d'ordenació per inserció.
Paràmetres:
    v: Vector d'enters per ordenar.
    nelem: Nombre d'elements del vector.
Retorn: No retorna res. El vector d'enters
es passa per referència i, per tant, quan
es surti de la funció, ja estarà modificat.
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
posició intermitja cap a baix i des de la
posició intermitja cap amunt, retorna el vector
completament ordenat.
Paràmetres:
    v: Vector d'enters.
    ini: Posició inicial del vector.
    mig: Posició intermitja del vector.
    fin: Posició final del vector.
Retorn: No retorna res. El vector d'enters
es passa per referència i, per tant, quan
es surti de la funció, ja estarà modificat.
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
Funció que ordena tots els elements d'un vector
d'enters del més petit al més gran mitjançant
l'algorisme d'ordenació MergeSort.
Paràmetres:
    v: Vector d'enters per ordenar.
    ini: Posició inicial del vector.
    fin: Posició final del vector.
Retorn: No retorna res. El vector d'enters
es passa per referència i, per tant, quan
es surti de la funció, ja estarà modificat.
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
Funció que, donat un vector d'enters, selecciona
el primer element del vector com a pivot i ubica
aquest pivot en una posició del vector de manera
que tots els elements més petit que aquest siguin
colocats a la seva esquerra i tots els elements
més grans siguin colocats a la seva dreta.
Paràmetres:
    v: Vector d'enters.
    ini: Posició inicial del vector.
    fin: Posició final del vector.
Retorn: Retorna la posició del vector en la
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
Funció que ordena tots els elements d'un vector
d'enters del més petit al més gran mitjançant
l'algorisme d'ordenació QuickSort.
Paràmetres:
    v: Vector d'enters per ordenar.
    ini: Posició inicial del vector.
    fin: Posició final del vector.
Retorn: No retorna res. El vector d'enters
es passa per referència i, per tant, quan
es surti de la funció, ja estarà modificat.
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
Funció que, per cada vector d'enters d'una
llargada determinada per paràmetre, ordena tots
aquests enters mitjançant un algorisme d'ordenació
també determinat per paràmetre.
Paràmetres:
    vector: vector d'enters desordenats.
    n: Llargada del vector
    algorisme: Lletra inicial de l'algorisme que
                es vol utilitzar per ordenar el
                vector.
    fitxer_sortida: Fitxer en el qual s'emmagatzemarà
                el temps d'ordenació del vector
                que s'avalua per a l'algorisme
                d'ordenació que s'avalua.
Retorn: No retorna res. El valor del temps
d'ordenació s'emmagatzema en un fitxer de text.
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
Funció que, per cada algorisme d'ordenació, crida
a una funció per a cada vector d'una llargada
determinada que s'encarregarà d'ordenar aquest
vector mitjançant l'algorisme d'ordenació
determinat per paràmetre.
Paràmetres:
    algorisme: Lletra inicial de l'algorisme que
                es vol utilitzar per ordenar el
                vector.
    fitxer_sortida: Fitxer en el qual s'emmagatzemaran
                tots els temps d'ordenació de
                cada vector per a l'algorisme
                d'ordenació que s'avalua.
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

    fprintf(fitxer_sortida, "#GRUP BOSCA, CAÑELLES, FERRERO\n#Metode\tN\ttemps(s)\n");

    for (i=0; i<MAX_ALGORISMES; i++) {
        PerCadaAlgorismeOrdenacio(algorismes[i], fitxer_sortida);
    }

    fclose(fitxer_sortida);

    return 0;
}
