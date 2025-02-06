#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAILLE 50000000

const float goal = 1.0;
const float epsilon = 0.0003;


typedef struct etat {
	float Va;
	float Vb;
	float Vc;
	int depth;
} Etat;

Etat cycle[TAILLE] = {{0,0, 0,0}};
int indice = 0; /* indique le premier indice libre dans le tableau */

int ops[50];
char *opsNames[] = {"TA", "TB", "TC", "AS", "BS", "CS", "AB", "AC", "BA", "BC", "CA", "CB"};
int opsDepth = 0;

float VA,VB,VC;

int check(Etat e) {
	return  (fabs(goal - e.Va) <= epsilon) ||
			(fabs(goal - e.Vb) <= epsilon) ||
			(fabs(goal - e.Vc) <= epsilon);
}

/* Teste si un état est dans le tableau des cycles */
int isInCycleAndAdd(Etat e) {
    int i;
    for (i = 0; i < indice; i++)
		if (cycle[i].Va == e.Va &&
			cycle[i].Vb == e.Vb &&
			cycle[i].Vc == e.Vc &&
			cycle[i].depth >= e.depth)
            return 1;
    if (indice >= TAILLE) {
	    printf("Trop d'etats a memoriser\n");
        exit(1);
    }
	cycle[indice++] = e;

    return 0;
}

void printOps(void) {
	int i;
	for (i=0; i<opsDepth; i++)
		printf("%s ", opsNames[ops[i]]);
	printf("\n");
}

int operations(Etat e) {
	Etat nvE;
	if (check(e)) {
		printf("OK : [%lf, %lf, %lf] avec \n", e.Va, e.Vb, e.Vc);
		printOps();
		exit(0);
	}
	if (e.depth == 0 || isInCycleAndAdd(e))
		return 0;
	// First we fill the jugs
	if (e.Va != VA) {
		nvE.Va = VA;
		nvE.Vb = e.Vb;
		nvE.Vc = e.Vc;
		nvE.depth = e.depth-1;
		ops[opsDepth-e.depth]=0;
		operations(nvE);
	}
	if (e.Vb != VB) {
		nvE.Va = e.Va;
		nvE.Vb = VB;
		nvE.Vc = e.Vc;
		nvE.depth = e.depth-1;
		ops[opsDepth-e.depth]=1;
		operations(nvE);
	}
	if (e.Vc != VC) {
		nvE.Va = e.Va;
		nvE.Vb = e.Vb;
		nvE.Vc = VC;
		nvE.depth = e.depth-1;
		ops[opsDepth-e.depth]=2;
		operations(nvE);
	}

// We empty the jugs
	if (e.Va != 0) {
		nvE.Va = 0;
		nvE.Vb = e.Vb;
		nvE.Vc = e.Vc;
		nvE.depth = e.depth-1;
		ops[opsDepth-e.depth]=3;
		operations(nvE);
	}
	if (e.Vb != 0) {
		nvE.Va = e.Va;
		nvE.Vb = 0;
		nvE.Vc = e.Vc;
		nvE.depth = e.depth-1;
		ops[opsDepth-e.depth]=4;
		operations(nvE);
	}
	if (e.Vc != 0) {
		nvE.Va = e.Va;
		nvE.Vb = e.Vb;
		nvE.Vc = 0;
		nvE.depth = e.depth-1;
		ops[opsDepth-e.depth]=5;
		operations(nvE);
	}

// We transfer A into B
	if (e.Va > 0) {
		if (e.Va > (VB - e.Vb)) { // more in A to fill B
			nvE.Vb = VB;
			nvE.Va = e.Va - (VB - e.Vb);
		} else {
			nvE.Vb = e.Vb + e.Va ;
			nvE.Va = 0;
		}
		nvE.Vc = e.Vc;
		nvE.depth = e.depth-1;
		ops[opsDepth-e.depth]=6;
		operations(nvE);
	}
// We transfer A into C
	if (e.Va > 0) {
		if (e.Va > (VC - e.Vc)) { // more in A to fill C
			nvE.Vc = VC;
			nvE.Va = e.Va - (VC - e.Vc);
		} else {
			nvE.Vc = e.Vc + e.Va ;
			nvE.Va = 0;
		}
		nvE.Vb = e.Vb;
		nvE.depth = e.depth-1;
		ops[opsDepth-e.depth]=7;
		operations(nvE);
	}

// We transfer B into A
	if (e.Vb > 0) {
		if (e.Vb > (VA - e.Va)) { // more in B to fill A
			nvE.Va = VA;
			nvE.Vb = e.Vb - (VA - e.Va);
		} else {
			nvE.Va = e.Va + e.Vb ;
			nvE.Vb = 0;
		}
		nvE.Vc = e.Vc;
		nvE.depth = e.depth-1;
		ops[opsDepth-e.depth]=8;
		operations(nvE);
	}
// We transfer B into C
	if (e.Vb > 0) {
		if (e.Vb > (VC - e.Vc)) { // more in B to fill C
			nvE.Vc = VC;
			nvE.Vb = e.Vb - (VC - e.Vc);
		} else {
			nvE.Vc = e.Vc + e.Vb ;
			nvE.Vb = 0;
		}
		nvE.Va = e.Va;
		nvE.depth = e.depth-1;
		ops[opsDepth-e.depth]=9;
		operations(nvE);
	}

// We transfer C into A
	if (e.Vc > 0) {
		if (e.Vc > (VA - e.Va)) { // more in C to fill A
			nvE.Va = VA;
			nvE.Vc = e.Vc - (VA - e.Va);
		} else {
			nvE.Va = e.Va + e.Vc ;
			nvE.Vc = 0;
		}
		nvE.Vb = e.Vb;
		nvE.depth = e.depth-1;
		ops[opsDepth-e.depth]=10;
		operations(nvE);
	}
// We transfer C into B
	if (e.Vc > 0) {
		if (e.Vc > (VB - e.Vb)) { // more in C to fill B
			nvE.Vb = VB;
			nvE.Vc = e.Vc - (VB - e.Vb);
		} else {
			nvE.Vb = e.Vb + e.Vc ;
			nvE.Vc = 0;
		}
		nvE.Va = e.Va;
		nvE.depth = e.depth-1;
		ops[opsDepth-e.depth]=11;
		operations(nvE);
	}
	
	return 0;
}

int main(void) {
	int d;
	VA = sqrt(5);
	VB = sqrt(3);
	VC = sqrt(2);
	Etat e = {0,0,0,0};
	for (d = 1; d < 40; d++) {
		printf("Trying depth %d\n", d);
		opsDepth = e.depth = d;
		operations(e);
	}



}



