# Explicación Línea por Línea del Código (`AppCami.cpp`)

Este documento detalla el funcionamiento de cada línea de código del archivo principal `AppCami.cpp` ubicado en `AppCami/AppCami/AppCami.cpp`.

---

## 📋 Índice del Código

1. [Bibliotecas e Importaciones (Líneas 1-8)](#1-bibliotecas-e-importaciones-líneas-1-8)
2. [Estructura Jugador (Líneas 10-17)](#2-estructura-jugador-líneas-10-17)
3. [Clase Juego: Atributos Privados (Líneas 20-30)](#3-clase-juego-atributos-privados-líneas-20-30)
4. [Clase Juego: Limpieza de Buffer (Líneas 32-38)](#4-clase-juego-limpieza-de-buffer-líneas-32-38)
5. [Clase Juego: Elección Aleatoria Computadora (Líneas 40-47)](#5-clase-juego-elección-aleatoria-computadora-líneas-40-47)
6. [Clase Juego: Determinación del Ganador (Líneas 49-69)](#6-clase-juego-determinación-del-ganador-líneas-49-69)
7. [Clase Juego: Constructor (Líneas 71-78)](#7-clase-juego-constructor-líneas-71-78)
8. [Clase Juego: Captura de Datos (Líneas 80-103)](#8-clase-juego-captura-de-datos-líneas-80-103)
9. [Clase Juego: Menú Principal (Líneas 105-151)](#9-clase-juego-menú-principal-líneas-105-151)
10. [Clase Juego: Ejecución de una Ronda (Líneas 153-211)](#10-clase-juego-ejecución-de-una-ronda-líneas-153-211)
11. [Clase Juego: Visualización de Estadísticas (Líneas 213-230)](#11-clase-juego-visualización-de-estadísticas-líneas-213-230)
12. [Clase Juego: Reinicio de Estadísticas (Líneas 232-239)](#12-clase-juego-reinicio-de-estadísticas-líneas-232-239)
13. [Clase Juego: Reglas del Juego (Líneas 241-255)](#13-clase-juego-reglas-del-juego-líneas-241-255)
14. [Función main (Líneas 257-271)](#14-función-main-líneas-257-271)

---

### 1. Bibliotecas e Importaciones (Líneas 1-8)

```cpp
1: #include <iostream>
2: #include <map>
3: #include <string>
4: #include <random>
5: #include <iomanip>
6: #include <limits>
7: 
8: using namespace std;
```

* **Línea 1**: `#include <iostream>` importa la biblioteca estándar de flujo de entrada y salida (`std::cin`, `std::cout`, etc.), permitiendo interactuar con el usuario mediante la consola.
* **Línea 2**: `#include <map>` importa el contenedor asociativo `std::map`, utilizado aquí para almacenar las estadísticas del juego (asociar texto como `"victorias"` con un número entero).
* **Línea 3**: `#include <string>` importa la clase `std::string`, necesaria para manejar textos (como el nombre del jugador).
* **Línea 4**: `#include <random>` proporciona facilidades avanzadas para generar números aleatorios (como el motor Mersenne Twister y distribuciones numéricas uniformes).
* **Línea 5**: `#include <iomanip>` importa herramientas para formatear los flujos de salida (en este caso, controlar la cantidad de decimales al mostrar la tasa de victorias).
* **Línea 6**: `#include <limits>` proporciona información sobre los límites de los tipos de datos fundamentales. Se usa aquí para limpiar el buffer de entrada de consola hasta el límite máximo de caracteres del sistema.
* **Línea 8**: `using namespace std;` permite escribir funciones y clases de la biblioteca estándar (como `cout`, `string`, `map`) sin necesidad de anteponerles el prefijo `std::`.

---

### 2. Estructura Jugador (Líneas 10-17)

```cpp
10: /**
11:  * @struct Jugador
12:  * @brief Estructura que representa los datos de un participante en el juego.
13:  */
14: struct Jugador {
15:     string nombre; /**< Nombre completo del usuario */
16:     int edad;      /**< Edad del usuario */
17: };
```

* **Líneas 10-13**: Comentarios Doxygen que documentan la estructura `Jugador`.
* **Línea 14**: `struct Jugador {` declara una estructura de datos pública llamada `Jugador`.
* **Línea 15**: `string nombre;` define el miembro `nombre` para guardar el nombre de usuario.
* **Línea 16**: `int edad;` define el miembro `edad` como un entero para guardar la edad.
* **Línea 17**: `};` finaliza la declaración de la estructura.

---

### 3. Clase Juego: Atributos Privados (Líneas 20-30)

```cpp
20: /**
21:  * @class Juego
22:  * @brief Clase principal que gestiona la logica y el flujo de las rondas.
23:  */
24: class Juego {
25: private:
26:     Jugador jugador; /**< Instancia de la estructura Jugador */
27:     map<string, int> stats = { {"victorias", 0}, {"derrotas", 0}, {"empates", 0} }; /**< Mapa para registrar el historial de partidas */
28:     string textoOpciones[3] = { "Piedra", "Papel", "Tijera" }; /**< Diccionario de etiquetas para las opciones validas */
29: 
30:     // Generador moderno de números pseudoaleatorios (Mersenne Twister)
31:     mt19937 rng;
```

* **Líneas 20-24**: Declaran el inicio de la clase principal `Juego`.
* **Línea 25**: `private:` define que los miembros que le siguen solo son accesibles desde dentro de la clase `Juego` (principio de encapsulamiento).
* **Línea 26**: `Jugador jugador;` declara una variable de tipo `Jugador` para almacenar los datos del usuario en esta partida.
* **Línea 27**: `map<string, int> stats = { {"victorias", 0}, ... };` crea e inicializa un mapa que asocia strings con enteros para contabilizar victorias, derrotas y empates, todos empezando en `0`.
* **Línea 28**: `string textoOpciones[3] = { "Piedra", "Papel", "Tijera" };` define un arreglo estático de textos que contiene los nombres legibles de las 3 opciones de juego correspondientes a los índices 0, 1 y 2.
* **Línea 31**: `mt19937 rng;` declara un generador de números aleatorios usando el algoritmo Mersenne Twister, un generador rápido y con excelentes propiedades estadísticas.

---

### 4. Clase Juego: Limpieza de Buffer (Líneas 32-38)

```cpp
32:     /**
33:      * @brief Limpia el buffer de entrada de cin para prevenir comportamientos inesperados ante entradas no válidas.
34:      */
35:     void limpiarBuffer() {
36:         cin.clear();
37:         cin.ignore(numeric_limits<streamsize>::max(), '\n');
38:     }
```

* **Línea 35**: `void limpiarBuffer() {` define un método privado que no devuelve ningún valor.
* **Línea 36**: `cin.clear();` limpia los estados de error del flujo de entrada (`std::cin`). Si el usuario ingresó letras cuando se esperaba un número, esta línea restablece el canal de entrada a su estado normal.
* **Línea 37**: `cin.ignore(numeric_limits<streamsize>::max(), '\n');` descarta todos los caracteres no procesados en el buffer de entrada de la consola hasta encontrar un salto de línea (`'\n'`). Esto evita que queden restos en el buffer que interfieran en futuras lecturas de datos.
* **Línea 38**: `}` cierra la función.

---

### 5. Clase Juego: Elección Aleatoria Computadora (Líneas 40-47)

```cpp
40:     /**
41:      * @brief Genera la elección aleatoria de la computadora.
42:      * @return int 0 para Piedra, 1 para Papel, 2 para Tijera.
43:      */
44:     int obtenerEleccionComputadora() {
45:         uniform_int_distribution<int> dist(0, 2);
46:         return dist(rng);
47:     }
```

* **Línea 44**: `int obtenerEleccionComputadora() {` declara una función privada que devuelve un entero.
* **Línea 45**: `uniform_int_distribution<int> dist(0, 2);` define una distribución uniforme entera que asegura que los números 0, 1 y 2 tengan exactamente la misma probabilidad de ocurrir.
* **Línea 46**: `return dist(rng);` alimenta la distribución con el generador `rng` de la clase, produce el número aleatorio entre 0 y 2, y lo retorna.
* **Línea 47**: `}` cierra la función.

---

### 6. Clase Juego: Determinación del Ganador (Líneas 49-69)

```cpp
49:     /**
50:      * @brief Determina el ganador de la ronda comparando las elecciones.
51:      * @param jugadorEleccion Elección del jugador (0-2).
52:      * @param compEleccion Elección de la computadora (0-2).
53:      * @return string "jugador", "computadora" o "empate".
54:      */
55:     string determinarGanador(int jugadorEleccion, int compEleccion) {
56:         if (jugadorEleccion == compEleccion) {
57:             return "empate";
58:         }
59: 
60:         // Piedra (0) vence a Tijera (2)
61:         // Papel (1) vence a Piedra (0)
62:         // Tijera (2) vence a Papel (1)
63:         if ((jugadorEleccion == 0 && compEleccion == 2) ||
64:             (jugadorEleccion == 1 && compEleccion == 0) ||
65:             (jugadorEleccion == 2 && compEleccion == 1)) {
66:             return "jugador";
67:         }
68:         return "computadora";
69:     }
```

* **Línea 55**: `string determinarGanador(int jugadorEleccion, int compEleccion) {` declara el método que calcula el resultado de la ronda recibiendo las elecciones del usuario y la computadora.
* **Línea 56**: `if (jugadorEleccion == compEleccion) {` evalúa si ambos jugadores hicieron la misma elección.
* **Línea 57**: `return "empate";` si es verdadero, retorna la cadena `"empate"`.
* **Líneas 63-65**: `if ((jugadorEleccion == 0 && compEleccion == 2) || ...` evalúa todas las condiciones bajo las cuales gana el jugador:
  * Piedra (`0`) contra Tijera (`2`).
  * Papel (`1`) contra Piedra (`0`).
  * Tijera (`2`) contra Papel (`1`).
* **Línea 66**: `return "jugador";` si alguna condición se cumple, retorna `"jugador"`.
* **Línea 68**: `return "computadora";` si no hubo empate ni ganó el jugador, por descarte gana la computadora, por lo que retorna `"computadora"`.
* **Línea 69**: `}` cierra la función.

---

### 7. Clase Juego: Constructor (Líneas 71-78)

```cpp
71: public:
72:     /**
73:      * @brief Constructor: Inicializa el generador de números aleatorios usando un dispositivo de hardware si está disponible.
74:      */
75:     Juego() {
76:         random_device rd;
77:         rng.seed(rd());
78:     }
```

* **Línea 71**: `public:` indica que los miembros a partir de este punto pueden ser llamados por agentes externos a la clase (como la función `main`).
* **Línea 75**: `Juego() {` es el constructor por defecto de la clase. Se ejecuta automáticamente al instanciar el objeto.
* **Línea 76**: `random_device rd;` declara un generador de entropía de hardware para obtener un valor semilla verdaderamente aleatorio del sistema operativo.
* **Línea 77**: `rng.seed(rd());` usa la semilla obtenida de `rd` para inicializar el motor `rng` (`mt19937`), asegurando que las partidas no se repitan de la misma forma en cada ejecución del programa.
* **Línea 78**: `}` cierra el constructor.

---

### 8. Clase Juego: Captura de Datos (Líneas 80-103)

```cpp
80:     /**
81:      * @brief Captura la informacion inicial del jugador por consola de forma segura.
82:      */
83:     void obtenerDatos() {
84:         cout << "\n==============================================\n";
85:         cout << "||          PIEDRA, PAPEL O TIJERA          ||\n";
86:         cout << "==============================================\n";
87:         cout << "  Nombre del jugador: ";
88:         getline(cin, jugador.nombre);
89:         if (jugador.nombre.empty()) {
90:             jugador.nombre = "Jugador Anónimo";
91:         }
92: 
93:         while (true) {
94:             cout << "  Edad: ";
95:             if (cin >> jugador.edad && jugador.edad > 0) {
96:                 limpiarBuffer();
97:                 break;
98:             }
99:             else {
100:                 cout << "  [!] Por favor, ingresa una edad numérica válida.\n";
101:                 limpiarBuffer();
102:             }
103:         }
104:     }
```

* **Líneas 84-87**: Imprime en consola un encabezado estético y solicita el nombre al jugador.
* **Línea 88**: `getline(cin, jugador.nombre);` lee una línea completa de la consola (incluyendo espacios vacíos) y la asigna a la variable `nombre` de la estructura `jugador`.
* **Líneas 89-91**: Evalúa si el usuario presionó ENTER directamente dejando el nombre vacío (`empty()`); si es así, le asigna el valor genérico `"Jugador Anónimo"`.
* **Línea 93**: `while (true) {` inicia un bucle de validación infinito que solo terminará cuando se ingrese una edad correcta.
* **Línea 94**: Solicita la edad en pantalla.
* **Línea 95**: `if (cin >> jugador.edad && jugador.edad > 0) {` lee el valor numérico en `jugador.edad` y comprueba que sea un valor numérico correcto y mayor que 0.
* **Línea 96**: `limpiarBuffer();` remueve los caracteres sobrantes (como el ENTER `\n`) del flujo de entrada.
* **Línea 97**: `break;` rompe el bucle `while` al tener una entrada correcta.
* **Líneas 99-102**: `else { ... }` si el usuario no introduce un número válido o ingresa letras, imprime un mensaje de error y ejecuta `limpiarBuffer()` para recuperar el flujo de entrada e iniciar otra iteración del bucle.
* **Línea 104**: `}` cierra el método.

---

### 9. Clase Juego: Menú Principal (Líneas 105-151)

```cpp
105:     /**
106:      * @brief Muestra el menú principal y gestiona la navegación por las diferentes opciones.
107:      */
108:     void jugar() {
109:         int opcionMenu = 0;
110:         do {
...
120:             cout << "----------------------------------------------\n";
121:             cout << "  Selecciona una opción (1-5): ";
122: 
123:             if (!(cin >> opcionMenu)) {
124:                 cout << "\n  [!] Opción no válida. Por favor introduce un número.\n";
125:                 limpiarBuffer();
126:                 continue;
127:             }
128:             limpiarBuffer();
129: 
130:             switch (opcionMenu) {
131:             case 1:
132:                 jugarRonda();
133:                 break;
134:             case 2:
135:                 mostrarEstadisticas();
136:                 break;
137:             case 3:
138:                 restablecerEstadisticas();
139:                 break;
140:             case 4:
141:                 mostrarReglas();
142:                 break;
143:             case 5:
144:                 cout << "\n  ¡Gracias por jugar, " << jugador.nombre << "! ¡Hasta la próxima!\n\n";
145:                 break;
146:             default:
147:                 cout << "\n  [!] Opción fuera de rango (1-5).\n";
148:                 break;
149:             }
150:         } while (opcionMenu != 5);
151:     }
```

* **Línea 109**: `int opcionMenu = 0;` declara una variable local para guardar la opción elegida del menú.
* **Línea 110**: `do {` inicia un bucle de ejecución del menú que correrá al menos una vez y continuará iterando hasta que `opcionMenu` sea `5`.
* **Líneas 111-121**: Imprime por pantalla el menú de opciones (Jugar, Estadísticas, Restablecer, Reglas, Salir).
* **Línea 123**: `if (!(cin >> opcionMenu)) {` lee la opción ingresada. Si la lectura falla (ej. ingresa una letra), ejecuta el bloque.
* **Línea 124**: Avisa al usuario que la opción debe ser un número.
* **Línea 125**: `limpiarBuffer();` restablece y limpia el buffer de entrada erróneo.
* **Línea 126**: `continue;` interrumpe la iteración actual y regresa al inicio del menú sin evaluar el `switch`.
* **Línea 128**: `limpiarBuffer();` limpia el buffer cuando la lectura fue exitosa (removiendo el salto de línea `\n`).
* **Línea 130**: `switch (opcionMenu) {` evalúa el valor numérico ingresado:
  * **Casos 1-4**: Invocan a sus respectivos métodos del juego (`jugarRonda()`, `mostrarEstadisticas()`, `restablecerEstadisticas()`, `mostrarReglas()`) y terminan con un `break;`.
  * **Caso 5**: Imprime un saludo de despedida.
  * **Default (Líneas 146-148)**: Si la opción es numérica pero diferente de 1-5, muestra un mensaje indicando que está fuera de rango.
* **Línea 150**: `} while (opcionMenu != 5);` evalúa la condición de salida. Si la opción seleccionada no fue `5`, se reinicia el menú.
* **Línea 151**: `}` cierra el método.

---

### 10. Clase Juego: Ejecución de una Ronda (Líneas 153-211)

```cpp
153:     /**
154:      * @brief Ejecuta el flujo principal de una ronda de Piedra, Papel o Tijera.
155:      */
156:     void jugarRonda() {
157:         int eleccionJugador = -1;
...
167:         cout << "----------------------------------------------\n";
168: 
169:         while (true) {
170:             cout << "  Tu elección (1-4): ";
171:             if (cin >> eleccionJugador && eleccionJugador >= 1 && eleccionJugador <= 4) {
172:                 limpiarBuffer();
173:                 break;
174:             }
175:             else {
176:                 cout << "  [!] Entrada inválida. Elige un número del 1 al 4.\n";
177:                 limpiarBuffer();
178:             }
179:         }
180: 
181:         if (eleccionJugador == 4) {
182:             cout << "\n  Ronda cancelada.\n";
183:             return;
184:         }
185: 
186:         // Ajustamos la elección a base 0 (0: Piedra, 1: Papel, 2: Tijera)
187:         eleccionJugador--;
188: 
189:         int eleccionComp = obtenerEleccionComputadora();
...
194: 
195:         string resultado = determinarGanador(eleccionJugador, eleccionComp);
196: 
197:         if (resultado == "jugador") {
198:             cout << "  ¡Felicidades, ganaste esta ronda!\n";
199:             stats["victorias"]++;
200:         }
201:         else if (resultado == "computadora") {
202:             cout << "  La Computadora gana esta ronda. ¡Inténtalo de nuevo!\n";
203:             stats["derrotas"]++;
204:         }
205:         else {
206:             cout << "  ¡Es un empate!\n";
207:             stats["empates"]++;
208:         }
209:         cout << "==============================================\n";
210:     }
```

* **Línea 157**: `int eleccionJugador = -1;` define una variable local para registrar el movimiento del usuario.
* **Líneas 158-167**: Imprimen en consola el menú para seleccionar la jugada (Piedra, Papel, Tijera, o Cancelar).
* **Líneas 169-179**: Bucle `while (true)` que valida la entrada del usuario de manera análoga a la edad. Solo sale del bucle si el valor leído está entre 1 y 4.
* **Líneas 181-184**: Evalúa si el usuario seleccionó la opción `4` (Cancelar). De ser así, aborta la función inmediatamente con un `return;`.
* **Línea 187**: `eleccionJugador--;` resta `1` a la entrada del jugador para ajustar el rango `1-3` (ingresado por pantalla) a índices en base cero `0-2` (Piedra = 0, Papel = 1, Tijera = 2), lo cual mapea con el arreglo `textoOpciones` y el cálculo matemático.
* **Línea 189**: `int eleccionComp = obtenerEleccionComputadora();` invoca el generador pseudoaleatorio privado para obtener el movimiento de la máquina.
* **Líneas 190-193**: Muestra en pantalla de forma estética las selecciones de ambos competidores.
* **Línea 195**: `string resultado = determinarGanador(...)` ejecuta la lógica comparativa del juego y almacena el resultado (`"jugador"`, `"computadora"`, o `"empate"`).
* **Líneas 197-208**: Según el resultado:
  * Si es `"jugador"`, felicita al usuario e incrementa en `1` la clave `"victorias"` del mapa de estadísticas.
  * Si es `"computadora"`, lo notifica e incrementa `"derrotas"`.
  * Si es cualquier otra opción (empate), incrementa `"empates"`.
* **Líneas 209-210**: Imprimen la línea final estética de cierre y finalizan el método.

---

### 11. Clase Juego: Visualización de Estadísticas (Líneas 213-230)

```cpp
213:     /**
214:      * @brief Muestra las estadísticas detalladas del jugador en consola.
215:      */
216:     void mostrarEstadisticas() {
217:         int total = stats["victorias"] + stats["derrotas"] + stats["empates"];
218:         double tasaVictorias = 0.0;
219:         if (total > 0) {
220:             tasaVictorias = (double)stats["victorias"] / total * 100.0;
221:         }
...
228:         cout << "  Rendimiento: " << fixed << setprecision(1) << tasaVictorias << "%\n";
229:         cout << "==============================================\n";
230:     }
```

* **Línea 217**: `int total = ...` calcula el total de partidas jugadas sumando victorias, derrotas y empates guardados en el mapa `stats`.
* **Línea 218**: `double tasaVictorias = 0.0;` inicializa el rendimiento porcentual en `0.0`.
* **Línea 219**: `if (total > 0) {` previene un error matemático grave de **división por cero** en caso de que el usuario consulte estadísticas sin haber jugado ninguna ronda aún.
* **Línea 220**: `tasaVictorias = (double)stats["victorias"] / total * 100.0;` realiza la conversión de tipo explícita `(double)` de las victorias para efectuar una división con punto flotante, multiplicando por `100.0` para calcular el porcentaje.
* **Líneas 221-227**: Imprime en consola un desglose estético que incluye el nombre del jugador, edad, total de partidas, victorias, derrotas y empates.
* **Línea 228**: `cout << " Rendimiento: " << fixed << setprecision(1) << tasaVictorias << "%\n";` configura el formateador de salida:
  * `fixed`: Fuerza al flujo a usar formato de punto decimal fijo en lugar de notación científica.
  * `setprecision(1)`: Redondea el porcentaje a exactamente una posición decimal (por ejemplo: `66.7%`).
* **Línea 230**: `}` cierra la función.

---

### 12. Clase Juego: Reinicio de Estadísticas (Líneas 232-239)

```cpp
232:     /**
233:      * @brief Restablece el contador de estadísticas del juego.
234:      */
235:     void restablecerEstadisticas() {
236:         stats["victorias"] = 0;
237:         stats["derrotas"] = 0;
238:         stats["empates"] = 0;
239:         cout << "\n  [i] Estadísticas restablecidas con éxito.\n";
240:     }
```

* **Líneas 236-238**: Restablecen individualmente cada entrada en el mapa de estadísticas a su valor inicial de `0`.
* **Línea 239**: Notifica al usuario de la acción exitosa por pantalla.
* **Línea 240**: `}` cierra la función.

---

### 13. Clase Juego: Reglas del Juego (Líneas 241-255)

```cpp
241:     /**
242:      * @brief Imprime las reglas del juego en pantalla.
243:      */
244:     void mostrarReglas() {
245:         cout << "\n==============================================\n";
...
253:         cout << "  - Si ambos hacen la misma jugada, es EMPATE.\n";
254:         cout << "==============================================\n";
255:     }
```

* **Líneas 244-255**: Utiliza múltiples comandos `std::cout` para imprimir directamente las reglas oficiales de Piedra, Papel o Tijera en la consola de manera amigable y estructurada.

---

### 14. Función main (Líneas 257-271)

```cpp
258: int main() {
259:     // Configuración regional para caracteres en español (acentos, signos, etc.)
260:     setlocale(LC_ALL, "spanish");
261: 
262:     Juego juego;
263:     juego.obtenerDatos();
264:     juego.jugar();
265: 
266:     return 0;
267: }
```

* **Línea 258**: `int main() {` es el punto de entrada obligatorio de ejecución para cualquier aplicación de C++.
* **Línea 260**: `setlocale(LC_ALL, "spanish");` configura la localización del sistema en español. Esto es fundamental en sistemas Windows para que caracteres como la eñe (`ñ`), acentos (`á`, `é`, `í`, `ó`, `ú`) y signos especiales (`¡`, `¿`) se rendericen correctamente en la consola en lugar de mostrar caracteres extraños.
* **Línea 262**: `Juego juego;` instancia un objeto local de la clase `Juego` llamado `juego`, lo que ejecuta su constructor privado e inicializa las semillas aleatorias.
* **Línea 263**: `juego.obtenerDatos();` invoca el método que solicita el registro del nombre y edad del jugador.
* **Línea 264**: `juego.jugar();` inicia el menú de navegación del juego, dando inicio al ciclo de juego interactivo.
* **Línea 266**: `return 0;` indica al sistema operativo que el programa finalizó su ejecución de manera exitosa y sin errores.
* **Línea 267**: `}` cierra la función `main` y marca el fin del programa.
