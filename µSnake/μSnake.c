#include <stdio.h>
#include <stdlib.h>
#include <conio.h>    //kbhit() function resides here
#include <unistd.h>   //sleep() function resides here
#include <time.h>     //srand() functions resides here

void Ground();
void GenerateMusic();
void userInput();
void Movement();
void GenerateDamage();

int height = 26;
int width = 30;
int gameover;
int score;
int health = 100;
int x;
int y;
int musicX;
int musicY;
int flag;
int trapX;
int trapY;
int totalTail;
int tailX[100];
int tailY[100];


int main() {

    GenerateMusic();
    GenerateDamage();

    //runs the game while game is not ended
    while (gameover == 0) {
      Ground();
      userInput();
      Movement();
    }

    return 0;
}

//to draw the ground where the game would take place
void Ground() {

  system("cls");                            //to clear previous inputs, in linux system("clear")
  for (int i=0;i<height;i++) {
    for (int j=0;j<width;j++) {
      if (i==0 || i == height-1 || j ==0 || j == width-1) {
        printf("#");
      } else if (i == y && j == x) {
        printf("O");
      } else if (i == musicY && j == musicX) {
        printf("%c", 0xE);
      } else if (i == trapY && j == trapX) {
        printf("%c", 0x1F);
      } else {
        int draw = 0; //generates tail
        for (int k = 0; k < totalTail; k++) {
            if (tailX[k] == i && tailY[k] == j) {
                printf("o");
                draw = 1;
            }
        }
        if (draw == 0) {
            printf(" ");
        }
      }
      }
      printf("\n");
    }

  printf("Score = %d\t  Health = %d\n\n", score, health);

  printf("      W\n");
  printf("Use A S D keys to move the snake to find %c music it needs to grow, but Beware of %c traps...", 0xE, 0x1F);

}

//to generate the fruit
void GenerateMusic() {

  x = height / 2;
  y = width / 2;
  srand(time(0));
//to produce the music without intersecting the borders
label1:
  musicX = rand() % 30;
  if (musicX == 0) {
    goto label1;
  }
label2:
  musicY = rand() % 26;
  if (musicY == 0) {
    goto label2;
  }
}

void userInput() {
  //if a key has been pressed khbit returns non-zero value and otherwise it returns zero
  if (kbhit()) {
    switch(getch()) {
      case 'a':
        flag = 1;
        break;
      case 's':
        flag = 2;
        break;
      case 'd':
        flag = 3;
        break;
      case 'w':
        flag = 4;
        break;
      case 'x':
        gameover = 1;
        break;
    }
  }
}

//generate traps for the snake
void GenerateDamage() {
  srand(time(0));
label5:
  trapX = rand() % 30;
  if (trapX == 0) {
    goto label5;
  }

label6:
  trapY = rand() % 26;
  if (trapY == 0) {
    goto label6;
  }
}

void Movement() {
  //adding the tail of the snake
  int prevY = tailX[0];
  int prevX = tailY[0];
  int prev2X, prev2Y;
  tailX[0] = y;
  tailY[0] = x;
  for (int i = 1; i < totalTail; i++)
  {
      prev2Y = tailX[i];
      prev2X = tailY[i];
      tailX[i] = prevY;
      tailY[i] = prevX;
      prevX = prev2X;
      prevY = prev2Y;
  }
  sleep(0.01);            //to delay propgram execution for exact number of seconds
  switch (flag) {
    case 1:
      x--;
      break;
    case 2:
      y++;
      break;
    case 3:
      x++;
      break;
    case 4:
      y--;
      break;
  }

  //adding gameover boundaries so if the snake hits the wall game get over
  if (x < 0 || x >= width || y < 0 || y >= height) {
    gameover = 1;
  }

  //game gets over if snake collided with its tail
  for (int i = 0; i < totalTail; i++) {
      if (tailX[i] == y && tailY[i] == x) {
          gameover = 1;
      }
  }

  //generate musics after snake ate the previous one
  srand(time(0));
  if (x == musicX && y == musicY) {
  label3:
    musicX = rand() % 30;
    if (musicX == 0) {
      goto label3;
    }

  label4:
    musicY = rand() % 26;
    if (musicY == 0) {
      goto label4;
    }
    score += 5;
    totalTail++;
  }

  //generate another trap if snake got caught in first one
  if (x == trapX && y == trapY) {
  label7:
    trapX = rand() % 30;
    if (trapX == 0) {
      goto label7;
    }

  label8:
    trapY = rand() % 26;
    if (trapY == 0) {
      goto label8;
    }
    health -= 20;
  }

  //if the health gets lower than 0 game gets over
  if (health <= 0) {
    gameover = 1;
  }

}
