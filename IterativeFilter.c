/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2018                     */
/*                                                                   */
/* Author: Jordan Bonecutter                                         */
/*                                                                   */
/* IterativeFilter.c: file for iterative filters                     */
/*                                                                   */
/*********************************************************************/

#include "IterativeFilter.h"
//Iterate over image and apply filter on each entry depending on change value
MOVIE *doIterativeFilter(IMAGE *image, iterableFilter filter, float start, float end, float change)
{
	IMAGE *tmp;
	MOVIE *movie=CreateMovie();
	
	if(start>end){

		float i=start;
		
		while(i>=end){
			i=i-change;	
		
		
			tmp=CopyImage(image);
			tmp=filter(tmp,i);
			AppendRGBImage(movie->Frames,tmp);	
			

	}}
	if(start<end){

	
		float i=start;
		while(i<=end){
		      i=i+change;	
	              tmp=CopyImage(image);
	              tmp=filter(tmp,i);
	              AppendRGBImage(movie->Frames,tmp);
		    
		      
	}}
	
	RGB2YUVMovie(movie);
	
	return movie;}

