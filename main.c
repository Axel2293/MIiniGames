#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include <string.h>



// This is for PONG game
#define VERTICAL 18
#define HORIZONTAL 80








typedef struct user_info
{
    char name[20];

} user_info;







void print_menu();

// PONG
int pong();
void start(char[VERTICAL][HORIZONTAL], int, int, int, int, int, int);
void border_pong(char[VERTICAL][HORIZONTAL]);
void player_raquet(char [VERTICAL][HORIZONTAL], int, int);
void ia_raquet(char [VERTICAL][HORIZONTAL], int, int);
void print_pong(char [VERTICAL][HORIZONTAL], int,int);
void ball(char[VERTICAL][HORIZONTAL], int, int);
void pong_loop(char[VERTICAL][HORIZONTAL], int, int, int, int, int, int, int, int, int, char);
void draw(char [VERTICAL][HORIZONTAL], int, int);
void input(char [VERTICAL][HORIZONTAL], int *,int *, int *, int *, int *, int *, int *, int *, int *, int *, int *, char);
void update(char[VERTICAL][HORIZONTAL], int, int, int, int, int, int);
void randomx(int *);

int main(){


    print_menu();
    char choice;
    printf("\nInput your choice (ESC to exit)...  ");
    
    choice = getch();
    char qk_restart;

    switch(choice){
        case '1':
            
            while(qk_restart!=27){
                pong();
                system("cls");
                printf("Quick restart? (ESC exit).......");
                qk_restart= getch();
            }
            
            break;
        default:
            break;
    }


}

// Main menu (shows available games)
void print_menu(){
    system("cls");
    printf("\n\n\t===MINI GAMES===\n");
    printf("\n \n ---PONG--- == 1 ==\n");

}


int pong(){
    int ballx, bally, inijug, finjug, iniia, finia;

    int modx, mody, modia;

    char field [VERTICAL][HORIZONTAL];

    system("cls");
    printf("\n\n ===CONTROLLS===\n"
    "\n \tw -> UP\n\ts -> DOWN\n");
    printf("\nSelect dificulty...\n Easy      --- 1\n Normal    --- 2\n Hard      --- 3\nImposible --- 4\n\n.... ");
    char key= getch();

    // Set the seed for the random numbers
    srand(time(NULL));

    ballx=40;
    modx=-1;
    mody=-1;
    modia=-1;
    randomx(&bally);

    switch (key){
        case '1':
            inijug=8;
            finjug=14;

            iniia=8;
            finia=12;
            break;
        case '2':
            inijug=9;
            finjug=14;

            iniia=6;
            finia=14;
            break;
        case '3':
            inijug=10;
            finjug=14;

            iniia=3;
            finia=15;
            break;
        case '4':
            inijug=8;
            finjug=14;

            iniia=8;
            finia=12;
        default:
            break;
    }
    start(field, ballx, bally, inijug, finjug, iniia, finia);
    pong_loop(field, ballx, bally, inijug, finjug, iniia, finia, modx, mody, modia, key);
    

    return 0;
}

