#include "tests.h"
#include <stdio.h>
#include <stdbool.h>
#include <cspecs/cspec.h>

context (test_de_alumnos) {
  
  describe("Tests de Alumno") {
    Alumno * crearAlumno() {
      return Alumno_new("Nico", "Gomez", "Av. siempre viva 742", 20, 111111, estudioso);
    }

    Alumno * crearAlumnoEstudioso() {
      return Alumno_new("Nico", "Gomez", "Av. siempre viva 742", 20, 111111, estudioso);
    }

    Alumno * crearAlumnoHijoDelRigor() {
      return Alumno_new("Nico", "Gomez", "Av. siempre viva 742", 20, 111111, hijoDelRigor);
    }

    Alumno * crearAlumnoCabulero() {
      return Alumno_new("Nico", "Gomez", "Av. siempre viva 742", 20, 111111, cabulero);
    }

    Parcial * crearParcialConLongitudPar() {
      return Parcial_new("Paradigmas de programacion", 5);
    }

    Parcial * crearParcialConLongitudImpar() {
      return Parcial_new("Sistemas Operativos", 8);
    }

    Parcial * crearParcialConMuchasPreguntas() {
      return Parcial_new("Paradigmas de programacion", 6);
    }

    Parcial * crearParcialConPocasPreguntas() {
      return Parcial_new("Sistemas Operativos", 4);
    }

    it("nombre completo de un alumno") {
      // Arrange
      Alumno * alumno = crearAlumno();
      // Assert
      string fullName = nombreCompleto(alumno);
      should_string(fullName) be equal to("Gomez, Nico");
      // Liberamos espacio. nombreCompleto hace malloc, así que quien lo llama
      // se hace cargo del free. Alternativa: hooks before/after, pero cuando
      // crece el archivo es difícil controlar el juego de datos.
      free(fullName);
      FREE(alumno);
    } end

    it("una persona es mayor de edad") {
      Alumno * alumno = crearAlumno();
      should_bool(esMayorDeEdad(alumno)) be truthy;
      FREE(alumno);
    } end
    
    it("una persona no es mayor de edad") {
      Alumno * alumno = crearAlumno();
      alumno->edad = 15;
      should_bool(esMayorDeEdad(alumno)) be falsey;
      FREE(alumno);
    } end
    
    it("una persona estudiosa siempre estudia") {
      Alumno * alumnoEstudioso = crearAlumnoEstudioso();
      Parcial * parcial = crearParcialConLongitudPar();
      should_bool(estudia(alumnoEstudioso, parcial)) be truthy;
      FREE(parcial);
      FREE(alumnoEstudioso);
    } end

    it("una persona hija del rigor NO estudia si el parcial tiene pocas preguntas"){
      Alumno * alumnoHijoDelRigor = crearAlumnoHijoDelRigor();
      Parcial * parcialConPocasPreguntas = crearParcialConPocasPreguntas();
      should_bool(estudia(alumnoHijoDelRigor, parcialConPocasPreguntas)) be falsey;
      FREE(parcialConPocasPreguntas);
      FREE(alumnoHijoDelRigor);
    } end
    
    it("una persona hija del rigor estudia si el parcial tiene muchas preguntas"){
      Alumno * alumnoHijoDelRigor = crearAlumnoHijoDelRigor();
      Parcial * parcialConMuchasPreguntas = crearParcialConMuchasPreguntas();
      should_bool(estudia(alumnoHijoDelRigor, parcialConMuchasPreguntas)) be truthy;
      FREE(parcialConMuchasPreguntas);
      FREE(alumnoHijoDelRigor);
    } end

    it("una persona cabulera estudia si la materia tiene una cantidad impar de letras"){
      Alumno * alumnoCabulero = crearAlumnoCabulero();
      Parcial * parcialConLongitudImpar = crearParcialConLongitudImpar();
      should_bool(estudia(alumnoCabulero, parcialConLongitudImpar)) be truthy;
      FREE(parcialConLongitudImpar);
      FREE(alumnoCabulero);
    } end

    it("una persona cabulera NO estudia si la materia tiene una cantidad par de letras"){
      Alumno * alumnoCabulero = crearAlumnoCabulero();
      Parcial * parcialConLongitudPar = crearParcialConLongitudPar();
      should_bool(estudia(alumnoCabulero, parcialConLongitudPar)) be falsey;
      FREE(parcialConLongitudPar);
      FREE(alumnoCabulero);
    } end

  } end

}