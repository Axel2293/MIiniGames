#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>

// Structs BLACKJACK
typedef struct deck{
  int cards[21];
}deck;

// GENERAL struct for the leaderboard
typedef struct player{
  char name[15];
  int wins;
}player;

typedef struct table_lb{
  player player[100];
  int free_indx;
  int found_indx;
}table_lb;

// GATO
int verify_win(char board[3][3], char a);
void print_gato(char board[3][3] , char[]);

// BLACKJACK
int hit();
void print_deck(deck);
int chek_21(deck);

// PONG
#define VERTICAL 18
#define HORIZONTAL 80

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


// Returns the index of the user in the struct or -1 if its not found
// Search with recursivity
int search_user(table_lb game_lb, char search[], int actual_pos)
{
  if(actual_pos < game_lb.free_indx){
    if (strcmp(game_lb.player[actual_pos].name,search) == 0)
      {
        return actual_pos;
      }
    else
    {
      search_user(game_lb, search, actual_pos+1);
    }
  }
  else
  {
    return -1;
  }

}

// ======GATO===================
table_lb gato(table_lb game_lb)
{    
  srand(time(NULL));
  int x=0,y=0;
  char board[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
  system("cls");
  printf("\t ______     ______     ______   ______   \n"  
        "\t/\\  ___\\   /\\  __ \\   /\\__  _\\ /\\  __ \\   \n"
        "\t\\ \\ \\__ \\  \\ \\  __ \\  \\/_/\\ \\/ \\ \\ \\/\\ \\  \n"
        "\t \\ \\_____\\  \\ \\_\\ \\_\\    \\ \\_\\  \\ \\_____\\ \n"
        "\t  \\/_____/   \\/_/\\/_/     \\/_/   \\/_____/ \n");
  printf("\nBienvenido al minijuego de gato\nQuieres registrarte (1) o buscar tu nombre (2) ?\n....... ");
  int res=0;
  scanf("%d",&res);
  getchar();

  // Search for player name so player can save their wins or register for new players
  switch(res){
    case 1:
      printf("Introduce tu nombre para comenzar:\n");
      scanf("%s", game_lb.player[game_lb.free_indx].name);
      getchar();
      game_lb.found_indx=game_lb.free_indx;
      game_lb.free_indx++;
      break;
    case 2:
      printf("Introduce tu nombre para buscar: \n");
      char search[15];
      scanf("%s", search);
      getchar();
      int indx=search_user(game_lb,search,0);
      if(indx!=-1){
        game_lb.found_indx=indx;
        break;
      }
      else
      {
        printf("\nNombre no encontrado\n");
      }
    default:
      printf("Introduce tu nombre para comenzar:\n");
      scanf("%s", game_lb.player[game_lb.free_indx].name);
      getchar();
      game_lb.found_indx=game_lb.free_indx;
      game_lb.free_indx++;
      break;

  } 
    
  int win_usr=0, win_machine=0;

  while(win_usr==0 && win_machine==0)
  {
    
    print_gato(board, game_lb.player[game_lb.found_indx].name);
    // PLAYERS TURN
    while(verify_win(board, 'X')==0)
    {
      printf("Introduce la posición de tu X (x,y):\n");
      scanf("%d %d",&x,&y);
      getchar();
      if (board[x][y]!='X' && board[x][y]!='O')
      {
        board[x][y]='X';
        print_gato(board, game_lb.player[game_lb.found_indx].name);
        break;
      }
      else
      {
        printf("\nEl lugar seleccionado ya está ocupado, vuelve a introducir la posición...\n");
      }
    }
    if(verify_win(board,'X')==1)
    {
      printf("Ganador: %s\n",game_lb.player[game_lb.found_indx].name);
      printf("Presiona ENTER para continuar...\n");
      getchar();
      win_usr=1;
      game_lb.player[game_lb.found_indx].wins++;
      break;
    }


    // IA TURN
    while(verify_win(board, 'O')==0)
    {
      printf("Turno de la máquina\n");
      x = rand() % 3;
      y = rand() % 3;
      if (board[x][y]!='X' && board[x][y]!='O')
      {
        board[x][y]='O';
        print_gato(board, game_lb.player[game_lb.found_indx].name);
        break;
      }
      else
      {
        continue;
      }

    }
    if(verify_win(board,'O')==1)
    {
      printf("Perdiste contra la IA :c\n");
      printf("Presiona ENTER para continuar...\n");
      getchar();
      win_machine = 1;
      break;
    }
  }
  return game_lb;
}

void print_gato(char board [3][3], char name[])
{
  system("cls");
  printf("\nJugador : %s\n", name); 
  printf("----------------------\n");
  for (int i=0; i<3; i++)
  {
    for(int j=0; j<3; j++)
    {
      printf("|  %c   ",board[i][j]);
      if(j==2) printf("|\n");
    }
    printf("----------------------\n");
  }
}

int verify_win(char board[3][3], char a)
{
  // DIAGONAL
  // printf("\nCOMP = %d\n", board[0][0]==a);
  if(board[0][0]==a && board[1][1]==a && board[2][2]==a)
  {
    return 1;
  }
  else if(board[0][2]==a && board[1][1]==a && board[2][0]==a)
  {
    return 1;
  }

  // VERTICAL HORIZONTAL
  for(int i=0; i<3; i++)
  {
    // horizontal
    if(board[i][0] == a && board[i][1] == a && board[i][2] == a)
    {
      return 1;
    }
    // Vertical
    else if(board[0][i] == a && board[1][i] == a && board[2][i] == a)
    {
      return 1;
    }
  }
  return 0;
}


// =========== Ahorcado ================
table_lb Ahorcado(table_lb ahorcado_lb)
{
  system("cls");
  srand(time(NULL));
  printf("\t     ,---,        ,---,                                                                     \n"
         "\t    '  .' \\     ,--.' |                                                 ,---,              \n"
         "\t   /  ;    '.   |  |  :       ,---.    __  ,-.                        ,---.'|   ,---.       \n"
         "\t  :  :       \\  :  :  :      '   ,'\\ ,' ,'/ /|                        |   | :  '   ,'\\   \n"
         "\t  :  |   /\\   \\ :  |  |,--. /   /   |'  | |' | ,---.     ,--.--.      |   | | /   /   |   \n"
         "\t  |  :  ' ;.   :|  :  '   |.   ; ,. :|  |   ,'/     \\   /       \\   ,--.__| |.   ; ,. :   \n"
         "\t  |  |  ;/  \\   \\  |   /' :'   | |: :'  :  / /    / '  .--.  .-. | /   ,'   |'   | |: :   \n"
         "\t  '  :  | \\  \\ ,'  :  | | |'   | .; :|  | ' .    ' /    \\__\\/: . ..   '  /  |'   | .; : \n"
         "\t  |  |  '  '--' |  |  ' | :|   :    |;  : | '   ; :__   ,\" .--.; |'   ; |:  ||   :    |     \n"
         "\t  |  :  :       |  :  :_:,\' \\   \\  / |  , ; '   | '\\.'| /  /  ,.  ||   | '/  ' \\   \\  /    \n"
         "\t  |  | ,'       |  | ,'      `----'   ---'  |   :    :;  :   .'   \\   :    :|  `----'       \n"
         "\t  `--''         `--''                        \\   \\  / |  ,     .-./\\   \\  /             \n"
         "\t                                              `----'   `--`---'     `----'              \n"
         "\t                                                                          \n");
  printf("¡Bienvenido al juego del Ahorcado!\n");
  printf("Quieres registrarte (1) o buscar tu nombre (2) ?\n....... ");
  int res=0;
  scanf("%d",&res);
  getchar();

  // Search for player name so player can save their wins or register for new players
  switch(res){
    case 1:
      printf("Introduce tu nombre para comenzar:\n");
      scanf("%s", ahorcado_lb.player[ahorcado_lb.free_indx].name);
      getchar();
      ahorcado_lb.found_indx=ahorcado_lb.free_indx;
      ahorcado_lb.free_indx++;
      break;
    case 2:
      printf("Introduce tu nombre para buscar: \n");
      char search[15];
      scanf("%s", search);
      getchar();
      int indx=search_user(ahorcado_lb,search,0);
      if(indx!=-1){
        ahorcado_lb.found_indx=indx;
        break;
      }
      else
      {
        printf("\nNombre no encontrado\n");
      }
    default:
      printf("Introduce tu nombre para comenzar:\n");
      scanf("%s", ahorcado_lb.player[ahorcado_lb.free_indx].name);
      getchar();
      ahorcado_lb.found_indx=ahorcado_lb.free_indx;
      ahorcado_lb.free_indx++;
      break;

  } 
  
  int wins = 0;
  char decision = 's';
  char palabras[20][30] = {"gato", "perro", "capuchino", "perezoso", "alberca", "otorrinolaringologo", "aeronautica", "ornitorrinco", "historiador", "onomatopeya","jugador","volcan","orquidea","ultrasonido","reinona","cerveza","lampara","zapateado","proyecto","dulceria"};
  printf("Presiona para comenzar...\n");
  getchar();
  int counter = 1;
  int error = 0;
  int x = rand() % 19;
  char palabra_elegida[30];
  char palabra_jugador[30];
  char letra;
  strcpy(palabra_elegida,palabras[x]);
  palabra_jugador[strlen(palabra_elegida)]='\0';
  system("cls");
  //Ciclo de juego
  while(1)
  { 
    if(strcmp(palabra_elegida,palabra_jugador) == 0)
    {
      printf("\n!Felicidades, adivinaste la palabra!\n\n");
      ahorcado_lb.player[ahorcado_lb.found_indx].wins++;
      printf("Partidas ganadas: %d\n",ahorcado_lb.player[ahorcado_lb.found_indx].wins);
      printf("Si quieres jugar de nuevo, escribe s, si no, escribe n\n");
      scanf("%c",&decision);
      getchar();
      if(decision=='s')
      {
        x = rand() % 19;
        strcpy(palabra_elegida,palabras[x]);
        palabra_jugador[strlen(palabra_elegida)]='\0';
        error=0;
        continue;
      }
      if(decision=='n')
      {
        break;
      }
    }
    else if(error == 5)
    {
      printf("Perdiste :( no adivinaste la palabra\n");
      printf("Si quieres jugar de nuevo, escribe s, si no, escribe n\n");
      scanf("%c",&decision);
      getchar();
      if(decision=='s')
      {
        x = rand() % 19;
        strcpy(palabra_elegida,palabras[x]);
        palabra_jugador[strlen(palabra_elegida)]='\0';
        error=0;
        continue;
      }
      if(decision=='n')
      {
        break;
      }
    }      
    printf("\n");
    printf("Numero de letras: %lu\n",strlen(palabra_elegida));
    printf("Errores: %d\n",error);
    printf("Introduce una letra: ");
    scanf("%c",&letra);
    getchar();
    for(int i = 0; i < strlen(palabra_elegida); i++)
    {
      if(palabra_elegida[i]==letra)
      {
        palabra_jugador[i] = letra;
        counter = 1;
      }
      else if(counter == strlen(palabra_elegida))
      {
        counter = 1;
        error++;
      }
      else
      {
        counter++;
      }
    }
    counter = 1;
    system("cls");
    for(int i = 0; i < strlen(palabra_elegida); i++)
    {
      if(palabra_elegida[i]==palabra_jugador[i])
      {
        printf("%c ",palabra_jugador[i]);
      }
      else
      {
        printf("_ ");
      }
    }
  
  }
  error=0;
  return ahorcado_lb;

}


// ===========BLACK JACK================
table_lb blackjack(table_lb bj_lb)
{
  system("cls");
  printf("\t     /$$$$$$$  /$$                     /$$                /$$$$$                     /$$\n"
           "\t   | $$__  $$| $$                    | $$               |__  $$                    | $$\n"      
           "\t   | $$  \\ $$| $$  /$$$$$$   /$$$$$$$| $$   /$$            | $$  /$$$$$$   /$$$$$$$| $$   /$$\n"
           "\t   | $$$$$$$ | $$ |____  $$ /$$_____/| $$  /$$/            | $$ |____  $$ /$$_____/| $$  /$$/\n"
           "\t   | $$__  $$| $$  /$$$$$$$| $$      | $$$$$$/        /$$  | $$  /$$$$$$$| $$      | $$$$$$/ \n"
           "\t   | $$  \\ $$| $$ /$$__  $$| $$      | $$_  $$       | $$  | $$ /$$__  $$| $$      | $$_  $$ \n"
           "\t   | $$$$$$$/| $$|  $$$$$$$|  $$$$$$$| $$ \\  $$      |  $$$$$$/|  $$$$$$$|  $$$$$$$| $$ \\  $$\n"
           "\t   |_______/ |__/ \\_______/ \\_______/|__/  \\__/       \\______/  \\_______/ \\_______/|__/  \\__/ \n");
  
  printf("\nQuieres registrarte (1) o buscar tu nombre (2) ?\n....... ");
  int res=0;
  scanf("%d",&res);
  getchar();

  // Search for player name so player can save their wins or register for new players
  switch(res){
    case 1:
      printf("Introduce tu nombre para comenzar:\n");
      scanf("%s", bj_lb.player[bj_lb.free_indx].name);
      getchar();
      bj_lb.found_indx=bj_lb.free_indx;
      bj_lb.free_indx++;
      break;
    case 2:
      printf("Introduce tu nombre para buscar: \n");
      char search[15];
      scanf("%s", search);
      getchar();
      int indx=search_user(bj_lb,search,0);
      if(indx!=-1){
        bj_lb.found_indx=indx;
        break;
      }
      else
      {
        printf("\nNombre no encontrado\n");
      }
    //  In case name is not found or user inputs other  option 
    default:
      printf("Introduce tu nombre para comenzar:\n");
      scanf("%s", bj_lb.player[bj_lb.free_indx].name);
      getchar();
      bj_lb.found_indx=bj_lb.free_indx;
      bj_lb.free_indx++;
      break;
  }

  // DECKS
  deck player_deck;
  deck IA_deck;
  
  // Iniitalize free card spaces with 0
  for(int i=0; i<21; i++)
  {
    player_deck.cards[i]=0;
    IA_deck.cards[i]=0;
  }
  
  // Seed the rand to obtain always random numbers
  srand(time(NULL));

  // First given card
  player_deck.cards[0]=hit();
  IA_deck.cards[0]=hit();
  
  // MAIN GAME
  int h_p=1,  free_plyr=1, free_ia=1;
  while(1)
  {
    system("cls");
    
    while(h_p==1)
    {
      printf("Dealer DECK:\n");
      print_deck(IA_deck);
      printf("\n\nTu turno: \n");
      print_deck(player_deck);
      printf("\tHIT -- 1\n\tSTAND -- 2\n...");
      scanf("%d",&h_p);
      getchar();
      if(h_p==2)
      {
          break;
      }
      else
      {
          player_deck.cards[free_plyr]=hit();
          free_plyr++;
          system("cls");
          printf("Dealer DECK:\n");
          print_deck(IA_deck);
          printf("\n\nTu turno: \n");
          print_deck(player_deck);
        
          // CHECK IF PLAYER LOST OR WON WITH A BLACKJACK
          if(chek_21(player_deck)>21 )
          {
            printf("\nJugador pierde\nPresiona enter para continuar......");
            getchar();
            break;
          }
          else if(chek_21(player_deck)==21)
          {
            bj_lb.player[bj_lb.found_indx].wins++;
            printf("\nJugador GANA  -BLACKJACK-\nPresiona enter para continuar......");
            getchar();
            break;
          }
          system("cls");
      }
    }
    // CHECK IF PLAYER LOST OR WON WITH A BLACKJACK THIS PART JUST BREAKS THE MAINLOOP
    if(chek_21(player_deck)>21 )
    {
      break;
    }
    else if(chek_21(player_deck)==21)
    {
      break;
    }
  
    // RULE Dealer hits if sum of cards is less than 17 greater he stands
    while(chek_21(IA_deck)<17)
    {
      IA_deck.cards[free_ia]=hit();
      free_ia++;

      system("cls");
      printf("\n========================Tus cartas============================\n"); 
      print_deck(player_deck);        
      printf("\n========================DEALER============================\n");   
      print_deck(IA_deck);
      
      sleep(3);
    }


    // Check if IA passed 21
    if (chek_21(IA_deck)>21)
    {
      bj_lb.player[bj_lb.found_indx].wins++;
      printf("\nJugador ! GANA \nPresiona enter para continuar......");
      getchar();
      break;
    }
    // Check if IA got 21
    else if(chek_21(IA_deck)==21)
    {
      printf("\nJugador pierde\nPresiona enter para continuar......");
      getchar();
      break;
    }

    // Check if player has more points than the AI
    else if(chek_21(IA_deck)<chek_21(player_deck))
    {
      bj_lb.player[bj_lb.found_indx].wins++;
      printf("\nJugador ! GANA \nPresiona enter para continuar......");
      getchar();
      break;
    }

     // Check if IA has more points than the player
    else if(chek_21(IA_deck)>chek_21(player_deck))
    {
      printf("\nJugador pierde\nPresiona enter para continuar......");
      getchar();
      break;
    }
 
  }
  
  // Return the leader board with the players result
  return bj_lb;
}
// Returns a value from 1 to 11
int hit()
{
  int card=rand() % 11;
  if (card==0)
  {
    return 11;
  }
  else
  {
    return card;
  }
}

// Prints the user deck
void print_deck(deck player)
{
  printf("\t==========================================\n\tDECK \t[ ");
  for(int j=0; j<21; j++)
  {
    if(player.cards[j]!=0){
      printf(" -%d- ", player.cards[j]);
    }
  }
  printf("  ]\n\t==========================================\n");
  printf("Suma de cartas ==[%d]==\n", chek_21(player));
  
}

int chek_21(deck player)
{
  int sum=0;
  for(int i=0; i<21; i++)
  {
    if(player.cards[i]!=0)
    {
      sum+=player.cards[i];
    }
  }
  return sum;
}

#define VERTICAL 18
#define HORIZONTAL 80

table_lb pong(table_lb game_lb){
    // Ball movement directions and palets of player and IA
    int ballx, bally, inijug, finjug, iniia, finia;

    int modx, mody, modia;
    // The game board
    char field [VERTICAL][HORIZONTAL];
    system("cls");

    printf("                   _____                   _______                   _____                    _____                  \n"
        "\t          /\\    \\                 /::\\    \\                 /\\    \\                  /\\    \\         \n"
        "\t         /::\\    \\               /::::\\    \\               /::\\____\\                /::\\    \\        \n"
        "\t        /::::\\    \\             /::::::\\    \\             /::::|   |               /::::\\    \\         \n"
        "\t       /::::::\\    \\           /::::::::\\    \\           /:::::|   |              /::::::\\    \\        \n"
        "\t      /:::/\\:::\\    \\         /:::/~~\\:::\\    \\         /::::::|   |             /:::/\\:::\\    \\     \n"
        "\t     /:::/__\\:::\\    \\       /:::/    \\:::\\    \\       /:::/|::|   |            /:::/  \\:::\\    \\    \n"
        "\t    /::::\\   \\:::\\    \\     /:::/    / \\:::\\    \\     /:::/ |::|   |           /:::/    \\:::\\    \\   \n"
        "\t   /::::::\\   \\:::\\    \\   /:::/____/   \\:::\\____\\   /:::/  |::|   | _____    /:::/    / \\:::\\    \\  \n"
        "\t  /:::/\\:::\\   \\:::\\____\\ |:::|    |     |:::|    | /:::/   |::|   |/\\    \\  /:::/    /   \\:::\\ ___\\ \n"
        "\t /:::/  \\:::\\   \\:::|    ||:::|____|     |:::|    |/:: /    |::|   /::\\____\\/:::/____/  ___\\:::|    |\n"
        "\t \\::/    \\:::\\  /:::|____| \\:::\\    \\   /:::/    / \\::/    /|::|  /:::/    /\\:::\\    \\ /\\  /:::|____|\n"
        "\t  \\/_____/\\:::\\/:::/    /   \\:::\\    \\ /:::/    /   \\/____/ |::| /:::/    /  \\:::\\    /::\\ \\::/    / \n"
        "\t           \\::::::/    /     \\:::\\    /:::/    /            |::|/:::/    /    \\:::\\   \\:::\\ \\/____/  \n"
        "\t            \\::::/    /       \\:::\\__/:::/    /             |::::::/    /      \\:::\\   \\:::\\____\\    \n"
        "\t             \\::/____/         \\::::::::/    /              |:::::/    /        \\:::\\  /:::/    /    \n"
        "\t                                \\::::::/    /               |::::/    /          \\:::\\/:::/    /     \n"
        "\t                                 \\::::/    /                /:::/    /            \\::::::/    /      \n"
        "\t                                  \\::/____/                /:::/    /              \\::::/    /       \n"
        "\t                                                           \\::/    /                \\::/____/        \n"
        "\t                                                            \\/____/                                 \n\n");
  printf("\nBienvenido al minijuego PONG \nQuieres registrarte (1) o buscar tu nombre (2) ?\n....... ");
  int res=0;
  scanf("%d",&res);
  getchar();

  // Search for player name so player can save their wins or register for new players
  switch(res){
    case 1:
      printf("Introduce tu nombre para comenzar:\n");
      scanf("%s", game_lb.player[game_lb.free_indx].name);
      getchar();
      game_lb.found_indx=game_lb.free_indx;
      game_lb.free_indx++;
      break;
    case 2:
      printf("Introduce tu nombre para buscar: \n");
      char search[15];
      scanf("%s", search);
      getchar();
      int indx=search_user(game_lb,search,0);
      if(indx!=-1){
        game_lb.found_indx=indx;
        break;
      }
      else
      {
        printf("\nNombre no encontrado\n");
      }
    default:
      printf("Introduce tu nombre para comenzar:\n");
      scanf("%s", game_lb.player[game_lb.free_indx].name);
      getchar();
      game_lb.found_indx=game_lb.free_indx;
      game_lb.free_indx++;
      break;

  } 


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

    // Dificultades, cada una cuenta con diferentes configuraciones
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
    game_lb=pong_loop(field, ballx, bally, inijug, finjug, iniia, finia, modx, mody, modia, key, game_lb);
    

    return game_lb;
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
// Esta funcion imprime el tablero o campo de juego
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
table_lb pong_loop(char field[VERTICAL][HORIZONTAL], int ballx,int bally, int inijug, int finjug, int iniia, int finia, int modx, int mody, int modia, char dif, table_lb game_lb){
    int score_player=0, score_ia=0;
    do{
        draw(field, score_player, score_ia);
        input(field, &ballx, &bally, &inijug, &finjug, &iniia, &finia, &modx, &mody, &modia, &score_player, &score_ia, dif);
        update(field, ballx, bally, inijug, finjug, iniia, finia);
        // usleep(10000);

    }while (score_player <10 && score_ia<10);
    if (score_player==10){
        game_lb.player[game_lb.found_indx].wins++;
        printf("\nPlayer WINS!!!\nEnter to continue...");
        getchar();
    }
    else if(score_ia==10){
        printf("\nIA WINS!!!\nEnter to continue...");
        getchar();
    }

  return game_lb;
}
void draw(char field[VERTICAL][HORIZONTAL], int score_player, int score_ia){
    system("cls");
    print_pong(field, score_player, score_ia);
}

// Give all variables by reference, ant not by value so we can directly modify them POINTERS :0
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
