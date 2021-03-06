#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "imageData.h"
#include "functions.h"
#include "solution.h"

#define IMAGE_WIDTH 480
#define IMAGE_HEIGHT 320

Image *initialize_input();
int check_gaus_filter(double *stud,double *sol,int size);
int check_image(Image *stud,Image *sol);
double image_error(Image *stud,Image *sol);

/* Runs a series of unit tests for functions in functions.c
 * A randomly generated image is used
 * Output compared to solution code, and results printed
 */
int main()
{
  //Make images
  Image *input_image=initialize_input();
  Image *input_image_sol=generate_output(input_image);
  int iImage = 0;
  for(iImage = 0; iImage<(input_image->width)*(input_image->height); iImage++){
      input_image_sol->red_channel[iImage]=input_image->red_channel[iImage];
      input_image_sol->blue_channel[iImage]=input_image->blue_channel[iImage];
      input_image_sol->green_channel[iImage]=input_image->green_channel[iImage];
      input_image_sol->alpha_channel[iImage]=input_image->alpha_channel[iImage];
  }
  Image *stud_image=generate_output(input_image);
  Image *sol_image=generate_output(input_image);
  const double gmonomult[3]={.299,.587,.114};

  //Test cosine filter for two different radii
  int radius = 2;
  int size=(2*radius+1)*(2*radius+1);
  double *cos_filter=(double*)malloc(sizeof(double)*size);
  double *cos_filter_sol=(double*)malloc(sizeof(double)*size);
  printf("\nTesting calculate_cosine_filter with Radius=%d:\n",radius);
  calculate_cosine_filter(cos_filter,radius);
  calculate_cosine_filter_sol(cos_filter_sol,radius);
  if(!check_gaus_filter(cos_filter,cos_filter_sol,size))
  {
    printf("calculate_cosine_filter correct\n");
  }
  else	
  {
    printf("calculate_cosine_filter incorrect, Error >0.002\n");
  }

  radius = 3;
  size=(2*radius+1)*(2*radius+1);
  double *cos_filter2=(double*)malloc(sizeof(double)*size);
  double *cos_filter_sol2=(double*)malloc(sizeof(double)*size);
  printf("\nTesting calculateCosineFilter with Radius=%d:\n",radius);
  calculate_cosine_filter(cos_filter2,radius);
  calculate_cosine_filter_sol(cos_filter_sol2,radius);
  if(!check_gaus_filter(cos_filter2,cos_filter_sol2,size))
  {
    printf("calculate_cosine_filter correct\n");
  }
  else	
  {
    printf("calculate_cosine_filter incorrect, Error >0.002\n");
  }

  //Get image channels- input for student and solution, 
  //output for student and solution
  uint8_t *in_red=input_image->red_channel;
  uint8_t *in_green=input_image->green_channel;
  uint8_t *in_blue=input_image->blue_channel;
  uint8_t *in_redsol=input_image_sol->red_channel;
  uint8_t *in_greensol=input_image_sol->green_channel;
  uint8_t *in_bluesol=input_image_sol->blue_channel;
  uint8_t *in_alpha=input_image->alpha_channel;
  uint8_t *in_alphasol=input_image_sol->alpha_channel;
  uint8_t *stud_red=stud_image->red_channel;
  uint8_t *stud_green=stud_image->green_channel;
  uint8_t *stud_blue=stud_image->blue_channel;
  uint8_t *stud_alpha=stud_image->alpha_channel;
  uint8_t *sol_red=sol_image->red_channel;
  uint8_t *sol_green=sol_image->green_channel;
  uint8_t *sol_blue=sol_image->blue_channel;
  uint8_t *sol_alpha=sol_image->alpha_channel;
  
  //Convolution test
  radius = 7;
  printf("\nTesting convolve_image with Cosine Filter, radius=%d:\n",radius);
  size=(2*radius+1)*(2*radius+1);
  double *cos_filter_test=(double*)malloc(sizeof(double)*size);
  calculate_cosine_filter_sol(cos_filter_test,radius);

  convolve_image(in_red,in_green,in_blue,in_alpha,stud_red,stud_green,stud_blue,
                stud_alpha,cos_filter_test,radius,IMAGE_WIDTH,IMAGE_HEIGHT);
  convolve_image_sol(in_redsol,in_greensol,in_bluesol,in_alphasol,sol_red,sol_green,sol_blue,
                   sol_alpha,cos_filter_test,radius,IMAGE_WIDTH,IMAGE_HEIGHT);
    double convolve_error = 0.00005;
  if(image_error(stud_image,sol_image)<convolve_error)
  {
    printf("convolve_image correct with error %lf < %lf\n",image_error(stud_image,sol_image),convolve_error);
  }
  else
  {
    printf("convolve_image incorrect with error %lf > %lf\n",image_error(stud_image,sol_image),convolve_error);
  }

  //reset student output before next test
  for(iImage = 0; iImage<(input_image->width)*(input_image->height); iImage++){
      stud_red[iImage]=0;
      stud_green[iImage]=0;
      stud_blue[iImage]=0;
      stud_alpha[iImage]=0;
  }

  //Convert to gray
    printf("\nTesting convert_to_gray\n");
  convert_to_gray(in_red,in_green,in_blue,in_alpha,stud_red,stud_green,stud_blue,
                stud_alpha,gmonomult,IMAGE_WIDTH,IMAGE_HEIGHT);
  convert_to_gray_sol(in_redsol,in_greensol,in_bluesol,in_alphasol,sol_red,sol_green,sol_blue,
                   sol_alpha,gmonomult,IMAGE_WIDTH,IMAGE_HEIGHT);
  if(!check_image(stud_image,sol_image))
  {
    printf("convert_to_gray correct\n");
  }
  else
  {
    printf("convert_to_gray incorrect\n");
  }

  //reset student output before next test
  for(iImage = 0; iImage<(input_image->width)*(input_image->height); iImage++){
      stud_red[iImage]=0;
      stud_green[iImage]=0;
      stud_blue[iImage]=0;
      stud_alpha[iImage]=0;
  }

  //Flip test
  printf("\nTesting flip_vertical:\n");
  flip_vertical(in_red,in_green,in_blue,in_alpha,stud_red,stud_green,stud_blue,
              stud_alpha,IMAGE_WIDTH,IMAGE_HEIGHT);
  flip_vertical_sol(in_redsol,in_greensol,in_bluesol,in_alphasol,sol_red,sol_green,sol_blue,
                 sol_alpha,IMAGE_WIDTH,IMAGE_HEIGHT);
  if(!check_image(stud_image,sol_image))
  {
    printf("flip_vertical correct\n");
  }
  else
  {
    printf("flip_vertical incorrect\n");
  }

  //reset student output before next test
  for(iImage = 0; iImage<(input_image->width)*(input_image->height); iImage++){
      stud_red[iImage]=0;
      stud_green[iImage]=0;
      stud_blue[iImage]=0;
      stud_alpha[iImage]=0;
  }

  //Threshold test
  printf("\nTesting color_threshold R Thres=20 B Thres = 100 G Thres = 40:\n");
  color_threshold(in_red,in_green,in_blue,in_alpha,stud_red,stud_green,stud_blue,
              stud_alpha,IMAGE_WIDTH,IMAGE_HEIGHT,20,100,40);
  color_threshold_sol(in_redsol,in_greensol,in_bluesol,in_alphasol,sol_red,sol_green,sol_blue,
                 sol_alpha,IMAGE_WIDTH,IMAGE_HEIGHT,20,100,40);
  if(!check_image(stud_image,sol_image))
  {
    printf("color_threshold correct\n");
  }
  else
  {
    printf("color_threshold incorrect\n");
  }
 
  //Free everything
  free(cos_filter);
  free(cos_filter_sol);
  free(cos_filter2);
  free(cos_filter_sol2);
  free(cos_filter_test);
  free_image(input_image);
  free_image(input_image_sol);
  free_image(stud_image);
  free_image(sol_image);
  return 0;
}

