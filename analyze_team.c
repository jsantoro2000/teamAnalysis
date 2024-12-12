#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "team_member.h"

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Missing command line arguments\n\n");
        printf("./teamData oldData.txt newData.txt outName.txt numStats numPlayers\n");
        return 1;
    }

    char *oldDataFile = argv[1];
    char *newDataFile = argv[2];
    char *outFile = argv[3];
    int numStats = atoi(argv[4]);
    int numPlayers = atoi(argv[5]);

    // Allocate memory for the team
    TeamMember theTeam[numPlayers];

    // Load old data
    char* firstLine = loadData(numPlayers, theTeam, oldDataFile, numStats);

    // Add new data
    addData(numPlayers, theTeam, newDataFile, numStats, numPlayers);

    // Print combined data to the output file
    printData(numPlayers, theTeam, outFile, numStats, firstLine);

    // Free any dynamically allocated memory
    free(firstLine);
    for (int i = 0; i < numPlayers; i++) {
        free(theTeam[i].memberData);
    }

    return 0;
}
