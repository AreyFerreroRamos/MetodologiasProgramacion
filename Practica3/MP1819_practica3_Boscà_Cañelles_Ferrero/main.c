#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SOLUCIO 1977
#define MAX_GENS 30
#define MAX_GENERACIONS 100
#define MAX_CROMOSOMES 20
#define PARAMETRE_K 5
#define PROBABILITAT_MUTACIO 0.05
#define MILLOR_FITNES_INICIAL 9500

/****************************************************
cromosoma_t
Estructura de tipus registere que conté tota la
informació necesaria per a definir un cromosoma.
Paràmetres:
    cromosoma: Vector a on cada posició representa
        un gen.
    solve: Variable booleana que indica si el
        aquest cromosoma concret és la millor solució
        possible al problema d'optimització plantejat.
******************************************************/
typedef struct
{
    int cromosoma[MAX_GENS];        //Cromosoma amb gens
    int solve;                      //Boolea que s'activara quan el cromosoma coincideixi exactament amb la solució.
}cromosoma_t;

/****************************************************
Inicialitzacions
Acció que inicialitza tots els gens de tots els
cromosomes amb un número enter aleatori localitzat
entre 0 i 1.
Paràmetres:
    poblacio: Vector a on cada posició representa un
        cromosoma.
Retorn: No retorna res.
******************************************************/
void Inicialitzacions(cromosoma_t poblacio[])
{
    int num_cromosoma, num_gen;

    for (num_cromosoma=0; num_cromosoma<MAX_CROMOSOMES; num_cromosoma++){
        for (num_gen=0; num_gen<MAX_GENS; num_gen++){
            poblacio[num_cromosoma].cromosoma[num_gen]= rand()%2;        //S'inicialitza el gen amb un nombre enter aleatori loaclitzat entre 0 i 1.

        }
        poblacio[num_cromosoma].solve=0;
    }
}

/****************************************************
FitnessFunction
Funció de fitness. S'encarrega de determinar com
d'apte és un cromosoma avaluant, mitjançant la fórmula
plantejada en l'enunciat del problema, la proximitat
d'aquest a la solució real.
Paràmetres:
    cromosoma: Vector a on cada posició representa
        un gen.
Retorn: Retorna la diferència entre la solució local
del cromosoma i la solució real. A mesura que aquesta
solució sigui més propera a 0, més a prop s'estarà
de la solució.
******************************************************/
int FitnessFunction(int cromosoma[])
{
    int i, acum=0;                   //acum és un acumulador que permetrá acumular cada resultat parcial de la iteració, es adir, el resultat de multiplicar cada gen per la posició del cromosoma a on es troba.

    for (i=1; i<=MAX_GENS; i++){          //Cada valor de i representa un gen del cromosoma.
        acum=acum+cromosoma[i-1]*(i*i);
    }
    acum=acum-SOLUCIO;

    if (acum<0) {
        acum=-acum;
    }
   return acum;
}

/****************************************************
UpdateFitness
Funció que incorpora de forma ordenada el nou valor
de fitness al vector que emmagatzema els K millors
valors de fitness y, la referencia al cromosoma al
que pertany el nou valor de fitness a un vector que
emmagatzema totes les referencies a tots els cromosomes
que contenen un valor de fitness emmagatzemat en el
vector anterior.
Paràmetres:
    fitness_cromosoma: Valor de fitness que es vol
        afegir.
    num_cromosoma: Index de un cromosoma de la
        població.
    millor_fitness: Vector que guarda els millors
        valors de fitness de la població.
    index_millor_fitness: Vector que conté la referencia
        als cromosoma als que pertanyen els fitness
        que está emmagatzemats en el vector_millor
        fitness. Les posicions iguals dels dos
        vectors fan referencia al mateix cromosoma.
Retorn: No retorna res.
******************************************************/
void UpdateFitness(int fitness_cromosoma, int num_cromosoma, int millor_fitness[], int index_millor_fitness[])
{
    int i=0, j, k, last_pos=PARAMETRE_K-1;

    while ((fitness_cromosoma<millor_fitness[last_pos]) && (i<PARAMETRE_K)){
        if (fitness_cromosoma<millor_fitness[i]){
            k=0;
            for (j=i; j<last_pos; j++) {                 //Es desplaçaran cap a la dreta tots els valors de fitness emmagatzemats al vector millor_fitness desde la posició final fins a la posició que ocupará el nou valor de fitness que es vol emmagatzemar al vector.
                millor_fitness[last_pos-k]=millor_fitness[last_pos-k-1];
                index_millor_fitness[last_pos-k]=index_millor_fitness[last_pos-k-1];
                k++;
            }
            millor_fitness[last_pos-k]=fitness_cromosoma;
            index_millor_fitness[last_pos-k]=num_cromosoma;
            i=PARAMETRE_K;
        }
        else {
            i++;
        }
    }
}

