#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "minigames.h"


void print_menu();
void print_lb(table_lb);
table_lb sort_lb(table_lb);
table_lb add_random(table_lb);


int main()
{
  
  int first_gato=0, first_blackjack=0;
  char gamename='N';
  
  // ========= Leaderboards for games =========
  
  // ========= GATO
  table_lb game_lb;
  game_lb.free_indx=0;
      //initialize all FREE spaces
  for(int i = 0;i <= 99;i++)
  {
    strcpy(game_lb.player[i].name,"FREE");
    game_lb.player[i].wins=0;
  } 
      // Add some example data
  game_lb=add_random(game_lb);
      // Sort by wins
  game_lb=sort_lb(game_lb);
  
  // ========= BLACKJACK
  table_lb bj_lb;
  bj_lb.free_indx=0;
    //initialize all FREE spaces
  for(int i = 0;i <= 99;i++)
  {
    strcpy(bj_lb.player[i].name,"FREE");
    bj_lb.player[i].wins=0;
  } 
      // Add some example data
  bj_lb=add_random(bj_lb);
      // Sort by wins
  bj_lb=sort_lb(bj_lb);
  
  // ========= AHORCADO
  table_lb ah_lb;
  ah_lb.free_indx=0;
      //initialize all FREE spaces
  for(int i = 0;i <= 99;i++)
  {
    strcpy(ah_lb.player[i].name,"FREE");
    ah_lb.player[i].wins=0;
  } 
      // Add some example data
  ah_lb=add_random(ah_lb);
      // Sort by wins
  ah_lb=sort_lb(ah_lb);

  // =========== PONG
  table_lb pong_lb;
  pong_lb.free_indx=0;
    //initialize all FREE spaces
  for(int i = 0;i <= 99;i++)
  {
    strcpy(pong_lb.player[i].name,"FREE");
    pong_lb.player[i].wins=0;
  } 
       // Add some example data
  pong_lb=add_random(pong_lb);
      // Sort by wins
  pong_lb=sort_lb(pong_lb);

  while(1)
  {
      print_menu();
      char gamename;
      scanf("%c",&gamename);
      getchar();
      
      switch(gamename)
      {
        case 'G':
          game_lb=gato(game_lb);
          game_lb=sort_lb(game_lb);
          break;
        case 'B':
          bj_lb=blackjack(bj_lb);
          bj_lb=sort_lb(bj_lb);
          break;
        case 'A':
          ah_lb=Ahorcado(ah_lb);
          ah_lb=sort_lb(ah_lb);
          break;
        case 'P':
          pong_lb=pong(pong_lb);
          pong_lb=sort_lb(pong_lb);
          break;
        case 'L':
          print_lb(game_lb);
          break;
        case 'K':
          print_lb(bj_lb);
          break;
        case 'J':
          print_lb(ah_lb);
          break;
        case 'O':
          print_lb(pong_lb);
          break;
        case 'S':
          printf("¡Nos vemos pronto!\n");
          return 0;
          break;
        default:
          printf("Introduce un nombre válido\n");
          break;
      }
  }
}

void print_lb(table_lb game_lb)
{
  system("cls");
  if(game_lb.free_indx!=0){
    printf("Leaderboard\n===================================\nNombre         || Juegos Ganados ||\n");
    printf("-----------------------------------\n");
    for(int i=0; i<game_lb.free_indx; i++)
    {
      printf("%-15s||%16.d||\n", game_lb.player[i].name, game_lb.player[i].wins);  
    }
    printf("===================================\n");
    printf("\nPresiona enter para regresar......");
    getchar();
  }
  else
  {
    printf("\nNo hay Usuarios Registrados\n");
    printf("Presiona enter para regresar......");
    getchar();
  }
}

// SORT BY WINS
table_lb sort_lb(table_lb game_lb)
{
  
  player aux_var, aux_var1;
  
  for(int j=0; j<game_lb.free_indx-1; j++)
  {
    for (int i=0; i<(game_lb.free_indx-1); i++)
    {
      // Sort by who has the most wins
      if (game_lb.player[i].wins < game_lb.player[i+1].wins){
        aux_var=game_lb.player[i];
        aux_var1=game_lb.player[i+1];
        game_lb.player[i]=aux_var1;
        game_lb.player[i+1]=aux_var;
      }
    }
  }
  return game_lb;
}

// EXAMPLE NAMES IN LEADERBOARD
table_lb add_random(table_lb game_lb)
{
  char rand_names[3][15]={"Oscar", "Abraham", "Ramiro"};
  for(int i=0; i<3; i++)
  {
    strcpy(game_lb.player[game_lb.free_indx].name, rand_names[i]);
    game_lb.player[game_lb.free_indx].wins=i+1;
    game_lb.free_indx++;
  }
  return game_lb;
}

void print_menu(){
  system("cls");
  printf("\t.___  ___.  __  .__   __.  __       _______      ___      .___  ___.  _______     _______.    \n"
        "\t|   \\/   | |  | |  \\ |  | |  |     /  _____|    /   \\     |   \\/   | |   ____|   /       | \n"
        "\t|  \\  /  | |  | |   \\|  | |  |    |  |  __     /  ^  \\    |  \\  /  | |  |__     |   (----` \n"
        "\t|  |\\/|  | |  | |  . `  | |  |    |  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|     \\   \\   \n"
        "\t|  |  |  | |  | |  |\\   | |  |    |  |__| |  /  _____  \\  |  |  |  | |  |____.----)   |      \n"
        "\t|__|  |__| |__| |__| \\__| |__|     \\______| /__/     \\__\\ |__|  |__| |_______|_______/     \n");
  printf("\t--------------------------------\n");
  printf("!Bienvenido al arcade! Que minijuego quieres jugar?\n");
  printf("\t- Gato --> G\n\t- Blackjack --> B\n\t- Ahorcado --> A\n\t- Pong --> P\n\n\t- Gato Leaderboard --> L\n\t- Blackjack Leaderboard --> K\n\t- Ahorcado Leaderboard --> J\n\t- Pong Leaderboard --> O\n\n\t- Salir --> S\n");
}



