// main.c - simple menu driven program
#include <stdio.h>
#include "ticket.h"
#include "fileops.h"
int main(void) {
    int ch;
    do {
        printf("\n===== BUS TICKET BOOKING SYSTEM =====\n");
        printf("1. Book Ticket\n");
        printf("2. View All Tickets\n");
        printf("3. View Tickets of a Bus\n");
        printf("4. View by Destination\n");
        printf("5. Cancel Ticket\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &ch) != 1) {
            clearInput();
            printf("Invalid input.\n");
            ch = 0;
        }
        switch (ch) {
            case 1:
                bookTicket();
                break;
            case 2:
                viewAllTickets();
                break;
            case 3:
                viewBusTickets();
                break;
            case 4:
                viewByDestination();
                break;
            case 5:
                cancelTicket();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Wrong option!\n");
        }
    } while (ch != 6);
    return 0;
}
