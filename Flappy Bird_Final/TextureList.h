#include "texture.h"

//texture smurfTexture;
//texture character;
//texture background;

//texture pic;
texture bGround;
texture pipe_Up;
texture pipe_Down;
texture b[10];


void textureInit()
{
	//smurfTexture.Create("Nets_court_2.bmp");
	//character.Create("Flappy_Bird.bmp");
    //pic.Create("flappy-bird_design.bmp");
    bGround.Create("BG_1066.bmp");
    pipe_Up.Create("pipe up.bmp");
    pipe_Down.Create("pipe down.bmp");
    b[0].Create("1.bmp");
    b[1].Create("2.bmp");
    b[2].Create("3.bmp");
    b[3].Create("4.bmp");
    b[4].Create("5.bmp");
    b[5].Create("6.bmp");
    b[6].Create("7.bmp");
    b[7].Create("8.bmp");
    b[8].Create("9.bmp");
    b[9].Create("10.bmp");
}