/****************************************************
MatingPool
Funció que genera la nova població amb els K cromosomes
que tenen el millor fitness organitzats de manera que
cada cromosoma mai s'encreui amb ell mateix i per a
que, d'aquests, els que tenen un fitness encara millor
apareguin en la nova població amb una frecuencia més
elevada.
Paràmetres:
    poblacio: Població que recull tots els cromosomes
        de la generació anterior. Es tracta d'un
        vector a on cada posició representa un
        cromosoma.
    nova_poblacio: Població que recull tots els
        cromosomes de la nova generació.Es tracta d'un
        vector a on cada posició representa un
        cromosoma.
    index_millor_fitness: Vector que conte la referencia
        als cromosoma als que pertanyen els fitness
        que está emmagatzemats en el vector_millor
        fitness. Les posicions iguals dels dos
        vectors fan referencia al mateix cromosoma.
Retorn: No retorna res.
******************************************************/
void MatingPool(cromosoma_t poblacio[], cromosoma_t nova_poblacio[], int index_millor_fitness[])
{
    int i=0, j, num_cromosoma=0;

    while (num_cromosoma<MAX_CROMOSOMES-2){            //Es recorren tots els cromosomes fins arribar a l'últim.
        j=i+1;
        while ((num_cromosoma<MAX_CROMOSOMES-2) && (j<PARAMETRE_K)){
            nova_poblacio[num_cromosoma]=poblacio[index_millor_fitness[i]];
            nova_poblacio[num_cromosoma+1]=poblacio[index_millor_fitness[j]];
            num_cromosoma=num_cromosoma+2;
            j++;
        }
        if (i<PARAMETRE_K-1) {
            i++;
        }
        else {
            i=0;
        }
    }
    if (num_cromosoma<MAX_CROMOSOMES) {
        nova_poblacio[num_cromosoma]=poblacio[index_millor_fitness[i]];
    }
    if (num_cromosoma+1<MAX_CROMOSOMES) {
        nova_poblacio[num_cromosoma+1]=poblacio[index_millor_fitness[j-1]];
    }
}

/****************************************************
TournamentSelection
Funcio que dels cromosomes de la població de la
generació anterior, en selecciona aquells que tenen
el millor fitness per a començar a constituïr la
població la nova generació. A més, es comproba si
s'ha trobat la solució definitiva i, en cas de que no
sigui així, es fa una reproducció de  tota la població.
Paràmetres:
    poblacio: Població que recull tots els cromosomes
        de la generació anterior. Es tracta d'un
        vector a on cada posició representa un
        cromosoma.
    nova_poblacio: Població que recull tots els
        cromosomes de la nova generació.Es tracta d'un
        vector a on cada posició representa un
        cromosoma.
Retorn: Retorna el cromosoma amb millor fitness. Es
distingirà si es tracta de la solució definitiva o
només d'una aproximació.
******************************************************/
cromosoma_t TournamentSelection(cromosoma_t poblacio[], cromosoma_t nova_poblacio[])
{
    int i, num_cromosoma=0;
    int fitness_cromosoma;                          //Fitness del cromosoma.
    int millor_fitness[PARAMETRE_K];                    //Vector que emmagatzema els K millors fitness. Aquests estaran ordenats de millor a pitjor.
    int index_millor_fitness[PARAMETRE_K];              //Vector que conte la referencia als cromosoma als que pertanyen els fitness que está emmagatzemats en el vector_millor fitness. Les posicions iguals dels dos vectors fan referencia al mateix cromosoma.

    for (i=0; i<PARAMETRE_K; i++){                      //S'inicialitza el vector fitness.
        millor_fitness[i]=MILLOR_FITNES_INICIAL+i;
    }

    while ((!poblacio[num_cromosoma].solve) && (num_cromosoma<MAX_CROMOSOMES)){     //Es mira el fitness de cada cromosoma i s'emmagatzemen el K millors.
        fitness_cromosoma=FitnessFunction(poblacio[num_cromosoma].cromosoma);
        if (fitness_cromosoma==0) {
            poblacio[num_cromosoma].solve=1;
        }
        else {
            UpdateFitness(fitness_cromosoma, num_cromosoma, millor_fitness, index_millor_fitness);
            num_cromosoma++;
        }
    }
    if ((poblacio[num_cromosoma].solve) && (num_cromosoma<MAX_CROMOSOMES)) {
        return poblacio[num_cromosoma];
    }
    else {
        MatingPool(poblacio, nova_poblacio, index_millor_fitness);
        return poblacio[index_millor_fitness[0]];
    }
}

