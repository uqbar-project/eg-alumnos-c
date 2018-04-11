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
    bool (*criterioEstudio)(Parcial* );
} Alumno;


char * getNombre(Alumno * unAlumno);
char * getApellido(Alumno * unAlumno);
char * getNombreCompleto(Alumno * unAlumno);
char * getDireccion(Alumno * unAlumno);
int getEdad(Alumno * unAlumno);
int getLegajo(Alumno * unAlumno);
void setNombre(Alumno * unAlumno, char * unNombre);
bool esMayorDeEdad(Alumno * unAlumno);

Alumno * Alumno_new(char * nombre, char * apellido, char * direccion,int edad,int legajo,bool (*criterioEstudio)(Parcial *));

#endif /* ALUMNO_H_ */
