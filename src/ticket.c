// ticket.c - all booking / viewing / cancelling functions (TEXT mode)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ticket.h"
#include "fileops.h"
// fixed buses and their destinations
Bus buses[4] = {
    {101, "Delhi",      500},
    {102, "Jaipur",     450},
    {103, "Chandigarh", 400},
    {104, "Mumbai",     900}
};
// get next ticket ID by reading text file
int getNextTicketID(void) {
    FILE *fp = fopen(DATAFILE, "r");
    if (!fp) {
        return 1; // first ticket
    }
    Ticket t;
    int lastId = 0;
    while (fscanf(fp, "%d %d %d %49s %49s %d",
                  &t.id,
                  &t.busNo,
                  &t.seatNo,
                  t.name,
                  t.destination,
                  &t.fare) == 6) {
        lastId = t.id;
    }
    fclose(fp);
    return lastId + 1;
}
// check if seat for a bus already booked (using text file)
int seatTaken(int busNo, int seatNo) {
    FILE *fp = fopen(DATAFILE, "r");
    if (!fp) {
        return 0; // file does not exist -> no seats taken
    }
    Ticket t;
    while (fscanf(fp, "%d %d %d %49s %49s %d",
                  &t.id,
                  &t.busNo,
                  &t.seatNo,
                  t.name,
                  t.destination,
                  &t.fare) == 6) {
        if (t.busNo == busNo && t.seatNo == seatNo) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
// helper: find bus structure by bus number
static Bus *findBus(int busNo) {
    for (int i = 0; i < 4; ++i) {
        if (buses[i].busNo == busNo) {
            return &buses[i];
        }
    }
    return NULL;
}
// book a ticket
void bookTicket(void) {
    Ticket t;
    int busNo, seatNo;
    printf("\n--- Available Buses ---\n");
    for (int i = 0; i < 4; ++i) {
        printf("%d. Bus No %d -> %s (Fare: %d)\n",
               i + 1, buses[i].busNo, buses[i].destination, buses[i].fare);
    }
    printf("Enter Bus Number: ");
    if (scanf("%d", &busNo) != 1) {
        clearInput();
        printf("Invalid input.\n");
        return;
    }
    Bus *b = findBus(busNo);
    if (!b) {
        printf("Invalid bus number.\n");
        return;
    }
    printf("Enter Seat Number: ");
    if (scanf("%d", &seatNo) != 1) {
        clearInput();
        printf("Invalid input.\n");
        return;
    }
    if (seatTaken(busNo, seatNo)) {
        printf("Seat already booked.\n");
        return;
    }
    printf("Enter Passenger Name (no spaces): ");
    if (scanf("%49s", t.name) != 1) {
        clearInput();
        printf("Invalid input.\n");
        return;
    }
    t.id       = getNextTicketID();
    t.busNo    = busNo;
    t.seatNo   = seatNo;
    strcpy(t.destination, b->destination);
    t.fare     = b->fare;
    addTicketToFile(&t);
    printf("Ticket Booked! Your Ticket ID = %d\n", t.id);
}
// show all tickets
void viewAllTickets(void) {
    FILE *fp = fopen(DATAFILE, "r");
    if (!fp) {
        printf("No tickets booked yet.\n");
        return;
    }
    Ticket t;
    printf("\n--- All Tickets ---\n");
    while (fscanf(fp, "%d %d %d %49s %49s %d",
                  &t.id,
                  &t.busNo,
                  &t.seatNo,
                  t.name,
                  t.destination,
                  &t.fare) == 6) {
        printf("ID:%d  Bus:%d  Seat:%d  Name:%s  Dest:%s  Fare:%d\n",
               t.id, t.busNo, t.seatNo, t.name, t.destination, t.fare);
    }
    fclose(fp);
}
// view tickets for a particular bus number
void viewBusTickets(void) {
    int busNo;
    printf("Enter Bus Number: ");
    if (scanf("%d", &busNo) != 1) {
        clearInput();
        printf("Invalid input.\n");
        return;
    }
    FILE *fp = fopen(DATAFILE, "r");
    if (!fp) {
        printf("No tickets booked yet.\n");
        return;
    }
    Ticket t;
    int found = 0;
    printf("\n--- Tickets for Bus %d ---\n", busNo);
    while (fscanf(fp, "%d %d %d %49s %49s %d",
                  &t.id,
                  &t.busNo,
                  &t.seatNo,
                  t.name,
                  t.destination,
                  &t.fare) == 6) {
        if (t.busNo == busNo) {
            printf("ID:%d  Seat:%d  Name:%s  Dest:%s  Fare:%d\n",
                   t.id, t.seatNo, t.name, t.destination, t.fare);
            found = 1;
        }
    }
    if (!found) {
        printf("No tickets for this bus.\n");
    }
    fclose(fp);
}
// view tickets by destination
void viewByDestination(void) {
    char dest[50];
    printf("Enter Destination (no spaces): ");
    if (scanf("%49s", dest) != 1) {
        clearInput();
        printf("Invalid input.\n");
        return;
    }
    FILE *fp = fopen(DATAFILE, "r");
    if (!fp) {
        printf("No tickets booked yet.\n");
        return;
    }
    Ticket t;
    int found = 0;
    printf("\n--- Tickets going to %s ---\n", dest);
    while (fscanf(fp, "%d %d %d %49s %49s %d",
                  &t.id,
                  &t.busNo,
                  &t.seatNo,
                  t.name,
                  t.destination,
                  &t.fare) == 6) {
        if (strcmp(t.destination, dest) == 0) {
            printf("ID:%d  Bus:%d  Seat:%d  Name:%s  Fare:%d\n",
                   t.id, t.busNo, t.seatNo, t.name, t.fare);
            found = 1;
        }
    }
    if (!found) {
        printf("No tickets for this destination.\n");
    }
    fclose(fp);
}
// cancel ticket using ID
void cancelTicket(void) {
    int id;
    printf("Enter Ticket ID to Cancel: ");
    if (scanf("%d", &id) != 1) {
        clearInput();
        printf("Invalid input.\n");
        return;
    }
    int ok = removeTicketByID(id);
    if (ok) {
        printf("Ticket cancelled.\n");
    } else {
        printf("Ticket ID not found.\n");
    }
}
