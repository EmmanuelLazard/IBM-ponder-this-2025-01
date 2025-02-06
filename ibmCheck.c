#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct etat {
	double Va;
	double Vb;
	double Vc;
} Etat;

double VA,VB,VC;

void checkOperations(Etat e, char *listeOps) {

	printf("Start: [%lf, %lf, %lf]\n", e.Va, e.Vb, e.Vc);
	char *OP = strtok ( listeOps, " " );
    while (OP != NULL) {
		// First we fill the jugs
		if (!strcmp(OP, "TA")) {
			e.Va = VA;
		}
		if (!strcmp(OP, "TB")) {
			e.Vb = VB;
		}
		if (!strcmp(OP, "TC")) {
			e.Vc = VC;
		}
		// We empty the jugs
		if (!strcmp(OP, "AS")) {
			e.Va = 0.0L;
		}
		if (!strcmp(OP, "BS")) {
			e.Vb = 0.0L;
		}
		if (!strcmp(OP, "CS")) {
			e.Vc = 0.0L;
		}
	// We transfer A into B
		if (!strcmp(OP, "AB")) {
			if (e.Va > (VB - e.Vb)) { // more in A to fill B
				e.Va -= (VB - e.Vb);
				e.Vb = VB;
			} else {
				e.Vb += e.Va ;
				e.Va = 0;
			}
		}
	// We transfer A into C
		if (!strcmp(OP, "AC")) {
			if (e.Va > (VC - e.Vc)) { // more in A to fill C
				e.Va -= (VC - e.Vc);
				e.Vc = VC;
			} else {
				e.Vc += e.Va ;
				e.Va = 0;
			}
		}
	// We transfer B into A
		if (!strcmp(OP, "BA")) {
			if (e.Vb > (VA - e.Va)) { // more in B to fill A
				e.Vb -= (VA - e.Va);
				e.Va = VA;
			} else {
				e.Va += e.Vb ;
				e.Vb = 0;
			}
		}
	// We transfer B into C
		if (!strcmp(OP, "BC")) {
			if (e.Vb > (VC - e.Vc)) { // more in B to fill C
				e.Vb -= (VC - e.Vc);
				e.Vc = VC;
			} else {
				e.Vc += e.Vb ;
				e.Vb = 0;
			}
		}
		// We transfer C into A
		if (!strcmp(OP, "CA")) {
			if (e.Vc > (VA - e.Va)) { // more in C to fill A
				e.Vc -= (VA- e.Va);
				e.Va = VA;
			} else {
				e.Va += e.Vc ;
				e.Vc = 0;
			}
		}
	// We transfer C into B
		if (!strcmp(OP, "CB")) {
			if (e.Vc > (VB - e.Vb)) { // more in C to fill B
				e.Vc -= (VB - e.Vb);
				e.Vb = VB;
			} else {
				e.Vb += e.Vc ;
				e.Vc = 0;
			}
		}
	
		printf("After %s: [%lf, %lf, %lf]\n", OP, e.Va, e.Vb, e.Vc);
		OP = strtok ( NULL, " " );
	}
}

int main(void) {
	VA = sqrt(5);
	VB = sqrt(3);
	VC = sqrt(2);
	Etat e = {0,0,0};
	char str[] = "TC CA TC CA AS CA TC CA TC AB CA TC CA AS CA TC CA AS CA TC CA TC CA AS CA TC CA TC CA AS CA TC CA AS CA TC CA TC CA";
	checkOperations(e, str);
}



