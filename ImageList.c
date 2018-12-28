/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

/* Create a new image entry */
IENTRY *CreateImageEntry(void)
{    IENTRY *newentry=(IENTRY *)malloc(sizeof(IENTRY));
     if(!newentry){
	perror("Out of memory! Aborting...");
	exit(10);}
     
     newentry->List=NULL;
     newentry->Next=NULL;
     newentry->Prev=NULL;
     newentry->RGBImage=NULL;
     newentry->YUVImage=NULL;
     return newentry;	

}

/* Delete image entry (and image objects)*/
void DeleteImageEntry(IENTRY *entry)
{
     assert(entry);
     if (entry->RGBImage!=NULL){
	DeleteImage(entry->RGBImage);}
     if(entry->YUVImage!=NULL){
	DeleteYUVImage(entry->YUVImage);}
     
     free(entry);
}

/* Create a new image list */
ILIST *CreateImageList(void)
{    ILIST *newlist=(ILIST *)malloc(sizeof(ILIST));
     if(! newlist){
	perror("Out of memory! Aborting...");
	exit(10);}
     newlist->length=0;
     newlist->First=NULL;
     newlist->Last=NULL;
     return newlist;
     

}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{    IENTRY *e,*n;
     
     assert(list);
     e=list->First;
     while(e){
	n=e->Next;
	DeleteImageEntry(e);
	e=n;}
     free(list);
	
	
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{    IENTRY *e=NULL;
     assert(list);
     assert(RGBimage);
     e=CreateImageEntry();
     e->RGBImage=RGBimage;    
     if(list->Last){
	e->List=list;
        e->Next=NULL;
        e->Prev=list->Last;
        list->Last->Next=e;
        list->Last=e;}
     else{

	e->List=list;
	e->Next=NULL;
        e->Prev=NULL;
        list->First=e;
        list->Last=e;}
     list->length++;
	    	
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{   
     IENTRY *e=NULL;
     assert(list);
     assert(YUVimage);
     e=CreateImageEntry();
     e->YUVImage=YUVimage;
     if(list->Last){
        e->List=list;
        e->Next=NULL;
        e->Prev=list->Last;
        list->Last->Next=e;
        list->Last=e;}
     else{

        e->List=list;
        e->Next=NULL;
        e->Prev=NULL;
        list->First=e;
        list->Last=e;}
     list->length++;


}

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
	unsigned int newFrameNum = 0;
	unsigned int counter = 0;
	IENTRY *curr = NULL; /* current entry in the list */
	IENTRY *prev = NULL; /* previous kept entry in the list */
	IENTRY *next = NULL; /* next entry in the list */

	assert(list);
	assert(factor > 0);

	curr = list->First;

	while (curr != NULL) {
		next = curr->Next;

		if (counter % factor == 0) {
			newFrameNum ++;

			curr->Prev = prev;
			if (prev != NULL) {
				prev->Next = curr;
			}
			prev = curr;
		} else {
			if (curr->RGBImage != NULL) {
				DeleteImage(curr->RGBImage);
			}

			if (curr->YUVImage != NULL) {
				DeleteYUVImage(curr->YUVImage);
			}

			curr->List = NULL;
			curr->Next = NULL;
			curr->Prev = NULL;
			curr->RGBImage = NULL;
			curr->YUVImage = NULL;
			free(curr);
		}

		curr = next;
		counter ++;
	}

	list->Last = prev;
	if (prev != NULL) {
		prev->Next = NULL;
	}
	list->length = newFrameNum;
}

//Reverse the movie
void ReverseImageList(ILIST *list){

	assert(list);

	IENTRY *current,*tmp;
	//IENTRY *next=NULL,*prev=NULL;


	current=list->First;

	while(current !=NULL){
		tmp=current->Prev;
		current->Prev=current->Next;
		current->Next=tmp;
		current=current->Prev;}
	tmp=list->First;
	list->First=list->Last;
	list->Last=tmp;
	}
	





/* EOF */
