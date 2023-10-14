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
Estructura de tipus registere que cont� tota la
informaci� necesaria per a definir un cromosoma.
Par�metres:
    cromosoma: Vector a on cada posici� representa
        un gen.
    solve: Variable booleana que indica si el
        aquest cromosoma concret �s la millor soluci�
        possible al problema d'optimitzaci� plantejat.
******************************************************/
typedef struct
{
    int cromosoma[MAX_GENS];        //Cromosoma amb gens
    int solve;                      //Boolea que s'activara quan el cromosoma coincideixi exactament amb la soluci�.
}cromosoma_t;

/****************************************************
Inicialitzacions
Acci� que inicialitza tots els gens de tots els
cromosomes amb un n�mero enter aleatori localitzat
entre 0 i 1.
Par�metres:
    poblacio: Vector a on cada posici� representa un
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
Funci� de fitness. S'encarrega de determinar com
d'apte �s un cromosoma avaluant, mitjan�ant la f�rmula
plantejada en l'enunciat del problema, la proximitat
d'aquest a la soluci� real.
Par�metres:
    cromosoma: Vector a on cada posici� representa
        un gen.
Retorn: Retorna la difer�ncia entre la soluci� local
del cromosoma i la soluci� real. A mesura que aquesta
soluci� sigui m�s propera a 0, m�s a prop s'estar�
de la soluci�.
******************************************************/
int FitnessFunction(int cromosoma[])
{
    int i, acum=0;                   //acum �s un acumulador que permetr� acumular cada resultat parcial de la iteraci�, es adir, el resultat de multiplicar cada gen per la posici� del cromosoma a on es troba.

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
Funci� que incorpora de forma ordenada el nou valor
de fitness al vector que emmagatzema els K millors
valors de fitness y, la referencia al cromosoma al
que pertany el nou valor de fitness a un vector que
emmagatzema totes les referencies a tots els cromosomes
que contenen un valor de fitness emmagatzemat en el
vector anterior.
Par�metres:
    fitness_cromosoma: Valor de fitness que es vol
        afegir.
    num_cromosoma: Index de un cromosoma de la
        poblaci�.
    millor_fitness: Vector que guarda els millors
        valors de fitness de la poblaci�.
    index_millor_fitness: Vector que cont� la referencia
        als cromosoma als que pertanyen els fitness
        que est� emmagatzemats en el vector_millor
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
            for (j=i; j<last_pos; j++) {                 //Es despla�aran cap a la dreta tots els valors de fitness emmagatzemats al vector millor_fitness desde la posici� final fins a la posici� que ocupar� el nou valor de fitness que es vol emmagatzemar al vector.
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
Funci� que genera la nova poblaci� amb els K cromosomes
que tenen el millor fitness organitzats de manera que
cada cromosoma mai s'encreui amb ell mateix i per a
que, d'aquests, els que tenen un fitness encara millor
apareguin en la nova poblaci� amb una frecuencia m�s
elevada.
Par�metres:
    poblacio: Poblaci� que recull tots els cromosomes
        de la generaci� anterior. Es tracta d'un
        vector a on cada posici� representa un
        cromosoma.
    nova_poblacio: Poblaci� que recull tots els
        cromosomes de la nova generaci�.Es tracta d'un
        vector a on cada posici� representa un
        cromosoma.
    index_millor_fitness: Vector que conte la referencia
        als cromosoma als que pertanyen els fitness
        que est� emmagatzemats en el vector_millor
        fitness. Les posicions iguals dels dos
        vectors fan referencia al mateix cromosoma.
Retorn: No retorna res.
******************************************************/
void MatingPool(cromosoma_t poblacio[], cromosoma_t nova_poblacio[], int index_millor_fitness[])
{
    int i=0, j, num_cromosoma=0;

    while (num_cromosoma<MAX_CROMOSOMES-2){            //Es recorren tots els cromosomes fins arribar a l'�ltim.
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
Funcio que dels cromosomes de la poblaci� de la
generaci� anterior, en selecciona aquells que tenen
el millor fitness per a comen�ar a constitu�r la
poblaci� la nova generaci�. A m�s, es comproba si
s'ha trobat la soluci� definitiva i, en cas de que no
sigui aix�, es fa una reproducci� de  tota la poblaci�.
Par�metres:
    poblacio: Poblaci� que recull tots els cromosomes
        de la generaci� anterior. Es tracta d'un
        vector a on cada posici� representa un
        cromosoma.
    nova_poblacio: Poblaci� que recull tots els
        cromosomes de la nova generaci�.Es tracta d'un
        vector a on cada posici� representa un
        cromosoma.
Retorn: Retorna el cromosoma amb millor fitness. Es
distingir� si es tracta de la soluci� definitiva o
nom�s d'una aproximaci�.
******************************************************/
cromosoma_t TournamentSelection(cromosoma_t poblacio[], cromosoma_t nova_poblacio[])
{
    int i, num_cromosoma=0;
    int fitness_cromosoma;                          //Fitness del cromosoma.
    int millor_fitness[PARAMETRE_K];                    //Vector que emmagatzema els K millors fitness. Aquests estaran ordenats de millor a pitjor.
    int index_millor_fitness[PARAMETRE_K];              //Vector que conte la referencia als cromosoma als que pertanyen els fitness que est� emmagatzemats en el vector_millor fitness. Les posicions iguals dels dos vectors fan referencia al mateix cromosoma.

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
Par�metres:
    nova_poblacio: Poblaci� que recull tots els
        cromosomes de la nova generaci�.Es tracta d'un
        vector a on cada posici� representa un
        cromosoma.
Retorn: No retorna res.
******************************************************/
void OnePointCrossover(cromosoma_t nova_poblacio[])
{
    int num_cromosoma, gen, punt_encreuament;
    cromosoma_t auxiliar;

    for (num_cromosoma=0; num_cromosoma<MAX_CROMOSOMES-1; num_cromosoma=num_cromosoma+2){
        punt_encreuament=rand()%MAX_GENS;                      //La posici� respecte a la cual es generar� l'encreuament s'obtindr� de manera aleatoria.
        for (gen=punt_encreuament; gen<MAX_GENS; gen++){
            auxiliar.cromosoma[gen]=nova_poblacio[num_cromosoma].cromosoma[gen];
            nova_poblacio[num_cromosoma].cromosoma[gen]=nova_poblacio[num_cromosoma+1].cromosoma[gen];
            nova_poblacio[num_cromosoma+1].cromosoma[gen]=auxiliar.cromosoma[gen];
        }
    }
}

/****************************************************
FlipMutation
Funci� que realiza mutacions en un 5% dels gens.
Aquestes mutacions consisteixen en la negaci� del
valor del gen. Es a dir, si el valor del gen es 0, es
convertir� en 1, mentre que, si el valor del gen es
1, es convertir� en 0.
Par�metres:
     nova_poblacio: Poblaci� que recull tots els
        cromosomes de la nova generaci�.Es tracta d'un
        vector a on cada posici� representa un
        cromosoma.
Retorn: No retorna res.
******************************************************/
void FlipMutation(cromosoma_t nova_poblacio[])
{
    int num_cromosoma, gen;
    float probabilitat;

    for (num_cromosoma=0; num_cromosoma<MAX_CROMOSOMES; num_cromosoma++){
        for (gen=0; gen<MAX_GENS; gen++){
            probabilitat=(rand()%100)+1;            //Com que el 0 es un dels valors que pot sorgir aleatoriament en aplicar la funci� rand(), s'ha de sumar 1 al resultat per prevenir la posibilitat de dividir per 0.
            probabilitat=probabilitat/100;
            if (probabilitat<PROBABILITAT_MUTACIO){
                nova_poblacio[num_cromosoma].cromosoma[gen]=!nova_poblacio[num_cromosoma].cromosoma[gen];
            }
        }
    }
}

/****************************************************
Supervivencia
Funci� que canv�a de generaci�. Aquest proc�s
consisteix en la substituci� de la poblaci� antiga
per la nova poblaci� que s'ha estat desenvolupant en
les etapes anteriors.
Par�metres:
    poblacio: Poblaci� que recull tots els cromosomes
        de la generaci� anterior. Es tracta d'un
        vector a on cada posici� representa un
        cromosoma.
    nova_poblacio: Poblaci� que recull tots els
        cromosomes de la nova generaci�.Es tracta d'un
        vector a on cada posici� representa un
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
Funci� que, en arribar a una nova generaci�,
desenvolupa una nova poblaci� amb cromosomes que
presenten un millor fitness que el cromosomes de la
poblaci� de la generaci� anterior. Aquest proc�s es
realitza en quatre etapes ben diferenciades: Selecci�,
Crossover, Mutaci� i Supervivencia.
Par�metres:
    poblacio: Vector a on cada posici� representa un
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

    millor_cromosoma=Generacio(poblacio);          //S'emagatzema el millor cromosoma de tota la primera generaci�.

    while ((!millor_cromosoma.solve)&&(generacio<MAX_GENERACIONS)){
        millor_cromosoma=Generacio(poblacio);
        generacio++;
    }

    printf("Generacio: %d\n\nCromosoma:", generacio);         //S'imprimeix per pantalla el millor cromosoma, en quina generaci� s'ha trobat i amb quin fitness.
    for(num_gen=0; num_gen<MAX_GENS; num_gen++){
        printf(" %d", millor_cromosoma.cromosoma[num_gen]);
    }
    printf("\n\nAmb fitness: %d\n", FitnessFunction(millor_cromosoma.cromosoma));

    return 0;
}
