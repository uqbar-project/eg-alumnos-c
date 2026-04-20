# Ejercicio de modelado de Alumnos

[![C/C++ CI](https://github.com/uqbar-project/eg-alumnos-c/actions/workflows/build.yml/badge.svg)](https://github.com/uqbar-project/eg-alumnos-c/actions/workflows/build.yml)

Resolución del ejercicio de alumno en ANSI C modelando con TADs y testeado con cSpec perteneciente [al apunte](https://docs.google.com/document/d/11C2UAbP70dP7sTID-ZxJm_a-5ypKxQUEuZr6GVk5yFI/edit?usp=sharing) de modelado del paradigma funcional.

## Cómo instalar

1. Un editor con buen soporte de C — recomendado: [VS Code](https://code.visualstudio.com/) con la extensión C/C++ de Microsoft.
2. [cSpec](https://docs.utnso.com.ar/guias/herramientas/cspec) para correr los tests:

    ```bash
    git clone https://github.com/mumuki/cspec.git
    cd cspec
    make
    sudo make install
    ```

3. En **Mac**, cspec usa *nested functions* + *statement expressions* (extensiones de GCC que Apple clang no soporta). Hay que tener GCC real de Homebrew:

    ```bash
    brew install gcc
    ```

    El makefile detecta automáticamente la mayor versión `gcc-N` instalada (ARM o Intel) y aborta con un mensaje si no encuentra ninguna.

## Enunciado

Modelar un alumno, que define

- un nombre, 
- la fecha de nacimiento, 
- el legajo (sin dígito verificador), 
- las materias que cursa 
- y el criterio para estudiar ante un parcial:
  - algunos son estudiosos: estudian siempre, 
  - otros son hijos del rigor: estudian si el parcial tiene más de n preguntas, 
  - y también están los cabuleros, que estudian si la materia tiene una cantidad impar de letras. 

## Requerimientos

1. Modelar un parcial
1. Modelar el tipo que representa el criterio de estudio.
1. Modelar genéricamente un alumno.
1. Representar con la abstracción que crea más conveniente al criterio estudioso, hijo del rigor y cabulero.
1. Modelar a Nico, un alumno estudioso
1. Hacer que Nico pase de ser estudioso a hijo del rigor (buscar una abstracción lo suficientemente genérica)
1. Determinar si Nico va a estudiar para el parcial de Paradigmas

Los últimos tres puntos (Nico estudioso → hijo del rigor → evaluar si estudia Paradigmas) están cubiertos por el demo ejecutable: `make run`.

## Modelado

Si bien se implementa un recorte del enunciado, creamos un **TAD** que representa la abstracción de Alumno. En nuestro diseño tomamos **la estructura de datos** y construimos sobre él

- las funciones primitivas, que están acopladas a esa estructura desde la interfaz
- y funciones de más alto nivel, que en su interfaz solo reciben el alumno y dejan los detalles internos a la implementación.

En general, podemos modelar un TAD en capas, como se muestra a continuación:

![TAD](./images/TAD.png)

Y más específicamente para un alumno:

![TAD Alumno](./images/TAD%20Alumno.png)

## Implementación

Veamos cómo el modelo en cuestión define la siguiente estructura de datos y funciones que trabajan sobre los mismos:

```C
// ***************************************************************************
// TAD Alumno - Interfaz
// ***************************************************************************

// ***************************************************************************
// estructura del Alumno
typedef struct AlumnoType {
  string nombre;
  string apellido;
  string direccion;
  int edad;
  int legajo;
  bool (*criterioEstudio)(Parcial*);
} Alumno;

// ***************************************************************************
// función constructora
Alumno * Alumno_new(string nombre, string apellido, string direccion, int edad,
    int legajo, bool (*criterioEstudio)(Parcial *));

// ***************************************************************************
// primitivas
void setCriterioDeEstudio(Alumno * unAlumno, bool (*criterioEstudio)(Parcial*));

// ***************************************************************************
// operaciones de alto nivel
string nombreCompleto(Alumno * unAlumno);
bool esMayorDeEdad(Alumno * unAlumno);
bool estudia(Alumno * unAlumno, Parcial * unParcial);
```

### Los criterios de estudio **no** son un TAD

El criterio de estudio vive en `criterio.h` / `criterio.c` como un **módulo de predicados**, no como un TAD. No define un tipo (no hay `typedef struct`) ni tiene estado propio: son simplemente funciones sobre `Parcial`.

```c
bool estudioso (Parcial *);
bool hijoDelRigor (Parcial *);
bool hijoDelRigorConMasDe (int, Parcial *);
bool cabulero (Parcial *);
```

Cada función es un *valor* asignable al puntero `criterioEstudio` del alumno, lo que permite cambiar el comportamiento en runtime. Ahí aparece el paralelo con el módulo de modelado funcional: el criterio también es un valor de primera clase que se pasa como argumento.

### Limitación: aplicación parcial en C

En funcional, si quisiéramos un hijo del rigor parametrizado por N preguntas, escribiríamos algo como:

```js
const criterio = hijoDelRigorConMasDe(7)   // currificación
alumno.criterio = criterio
```

En C esto **no se puede hacer directamente**, porque `hijoDelRigorConMasDe` tiene firma `bool(int, Parcial*)` y el puntero que guarda `Alumno` espera `bool(*)(Parcial*)`. Las firmas no coinciden.

Hay dos caminos para resolverlo:

- **Aplicación parcial en tiempo de compilación**, con una macro que genere una función especializada por cada N conocido en código. Solo sirve si el N es literal.
- **Modelar el criterio como struct con función + contexto** (una *closure* construida a mano). Permite fijar el N en runtime, y transforma al criterio en un TAD real — con tipo, constructor y operación de evaluación.

Dejamos esta variante como iteración futura: es un buen disparador para contrastar qué te da gratis el paradigma funcional y qué hay que construir a mano en C.

Para verificar el funcionamiento del modelo se incluye una suite de tests con cSpec.

## Diagrama general de la solución

Los archivos terminan conformando un módulo o componente que resuelve los requerimientos pedidos para alumno:

![Diagrama general](./images/Modulo%20Alumno.png)

En nuestro diseño podemos pensar

- que a bajo nivel, alumno, criterio de estudio y parcial son componentes de nuestro módulo Alumno
- a más alto nivel, el módulo Alumno conforma un componente en sí mismo para trabajar con otros módulos para terminar de conformar un sistema

## Creación y destrucción de alumnos

- *Alumno_new* usa el macro `NEW` definido en `commons/constructor.h`, que encapsula el `malloc(sizeof(...))`. Es un [macro de ANSI C](https://gcc.gnu.org/onlinedocs/cpp/Macros.html) que evita repetir el patrón en cada TAD.
- Lo mismo para `FREE`, simétrico con `NEW`.
- Definimos un alias de tipo `string` para `char *` en `commons/string.h`. Eso permite subir el nivel de abstracción; podríamos hacer lo mismo para los punteros a TAD (lo dejamos para otra iteración).

### Ownership y ciclo de vida de strings

Hay dos sutilezas de C que conviene hacer explícitas, porque no aparecen en el paradigma funcional (el GC te las oculta):

- **`Alumno` no es dueño de sus strings.** La estructura guarda `char *` crudos, no una copia. Si el caller libera o modifica los buffers que le pasó a `Alumno_new`, el alumno queda apuntando a memoria inválida. Para un ejercicio didáctico con literales alcanza; conviene tenerlo presente cuando los strings no vengan de literales.
- **`nombreCompleto` devuelve memoria reservada con `malloc`**, no un puntero a memoria del alumno. Quien lo llama se hace cargo del `free`. Se ve explícito en los tests:

    ```c
    string fullName = nombreCompleto(alumno);
    should_string(fullName) be equal to("Gomez, Nico");
    free(fullName);
    ```

    Usamos `free` directo (no `FREE`) porque la alocación vino de `malloc`, no de `NEW`. Mantener la simetría `malloc ↔ free` y `NEW ↔ FREE` ayuda a leer el código.

## Cómo compilar y correr

El makefile produce **dos binarios separados**:

- `eg-alumnos-c` — demo del enunciado (Nico estudiando Paradigmas).
- `eg-alumnos-c-tests` — suite de tests con cSpec.

Los tests no arrastran al `main.c`, y el demo no linkea cSpec. Cada binario hace lo suyo.

### Targets disponibles

```bash
make          # compila el demo
make run      # compila y corre el demo
make test     # compila y corre los tests
make clean    # borra artefactos de build y binarios
```

### Salida esperada del demo

```text
$ make run
Alumno: Gomez, Nico (legajo 111111)
  Mayor de edad? si
  Como estudioso, estudia para Paradigmas de programacion? si
  Como hijo del rigor, estudia para Paradigmas de programacion? no
```

(Nico deja de estudiar al pasar a hijo del rigor porque el parcial tiene 4 preguntas, por debajo del umbral de 5.)
