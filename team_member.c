#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "team_member.h"

/**********************************************************
 * void normalizeLine(char* line)
 * This function deletes extra spaces in the input file so that it can be more easily parsed and read by
 * the following functions.
 * Parameters:
 * char *line points to the current line being read in the file.
 * Returns:
 * VOID
 **********************************************************/
void normalizeLine(char* line) {
    char* src = line;
    char* dest = line;
    int inSpace = 0;

    while (*src) {
        if (*src == ' ' || *src == '\t') {
            if (!inSpace) {
                *dest++ = ' ';
                inSpace = 1;
            }
        } else {
            *dest++ = *src;
            inSpace = 0;
        }
        src++;
    }
    *dest = '\0'; // Null-terminate the string
}

/**********************************************************
 * char* loadData(int size, TeamMember theTeam[], char* name, int numStats)
 * Parameters:
 * int size: The number of players, hence the size of the team.
 * TeamMember theTeam[]: The array for each team member's stats within the stucture, TeamMember
 * char* name: References the name of the file being read. In this case, the first input file.
 * int numStats: The number of stats for the sport type inputted by the user.
 * Returns:
 * char* firstline: The first line of headers in the inputfile used in the final output file.
 **********************************************************/

char* loadData(int size, TeamMember theTeam[], char* name, int numStats) {
    FILE *file = fopen(name, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    char line[1024];
    fgets(line, sizeof(line), file);  // Read header line
    char* firstLine = strdup(line);  // Save header for later use

    // Read each line of team member data
    for (int i = 0; i < size; i++) {
        fgets(line, sizeof(line), file);
        normalizeLine(line);
        sscanf(line, "%d %s %s", &theTeam[i].ID, theTeam[i].firstName, theTeam[i].lastName);

        // Allocate memory for the stats array
        theTeam[i].memberData = (float*)malloc(numStats * sizeof(float));

        // Read stats into the memberData array
        char* statsStart = line;
        //Move statsStart past the first three fields
        for(int skip = 0; skip < 3; skip++){
            statsStart = strchr(statsStart, ' ') + 1; 
        }
         

        // Parse each stat into the memberData array
        for (int j = 0; j < numStats; j++) {
            sscanf(statsStart, "%f", &theTeam[i].memberData[j]);
            statsStart = strchr(statsStart, ' ') + 1; // Advance to the next stat
        }
    }

    fclose(file);
    return firstLine;
}

/**********************************************************
 * char* addData(TeamMember theTeam[], char* name, int numStats, int numPlayers)
 * This function takes the second input file and reads it into new arrays. The old player data arrays
 * are then updated as needed.
 * Parameters:
 * 
 * TeamMember theTeam[]: The array for each team member's stats within the stucture, TeamMember
 * char* name: References the name of the file being read. In this case, the first input file.
 * int numStats: The number of stats for the sport type inputted by the user.
 * int numPlayers: The number of players in the first file. The grand total number of players on the team.
 * Returns:
 * char* name: return filename
 **********************************************************/
char* addData(int size, TeamMember theTeam[], char* name, int numStats, int numPlayers) {
    FILE *file = fopen(name, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    char line[1024];

    // Read each line of team member data
    for (int newIndexSt = numPlayers; newIndexSt < numPlayers + 19; newIndexSt++) {
        fgets(line, sizeof(line), file);
        normalizeLine(line);
        sscanf(line, "%d %s %s", &theTeam[newIndexSt].ID, theTeam[newIndexSt].firstName, theTeam[newIndexSt].lastName);

        // Allocate memory for the stats array
        theTeam[newIndexSt].memberData = (float*)malloc(numStats * sizeof(float));

        // Read stats into the memberData array
        char* statsStart = line;
        //Move statsStart past the first three fields
        for(int skip = 0; skip < 3; skip++){
            statsStart = strchr(statsStart, ' ') + 1; 
        }
         

        // Parse each stat into the memberData array
        for (int arrIndex = 0; arrIndex < numStats; arrIndex++) {
            sscanf(statsStart, "%f", &theTeam[newIndexSt].memberData[arrIndex]);
            statsStart = strchr(statsStart, ' ') + 1; // Advance to the next stat
        }
    }

    for(int oldIndexSt = 0; oldIndexSt < numPlayers; oldIndexSt++){
        for (int newIndexSt = numPlayers; newIndexSt < numPlayers * 2; newIndexSt++){
            if(theTeam[newIndexSt].ID == theTeam[oldIndexSt].ID){
                for(int arrIndex = 0; arrIndex < numStats; arrIndex++){
                    theTeam[oldIndexSt].memberData[arrIndex] += theTeam[newIndexSt].memberData[arrIndex];
                }
                break;
            }
        }

    }

    fclose(file);
    return name;
}

/**********************************************************
 * void printData(int size, TeamMember theTeam[], char* fileName, int numStats, char* firstLine)
 * This function takes the updated arrays and prints them to a formatted ouput file. The file is named
 * from the user input in the terminal.
 * Parameters:
 * int size: The total size of the team.  
 * TeamMember theTeam[]: The array for each team member's stats within the stucture, TeamMember
 * char* name: References the name of the file being read. In this case, the first input file.
 * int numStats: The number of stats for the sport type inputted by the user.
 * char* firstLine: References the stored headers from the first function
 * Returns:
 * VOID
 **********************************************************/

void printData(int size, TeamMember theTeam[], char* fileName, int numStats, char* firstLine) {
    FILE *file = fopen(fileName, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "%s", firstLine);  // Print header line

    // Print each team member data
    for (int i = 0; i < size; i++) {
        // Print ID, firstName, and lastName
        fprintf(file, "%d\t%s\t%s\t", theTeam[i].ID, theTeam[i].firstName, theTeam[i].lastName);
        
        // Print stats, avoiding a trailing tab
        for (int j = 0; j < numStats; j++) {
            // Print stats without a tab after the last stat
            fprintf(file, "%.0f", theTeam[i].memberData[j]);
            if (j < numStats - 1) {
                fprintf(file, "\t");  // Print tab after each stat except the last one
            }
        }

        // Print the newline after each team member's data
        fprintf(file, "\n");
    }

    fclose(file);
}