/****************************************************
OnePointCrossover
Funcio que realiza l'encreuament de dos
cromosomes contigus respecte a un gen seleccionat
aleatoriament donant com a resultat dos cromosomes
fills que presenten gens dels dos cromosomes
progenitors.
Paràmetres:
    nova_poblacio: Població que recull tots els
        cromosomes de la nova generació.Es tracta d'un
        vector a on cada posició representa un
        cromosoma.
Retorn: No retorna res.
******************************************************/
void OnePointCrossover(cromosoma_t nova_poblacio[])
{
    int num_cromosoma, gen, punt_encreuament;
    cromosoma_t auxiliar;

    for (num_cromosoma=0; num_cromosoma<MAX_CROMOSOMES-1; num_cromosoma=num_cromosoma+2){
        punt_encreuament=rand()%MAX_GENS;                      //La posició respecte a la cual es generará l'encreuament s'obtindrà de manera aleatoria.
        for (gen=punt_encreuament; gen<MAX_GENS; gen++){
            auxiliar.cromosoma[gen]=nova_poblacio[num_cromosoma].cromosoma[gen];
            nova_poblacio[num_cromosoma].cromosoma[gen]=nova_poblacio[num_cromosoma+1].cromosoma[gen];
            nova_poblacio[num_cromosoma+1].cromosoma[gen]=auxiliar.cromosoma[gen];
        }
    }
}

/****************************************************
FlipMutation
Funció que realiza mutacions en un 5% dels gens.
Aquestes mutacions consisteixen en la negació del
valor del gen. Es a dir, si el valor del gen es 0, es
convertirà en 1, mentre que, si el valor del gen es
1, es convertirà en 0.
Paràmetres:
     nova_poblacio: Població que recull tots els
        cromosomes de la nova generació.Es tracta d'un
        vector a on cada posició representa un
        cromosoma.
Retorn: No retorna res.
******************************************************/
void FlipMutation(cromosoma_t nova_poblacio[])
{
    int num_cromosoma, gen;
    float probabilitat;

    for (num_cromosoma=0; num_cromosoma<MAX_CROMOSOMES; num_cromosoma++){
        for (gen=0; gen<MAX_GENS; gen++){
            probabilitat=(rand()%100)+1;            //Com que el 0 es un dels valors que pot sorgir aleatoriament en aplicar la funció rand(), s'ha de sumar 1 al resultat per prevenir la posibilitat de dividir per 0.
            probabilitat=probabilitat/100;
            if (probabilitat<PROBABILITAT_MUTACIO){
                nova_poblacio[num_cromosoma].cromosoma[gen]=!nova_poblacio[num_cromosoma].cromosoma[gen];
            }
        }
    }
}

/****************************************************
Supervivencia
Funció que canvïa de generació. Aquest procés
consisteix en la substitució de la població antiga
per la nova població que s'ha estat desenvolupant en
les etapes anteriors.
Paràmetres:
    poblacio: Població que recull tots els cromosomes
        de la generació anterior. Es tracta d'un
        vector a on cada posició representa un
        cromosoma.
    nova_poblacio: Població que recull tots els
        cromosomes de la nova generació.Es tracta d'un
        vector a on cada posició representa un
        cromosoma.
Retorn: No retorna res.
******************************************************/
void Supervivencia(cromosoma_t poblacio[], cromosoma_t nova_poblacio[])
{
    int num_cromosoma;

    for (num_cromosoma=0; num_cromosoma<MAX_CROMOSOMES; num_cromosoma++){
        poblacio[num_cromosoma]=nova_poblacio[num_cromosoma];
    }
}

/****************************************************
Generacio
Funció que, en arribar a una nova generació,
desenvolupa una nova població amb cromosomes que
presenten un millor fitness que el cromosomes de la
població de la generació anterior. Aquest procés es
realitza en quatre etapes ben diferenciades: Selecció,
Crossover, Mutació i Supervivencia.
Paràmetres:
    poblacio: Vector a on cada posició representa un
        cromosoma.
Retorn: Retorna el cromosoma amb el millor fitness.
******************************************************/
cromosoma_t Generacio(cromosoma_t poblacio[])
{
    cromosoma_t millor_cromosoma;
    cromosoma_t nova_poblacio[MAX_CROMOSOMES];

    millor_cromosoma=TournamentSelection(poblacio, nova_poblacio);
    if (!millor_cromosoma.solve){
        OnePointCrossover(nova_poblacio);
        FlipMutation(nova_poblacio);
        Supervivencia(poblacio, nova_poblacio);
    }
    return millor_cromosoma;
}

int main()
{
    int generacio=1, num_gen;
    cromosoma_t poblacio[MAX_CROMOSOMES], millor_cromosoma;

    srand(time(NULL));
    Inicialitzacions(poblacio);

    millor_cromosoma=Generacio(poblacio);          //S'emagatzema el millor cromosoma de tota la primera generació.

    while ((!millor_cromosoma.solve)&&(generacio<MAX_GENERACIONS)){
        millor_cromosoma=Generacio(poblacio);
        generacio++;
    }

    printf("Generacio: %d\n\nCromosoma:", generacio);         //S'imprimeix per pantalla el millor cromosoma, en quina generació s'ha trobat i amb quin fitness.
    for(num_gen=0; num_gen<MAX_GENS; num_gen++){
        printf(" %d", millor_cromosoma.cromosoma[num_gen]);
    }
    printf("\n\nAmb fitness: %d\n", FitnessFunction(millor_cromosoma.cromosoma));

    return 0;
}
