/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
	MOVIE *movie=(MOVIE *)malloc(sizeof(MOVIE));
	if(!movie){
		perror("Out of Memory, Aborting...");
		exit(10);
		} 
        movie->Frames=CreateImageList();
               
        return movie;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
	assert(movie);
	DeleteImageList(movie->Frames);
        free(movie);

}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{	assert(movie);
	int width,height;
        unsigned char Y,U,V;
	int C,D,E,R,G,B;
	IENTRY *e,*n;
	IMAGE *RGBimage;
	YUVIMAGE *YUVimage;
	height=MovieHeight(movie);
	width=MovieWidth(movie);
	//height=movie->Frames->First->YUVImage->H;
	//width=movie->Frames->First->YUVImage->W;

	e=movie->Frames->First;
	while(e){
	n=e->Next;
	RGBimage=CreateImage(width,height);
		
        YUVimage=e->YUVImage;
	//Get pixel from yuv and put in rgb image
	for(int x=0;x<width;x++){
		for(int y=0;y<height;y++){
			Y=GetPixelY(YUVimage,x,y);
			U=GetPixelU(YUVimage,x,y);
			V=GetPixelV(YUVimage,x,y);
			
			C = Y - 16;
			D = U - 128;
			E = V - 128;
			
			R = (( 298 * C + 409 * E + 128) >> 8);
			if(R<0){R=0;}
			if(R>255){R=255;}
			G = (( 298 * C - 100 * D - 208 * E + 128) >> 8);
			if(G<0){G=0;}
                        if(G>255){G=255;}

			B = (( 298 * C + 516 * D + 128) >> 8) ;
			if(B<0){B=0;}
                        if(B>255){B=255;}

			SetPixelR(RGBimage,x,y,R);
			SetPixelG(RGBimage,x,y,G);
			SetPixelB(RGBimage,x,y,B);	
        
      		 
        
		}
	}
	
	e->RGBImage=RGBimage;
	DeleteYUVImage(e->YUVImage);
	e->YUVImage=NULL;
	e=n;
	}
}
/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{       
	assert(movie);
	int width,height;
        unsigned char R,G,B;
        int Y,U,V;
        IENTRY *e,*n;
        IMAGE *RGBimage;
        YUVIMAGE *YUVimage;
	height=MovieHeight(movie);
	width=MovieWidth(movie);
	//height=movie->Frames->First->RGBImage->H;
        //width=movie->Frames->First->RGBImage->W;

        e=movie->Frames->First;
        while(e){
        n=e->Next;
        YUVimage=CreateYUVImage(width,height);

        RGBimage=e->RGBImage;
        for(int x=0;x<width;x++){
                for(int y=0;y<height;y++){

			R=GetPixelR(RGBimage,x,y);
                        G=GetPixelG(RGBimage,x,y);
                        B=GetPixelB(RGBimage,x,y);
			Y=((( 66*R+129*G+ 25*B+128)>>8)+ 16);
			if(Y<0){Y=0;}
			if(Y>255){Y=255;}
			U=(((-38*R-74*G+112*B+128)>>8)+128);
			if(U<0){U=0;}
			if(U>255){U=255;}
	 		V=(((112*R-94*G-18*B+128)>>8)+128); 
	                if(V<0){V=0;}
                        if(V>255){V=255;}

                        SetPixelY(YUVimage,x,y,Y);
                        SetPixelU(YUVimage,x,y,U);
                        SetPixelV(YUVimage,x,y,V);

			 }
        }

        e->YUVImage=YUVimage;
        DeleteImage(e->RGBImage);
        e->RGBImage=NULL;
        e=n;
        }

	
	
}
//get movie length
int MovieLength(const MOVIE *movie)
{	assert(movie);
	int Length;
	Length=movie->Frames->length;
	return Length;
	

}
//get movie height
int MovieHeight(const MOVIE *movie)
{
	assert(movie);
	unsigned int height;
	if(movie->Frames->First->RGBImage){
		height=movie->Frames->First->RGBImage->H;}
	else if(movie->Frames->First->YUVImage){
		height=movie->Frames->First->YUVImage->H;}
	return height;
}

//get movie width
int MovieWidth(const MOVIE *movie)
{	assert(movie);
	unsigned int width;
	if(movie->Frames->First->RGBImage){
                width=movie->Frames->First->RGBImage->W;}
        if(movie->Frames->First->YUVImage){
                width=movie->Frames->First->YUVImage->W;}
        return width;


}

/* EOF */