//Used to compare filters, error must not exceed 0.002
int check_gaus_filter(double *stud,double *sol,int size)
{
  int i;
  for(i=0;i<size;i++)
    if(fabs(sol[i]-stud[i])>.002)
      return -1;
  return 0;
}

//Check for exact image match
int check_image(Image *stud,Image *sol)
{
  uint8_t *stud_red=stud->red_channel;
  uint8_t *stud_green=stud->green_channel;
  uint8_t *stud_blue=stud->blue_channel;
  uint8_t *stud_alpha=stud->alpha_channel;
  uint8_t *sol_red=sol->red_channel;
  uint8_t *sol_green=sol->green_channel;
  uint8_t *sol_blue=sol->blue_channel;
  uint8_t *sol_alpha=sol->alpha_channel;

  int loc,row,col;
  for(row=0;row<IMAGE_HEIGHT;row++)
    for(col=0;col<IMAGE_WIDTH;col++)
    {
      loc=row*IMAGE_WIDTH+col;
      if(stud_red[loc]!=sol_red[loc])
        return -1;
      if(stud_green[loc]!=sol_green[loc])
        return -1;
      if(stud_blue[loc]!=sol_blue[loc])
        return -1;
      if(stud_alpha[loc]!=sol_alpha[loc])
        return -1;
    }

  return 0;
}

