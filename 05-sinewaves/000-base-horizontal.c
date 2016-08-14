#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TWOPI 6.28318530718

// output
char filename[128] = "000-base-horizontal.svg\0";
char path[128] = "out/\0";

// document
int width = 1200;
int height = 700;
float MARGIN = 30;

// groups
float NUM_GROUPS = 4;
float GROUP_SPACING = 170.0;
float GROUP_NUM_HORIZONTALS = 4.0;

// sine curve
float FREQUENCY = .03;
float AMPLITUDE = 10;


int mod2PosNeg(int iterator){
	if(iterator%2 == 0){ return -1; }
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
	
	for(int i = 0; i < NUM_GROUPS; i++){
		float yGroup = GROUP_SPACING * i;  // the major X axis of each group

		// 4 sine waves in every group
		for(int j = 0; j < GROUP_NUM_HORIZONTALS; j++){
			// pattern: L L R R L L ...
			int direction = mod2PosNeg(j*.5);   // -1 or +1

			// spacing
			float percentOfGroup = (j / GROUP_NUM_HORIZONTALS);
			float yInternalSpacing = percentOfGroup * GROUP_SPACING;

			fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" points=\"");  // hanging open quote
			for(float w = 0; w < width; w++){

				float sine = sinf(w*FREQUENCY) * AMPLITUDE;
				float x = w;
				float y = ((MARGIN)) + yGroup + yInternalSpacing + sine * direction;

				fprintf(file, "%.2f,%.2f ", x, y);
			}
			fprintf(file, "\"/>\n"); // closing quote
		}
	}

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}