#ifndef THEREMIN_NOTAS_H
#define THEREMIN_NOTAS_H

#include<math.h>
#include<stdlib.h>

#define DO  0
#define DOs 1
#define REb 1
#define RE  2
#define REs 3
#define MIb 3
#define MI  4
#define FA  5
#define FAs 6
#define SOLb 6
#define SOL 7
#define SOLs 8
#define LAb 8
#define LA 9
#define LAs 10
#define SIb 10
#define SI 11


class Musica{

private:
	double notas[12]; //{16.35,17.32,18.35,19.45,20.60,21.83,23.12,24.50,25.96,27.50,29.14,30.87};

	double octavas[8];

public:
	Musica();
	double getNota(int nota, int octava);
	double normalizar(double frecuencia);
        int getOctava(double frecuencia);	
};
#endif
