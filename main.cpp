#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>

#define MAX_PLAYERS 10

typedef struct {
    int points;
    int status; // 0 = en juego, 1 = plantado, 2 = abandonó
} PlayerStatus;

void deal_cards(int pipe_fd[], int player_id) {
    close(pipe_fd[0]); // Cierra la lectura
    int card = rand() % 7 + 1; // Genera una carta aleatoria de 1 a 7 puntos
    if (write(pipe_fd[1], &card, sizeof(int)) == -1) { // Manejo de errores en write
        perror("Error al enviar carta al jugador");
        exit(1);
    }
    printf("Jugador %d recibió una carta de %d puntos.\n", player_id, card);
    close(pipe_fd[1]); // Cierra la escritura después de enviar la carta
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s N (N = número de jugadores)\n", argv[0]);
        exit(1);
    }

    int N = atoi(argv[1]);
    if (N > MAX_PLAYERS) N = MAX_PLAYERS;

    srand(time(NULL)); // Inicializa la semilla para la generación aleatoria
    int pipe_fds[MAX_PLAYERS][2];      // Pipes para enviar cartas a los jugadores
    int result_pipe_fds[MAX_PLAYERS][2]; // Pipes para recibir el resultado de cada jugador
    PlayerStatus players[MAX_PLAYERS] = {{0, 0}}; // Inicializa con ceros

    for (int i = 0; i < N; i++) {
        if (pipe(pipe_fds[i]) == -1) {
            perror("Error al crear el pipe de entrada");
            exit(1);
        }
        if (pipe(result_pipe_fds[i]) == -1) {
            perror("Error al crear el pipe de salida");
            exit(1);
        }

        pid_t pid = fork();

        if (pid == -1) { // Manejo de errores en fork
            perror("Error al crear el proceso hijo");
            exit(1);
        } else if (pid == 0) { // Proceso jugador
            close(pipe_fds[i][1]); // Cierra la escritura del pipe de entrada
            close(result_pipe_fds[i][0]); // Cierra la lectura del pipe de salida

            while (1) {
                int card;
                if (read(pipe_fds[i][0], &card, sizeof(int)) == -1) { // Manejo de errores en read
                    perror("Error al recibir carta");
                    exit(1);
                }
                players[i].points += card; // Suma los puntos de la carta recibida

                // Decide si el jugador abandona, se planta o sigue en el juego
                if (players[i].points > 7) {
                    players[i].status = 2; // Abandona si tiene más de 7 puntos
                    printf("Jugador %d se pasó con %d puntos y abandona.\n", i + 1, players[i].points);
                    break;
                } else {
                    int decision = rand() % 2; // 0 para plantarse, 1 para pedir otra carta
                    if (decision == 0) {
                        players[i].status = 1; // Se planta
                        printf("Jugador %d se planta con %d puntos.\n", i + 1, players[i].points);
                        break;
                    } else {
                        printf("Jugador %d pide otra carta y tiene %d puntos.\n", i + 1, players[i].points);
                        if (write(result_pipe_fds[i][1], &players[i], sizeof(PlayerStatus)) == -1) {
                            perror("Error al enviar el estado del jugador al servidor");
                            exit(1);
                        }
                    }
                }
            }

            // Enviar el estado final al proceso principal
            if (write(result_pipe_fds[i][1], &players[i], sizeof(PlayerStatus)) == -1) {
                perror("Error al enviar el estado final del jugador");
                exit(1);
            }

            close(pipe_fds[i][0]); // Cierra la lectura del pipe de entrada
            close(result_pipe_fds[i][1]); // Cierra la escritura del pipe de salida
            exit(0);
        } else { // Proceso servidor
            deal_cards(pipe_fds[i], i + 1);
        }
    }

    // Espera a que todos los jugadores terminen y lee sus resultados
    for (int i = 0; i < N; i++) {
        wait(NULL); // Espera al proceso hijo
        close(result_pipe_fds[i][1]); // Cierra la escritura del pipe de salida en el padre
        if (read(result_pipe_fds[i][0], &players[i], sizeof(PlayerStatus)) == -1) { // Manejo de errores en read
            perror("Error al leer el estado final del jugador");
            exit(1);
        }
        close(result_pipe_fds[i][0]); // Cierra la lectura del pipe de salida
    }

    // Determinar el ganador
    int max_points = 0;
    int winner = -1;
    for (int i = 0; i < N; i++) {
        if (players[i].status == 1 && players[i].points > max_points) {
            max_points = players[i].points;
            winner = i + 1;
        }
        printf("Jugador %d - Puntos: %d, Estado: %s\n", i + 1, players[i].points,
               players[i].status == 2 ? "Abandonó" : (players[i].status == 1 ? "Plantado" : "En juego"));
    }

    if (winner != -1) {
        printf("El ganador es el Jugador %d con %d puntos.\n", winner, max_points);
    } else {
        printf("No hay ganador. Todos los jugadores abandonaron.\n");
    }

    return 0;
}
