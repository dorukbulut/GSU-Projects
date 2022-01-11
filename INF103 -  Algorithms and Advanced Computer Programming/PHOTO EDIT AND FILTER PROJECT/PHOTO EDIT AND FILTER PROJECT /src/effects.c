#include "effects.h"
#include <stdlib.h>

void swap_position(unsigned char* pixels,int index1,int index2){
    int temp = pixels[index1];
    pixels[index1] = pixels[index2];
    pixels[index2] = temp;
}
void effect_random_noise(unsigned char *pixels, int width, int height) {
    int nr_noisy_pixel = (width * height) / 5; // %20 oraninda noise ekle
    int i;

    for (i = 0; i < nr_noisy_pixel; ++i ) {
        int which_pixel = (rand() % (width * height));
        pixels[which_pixel] = (rand() % 256);
    }
}

/* TODO: Invert efekti her pikselin degerinin tumleyenini o pikselin
 * yeni degeri olarak belirler.
 */
void effect_invert(unsigned char *pixels, int width, int height) {

    int i,num_pixels = width*height;

    for ( i = 0; i < num_pixels; i++)
    {
        pixels[i] = 255-pixels[i];
    }
    
}

/* TODO: Verilen bir esik degerin altinda kalan pikselleri siyah,
 * uzerinde kalanlari ise beyaz yaparak 2 renkli bir resim olusturur.
 */
void effect_threshold(unsigned char *pixels, int width, int height, int threshold) {

    int i,num_pixels = width*height;

    for ( i = 0; i < num_pixels; i++)
    {
        if(pixels[i]<threshold) pixels[i] = 255;
    
        if(pixels[i]>threshold) pixels[i] = 0 ;
    }
    
}




// Parametre olarak aldigi resmin ayna goruntusunu alir
void effect_mirror(unsigned char* pixels,int width,int height){

    int i,j;
    

    for(i=0;i<height;i++){

        for(j=0;j<(width/2);j++){
            
            
            swap_position(pixels,(i*width)+j,((width-1)+(i*width))-j);
        }
    }
}

void effect_turn_90 (unsigned char *pixels, int width, int height) {
	int i, k, j=0;
	int size = width*height;
//orijinal diziyi saklamak icin yeni yer aciyoruz. 
	unsigned char *copy_pixels = malloc(size); 
	if (copy_pixels == NULL) exit(1);
	for (i=0; i<size; i=i+1) {
		copy_pixels[i] = pixels[i];
	}
//orijinal diziyi, saklanmis diziyi kullanarak yeniden sekillendiriyoruz
	for (i=0; i<width; i=i+1) {
		for (k=(height-1); k>=0; k=k-1) {
			pixels[j] = copy_pixels[k*width + i]; 
			j = j + 1;
		}

        }
	free(copy_pixels); //yeri bosaltiyoruz
}
