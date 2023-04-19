# Ejercicio de modelado de Alumnos

[![C/C++ CI](https://github.com/uqbar-project/eg-alumnos-c/actions/workflows/build.yml/badge.svg)](https://github.com/uqbar-project/eg-alumnos-c/actions/workflows/build.yml)
Resolución del ejercicio de alumno en ANSI C modelando con TADs y testeado con CUnit perteneciente [al apunte](https://docs.google.com/document/d/11C2UAbP70dP7sTID-ZxJm_a-5ypKxQUEuZr6GVk5yFI/edit?usp=sharing) de modelado del paradigma funcional.

## requisitos
1. Eclipse C/C++
2. CUnit 
   
     para su instalación correr 
	```bash
	 apt-get install libcunit1 libcunit1-doc libcunit1-dev
	```
	
# Enunciado
Modelar un alumno, que define 
* un nombre, 
* la fecha de nacimiento, 
* el legajo (sin dígito verificador), 
* las materias que cursa 
* y el criterio para estudiar ante un parcial:
  * algunos son estudiosos: estudian siempre, 
  * otros son hijos del rigor: estudian si el parcial tiene más de n preguntas, 
  * y también están los cabuleros, que estudian si la materia tiene una cantidad impar de letras. 

### Requerimientos
* Modelar un parcial
* Modelar el tipo que representa el criterio de estudio.
* Modelar genéricamente un alumno.
* Representar con la abstracción que crea más conveniente al criterio estudioso, hijo del rigor y cabulero.
* Modelar a Nico, un alumno estudioso
* Hacer que Nico pase de ser estudioso a hijo del rigor (buscar una abstracción lo suficientemente genérica)
* Determinar si Nico va a estudiar para el parcial de Paradigmas

# Modelado
Si bien se implementa un recorte del enunciado, creamos un **TAD** que representa la abstracción de Alumno. El modelo en cuestión define la siguiente estructura de datos y funciones que trabajan sobre los mismos:

```C
typedef struct AlumnoType {
	char * nombre;
	char * apellido;
	char * direccion;
	int edad;
	int legajo;
	bool (*criterioEstudio)(Parcial*);
} Alumno;

char * nombreCompleto(Alumno * unAlumno);
void setCriterioDeEstudio(Alumno * unAlumno, bool (*criterioEstudio)(Parcial*));
bool esMayorDeEdad(Alumno * unAlumno);

Alumno * Alumno_new(char * nombre, char * apellido, char * direccion, int edad,
		int legajo, bool (*criterioEstudio)(Parcial *));
```

El criterio de estudio lo consideramos como una nueva abstracción que se modela en otro **TAD**, ya que si bien no tiene un estado (que modelamos con la estructura), tenemos comportamiento diferencial bien definido. 

```c
bool estudioso (Parcial *);
bool hijoDelRigor (Parcial *);
bool hijoDelRigorConMasDe (int, Parcial *);
bool cabulero (Parcial *);
```

Para verificar el funcionamiento de nuestro modelo se realizaron una serie de tests que pueden ejecutar. 

### Otro tip

En la implementación de *Alumno_new* se encuentra comentado el _malloc_ que solicita el espacio de memoria, dado que fue reemplazado por la línea siguiente que ejecuta un [macro de Ansi C](https://gcc.gnu.org/onlinedocs/cpp/Macros.html)
