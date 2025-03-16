#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEAM 19 
#define MAX_NAME_LENGTH 50

void createFixture (char teams[][MAX_NAME_LENGTH] , int teamCount , FILE *output_file) {

    int totalWeeks = teamCount * 2 - 2 ; //Each team plays 2 times with 18 opponents
    int matchCount = (teamCount - 1) / 2 ; //Number of matches to be played each week

    fprintf(output_file, "Total team count: %d\n", teamCount) ;
    fprintf(output_file, "Total week count: %d\n\n", totalWeeks) ;

    for (int week = 0 ; week < totalWeeks ; week++) {

        fprintf(output_file , "Week %d:\n" , week + 1);

        int passByTeam = week % teamCount; //Each week one of teams rests
        fprintf(output_file , "Pass by team: %s\n" , teams[passByTeam]);

        for (int match = 0 ; match < matchCount ; match++) {

            int host = (week + match + 1) % teamCount ;
            int away = (week + teamCount - match - 1) % teamCount ;

            if (host == passByTeam || away == passByTeam) {

                continue ; //Pass by team doesnt participate in matches

            }

            if (week < teamCount - 1) {

                fprintf(output_file, "%s vs %s\n", teams[host], teams[away]) ;

            }
            else {

                fprintf(output_file, "%s vs %s\n", teams[away], teams[host]) ;//Since each team will meet twice, the home and away teams are swapped and written back into the fixture

            }

        }

        fprintf(output_file, "\n") ;

    }

}

int main() {

    FILE *input_file = fopen("teams.txt", "r") ;

    //Checks file
    if (input_file == NULL) {

        printf("teams.txt couldn't be opened") ;
        return 1;

    }

    char teams[MAX_TEAM][MAX_NAME_LENGTH] ;
    int teamCount = 0 ;

    //Here, the team names in teams.txt are transferred to the teams pointer.
    while (fgets(teams[teamCount], MAX_NAME_LENGTH, input_file)) {

        teams[teamCount][strcspn(teams[teamCount], "\n")] = 0 ;
        teamCount++ ;

    }

    fclose(input_file) ;

    //Checks the count
    if (teamCount != 19) {

        printf("Team count in file must be 19\n") ;
        return 1 ;

    }

    //Creates a file to save fixture
    FILE *output_file = fopen("fixture.txt", "w");

    if (output_file == NULL) {
        printf("fixture.txt couldn't be created") ;
        return 1 ;

    }

    createFixture(teams, teamCount, output_file) ;
    fclose(output_file) ;

    printf("Fixture succesfully created and saved to fixture.txt file\n") ;
    return 0 ;

}