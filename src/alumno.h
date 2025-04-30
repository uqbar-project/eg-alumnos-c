#ifndef ALUMNO_H_
#define ALUMNO_H_

#include <stdbool.h>
#include <string.h>
#include "parcial.h"
#include "tipoAlumno.h"

// ***************************************************************************
// TAD Alumno - Interfaz
// ***************************************************************************


// ***************************************************************************
// estructura del Alumno
typedef struct AlumnoType {
	char * nombre;
	char * apellido;
	char * direccion;
	int edad;
	int legajo;
	bool (*criterioEstudio)(Parcial*);
} Alumno;

// ***************************************************************************
// función constructora
Alumno * Alumno_new(char * nombre, char * apellido, char * direccion, int edad,
		int legajo, bool (*criterioEstudio)(Parcial *));

// ***************************************************************************
// primitivas
void setCriterioDeEstudio(Alumno * unAlumno, bool (*criterioEstudio)(Parcial*));

// ***************************************************************************
// operaciones de alto nivel
char * nombreCompleto(Alumno * unAlumno);
bool esMayorDeEdad(Alumno * unAlumno);
bool estudia(Alumno * unAlumno, Parcial * unParcial);

#endif /* ALUMNO_H_ */
