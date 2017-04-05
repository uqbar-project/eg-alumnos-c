#ifndef ALUMNO_H_
#define ALUMNO_H_

#include <stdbool.h>
#include <string.h>
#include "parcial.h"

typedef struct AlumnoType {
    char * nombre;
    char * direccion;
    int edad;
    int legajo;
    bool (*criterioEstudio)(Parcial* );
} Alumno;

bool estudioso (Parcial *);
bool hijoDelRigor (Parcial *);
bool hijoDelRigorConMasDe (int, Parcial *);
bool cabulero (Parcial *);

Alumno * Alumno_new(char * nombre,char * direccion,int edad,int legajo,bool (*criterioEstudio)(Parcial *));
void Alumno_free(Alumno *this);

#endif /* ALUMNO_H_ */
