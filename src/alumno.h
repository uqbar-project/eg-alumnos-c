#ifndef ALUMNO_H_
#define ALUMNO_H_

#include <stdbool.h>
#include <string.h>
#include "parcial.h"
#include "tipoAlumno.h"

typedef struct AlumnoType {
	char * nombre;
	char * apellido;
	char * direccion;
	int edad;
	int legajo;
	bool (*criterioEstudio)(Parcial*);
} Alumno;

char * nombreCompleto(Alumno * unAlumno);
void setCriterioDeEstudio(Alumno * unAlumno, bool (*criterioEstudio)(Parcial*));
bool esMayorDeEdad(Alumno * unAlumno);

Alumno * Alumno_new(char * nombre, char * apellido, char * direccion, int edad,
		int legajo, bool (*criterioEstudio)(Parcial *));

#endif /* ALUMNO_H_ */
