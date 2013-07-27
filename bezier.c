#include <stdarg.h>
#include <string.h>
#include  <stdio.h>
#define MAX_NODE 12 

typedef struct
{
	float x;
	float y;
} vec2f;

vec2f bezier( float t, int argc, ... )
{
	va_list arguments;
	vec2f nodes[MAX_NODE];
	int i;
	vec2f * temp;

	va_start( arguments, argc );
	for( i = 0; i < argc; i++ )
	{
		temp = va_arg( arguments, vec2f* );
		nodes[i].x = temp->x;
		nodes[i].y = temp->y;
	}
	va_end( arguments );

	for( ; argc > 1; argc-- )
	{
		for( i = 0; i < argc-1; i++ )
		{
			nodes[i].x = nodes[i].x * (1-t);
			nodes[i].y = nodes[i].y * (1-t);
			nodes[i].x += nodes[i+1].x * t;
			nodes[i].y += nodes[i+1].y * t;
		}
	}

	return nodes[0];
}
