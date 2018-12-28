/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/* Modified by Mihnea Chirila for EECS 22 Fall 2018                                                            */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"
#include "MovieIO.h"
#include "IterativeFilter.h"



void PrintUsage(char *ProgName){
	 fprintf(stderr,"Usage: %s [option...]\n" 
			"Option:    Function:\n" 
			"-i <file.ppm>: import image\n" 
			"-o <file.yuv>: export movie\n" 
			"-start= <x.y>: set start parameter\n" 
			"-end= <xyz.w>: set end parameter\n" 
			"-step= <x.yz>: set step parameter\n" 
			"-hue: use hue filter\n" 
			"-saturate: use saturation filter\n"

			"-m <file.yuv>: import movie. \n"
			"-o <file.yuv>: export movie.\n"
			"-f <frameNum>: number of frames in the input movie.\n"
			"-s <WxH>\n"
			"-reverse: reverse the movie\n"
			,ProgName);
}
int main(int argc, char *argv[])
{
    int i,saveint,reverseflag;
    char *ImageName=NULL;
    char *MovieName=NULL;
    IMAGE *image=NULL;
    iterableFilter filter=NULL;
    MOVIE *movie=NULL;
    char *importmovie=NULL;
    int framenum,mode;
    unsigned int width,height;
    float start,end,step;




    
    for(i=1;i<argc;i++){

	if(0==strcmp(argv[i],"-i")){
		i++;
		if(i<argc){
		    ImageName=argv[i];
		   
		    mode=1;
		   
		    
			}
		else{
		    fputs("Missing name of image for -i!\n",stderr);
		    PrintUsage(argv[0]);
		    exit(10);}}


	else if(0==strcmp(argv[i],"-o")){
		i++;
		if(i<argc){
			MovieName=argv[i];
			
			}
			
		else{
		    
                    fputs("Missing name of movie for -o!\n",stderr);
                    PrintUsage(argv[0]);
                    exit(10);}}


	else if(0==strcmp(argv[i],"-start=")){
		 i++;
		 
                if(i<argc){

                        start=atof(argv[i]);
			}

	         else{

                    fputs("Missing starting point for -start!\n",stderr);
                    PrintUsage(argv[0]);
                    exit(10);}
		}
        else if(0==strcmp(argv[i],"-end=")){
		 i++;
                if(i<argc){
                        end=atof(argv[i]);
			}
		 else{

                    fputs("Missing ending point for -end!\n",stderr);
                    PrintUsage(argv[0]);
                    exit(10);}
		}
	else if(0==strcmp(argv[i],"-step=")){
		 i++;
                if(i<argc){
                        step=atof(argv[i]);
			}
		 else{

                    fputs("Missing stepping value for -step!\n",stderr);
                    PrintUsage(argv[0]);
                    exit(10);}
	}
	else if(0==strcmp(argv[i],"-hue")){
		
	
		filter=&HueRotate;
		mode=1;	
		}

	else if(0==strcmp(argv[i],"-m")){
                 i++;
                if(i<argc){
                    importmovie=argv[i];
		    
		    mode=2; }
                 else{

                    fputs("Missing movie name for -m!\n",stderr);
                    PrintUsage(argv[0]);
                    exit(10);}}

	
	
	else if(0==strcmp(argv[i],"-f")){
                 i++;
                if(i<argc){
                        framenum=atoi(argv[i]);}
                 else{

                    fputs("Missing frame number input for -f!\n",stderr);
                    PrintUsage(argv[0]);
                    exit(10);}}

	else if(0==strcmp(argv[i],"-s")){
                 i++;
                if(i<argc){
                        sscanf(argv[i],"%ux%u",&width,&height);}
                 else{

                    fputs("Missing width and height values for -s!\n",stderr);
                    PrintUsage(argv[0]);
                    exit(10);}}

	else if(0==strcmp(argv[i],"-saturate")){
                 
                
		   filter=&Saturate;
		   mode=1;
                   } 
	else if(0==strcmp(argv[i],"-reverse")){
		   reverseflag=1;
		   mode=2;
		   }
		
	else { fprintf(stderr, "Unknown option %s!\n", argv[i]); 
	       PrintUsage(argv[0]); 
	       exit(10); }}
	
        
		
 	
	
  
	if(mode==1){
		
		image=LoadImage(ImageName);
		movie=doIterativeFilter(image,filter,start,end,step);
		saveint=SaveMovie(MovieName,movie);
		DeleteImage(image);
		DeleteMovie(movie);}

	 else if(mode==2){
   	 	movie=LoadMovie(importmovie,framenum,width,height);
		
		if(reverseflag==1){
			ReverseImageList(movie->Frames);}
         	saveint=SaveMovie(MovieName,movie);
		DeleteMovie(movie);}

	
  
	
     
	 
}

/* EOF */
