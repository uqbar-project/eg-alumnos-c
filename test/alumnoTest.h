#ifndef ALUMNOTEST_H_
#define ALUMNOTEST_H_

#include <CUnit/Basic.h>

#include "alumno.h"

int inicializar();
int limpiar();
void test_una_persona_estudiosa_siempre_estudia();
void test_una_persona_hija_del_rigor_no_estudia_si_el_parcial_tiene_menos_de_5_preguntas();
void test_una_persona_hija_del_rigor_estudia_si_el_parcial_tiene_6_o_mas_preguntas();
void test_una_persona_cabulera_estudia_si_el_parcial_tiene_cantidad_de_letras_par();
void test_una_persona_cabulera_no_estudia_si_el_parcial_tiene_cantidad_de_letras_impar();
void agregar_tests_persona();

#endif /* ALUMNOTEST_H_ */