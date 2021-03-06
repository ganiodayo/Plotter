#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TWOPI 6.28318530718

int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));

	float seed = rand()%1000/100.0;

	int width = 800;
	int height = 800;

	char path[128];
	path[0] = '\0';
	// strcat(path, directory);
	// strcat(path, filename);
	strcat(path, "homemade.svg");
	FILE *file = fopen(path, "w");
	fprintf(file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(file, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" ");
	fprintf(file, "x=\"0px\" y=\"0px\" width=\"");
	fprintf(file, "%d",width);
	fprintf(file, "px\" height=\"");
	fprintf(file, "%d",height);
	fprintf(file, "px\" viewBox=\"0 0 ");
	fprintf(file, "%d ",width);
	fprintf(file, "%d",height);
	fprintf(file, "\" xml:space=\"preserve\">\n");

	// int fputc( int c, FILE *file );
	// char x[10]="ABCDEFGHIJ";
	// fwrite(x, sizeof(x[0]), sizeof(x)/sizeof(x[0]), file);
	fprintf(file, "<g>\n");
	fprintf(file, "<polyline fill=\"none\" stroke=\"#FF0000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote

	float x, y;
	float SCALE = 26;
	float ENDCAP = .4;
	float ROUNDS = 11;//15.0;//18.0;
	
	float divider = 5 * 60;

	float wobbleFreq = 12.0;
	float wobbleMag = 0.05;

	float nudgeScale = 0.0333;

	float pathGap = 0.33;


	fprintf(file, "\"/>\n"); // closing quote
	fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote

	int i = 14;
		for(float a = 0; a <= TWOPI+.0001; a += TWOPI/divider){
			float wobbleIncr = (i + 2*a/TWOPI);
			// wobbleIncr = 1.0;
			x = width*.5  + SCALE * cos(a) * (i + sin(a*wobbleFreq)*wobbleMag*wobbleIncr );
			y = height*.5 + SCALE * sin(a) * (i + sin(a*wobbleFreq)*wobbleMag*wobbleIncr );
			fprintf(file, "%.2f,%.2f ", x, y);
		}




	//+ cos(turn) * .2*sqrt(i + 2*a/TWOPI) 
	fprintf(file, "\"/>\n"); // closing quote

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}