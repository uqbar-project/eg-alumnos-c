#include "tests.h"
#include <stdio.h>
#include <stdbool.h>
#include <cspecs/cspec.h>

context (test_de_alumnos) {
  
  describe("Dado un Alumno") {
    Alumno * nico;
    Parcial * materiaConLongitudPar;
    Parcial * materiaConLongitudImpar;

    before {
      nico = Alumno_new("Nico", "Gomez", "Av. siempre viva 742", 20, 111111,
			estudioso);
      materiaConLongitudPar = Parcial_new("Paradigmas de programacion", 5);
      materiaConLongitudImpar = Parcial_new("Sistemas Operativos", 8);
    } end

    after {
      FREE(nico);
      FREE(materiaConLongitudPar);
      FREE(materiaConLongitudImpar);
    } end

    it("nombre completo de un alumno") {
      should_string(nombreCompleto(nico)) be equal to("Gomez, Nico");
    } end

    it("una persona estudiosa siempre estudia") {
      setCriterioDeEstudio(nico,estudioso);
      should_bool(nico->criterioEstudio(materiaConLongitudPar)) be truthy;
    } end

    it("una persona es mayor de edad") {
        should_bool(esMayorDeEdad(nico)) be truthy;
    } end
    
    it("una persona no es mayor de edad") {
      nico->edad = 15;
      should_bool(esMayorDeEdad(nico)) be falsey;
    } end
    
    it("una persona hija del rigor no estudia si el parcial tiene pocas preguntas"){
      nico->criterioEstudio = hijoDelRigor;
      materiaConLongitudPar->cantidadDePreguntas = 5;
      should_bool(nico->criterioEstudio(materiaConLongitudPar)) be falsey;
    } end
    
    it("una persona hija del rigor estudia si el parcial tiene muchas preguntas"){
      nico->criterioEstudio = hijoDelRigor;
      materiaConLongitudPar->cantidadDePreguntas = 6;
      should_bool(nico->criterioEstudio(materiaConLongitudPar)) be truthy;
    } end

    it("una persona cabulera estudia si el parcial tiene una cantidad par de preguntas"){
      setCriterioDeEstudio(nico,cabulero);
      should_bool(nico->criterioEstudio(materiaConLongitudPar)) be truthy;
    } end

    it("una persona cabulera NO estudia si el parcial tiene una cantidad impar de preguntas"){
      setCriterioDeEstudio(nico,cabulero);
      should_bool(nico->criterioEstudio(materiaConLongitudImpar)) be falsey;
    } end

  } end

}