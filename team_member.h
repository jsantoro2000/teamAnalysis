#ifndef TEAM_MEMBER_H
#define TEAM_MEMBER_H

// Define the TeamMember struct
typedef struct {
    int ID;
    char lastName[50];
    char firstName[50];
    float* memberData; // Points to an array of stats
} TeamMember;

// Function prototypes
char* loadData(int size, TeamMember theTeam[], char* name, int numStats);
char* addData(int size, TeamMember theTeam[], char* name, int numStats, int numPlayers);
void printData(int size, TeamMember theTeam[], char* fileName, int numStats, char* firstLine);

#endif
