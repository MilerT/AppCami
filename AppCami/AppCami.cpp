#include <iostream>
#include <map>
#include <string>
#include <random>
#include <iomanip>
#include <limits>

using namespace std;

/**
 * @struct Jugador
 * @brief Estructura que representa los datos de un participante en el juego.
 */
struct Jugador {
    string nombre; /**< Nombre completo del usuario */
    int edad;      /**< Edad del usuario */
};

/**
 * @class Juego
 * @brief Clase principal que gestiona la logica y el flujo de las rondas.
 */
class Juego {
private:
    Jugador jugador; /**< Instancia de la estructura Jugador */
    map<string, int> stats = { {"victorias", 0}, {"derrotas", 0}, {"empates", 0} }; /**< Mapa para registrar el historial de partidas */
    string textoOpciones[3] = { "Piedra", "Papel", "Tijera" }; /**< Diccionario de etiquetas para las opciones validas */

    // Generador moderno de números pseudoaleatorios (Mersenne Twister)
    mt19937 rng;

    /**
     * @brief Limpia el buffer de entrada de cin para prevenir comportamientos inesperados ante entradas no válidas.
     */
    void limpiarBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    /**
     * @brief Genera la elección aleatoria de la computadora.
     * @return int 0 para Piedra, 1 para Papel, 2 para Tijera.
     */
    int obtenerEleccionComputadora() {
        uniform_int_distribution<int> dist(0, 2);
        return dist(rng);
    }

    /**
     * @brief Determina el ganador de la ronda comparando las elecciones.
     * @param jugadorEleccion Elección del jugador (0-2).
     * @param compEleccion Elección de la computadora (0-2).
     * @return string "jugador", "computadora" o "empate".
     */
    string determinarGanador(int jugadorEleccion, int compEleccion) {
        if (jugadorEleccion == compEleccion) {
            return "empate";
        }

        // Piedra (0) vence a Tijera (2)
        // Papel (1) vence a Piedra (0)
        // Tijera (2) vence a Papel (1)
        if ((jugadorEleccion == 0 && compEleccion == 2) ||
            (jugadorEleccion == 1 && compEleccion == 0) ||
            (jugadorEleccion == 2 && compEleccion == 1)) {
            return "jugador";
        }
        return "computadora";
    }

public:
    /**
     * @brief Constructor: Inicializa el generador de números aleatorios usando un dispositivo de hardware si está disponible.
     */
    Juego() {
        random_device rd;
        rng.seed(rd());
    }

    /**
     * @brief Captura la informacion inicial del jugador por consola de forma segura.
     */
    void obtenerDatos() {
        cout << "\n==============================================\n";
        cout << "||          PIEDRA, PAPEL O TIJERA          ||\n";
        cout << "==============================================\n";
        cout << "  Nombre del jugador: ";
        getline(cin, jugador.nombre);
        if (jugador.nombre.empty()) {
            jugador.nombre = "Jugador Anónimo";
        }

        while (true) {
            cout << "  Edad: ";
            if (cin >> jugador.edad && jugador.edad > 0) {
                limpiarBuffer();
                break;
            }
            else {
                cout << "  [!] Por favor, ingresa una edad numérica válida.\n";
                limpiarBuffer();
            }
        }
    }

    /**
     * @brief Muestra el menú principal y gestiona la navegación por las diferentes opciones.
     */
    void jugar() {
        int opcionMenu = 0;
        do {
            cout << "\n==============================================\n";
            cout << "||               MENÚ PRINCIPAL             ||\n";
            cout << "==============================================\n";
            cout << "  1. Jugar una ronda\n";
            cout << "  2. Ver estadísticas\n";
            cout << "  3. Restablecer estadísticas\n";
            cout << "  4. Ver reglas del juego\n";
            cout << "  5. Salir\n";
            cout << "----------------------------------------------\n";
            cout << "  Selecciona una opción (1-5): ";

            if (!(cin >> opcionMenu)) {
                cout << "\n  [!] Opción no válida. Por favor introduce un número.\n";
                limpiarBuffer();
                continue;
            }
            limpiarBuffer();

            switch (opcionMenu) {
            case 1:
                jugarRonda();
                break;
            case 2:
                mostrarEstadisticas();
                break;
            case 3:
                restablecerEstadisticas();
                break;
            case 4:
                mostrarReglas();
                break;
            case 5:
                cout << "\n  ¡Gracias por jugar, " << jugador.nombre << "! ¡Hasta la próxima!\n\n";
                break;
            default:
                cout << "\n  [!] Opción fuera de rango (1-5).\n";
                break;
            }
        } while (opcionMenu != 5);
    }

