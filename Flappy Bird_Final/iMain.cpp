/*
    Project by 1505080 (Abdullah Al Ishtiaq) and 1505089 (Shashata Sawmya)
*/
# include "iGraphics.h"
# include "FlappyBird.h"
# include <windows.h>

#define birdX 180
#define acc 6

int x = 300, y = 300, r = 20;
int opt=0,col=1,score=0;
double blocks[12]={800,width,0,1200,width,0,1600,width,0,2000,width,0};//this array is used to generate 4 blocks where the first one is the x of the ball
double background[2]={0,BG_Width};  // this array is for the background move

double birdY[2]={300,0};           //y coordinate  of the ball and its velocity


void timedControl(){                            // we are controlling the other functions time using this function
    if(opt==1 && col==0){
        leftshift(blocks,background,score);
        moveBird(birdY,  score);
        score=currentScore(score, birdX, blocks[0]+width);
    }

}

void playGame(){                // this function controls the game play calling the other functions

    if(opt==1 && col==0){

        int i;
        char scr[5];
        itoa(score,scr,10);

        iClear();
        drawTexture(background[0],0,bGround);
        drawTexture(background[1],0,bGround);

        buildblocks(blocks);

        drawbird(birdX, birdY[0]);    //the Bird is drawn using the ordinate and abscissa of the base point of the bird

        iSetColor(0,0,255);

        iText(20,560,"Score: ",GLUT_BITMAP_HELVETICA_18);
        iText(80,560,scr,GLUT_BITMAP_HELVETICA_18);
        col=checkCollision(birdX,birdY[0],blocks[0],blocks[2],score);

        drawLife(life);

        if(col==1){
            for(i=0;i<1500;i++){
                drawTexture(background[0],0,bGround);
                drawTexture(background[1],0,bGround);

                buildblocks(blocks);

                iSetColor(0,0,255);

                drawbird(birdX, birdY[0]);

                iText(20,560,"Score: ",GLUT_BITMAP_HELVETICA_18);
                iText(80,560,scr,GLUT_BITMAP_HELVETICA_18);

            }
                life--;
                if(life == 0){
                    PlaySound("sfx_hit&die.wav", NULL, SND_ASYNC);
                    opt = 5;

                }
                else{
                    col = 0;
                    PlaySound("sfx_hit.wav", NULL, SND_ASYNC);
                    for(i = 0; i < 9; i++){
                        blocks[i] = blocks[i+3];
                    }
                    blocks[9] = blocks[6]+400;
                    blocks[11] = rand()%(600-gap+10);
                    flag2=0;

                    birdY[0]=300;
                    birdY[1]=0;
                    opt = 1;

                }

            }



    }

}


void iDraw() {
    iClear();
	opt=controlScreen(opt,score,col);
	playGame();


}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	printf("x = %d, y= %d\n",mx,my);
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if(opt == 0 && col == 1){
            if(mx > 130 && mx < 190 && my > 300 && my < 318 ){  //starts the game
                opt = 1;
                col = 0;
                score=0;
                replayGame(birdY, blocks, background);

            }
          if(mx > 130 && mx < 250 && my > 100 && my < 118 ) {   //show credits
            //controlScreen(3,score,1);
            iClear();
            opt=3;
          }
          if(mx > 380 && mx < 500 && my > 300 && my < 318){     //show Highscore in start screen
            //printf("working");
            iClear();
            opt=2;
          }
          if(mx > 380 && mx < 440 && my > 100 && my < 118){     //exit the game in start screen
            //printf("w");
            iClear();
            opt=4;
          }
        }
    else if(opt==1 && col==0){
            //PlaySound("sfx_wing.wav", NULL, SND_ASYNC);
           if(score<10){                                  //for Level 1 the initial speed is 1.5 times the original speed
                birdY[1] +=acc;
                if(birdY[1]>1.5*acc){
                    birdY[1]=1.5*acc;
                }
            }
            else if(score<20){                            //for Level 2(score after 10 the initial speed is 2.25 times the original
                birdY[1] +=1.5*acc;                       //the acc of the bird is 1.5 times the acc of initial value
                if(birdY[1]>2.25*acc){
                    birdY[1]=2.25*acc;
                }
            }
            else {
                birdY[1] +=2*acc;
                if(birdY[1]>3*acc){
                    birdY[1]=3*acc;
                }
            }

        }
    else if(opt == 2 && col == 1){                             //this is changing the options in the high score screen

            if(mx > 130 && mx < 190 && my > 100 && my < 118){
                score=0;
                replayGame(birdY, blocks, background);
                col=0;
                iClear();
                opt=1;
            }
            if(mx > 250 && mx < 370 && my > 100 && my < 118){
                iClear();
                opt=3;

            }
            if(mx > 380 && mx < 440 && my > 100 && my < 118){
                iClear();
                opt=4;
            }
    }
    else if(opt == 3 && col == 1){                          //this is for changing the options in the credits screen

            if(mx > 130 && mx < 190 && my > 100 && my < 118){
                opt = 1;
                col = 0;
                score=0;
                replayGame(birdY, blocks, background);
            }
            if(mx > 250 && mx < 370 && my > 100 && my < 118){
                iClear();
                opt=2;
            }
            if(mx > 380 && mx < 440 && my > 100 && my < 118){
                iClear();
                opt=4;
            }


        }

    else if(opt == 5 && col == 1){                          //this is for changing the options in the gameover screen
       if(mx > 130 && mx < 250 && my > 200 && my < 218) {
             score=0;
             replayGame(birdY, blocks, background);
             col=0;
             iClear();
             opt=1;

        }
        if(mx > 380 && mx < 500 && my > 200 && my < 218){
             iClear();
             opt=2;
        }
        if(mx > 130 && mx < 220 && my > 100 && my < 118){
            iClear();
            opt=3;
            showCredits();
        }
        if(mx > 380 && mx < 440 && my > 100 && my < 118){
            iClear();
            opt=4;
        }

      }

    }






/*	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		x -= 10;
		y -= 10;
	}*/
}
void iMouseOver(int mx,int my){

    //px=mx;
    //qx=my;


    //printf("%d %d ",&mx,&my);

}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {             //this is for controlling the options using the keyboard
	if (key == '1' && col==1){
            score=0;
            replayGame(birdY, blocks, background);
            col=0;
            iClear();
            opt=1;
    }
    else if (key == '2' && col==1){
            iClear();
            opt=2;
    }
    else if (key == '3' && col==1){
            iClear();
            opt=3;
    }
    else if (key == '4' && col==1){
            iClear();
            opt=4;
    }

    else if (key == ' ' && col==0){
        if(score<10){
                birdY[1] +=acc;
                if(birdY[1]>1.5*acc){
                    birdY[1]=1.5*acc;
                }
            }
            else if(score<20){
                birdY[1] +=1.5*acc;
                if(birdY[1]>2.25*acc){
                    birdY[1]=2.25*acc;
                }
            }
            else {
                birdY[1] +=2*acc;
                if(birdY[1]>3*acc){
                    birdY[1]=3*acc;
                }
            }


    }
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_END) {
		exit(0);
	}
	//place your codes for other keys here
}


int main() {
	//place your own initialization codes here.
	//PlaySound("sfx_point.wav", NULL, SND_ASYNC);
	int i;
	srand(time(NULL));
	for(i = 2; i < 12; i+=3){

         blocks[i] = rand()%(600-gap+10);       // the height of the blocks is generated randomly in this loop
         printf("%lf\n",blocks[i]);
	}

	iSetTimer(15,timedControl);
	iInitialize(600, 600, "Flappy Bird");
	return 0;
}
