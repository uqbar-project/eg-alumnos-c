#include "alumno.h"
#include <stdlib.h>
#include "commons/constructor.h"

char * nombreCompleto(Alumno * unAlumno) {
	char * fullName = malloc(
			strlen(unAlumno->nombre) + 1 + strlen(unAlumno->apellido));
	strcpy(fullName, unAlumno->apellido);
	strcat(fullName, ", ");
	strcat(fullName, unAlumno->nombre);
	return fullName;
}

void setCriterioDeEstudio(Alumno * unAlumno, bool (*unCriterio)(Parcial*)){
	unAlumno->criterioEstudio = unCriterio;
}
bool esMayorDeEdad(Alumno * unAlumno) {
	return unAlumno->edad > 18;
}

Alumno * Alumno_new(char * nombre, char * apellido, char * direccion, int edad,
		int legajo, bool (*criterioEstudio)(Parcial *)) {
	//Alumno * unAlumno = malloc(sizeof(Alumno));
	NEW(unAlumno, Alumno);
	unAlumno->nombre = nombre;
	unAlumno->apellido = apellido;
	unAlumno->direccion = direccion;
	unAlumno->edad = edad;
	unAlumno->legajo = legajo;
	unAlumno->criterioEstudio = criterioEstudio;
	return unAlumno;
}