//Create random image
Image *initialize_input()
{
  int index;
  Image *new_image=(Image*)malloc(sizeof(Image));
  new_image->red_channel=(uint8_t*)malloc(sizeof(uint8_t)*IMAGE_HEIGHT*IMAGE_WIDTH);
  new_image->green_channel=(uint8_t*)malloc(sizeof(uint8_t)*IMAGE_HEIGHT*IMAGE_WIDTH);
  new_image->blue_channel=(uint8_t*)malloc(sizeof(uint8_t)*IMAGE_HEIGHT*IMAGE_WIDTH);
  new_image->alpha_channel=(uint8_t*)malloc(sizeof(uint8_t)*IMAGE_HEIGHT*IMAGE_WIDTH);

  for(index=0;index<(IMAGE_WIDTH*IMAGE_HEIGHT);index++)
  {
      new_image->red_channel[index]=rand()%256;
      new_image->green_channel[index]=rand()%256;
      new_image->blue_channel[index]=rand()%256;
      new_image->alpha_channel[index]=255;
  }
  new_image->width=IMAGE_WIDTH;
  new_image->height=IMAGE_HEIGHT;
  double sigma=1;
  int radius=get_radius_sol(sigma);
  int size=(2*radius+1)*(2*radius+1);
  double *gaus_filter_sol=(double*)malloc(sizeof(double)*size);
  calculate_gaus_filter_sol(gaus_filter_sol,sigma);

  Image *new_image_out=(Image*)malloc(sizeof(Image));
  new_image_out->red_channel=(uint8_t*)malloc(sizeof(uint8_t)*IMAGE_HEIGHT*IMAGE_WIDTH);
  new_image_out->green_channel=(uint8_t*)malloc(sizeof(uint8_t)*IMAGE_HEIGHT*IMAGE_WIDTH);
  new_image_out->blue_channel=(uint8_t*)malloc(sizeof(uint8_t)*IMAGE_HEIGHT*IMAGE_WIDTH);
  new_image_out->alpha_channel=(uint8_t*)malloc(sizeof(uint8_t)*IMAGE_HEIGHT*IMAGE_WIDTH);

  uint8_t *in_red=new_image->red_channel;
  uint8_t *in_green=new_image->green_channel;
  uint8_t *in_blue=new_image->blue_channel;
  uint8_t *in_alpha=new_image->alpha_channel;
  uint8_t *out_red=new_image_out->red_channel;
  uint8_t *out_green=new_image_out->green_channel;
  uint8_t *out_blue=new_image_out->blue_channel;
  uint8_t *out_alpha=new_image_out->alpha_channel;
  new_image_out->width=IMAGE_WIDTH;
  new_image_out->height=IMAGE_HEIGHT;
  
  convolve_image_sol(in_red,in_green,in_blue,in_alpha,out_red,out_green,out_blue,
                   out_alpha,gaus_filter_sol,radius,IMAGE_WIDTH,IMAGE_HEIGHT);
  free_image(new_image);
  free(gaus_filter_sol);//Forgot to free this! 
  return new_image_out;
}

//Compare images, allowing for some error. Ratio of error to image power calculated
double image_error(Image *stud,Image *sol)
{
  uint8_t *stud_red=stud->red_channel;
  uint8_t *stud_green=stud->green_channel;
  uint8_t *stud_blue=stud->blue_channel;
  uint8_t *sol_red=sol->red_channel;
  uint8_t *sol_green=sol->green_channel;
  uint8_t *sol_blue=sol->blue_channel;
  
  double power = 0;/*solution image power*/
  double error = 0;/*error power*/
  int index;
  double npix = IMAGE_HEIGHT*IMAGE_WIDTH;
  for(index=0;index<npix;index++){
      power = power + (1.0/npix)*(pow((double)sol_red[index],2.0) + pow((double)sol_green[index],2.0)
              + pow((double)sol_blue[index],2.0));
      error = error + (1.0/npix)*(pow((double)sol_red[index]-(double)stud_red[index],2.0)+pow((double)sol_green[index]
              -(double)stud_green[index],2.0)+pow((double)sol_blue[index]-(double)stud_blue[index],2.0));
  }
  return error/power;/*return error to signal ratio, want less than 1%*/
}

