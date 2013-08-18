#include "notas.h"

Musica::Musica(){
	notas[DO]=16.35;
	notas[DOs]=17.32;
	notas[RE]=18.35;
	notas[MIb]=19.45;
	notas[MI]=20.60;
	notas[FA]=21.83;
	notas[FAs]=23.12;
	notas[SOL]=24.50;
	notas[LAb]=25.96;
	notas[LA]=27.50;
	notas[SIb]=29.14;
	notas[SI]=30.87;
	

	for(int i=0;i<8;i++) octavas[i]=getNota(DO,i);
}

double Musica::getNota(int nota, int octava){
	return notas[nota]*pow(2,octava);
}

int Musica::getOctava(double frecuencia){
	int octava=0;
	for(int i=0; i<8;i++)
		if(frecuencia>=octavas[i] && frecuencia <=octavas[i+1])
			octava=i;	
	return octava;
}

double Musica::normalizar(double frecuencia){
	int octava=getOctava(frecuencia);
	double freq_base=frecuencia/pow(2,octava);	
	double menor=99;
	int nota;
	bool flag=0;
	
	for(nota=DO;nota<=SI && !flag;nota++){
		double aux=abs(notas[nota]-freq_base);
		if(aux<menor)
			menor=aux;
		else
			flag=1;
	}

	return getNota(nota,octava+3);
}
