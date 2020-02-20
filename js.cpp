#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SwinGame.h"
#define MAX_ITERATION 200
#define RVALUE -0.624
#define IVALUE 0.435



color get_color(double real,double imag)
{
	double xtemp,Re,Im,hue;
	color clr;
	int iteration;
	Re=real;
	Im=imag;

	for (iteration =0; iteration < MAX_ITERATION; iteration++)
	{
		xtemp=Re*Re-Im*Im + RVALUE;
		Im=2*Re*Im+IVALUE;
		Re=xtemp;
		if((Re*Re+Im*Im)>4)
			break;

	}

			if(iteration>=MAX_ITERATION)
		{
			clr=ColorPeru;
		}else
		{
			hue=0.6+(double)(iteration/MAX_ITERATION);
			clr=hsbcolor(hue,0.7,0.8);
		}
	return clr;
}

void draw_juliaset(double begin_x,double begin_y,double width,double height )
{
	double real,imag;
	double julia_w,julia_h;
	int x,y;
	color j_color;
	julia_w = width/screen_width();
	julia_h=height/screen_height();
	
	for(y=0;y<screen_height();y++)
	{
		for(x=0;x<screen_width();x++)
		{
			real=begin_x+x*julia_w;
			imag=begin_y+y*julia_h;
			j_color=get_color(real,imag);
			draw_pixel(j_color,x,y);

		}
	}
}

int main()
{	
	
	open_graphics_window("Julia set",400,300);
	load_default_colors();
	clear_screen(ColorWhite);
	double begin_x=-1.5,begin_y=-2.0,width=3,height=4;
	do 
	{
		clear_screen(ColorWhite);
		process_events();
		draw_juliaset(begin_x, begin_y, width, height);
		if(mouse_clicked(LEFT_BUTTON))
		{
			begin_x=begin_x+(mouse_x()/screen_width()*width);
			begin_y=begin_y+(mouse_y()/screen_height()*height);
			width=width/2;
			height=height/2;
			begin_x=begin_x-(width/2);
			begin_y=begin_y-(height/2);
		}
		if(mouse_clicked(RIGHT_BUTTON))
		{
			begin_x=begin_x+(mouse_x()/screen_width()*width);
			begin_y=begin_y+(mouse_y()/screen_height()*height);
			width=width*2;
			height=height*2;
			begin_x=begin_x-(width/2);
			begin_y=begin_y-(height/2);
		}
		refresh_screen();
	}while(!(window_close_requested()));



}