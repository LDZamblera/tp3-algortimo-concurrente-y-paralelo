#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define PORT 8080
#define MAX_PLAYERS 10

typedef struct {
    int points;
    int status; // 0 = en juego, 1 = plantado, 2 = abandonó
} PlayerStatus;

void handle_player(int client_sock) {
    PlayerStatus player = {0, 0}; // Inicializa los puntos y estado del jugador
    int decision;

    while (1) {
        int card = rand() % 7 + 1; // Genera una carta aleatoria de 1 a 7 puntos
        player.points += card;
        printf("Carta enviada al jugador: %d puntos (Total: %d puntos)\n", card, player.points);
        send(client_sock, &card, sizeof(card), 0);

        // Decide si el jugador se planta o sigue jugando
        if (player.points > 7) {
            player.status = 2; // Abandona si supera 7 puntos
            printf("Jugador se pasó con %d puntos y abandona.\n", player.points);
            break;
        } else {
            decision = rand() % 2; // 0 para plantarse, 1 para pedir otra carta
            if (decision == 0) {
                player.status = 1; // Se planta
                printf("Jugador se planta con %d puntos.\n", player.points);
                break;
            } else {
                printf("Jugador pide otra carta y tiene %d puntos.\n", player.points);
            }
        }
    }

    // Envía el estado final del jugador al cliente
    send(client_sock, &player, sizeof(PlayerStatus), 0);
    close(client_sock);
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    int player_count = 0;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_sock, MAX_PLAYERS);
    srand(time(NULL));

    printf("Servidor en espera de conexiones en el puerto %d...\n", PORT);

    while ((client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size)) && player_count < MAX_PLAYERS) {
        player_count++;
        if (fork() == 0) {
            close(server_sock);
            handle_player(client_sock);
            exit(0);
        } else {
            close(client_sock);
        }
    }

    close(server_sock);
    return 0;
}
