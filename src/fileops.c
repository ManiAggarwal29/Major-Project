// fileops.c - handles file reading/writing in TEXT mode
#include <stdio.h>
#include <stdlib.h>
#include "fileops.h"
// Format (one ticket per line) in tickets.txt:
// id busNo seatNo name destination fare
// Example:
// 1 101 5 Rahul Delhi 500
// append new ticket at end of text file
void addTicketToFile(const Ticket *t) {
    FILE *fp = fopen(DATAFILE, "a");   // text append mode
    if (!fp) {
        perror("Error opening ticket file");
        return;
    }
    // NOTE: name and destination should NOT contain spaces
    fprintf(fp, "%d %d %d %s %s %d\n",
            t->id,
            t->busNo,
            t->seatNo,
            t->name,
            t->destination,
            t->fare);
    fclose(fp);
}
// remove ticket using a temporary text file
int removeTicketByID(int id) {
    FILE *fp = fopen(DATAFILE, "r");
    if (!fp) {
        // file does not exist -> nothing to delete
        return 0;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        perror("Error opening temp file");
        fclose(fp);
        return 0;
    }
    Ticket t;
    int found = 0;
    // read each line in text format
    while (fscanf(fp, "%d %d %d %49s %49s %d",
                  &t.id,
                  &t.busNo,
                  &t.seatNo,
                  t.name,
                  t.destination,
                  &t.fare) == 6) {
        if (t.id == id) {
            found = 1;      // skip this ticket
        } else {
            // write back to temp file
            fprintf(temp, "%d %d %d %s %s %d\n",
                    t.id,
                    t.busNo,
                    t.seatNo,
                    t.name,
                    t.destination,
                    t.fare);
        }
    }
    fclose(fp);
    fclose(temp);
    if (found) {
        remove(DATAFILE);
        rename("temp.txt", DATAFILE);
    } else {
        remove("temp.txt");
    }
    return found;
}
// clears remaining characters from stdin when wrong input is given
void clearInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // discard
    }
}
