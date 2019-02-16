/*
    Project by 1505080 (Abdullah Al Ishtiaq) and 1505089 (Shashata Sawmya)
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define width 60                     //width of the pipe
#define gravity -0.16               //gravity acting in the bird
#define BG_Width 1066               //width of the BACKGROUND
#define height_pipe 600             //the height of each PIPE
#define gap 130                     //gap between the upper and lower pipe
#define speed 2                     // the initial speed of the game


int flag=0;                         //flag for changing the highscore
int flag2=0;                        //flag for scoring the game
int life=3;                         //initial life of the bird


void buildblocks(double x[]);
void leftshift(double x[], double y[], int score);
void drawbird( double x, double y);
int controlScreen(int opt, int score, int col);
void startScreen();
void showHighscore();
void showCredits();
void gameOver(int score);
void moveBird(double bird[]);
int checkCollision(int x,double y,double blockX,double height, int score);
void replayGame(double ballY[], double blocks[], double background[]  );
int currentScore(int score, int  ballX, double block );
void drawLife(int life);


void buildblocks(double x[]){           //using the two pictures of the pipe in the resized condition for the game
                                        //when this function is called it build two pipes upper and down in the space of 400 gap
    int i;
    //iSetColor(255,0,0);

    for(i = 0; i < 11; i+=3){
        //iFilledRectangle(x[i], 0, x[i+1] , x[i+2]);
        //iFilledRectangle(x[i], gap+x[i+2], x[i+1], 600-gap-x[i+2]);

        drawTexture(x[i] , x[i+2]-height_pipe , pipe_Down);
        drawTexture(x[i] , x[i+2]+gap , pipe_Up);

    }

    if(x[0]<=-60){

        for(i = 0; i < 9; i++){             //this is wrapping up the pipes
            x[i] = x[i+3];
        }
        x[9] = x[6]+400;                    //the last blocks of the que is generated manually for the random generation of the blocks
        x[11] = rand()%(600-gap+10);
        flag2=0;

    }



}

void leftshift(double x[], double y[], int score){

    int i;

    if(score<10){                             //the pipes move towards the left using this functions
        for(i = 0; i < 12; i+=3){
            x[i]=x[i]-speed;

        }
        y[0]-=speed;                        //the backgrounds are moved left using this speed
        y[1]-=speed;
    }

    else if(score<20){                      //level up
        for(i = 0; i < 12; i+=3){
            x[i]=x[i]-1.5*speed;

        }
        y[0]-=1.5*speed;
        y[1]-=1.5*speed;

    }
    else {                                  //third level up
        for(i = 0; i < 12; i+=3){
            x[i]=x[i]-2*speed;

        }
        y[0]-=2*speed;
        y[1]-=2*speed;

    }




        if(y[1]<=0){                    //the background is restored
            y[0]=0;
            y[1]=BG_Width;
        }


}


void drawbird( double x, double y){              //when this function is called it draws a bird using the reference position
        drawTexture(x, y, b[0]);
        drawTexture(x-4, y+2, b[1]);
        drawTexture(x-6, y+4, b[2]);
        drawTexture(x-8, y+8, b[3]);
        drawTexture(x-10, y+10, b[4]);
        drawTexture(x-10, y+12, b[5]);
        drawTexture(x-8, y+16, b[6]);
        drawTexture(x-4, y+18, b[7]);
        drawTexture(x-2, y+20, b[8]);
        drawTexture(x+2, y+22, b[9]);

}

int controlScreen(int opt, int score, int col){     //the screens are controlled using the options and the collisions
    if(opt==0 && col==1){
        iClear();
        startScreen();
        opt=0;
	}
    else if(opt==2 && col==1){
        iClear();
        showHighscore();
        opt=2;
	}
	else if(opt==3 && col==1){
        iClear();
        showCredits();
        opt=3;
    }
	else if(opt==4 && col==1){
	    iClear();
        exit(0);
	}
	else  if(opt==5 && col==1){
        iClear();
        gameOver(score);
        opt=5;

	}

	return opt;
}


void startScreen(){                                 //this is the start screen
    //iShowBMP(0,0,"background for flappy.bmp");
    drawTexture(0,0,bGround);
    iSetColor(67,3,168);
    iText(230,500,"Flappy Bird",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(130,300,"1.Play",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(380,300,"2.Highscores",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(130,100,"3.Credits",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(380,100,"4.Exit",GLUT_BITMAP_TIMES_ROMAN_24);


}

void showHighscore(){                       //THIS FUNCTION SHOWS THE HIGHSCORE IN THE SCREEN READING IT FROM THE HIGHSCORE FILE

    int hScore[5]={},i=0,x=100,y=500;

    char txt[10];


    drawTexture(0,0,bGround);
    FILE * fp;

    fp = fopen("flappy_highScore", "rb");
     if (fp == NULL) {
        printf("File doesn't exists!\n");
        fp = fopen("flappy_highScore", "wb");
    }

    while(fread(&hScore[i], sizeof(int), 1, fp) == 1) {
        i++;
    }
    fclose(fp);

    iSetColor(67,3,168);
    iText(100,550,"Highscores:",GLUT_BITMAP_HELVETICA_18);

    for(i=0;i<5;i++){

        itoa(i+1,txt,10);
        txt[1]='.';
        txt[2]=0;
        iText(x,y,txt,GLUT_BITMAP_HELVETICA_18);
        x+=25;

        itoa(hScore[i],txt,10);
        iText(x,y,txt,GLUT_BITMAP_HELVETICA_18);
        x=100;
        y-=50;
    }

    iText(130,100,"1.Play",GLUT_BITMAP_HELVETICA_18);
    iText(250,100,"3.Credits",GLUT_BITMAP_HELVETICA_18);
    iText(380,100,"4.Exit",GLUT_BITMAP_HELVETICA_18);
}

void showCredits(){                         //THIS FUNCTION SHOWS THE CREDITS PART, THE GAMEMAKERS AND THE ADVISOR
    drawTexture(0,0,bGround);
    iSetColor(67,3,168);
    iText(50,500,"1. Abdullah Al Ishtiaq",GLUT_BITMAP_HELVETICA_18);
    iText(50,480,"    1505080",GLUT_BITMAP_HELVETICA_18);
    iText(50,450,"2. Shashata Sawmya",GLUT_BITMAP_HELVETICA_18);
    iText(50,430,"    1505089",GLUT_BITMAP_HELVETICA_18);

    iText(280,500,"Advisor:     ",GLUT_BITMAP_HELVETICA_18);
    iText(280,480,"Siddharta Shankor Roy     ",GLUT_BITMAP_HELVETICA_18);
    iText(280,460,"Lecturer     ",GLUT_BITMAP_HELVETICA_18);
    iText(280,440,"Computer Science And Engineering,",GLUT_BITMAP_HELVETICA_18);
    iText(280,420,"BUET",GLUT_BITMAP_HELVETICA_18);


    //printf("credits\n");

    iText(130,100,"1.Play",GLUT_BITMAP_HELVETICA_18);
    iText(230,100,"2.Highscore",GLUT_BITMAP_HELVETICA_18);
    iText(380,100,"4.Exit",GLUT_BITMAP_HELVETICA_18);
}


void gameOver(int score){
    int hScore[5]={},i;
    char str[10];

    drawTexture(0,0,bGround);

    itoa(score,str,10);
    iSetColor(67,3,168);
    iText(230,500,"Game Over",GLUT_BITMAP_HELVETICA_18);
    iText(230,400,"Your Score:",GLUT_BITMAP_HELVETICA_18);
    iText(350,400,str,GLUT_BITMAP_HELVETICA_18);

    FILE * fp;

    fp = fopen("flappy_highScore", "rb");
     if (fp == NULL) {
        printf("File doesn't exists!\n");
        fp = fopen("flappy_highScore", "wb");
    }

    while(fread(&hScore[i], sizeof(int), 1, fp) == 1) {
        i++;
    }
    fclose(fp);

    itoa(hScore[0],str,10);
    iText(230,350,"Highscore:",GLUT_BITMAP_HELVETICA_18);
    iText(350,350,str,GLUT_BITMAP_HELVETICA_18);

    if(score>=hScore[0]){
            iText(222,300,"New Highscore!!!",GLUT_BITMAP_HELVETICA_18);
    }

    if(flag==0){                                            //CHANGING THE HIGHSCORE(IF REQUIRED)

       if(score>hScore[0]){
            hScore[4]=hScore[3];
            hScore[3]=hScore[2];
            hScore[2]=hScore[1];
            hScore[1]=hScore[0];
            hScore[0]=score;
        }
        else if (score>hScore[1]){
            hScore[4]=hScore[3];
            hScore[3]=hScore[2];
            hScore[2]=hScore[1];
            hScore[1]=score;
        }
        else if (score>hScore[2]){
            hScore[4]=hScore[3];
            hScore[3]=hScore[2];
            hScore[2]=score;
        }
        else if (score>hScore[3]){
            hScore[4]=hScore[3];
            hScore[3]=score;
        }
        else if (score>hScore[4]){
            hScore[4]=score;
        }

         fp = fopen("flappy_highScore", "wb");
         for (i = 0; i < 5; i++) {
            fwrite(&hScore[i], sizeof(int), 1, fp);
        }
         fclose(fp);

         flag=1;
    }


    iText(130,200,"1.Play Again",GLUT_BITMAP_HELVETICA_18);
    iText(380,200,"2.Highscores",GLUT_BITMAP_HELVETICA_18);
    iText(130,100,"3.Credits",GLUT_BITMAP_HELVETICA_18);
    iText(380,100,"4.Exit",GLUT_BITMAP_HELVETICA_18);

}


void moveBird(double bird[], int score){            //the bird is moved downward using the gravity
    if(score<10 ){
        bird[1]+=gravity;
        bird[0]+=bird[1];

    }
    else if(score<20){                              //LEVEL UP 1.5 TIMES GRAVITY
        bird[1]+=1.5*gravity;
        bird[0]+=bird[1];
    }
    else {
        bird[1]+=2*gravity;                        //THIRD LEVEL UP 2 TIMES GRAVITY
        bird[0]+=bird[1];
    }


}

int checkCollision(int x, double y, double blockX, double height, int score){

    if(y+24>=600||y<=0){                                    //THIS FUNCTION CHECKS THE COLLISION WHETHER THE BIRD IS ALIVE OR NOT

        return 1;
    }
    else if( (x+24>=blockX && x-10<=blockX+width) && (y<=height || y+24>=height+gap ) ){

        return 1;

    }
    else
        return 0;

}

void replayGame( double ballY[], double blocks[], double background[] ){

    ballY[0]=300;                                           //THIS FUNCTION IS FOR RESTORING THE INITIAL VALUES OF THE PARAMETERS
    ballY[1]=0;
    blocks[0]=800;
    blocks[1]=width;
    blocks[3]=1200;
    blocks[4]=width;
    blocks[6]=1600;
    blocks[7]=width;
    blocks[9]=2000;
    blocks[10]=width;
    background[0]=0;
    background[1]=BG_Width;
    flag=0;
    flag2=0;
    life=3;
    srand(time(NULL));

}


int currentScore(int score, int  ballX, double block ){
    if ((ballX-10)>=block && flag2 == 0){

        score++;
        PlaySound("sfx_point.wav", NULL, SND_ASYNC);
        flag2=1;
        //printf("\a");
    }

    return score;
}


void drawLife(int life){
    if (life==3){
        drawbird(468 ,560 );

    }
    if( life>=2){
        drawbird(512 ,560 );

    }

    if(life>=1){
        drawbird(556 ,560 );

    }

}

