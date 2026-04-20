#include <stdio.h>
#include <stdlib.h>
#include "alumno.h"
#include "criterio.h"
#include "parcial.h"
#include "commons/constructor.h"

// Demo: resuelve el pedido del enunciado con Nico.
//   1. Modelar a Nico, un alumno estudioso.
//   2. Hacer que Nico pase de estudioso a hijo del rigor.
//   3. Determinar si Nico va a estudiar para el parcial de Paradigmas.
int main(void) {
	Alumno * nico = Alumno_new("Nico", "Gomez", "Av. siempre viva 742", 20,
			111111, estudioso);
	Parcial * paradigmas = Parcial_new("Paradigmas de programacion", 4);

	string fullName = nombreCompleto(nico);
	printf("Alumno: %s (legajo %d)\n", fullName, nico->legajo);
	printf("  Mayor de edad? %s\n", esMayorDeEdad(nico) ? "si" : "no");

	printf("  Como estudioso, estudia para %s? %s\n",
			paradigmas->materia, estudia(nico, paradigmas) ? "si" : "no");

	setCriterioDeEstudio(nico, hijoDelRigor);
	printf("  Como hijo del rigor, estudia para %s? %s\n",
			paradigmas->materia, estudia(nico, paradigmas) ? "si" : "no");

	free(fullName);
	FREE(nico);
	FREE(paradigmas);
	return 0;
}
