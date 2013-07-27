#include "bezier.c"
#include <stdlib.h>
#include <SDL/SDL.h>
#include <math.h>
#include <time.h>

int main( int argc, char * argv[])
{
	START:
	if (SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		fprintf( stderr, "Unable to init SDL: %s\n", SDL_GetError() );
		return 1;
	}

	SDL_Surface *screen;

	screen = SDL_SetVideoMode( 640, 480, 16, SDL_SWSURFACE );
	if( screen == NULL )
	{
		fprintf( stderr, "Unable to create output surface: %s\n", SDL_GetError() );
		return 1;
	} 
	Uint32 white; 
	
	vec2f set[MAX_NODE];
	srand( time(NULL) );
	int i;
	for( i = 0; i < MAX_NODE; i++ )
	{
		set[i].x = rand() % screen->w;
		set[i].y = rand() % screen->h;
	}

	vec2f ret;
	float t;
	Uint16 *bufp;
	for( t = 0; t <= 1; t+= 0.0001 )
	{
		white = SDL_MapRGB( screen->format, t * 255, (1-t) * 255, 0 );
		ret = bezier( t, MAX_NODE, 
			&set[0], &set[1], &set[2], &set[3], 
			&set[4], &set[5], &set[6], &set[7], 
			&set[8], &set[9], &set[10], &set[11] );
		printf( "t: %f x: %hd y: %hd\n", t, (Uint16)ret.x, (Uint16)ret.y );
		bufp = (Uint16*)screen->pixels + (Uint16)ret.y*screen->pitch/2 + (Uint16)ret.x;
		*bufp = white;
		SDL_UpdateRect( screen, (Uint16)ret.x, (Uint16)ret.y, 1, 1 ); 
	}
	goto START;
	atexit( SDL_Quit );
}
