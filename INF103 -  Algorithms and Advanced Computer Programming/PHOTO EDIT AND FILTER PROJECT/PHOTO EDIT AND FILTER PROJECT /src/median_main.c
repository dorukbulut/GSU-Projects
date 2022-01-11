#include <stdio.h>
#include <stdlib.h>


#include "pgm.h"

#define N_IMAGES 9


/* TODO: Istediginiz bir siralama algoritmasiyla pixels dizisini
 * siralayin ve ortanca elemanin degerini geri dondurun. */

void swap_position(unsigned char* array,int index1,int index2){
    int tmp = array[index1];

    array[index1] = array[index2];
    array[index2] = tmp;
}




unsigned char sort_and_get_median(unsigned char *pixels, int size) {

    int low=0,high=size-1,i,j;
    int middle = (low+high)/2;
    

    for(i = 1;i<size;i++ ){
        j = i;

        while(j>0 && pixels[j]<pixels[j-1]){
            swap_position(pixels,j,j-1);
            j--;
        }
    }
    return  pixels[middle];
}

int main(int argc, const char *argv[])
{
    int i,j=0;
     
    char file_name[60];
      
    /* 9 adet resim var */
    PGMInfo images[N_IMAGES];
    unsigned char ordered[9];
    
    /* Temizlenmis resim icin baslik kismini hazirlayalim */
    
    PGMInfo filtered = pgm_read("median_images/1.pgm");
    free(filtered.pixels);
    filtered.pixels = NULL;
    
        
     
    
    /* Temizlenmis resmin pikselleri icin yer ayiralim */
    filtered.pixels = malloc(filtered.width*filtered.height*sizeof(char));
  
    /* Resimleri sirayla images[]'in ilgili elemanina okuyun.
     * Resimler median_images/ dizini altinda 1'den 9'a kadar adlandirilmis
     * olup uzantilari pgm'dir. Ornek: 1.pgm, 2.pgm, .. */
        
        /*  image_file'in icerisine okunacak dosya adini yazin (ipucu: sprintf()) */
        
        /* Resim dosyasini pgm_read() ile images[i] icerisine okuyun. */

        /* Hata olusursa programi sonlandir */

        /* Bilgileri ekrana yazdir */
    for(i=0;i<9;i++)
    {
        
        
        sprintf(file_name,"median_images/%d.pgm",i+1);
        images[i] = pgm_read(file_name);

        if(images[i].error>0){

            pgm_print_error(images[i]);
            exit(1);
        }

        pgm_print_header(images[i]); 
    }

    i=0;
    /* TODO: Median filtreleme */
    for (i=0;i<filtered.width*filtered.height;i++) {

        for(j=0;j<9;j++){

            ordered[j] = images[j].pixels[i];
        }

        filtered.pixels[i] = sort_and_get_median(ordered,9);

    }
    
    /* Temizlenmis resmi kaydedin. */
    pgm_write("median_images/filtered.pgm", filtered);

    
    /*  Temizlenmis resmin piksel alanini free() edin */

    free(filtered.pixels);
    /* Tum fotograflarin piksel alanlarini free() edin */
    i=0;
    
    for(i=0;i<9;i++){

        free(images[i].pixels);
    }
   

    return 0;
}
