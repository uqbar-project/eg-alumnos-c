/*
 ============================================================================
 Name        : main.c
 Author      : Juan
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Little example of ANSI C TAD'S
 ============================================================================
 */
#include <unistd.h>
#include "alumnoTest.h"

int main() {
   CU_initialize_registry();

   agregar_tests_persona();

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");
   CU_cleanup_registry();
   return CU_get_error();
}
