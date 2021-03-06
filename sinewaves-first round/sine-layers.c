#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../common/noise.c"

#define TWOPI 6.28318530718

// output
char filename[128] = "sine-layers.svg\0";
char path[128] = "out/\0";

// document
int width = 1200;
int height = 900;

// shape
float COLUMNS = 24;
float phase0 = 0.2;
// float magnitude0 = 40;
// float magnitude1 = 26;
// float magnitude2 = 28;
// float magnitude3 = 15;
// float magnitude4 = 15;
// float period1 = 0.03;
// float period2 = 0.056;
// float period3 = 0.06666;
// float period4 = 0.0896;
float magnitude0 = 30; //40;
float magnitude1 = 18; //26;
float magnitude2 = 30; //28;
float magnitude3 = 15; //15;
float magnitude4 = 15; //15;
float period1 = 0.02; //0.03;
float period2 = 0.005; //0.056;
float period3 = 0.015; //0.06666;
float period4 = 0.0175; //0.0896;

int posNeg(int in){
	if(in == 0){ return -1; }
	return 1;
}

int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));
	float seed = rand()%1000/100.0;

	strcat(path, filename);
	FILE *file = fopen(path, "w");
	fprintf(file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(file, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" ");
	fprintf(file, "x=\"0px\" y=\"0px\" width=\"%dpx\" height=\"%d", width, height);
	fprintf(file, "px\" viewBox=\"0 0 %d %d", width, height);
	fprintf(file, "\" xml:space=\"preserve\">\n<g>\n");

	for(int i = 0; i < COLUMNS; i++){
		fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote
		for(float j = 0; j < height; j++){
			int halfI = floor(i*.5);
			int one = floor((i+0)*.25);
			int three = floor((i+2)*.25);
			
			float phase = i*phase0;
			
			float wave1 = sinf(j*period1 + phase)*posNeg(halfI%2);
			float wave2 = sinf(j*period2 + phase);
			float wave3 = sinf(j*period3 + phase);
			float wave4 = sinf(j*period4 + phase);
			
			// wave1 = 0;
			// wave2 = 0;
			// wave3 = 0;
			// wave4 = 0;
			
			float x = 70 + magnitude0 * (i+one+three)
			             + magnitude1 * wave1
			             + magnitude2 * wave2
			             + magnitude3 * wave3
			             + magnitude4 * wave4;
			float y = j;

			fprintf(file, "%.2f,%.2f ", x, y);
		}
		fprintf(file, "\"/>\n"); // closing quote
	}

	fprintf(file, "\"/>\n"); // closing quote

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}