void start (char field[VERTICAL][HORIZONTAL], int ballx,int bally, int inijug, int finjug, int iniia, int finia){
    border_pong(field);
    player_raquet(field, inijug, finjug);
    ia_raquet(field, iniia, finia);
    ball(field,ballx, bally);
}
void border_pong(char field[VERTICAL][HORIZONTAL]){
    for (int i=0; i<VERTICAL; i++){
        for(int j=0; j<HORIZONTAL; j++){
            if(i==0 || i==VERTICAL-1){
                field[i][j]='#';
            }
            else if(j==0 || j==HORIZONTAL-1){
                field[i][j]='#';
            }
            else if(j==(HORIZONTAL/2)){
                field[i][j]='|';
            }
            else{
                field[i][j]=' ';
            }
        }
    }
}
void player_raquet(char field[VERTICAL][HORIZONTAL], int inijug, int finjug){
    int row=2;
    for (int i=inijug; i<finjug; i++){
        field[i][row]='|';
    }

}
void ia_raquet(char field[VERTICAL][HORIZONTAL], int iniia, int finia){
    int row=-3;
    for (int i=iniia; i<finia; i++){
        field[i+1][row]='|';
    }
}
void print_pong(char field[VERTICAL][HORIZONTAL], int score_player, int score_ia){
    printf("Player %d                                  IA %d\n",score_player,score_ia );
    for (int i=0; i<VERTICAL; i++){
        for(int j=0; j<HORIZONTAL; j++){
            printf("%c", field[i][j]);
        }
        printf("\n");
    }

}
void ball(char field[VERTICAL][HORIZONTAL], int ballx, int bally){
    field[bally][ballx]='o';
}
void pong_loop(char field[VERTICAL][HORIZONTAL], int ballx,int bally, int inijug, int finjug, int iniia, int finia, int modx, int mody, int modia, char dif){
    int score_player=0, score_ia=0;
    do{
        draw(field, score_player, score_ia);
        input(field, &ballx, &bally, &inijug, &finjug, &iniia, &finia, &modx, &mody, &modia, &score_player, &score_ia, dif);
        update(field, ballx, bally, inijug, finjug, iniia, finia);
        // usleep(10000);

    }while (score_player <10 && score_ia<10);
    if (score_player==10){
        printf("\nPlayer WINS!!!\nEnter to continue...");
        getchar();
    }
    else if(score_ia==10){
        printf("\nIA WINS!!!\nEnter to continue...");
        getchar();
    }
    
}
void draw(char field[VERTICAL][HORIZONTAL], int score_player, int score_ia){
    system("cls");
    print_pong(field, score_player, score_ia);
}
// Give all variables by reference, ant not by value so we can directly modify them
void input(char field[VERTICAL][HORIZONTAL], int *ballx,int *bally, int *inijug, int *finjug, int *iniia, int *finia, int *modx, int *mody, int *modia, int *score_player, int *score_ia, char dif){
    
    char key;

    // If ball hits the bottom we change direction on the y axis
    if (*bally==1 || *bally==VERTICAL-2){
        *mody*=-1;
    }

    // If ball hits left wall we count it as a point for the IA
    if(*ballx==1){
        *score_ia+=1;
        randomx(bally);
        *ballx=40;
    }
    // If ball hits right wall we count it as a point for the player
    if(*ballx==HORIZONTAL-2){
        *score_player+=1;
        randomx(bally);
        *ballx=40;
    }

    // If ball hits the raquet of the player we invert the x direction of the ball
    if(*ballx == 3){
        for(int i=(*inijug); i<=(*finjug); i++ ){
            if(i == (*bally)){
                *modx*=-1;
                
            }
        }
    }

    // If ball hits the raquet of the IA we invert the x direction of the ball
    if(*ballx == (HORIZONTAL-4)){
        for(int i=(*iniia); i<=(*finia); i++ ){
            if(i == (*bally)){
                *modx*=-1;
            }
        }
    }


    // Invert the direction of movement of the IA raquet once it reaches a border_pong
    if (dif!='4'){
        if(*iniia ==1 || *finia == VERTICAL-1){
            *modia*=-1;
        }
    }else{
        // Bit of more inteligence for the IA that makes the IA imposible to beat
        if(*mody==-1){
            *modia=-1;
        }
        else if(*mody==1){
            *modia=1;
        }
    }
    
    

    if (*score_ia<=10 && *score_player<=10){
    //BALL
        *ballx+=(*modx);
        *bally+=(*mody);

    //Raquet movement of IA
        if(dif=='4'){
            if (*iniia ==1 && *modia==1){
                *iniia+=(*modia);
                *finia+=(*modia);
            }
            else if(*finia ==VERTICAL-1 && *modia==-1){
                *iniia+=(*modia);
                *finia+=(*modia);
            }
            else if(*iniia !=1 && *finia != VERTICAL-1){
                *iniia+=(*modia);
                *finia+=(*modia);
            }
        }
        else{
            *iniia+=(*modia);
            *finia+=(*modia);
        }
        //
        if (kbhit()==1){
            key= getch();
            if (key=='w'){
                if(*inijug!=1){
                    *inijug-=1;
                    *finjug-=1;
                }
            }
            else if(key=='s'){
                if(*finjug!=VERTICAL-1){
                    *finjug+=1;
                    *inijug+=1;
                }
            }
        }
    }

}

void update(char field[VERTICAL][HORIZONTAL], int ballx,int bally, int inijug, int finjug, int iniia, int finia){
    border_pong(field);
    player_raquet(field, inijug, finjug);
    ia_raquet(field, iniia, finia);
    ball(field,ballx, bally);
}

void randomx( int *bally){
    int lower=3, upper=VERTICAL-3;
    *bally=(rand()%(upper - lower +1)) +lower;
}