    /**
     * @brief Ejecuta el flujo principal de una ronda de Piedra, Papel o Tijera.
     */
    void jugarRonda() {
        int eleccionJugador = -1;

        cout << "\n==============================================\n";
        cout << "||             NUEVA RONDA                  ||\n";
        cout << "==============================================\n";
        cout << "  Elige tu jugada:\n";
        cout << "  1. Piedra\n";
        cout << "  2. Papel\n";
        cout << "  3. Tijera\n";
        cout << "  4. Cancelar y volver\n";
        cout << "----------------------------------------------\n";

        while (true) {
            cout << "  Tu elección (1-4): ";
            if (cin >> eleccionJugador && eleccionJugador >= 1 && eleccionJugador <= 4) {
                limpiarBuffer();
                break;
            }
            else {
                cout << "  [!] Entrada inválida. Elige un número del 1 al 4.\n";
                limpiarBuffer();
            }
        }

        if (eleccionJugador == 4) {
            cout << "\n  Ronda cancelada.\n";
            return;
        }

        // Ajustamos la elección a base 0 (0: Piedra, 1: Papel, 2: Tijera)
        eleccionJugador--;

        int eleccionComp = obtenerEleccionComputadora();

        cout << "\n----------------------------------------------\n";
        cout << "  > " << jugador.nombre << " elige: " << textoOpciones[eleccionJugador] << "\n";
        cout << "  > La Computadora elige: " << textoOpciones[eleccionComp] << "\n";
        cout << "----------------------------------------------\n";

        string resultado = determinarGanador(eleccionJugador, eleccionComp);

        if (resultado == "jugador") {
            cout << "  ¡Felicidades, ganaste esta ronda!\n";
            stats["victorias"]++;
        }
        else if (resultado == "computadora") {
            cout << "  La Computadora gana esta ronda. ¡Inténtalo de nuevo!\n";
            stats["derrotas"]++;
        }
        else {
            cout << "  ¡Es un empate!\n";
            stats["empates"]++;
        }
        cout << "==============================================\n";
    }

    /**
     * @brief Muestra las estadísticas detalladas del jugador en consola.
     */
    void mostrarEstadisticas() {
        int total = stats["victorias"] + stats["derrotas"] + stats["empates"];
        double tasaVictorias = 0.0;
        if (total > 0) {
            tasaVictorias = (double)stats["victorias"] / total * 100.0;
        }

        cout << "\n==============================================\n";
        cout << "||         ESTADÍSTICAS DE JUGADOR          ||\n";
        cout << "==============================================\n";
        cout << "  Jugador:     " << jugador.nombre << " (" << jugador.edad << " años)\n";
        cout << "  Partidas:    " << total << "\n";
        cout << "----------------------------------------------\n";
        cout << "  Victorias:   " << stats["victorias"] << "\n";
        cout << "  Derrotas:    " << stats["derrotas"] << "\n";
        cout << "  Empates:     " << stats["empates"] << "\n";
        cout << "  Rendimiento: " << fixed << setprecision(1) << tasaVictorias << "%\n";
        cout << "==============================================\n";
    }

    /**
     * @brief Restablece el contador de estadísticas del juego.
     */
    void restablecerEstadisticas() {
        stats["victorias"] = 0;
        stats["derrotas"] = 0;
        stats["empates"] = 0;
        cout << "\n  [i] Estadísticas restablecidas con éxito.\n";
    }

    /**
     * @brief Imprime las reglas del juego en pantalla.
     */
    void mostrarReglas() {
        cout << "\n==============================================\n";
        cout << "||              REGLAS DEL JUEGO            ||\n";
        cout << "==============================================\n";
        cout << "  Reglas de Piedra, Papel o Tijera:\n";
        cout << "  - La PIEDRA vence a la TIJERA (la rompe).\n";
        cout << "  - La TIJERA vence al PAPEL (lo corta).\n";
        cout << "  - El PAPEL vence a la PIEDRA (la envuelve).\n";
        cout << "  - Si ambos hacen la misma jugada, es EMPATE.\n";
        cout << "==============================================\n";
    }
};

int main() {
    // Configuración regional para caracteres en español (acentos, signos, etc.)
    setlocale(LC_ALL, "spanish");

    Juego juego;
    juego.obtenerDatos();
    juego.jugar();

    return 0;
}