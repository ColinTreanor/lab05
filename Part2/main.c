#include <stdlib.h>
#include <stdio.h>

#define s 2
#define fg 3
#define td 6
#define tdfg 7
#define td2p 8

void score_combos(int score){
    char *scoringoptions[]= {"td+2", "td + 2fg", "td", "3fg", "s"};
    int vals[] = {8,7,6,3,2};

    for (int td2pt = 0; td2pt <= score/vals[0]; td2pt++){
        for (int td_fg = 0; td_fg <score/vals[1]; td_fg++){
            for (int t = 0; t <= score/vals[2]; t++) {
                for (int fgl = 0; fgl <= score/vals[3]; fgl++) {
                    for (int sfty = 0; sfty <= score/vals[4]; sfty++) {
                        if (t+2 * vals[0] + td_fg * vals[1] + t * vals[2] + fgl * vals[3] + sfty * vals[4] == score) {
                            printf("%d %s, %d %s, %d %s, %d %s, %d %s\n", td2p, scoringoptions[0], tdfg, scoringoptions[1], td, scoringoptions[2], fg, scoringoptions[3], sfty, scoringoptions[4]);
                        }
                    }
                }
            }
        }
    }
}

int main(){
    int sc = 2;
    printf("Enter 0 or 1 to STOP.\n");
    while (sc > 1){
        printf("Enter the NFL score: ");
        scanf("%d", &sc);

        printf("Possible scoring plays: \n");
        score_combos(sc);
        printf("\n");

    }
    return 0;
}
