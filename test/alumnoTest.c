#include "alumnoTest.h"

Alumno * nico;
Parcial * materiaConLongitudPar;
Parcial * materiaConLongitudImpar;

int inicializar() {
	nico = Alumno_new("Nico", "Gomez", "Av. siempre viva 742", 20, 111111,
			estudioso);
	materiaConLongitudPar = Parcial_new("Paradigmas de programacion", 5);
	materiaConLongitudImpar = Parcial_new("Sistemas Operativos", 8);
	return 0;
}

int limpiar() {
	FREE(nico);
	FREE(materiaConLongitudPar);
	FREE(materiaConLongitudImpar);
	return 0;
}

void test_un_campo_de_la_estructura_puede_ser_leido() {
	CU_ASSERT_STRING_EQUAL(getNombreCompleto(nico), "Gomez, Nico");
}
void test_un_campo_de_la_estructura_puede_setearse_correctamente() {
	setNombre(nico, "Pepe");
	CU_ASSERT_STRING_EQUAL(getNombre(nico), "Pepe");
}
void test_una_persona_estudiosa_siempre_estudia() {
	nico->criterioEstudio = estudioso;
	CU_ASSERT_TRUE(nico->criterioEstudio(materiaConLongitudPar));
}
void test_criterio_mator_de_edad(){
	CU_ASSERT_TRUE(esMayorDeEdad(nico));
}
void test_una_persona_hija_del_rigor_no_estudia_si_el_parcial_tiene_menos_de_5_preguntas() {
	nico->criterioEstudio = hijoDelRigor;
	materiaConLongitudPar->cantidadDePreguntas = 5;
	CU_ASSERT_FALSE(nico->criterioEstudio(materiaConLongitudPar));
}

void test_una_persona_hija_del_rigor_estudia_si_el_parcial_tiene_6_o_mas_preguntas() {
	nico->criterioEstudio = hijoDelRigor;
	materiaConLongitudPar->cantidadDePreguntas = 6;
	CU_ASSERT_TRUE(nico->criterioEstudio(materiaConLongitudPar));
}

void test_una_persona_cabulera_estudia_si_el_parcial_tiene_cantidad_de_letras_par() {
	nico->criterioEstudio = cabulero;
	CU_ASSERT_TRUE(nico->criterioEstudio(materiaConLongitudPar));
}
void test_una_persona_cabulera_no_estudia_si_el_parcial_tiene_cantidad_de_letras_impar() {
	nico->criterioEstudio = cabulero;
	CU_ASSERT_FALSE(nico->criterioEstudio(materiaConLongitudImpar));
}

void agregar_tests_persona() {

	CU_pSuite nicoConPdep = CU_add_suite("Nico Con Pdep", inicializar, limpiar);
	CU_add_test(nicoConPdep, "Acceso correcto a un parámetro de la estructura",
			test_un_campo_de_la_estructura_puede_ser_leido);
	CU_add_test(nicoConPdep, "cambio un parametro correctamente",
			test_un_campo_de_la_estructura_puede_setearse_correctamente);
	CU_add_test(nicoConPdep, "criterio de mayoría de edad",
			test_criterio_mator_de_edad);
	CU_add_test(nicoConPdep, "test_una_persona_estudiosa_siempre_estudia",
			test_una_persona_estudiosa_siempre_estudia);
	CU_add_test(nicoConPdep,
			"test_una_persona_hija_del_rigor_no_estudia_si_el_parcial_tiene_menos_de_5_preguntas",
			test_una_persona_hija_del_rigor_no_estudia_si_el_parcial_tiene_menos_de_5_preguntas);
	CU_add_test(nicoConPdep,
			"test_una_persona_hija_del_rigor_estudia_si_el_parcial_tiene_6_o_mas_preguntas",
			test_una_persona_hija_del_rigor_estudia_si_el_parcial_tiene_6_o_mas_preguntas);
	CU_add_test(nicoConPdep,
			"test_una_persona_cabulera_estudia_si_el_parcial_tiene_cantidad_de_letras_par",
			test_una_persona_cabulera_estudia_si_el_parcial_tiene_cantidad_de_letras_par);
	CU_add_test(nicoConPdep,
			"test_una_persona_cabulera_no_estudia_si_el_parcial_tiene_cantidad_de_letras_impar",
			test_una_persona_cabulera_no_estudia_si_el_parcial_tiene_cantidad_de_letras_impar);
}
