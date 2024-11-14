#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

typedef struct {
    int points;
    int status; // 0 = en juego, 1 = plantado, 2 = abandonó
} PlayerStatus;

int main() {
    int sock;
    struct sockaddr_in server_addr;
    int card;
    PlayerStatus player;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Conexión fallida");
        return 1;
    }

    printf("Conectado al servidor. Esperando cartas...\n");

    while (1) {
        if (recv(sock, &card, sizeof(card), 0) > 0) {
            printf("Carta recibida: %d puntos\n", card);
            player.points += card;
        }

        // Recibe el estado final del jugador del servidor
        if (recv(sock, &player, sizeof(PlayerStatus), 0) > 0) {
            if (player.status == 1) {
                printf("Jugador se planta con %d puntos.\n", player.points);
            } else if (player.status == 2) {
                printf("Jugador se pasó con %d puntos y abandona.\n", player.points);
            }
            break;
        }
    }

    close(sock);
    return 0;
}
