
// BLACK JACK STRUCTS
typedef struct deck{
  int cards[21];
}deck;

// General struct for leaderboards

typedef struct player{
  char name[15];
  int wins;
}player;

typedef struct table_lb{
  player player[100];
  int free_indx;
  int found_indx;
}table_lb;

// Pong board limits
#define VERTICAL 18
#define HORIZONTAL 80

table_lb gato(table_lb);
table_lb Ahorcado(table_lb);
table_lb blackjack( table_lb);


table_lb pong(table_lb);
void start(char[VERTICAL][HORIZONTAL], int, int, int, int, int, int);
void border_pong(char[VERTICAL][HORIZONTAL]);
void player_raquet(char [VERTICAL][HORIZONTAL], int, int);
void ia_raquet(char [VERTICAL][HORIZONTAL], int, int);
void print_pong(char [VERTICAL][HORIZONTAL], int,int);
void ball(char[VERTICAL][HORIZONTAL], int, int);
table_lb pong_loop(char[VERTICAL][HORIZONTAL], int, int, int, int, int, int, int, int, int, char, table_lb);
void draw(char [VERTICAL][HORIZONTAL], int, int);
void input(char [VERTICAL][HORIZONTAL], int *,int *, int *, int *, int *, int *, int *, int *, int *, int *, int *, char);
void update(char[VERTICAL][HORIZONTAL], int, int, int, int, int, int);
void randomx(int *);