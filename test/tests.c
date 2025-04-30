#include "tests.h"
#include <stdio.h>
#include <stdbool.h>
#include <cspecs/cspec.h>

context (test_de_alumnos) {
  
  describe("Tests de Alumno") {
    Alumno * nico;
    Alumno * alumnoEstudioso;
    Alumno * alumnoHijoDelRigor;
    Alumno * alumnoCabulero;
    Parcial * parcialConLongitudPar;
    Parcial * parcialConLongitudImpar;
    Parcial * parcialConMuchasPreguntas;
    Parcial * parcialConPocasPreguntas;

    before {
      nico = Alumno_new("Nico", "Gomez", "Av. siempre viva 742", 20, 111111, estudioso);
      alumnoEstudioso = Alumno_new("Nico", "Gomez", "Av. siempre viva 742", 20, 111111, estudioso);
      alumnoHijoDelRigor = Alumno_new("Nico", "Gomez", "Av. siempre viva 742", 20, 111111, hijoDelRigor);
      alumnoCabulero = Alumno_new("Nico", "Gomez", "Av. siempre viva 742", 20, 111111, cabulero);
      parcialConLongitudPar = Parcial_new("Paradigmas de programacion", 5);
      parcialConLongitudImpar = Parcial_new("Sistemas Operativos", 8);
      parcialConMuchasPreguntas = Parcial_new("Paradigmas de programacion", 6);
      parcialConPocasPreguntas = Parcial_new("Sistemas Operativos", 4);
    } end

    after {
      FREE(nico);
      FREE(alumnoEstudioso);
      FREE(alumnoHijoDelRigor);
      FREE(alumnoCabulero);
      FREE(parcialConLongitudPar);
      FREE(parcialConLongitudImpar);
    } end

    it("nombre completo de un alumno") {
      should_string(nombreCompleto(nico)) be equal to("Gomez, Nico");
    } end

    it("una persona es mayor de edad") {
        should_bool(esMayorDeEdad(nico)) be truthy;
    } end
    
    it("una persona no es mayor de edad") {
      nico->edad = 15;
      should_bool(esMayorDeEdad(nico)) be falsey;
    } end
    
    it("una persona estudiosa siempre estudia") {
      should_bool(estudia(alumnoEstudioso, parcialConLongitudPar)) be truthy;
    } end

    it("una persona hija del rigor NO estudia si el parcial tiene pocas preguntas"){
      should_bool(estudia(alumnoHijoDelRigor, parcialConPocasPreguntas)) be falsey;
    } end
    
    it("una persona hija del rigor estudia si el parcial tiene muchas preguntas"){
      should_bool(estudia(alumnoHijoDelRigor, parcialConMuchasPreguntas)) be truthy;
    } end

    it("una persona cabulera estudia si el parcial tiene una cantidad par de preguntas"){
      should_bool(estudia(alumnoCabulero, parcialConLongitudPar)) be truthy;
    } end

    it("una persona cabulera NO estudia si el parcial tiene una cantidad impar de preguntas"){
      should_bool(estudia(alumnoCabulero, parcialConLongitudImpar)) be falsey;
    } end

  } end

}