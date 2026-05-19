# Juego de Piedra, Papel o Tijera (C++)

Este proyecto es una implementación interactiva y moderna en consola del clásico juego **Piedra, Papel o Tijera**, programado en **C++** utilizando principios de Programación Orientada a Objetos (POO) y buenas prácticas de desarrollo.

El juego está diseñado para ejecutarse en terminales de Windows y cuenta con soporte completo para caracteres en español (acentos, eñes, etc.).

---

## 🚀 Características Principales

1. **Gestión de Jugadores**: Permite registrar el nombre y la edad del jugador con validación robusta de datos para evitar entradas inválidas.
2. **Generación Aleatoria Avanzada**: Utiliza el motor pseudoaleatorio Mersenne Twister (`std::mt19937`) junto con `std::random_device` para garantizar elecciones de la computadora verdaderamente impredecibles y distribuidas uniformemente.
3. **Control del Buffer de Entrada**: Implementa rutinas de limpieza segura del flujo `std::cin` para prevenir bucles infinitos causados por entradas erróneas (como ingresar texto en lugar de números).
4. **Sistema de Estadísticas Completo**:
   - Registro en tiempo real de **Victorias, Derrotas y Empates** usando un contenedor `std::map`.
   - Cálculo automático del **Rendimiento / Tasa de victorias** en formato porcentual.
   - Opción para restablecer las estadísticas a cero en cualquier momento.
5. **Menú de Navegación Interactivo**: Permite jugar múltiples rondas consecutivas, ver reglas, revisar estadísticas y salir del juego limpiamente.

---

## 📁 Archivos del Proyecto

* **`a.s` / `AppCami.cpp`**: Archivo fuente principal que contiene todo el código del juego. *(Nota: Aunque `a.s` posee extensión de ensamblador, contiene el código fuente puro en C++ para compatibilidad o pruebas directas).*
* **`AppCami/`**: Directorio de la solución de Visual Studio (`AppCami.slnx`) que contiene la configuración del proyecto de C++ para desarrollo en dicho entorno.
* **`Camitrabajo/`**: Solución alternativa de Visual Studio configurada para el desarrollo y depuración del proyecto.

---

## 🛠️ Estructura del Código

El código está organizado de manera modular bajo las siguientes estructuras:

### 1. Estructura `Jugador`
Define los atributos básicos del usuario:
* `std::string nombre`: Nombre del jugador (por defecto "Jugador Anónimo").
* `int edad`: Edad validada numéricamente.

### 2. Clase `Juego`
Es el núcleo del programa. Encapsula toda la lógica interna y del menú:
* **Privado**:
  * Contenedores de datos (`Jugador`, `std::map` para estadísticas, arreglo de strings con nombres de opciones).
  * `limpiarBuffer()`: Recupera la consola de ingresos de datos erróneos.
  * `obtenerEleccionComputadora()`: Genera una jugada aleatoria (0 = Piedra, 1 = Papel, 2 = Tijera).
  * `determinarGanador(...)`: Aplica la lógica del juego para decidir si el ganador es el jugador, la computadora o si es empate.
* **Público**:
  * `Juego()`: Constructor que inicializa la semilla del motor aleatorio.
  * `obtenerDatos()`: Solicita nombre y edad de forma segura.
  * `jugar()`: Controla el menú principal del sistema.
  * `jugarRonda()`: Flujo interactivo de la partida.
  * `mostrarEstadisticas()`: Imprime la tasa de victorias y los contadores en pantalla formateada.
  * `restablecerEstadisticas()`: Reinicia las estadísticas a cero.
  * `mostrarReglas()`: Muestra el instructivo básico en pantalla.

---

## 💻 Instrucciones de Compilación y Ejecución

### Requisitos Previos
Necesitarás un compilador de C++ compatible con el estándar C++11 o superior instalado en tu sistema. Se recomienda:
* **GCC / MinGW** (para terminales como CMD, PowerShell o MSYS2)
* **MSVC** (si utilizas Visual Studio)

---

### Opción A: Compilación por Consola (Recomendado)

1. Abre tu terminal (PowerShell o Símbolo del sistema) en la carpeta raíz del proyecto.
2. Compila el archivo utilizando el siguiente comando (puedes compilar `a.s` directamente como fuente C++):

   ```bash
   g++ -std=c++11 a.s -o juego.exe
   ```

   *O si prefieres compilar la versión del subdirectorio:*

   ```bash
   g++ -std=c++11 AppCami/AppCami/AppCami.cpp -o juego.exe
   ```

3. Ejecuta el archivo generado:

   ```bash
   .\juego.exe
   ```

---

### Opción B: Usando Visual Studio

1. Navega a la carpeta `AppCami` o `Camitrabajo`.
2. Haz doble clic en el archivo de solución correspondiente (`AppCami.slnx` o `Camitrabajo.slnx`).
3. Visual Studio cargará el proyecto.
4. Presiona **F5** (o haz clic en el botón *Iniciar*) para compilar y ejecutar el juego automáticamente en la consola de Visual Studio.

---

## 📜 Reglas del Juego

El juego sigue las reglas tradicionales:
* ✊ **Piedra** vence a ✌️ **Tijera** (la rompe).
* ✌️ **Tijera** vence a ✋ **Papel** (lo corta).
* ✋ **Papel** vence a ✊ **Piedra** (la envuelve).
* Si ambos realizan la misma jugada, se produce un **Empate**.
