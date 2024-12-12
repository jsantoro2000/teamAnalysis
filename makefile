all: teamData

teamData: analyze_team.o team_member.o
	gcc analyze_team.o team_member.o -o teamData

analyze_team.o: analyze_team.c team_member.h
	gcc -c analyze_team.c -o analyze_team.o

team_member.o: team_member.c team_member.h
	gcc -c team_member.c -o team_member.o

clean:
	rm -f analyze_team.o team_member.o teamData