#include "answer07.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define bmp_magic_number 0x21343632
#define FALSE 0
#define TRUE 1

static int BMP_checkValid(ImageHeader * header);

Image * Image_load(const char * filename)
{
  FILE * fp = NULL;
  ImageHeader header;
  size_t read;
  Image * tmp_im = NULL, * im = NULL;
  int err = FALSE;
	
  if(!err){
    fp = fopen(filename, "rb");
    if(!fp){
      fprintf(stderr, "Failed to open file '%s'\n",filename);
      err = TRUE;
    }
  }
	
  if(!err){
    read = fread(&header, sizeof(ImageHeader), 1, fp);
    if(read != 1){
      fprintf(stderr, "Failed to read header from '%s'\n", filename);
      err = TRUE;
    }
  }
	
  if(!err){
    if(!BMP_checkValid(&header)) {
      fprintf(stderr, "Invalid header in '%s'\n", filename);
      err = TRUE;
    }
  }
	
  if(!err){
    tmp_im = malloc(sizeof(Image));
    tmp_im->comment = NULL;
    tmp_im->data = NULL;
    if(tmp_im == NULL){
      fprintf(stderr, "Failed to allocate im structure\n");
      err = TRUE;
    }
  }
	
  if(!err){
    tmp_im->width = header.width;
    tmp_im->height = header.height;
    tmp_im->comment = malloc(sizeof(char*) *header.comment_len);
    if(tmp_im->comment == NULL){
      fprintf(stderr, "Fail to allocate comment\n");
      err = TRUE;
    }
  }
	
  if(!err){
    read = fread(tmp_im->comment, sizeof(char), header.comment_len, fp);
    if(read != header.comment_len || tmp_im->comment[header.comment_len-1] != '\0'){
      fprintf(stderr, "Comment does not end with null byte\n");
      err = TRUE;
    }
  }
	
  if(!err){
    tmp_im-> data = malloc(sizeof(uint8_t) * header.width * header.height);
    if(tmp_im-> data == NULL){
      fprintf(stderr, "Fail to allocate memory to data\n");
      err = TRUE;
    }
  }
  if(!err) {
    read = fread(tmp_im-> data, sizeof(uint8_t), header.width * header.height,fp);
    if(read != header.width * header.height){
      fprintf(stderr, "could not read all image data\n");
      err = TRUE;
    }
  }
  
  if(!err){
  if(fgetc(fp) != EOF){
    fprintf(stderr, "Have not reach the end of file\n");
    err = TRUE;
  }
  }

  if(!err){
    im = tmp_im;
    tmp_im = NULL;
  }
	
  Image_free(tmp_im);
  if(fp != NULL)
    fclose(fp);
  if(err)
    return NULL;
  else
    return im;
		
}
	

int Image_save(const char * filename, Image * image)
{
  FILE * fp = NULL;
  ImageHeader header;
  int len = strlen(image->comment) +1;
  fp = fopen(filename, "wb");

  if(fp == NULL){
    fprintf(stderr, "Failed to open file '%s'\n",filename);
    return 0;
  }
  else{
    header.magic_number = 0x21343632;
    header.width = image-> width;
    header.height = image-> height;
    header.comment_len = len;
	
    fwrite(&header, sizeof(ImageHeader),1, fp);
    fwrite(image->comment, len * sizeof(char), 1,fp);
    fwrite(image->data, sizeof(uint8_t), header.width * header.height, fp);
  }
	
  fclose(fp);
  return 1;
}
	
void Image_free(Image * image)
{
  if(image != NULL){
    free(image->comment);
    free(image->data);
    free(image);
  }
}
	
void linearNormalization(int width, int height, uint8_t * intensity)
{
  int ind;
  int min = 255;
  int max = 0;
  for(ind =0; ind < width * height; ind++)
    {
      if(intensity[ind] > max)
	{
	  max = intensity[ind];
	}
      if(intensity[ind] < min)
	{
	  min = intensity[ind];
	}
    }
  for(ind =0; ind< width * height; ind ++)
    {
      intensity[ind] = (intensity[ind] - min) * 255.0 / (max - min);
    }
}

	
static int BMP_checkValid(ImageHeader * header)
{
  if (header->magic_number != bmp_magic_number) return 0;

  if (header->width == 0) return 0;

  if (header->height == 0) return 0;
	
  if (header->comment_len == 0) return 0;

  return 1;
}

	
	
	
	
	
	
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
  
