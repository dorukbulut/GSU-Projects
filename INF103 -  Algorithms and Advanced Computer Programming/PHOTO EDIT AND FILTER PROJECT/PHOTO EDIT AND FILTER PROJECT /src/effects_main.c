#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Kendi baslik dosyalarimizi include ediyoruz */
#include "pgm.h"
#include "effects.h"
#include <time.h>
/* PROGRAMIN ORNEK KULLANIMI:
 *
 *      $ ./pgm_efekt
 *      Usage: ./pgm_efekt <invert|binarize|noise|smooth> <PGM image 1> <PGM image 2> ... <PGM image N>
 *
 *      $ ./pgm_efekt invert effect_images/man_ascii.pgm
 *      (Invert efekti uygulanan resim effect_images/man_ascii.pgm.invert olarak kaydedilir)
 */

int main(int argc, char *argv[])
{
    /* TODO: Program efekt adi ve EN AZ 1 resim dosyasi olmak uzere EN AZ
     * 2 arguman istemektedir. Bu bilgiye gore asagidaki if()'in icerisini
     * doldurun.
     */

    if(argc<3){
        printf("Usage: %s <PGM image1>.....<PGM image n>\n",argv[0]);
        exit(1);
    }

    /* Komut satirindan gelen efekt adi */
    char *effect_name = argv[1];
    int i,control ;
    char new_filename[50];
    PGMInfo new_pgm; 
    
    

    /* TODO: Bazi efektlerin ihtiyac duyabilecegi rand() rassal
     * sayi uretecini seed edin. */
    srand(time(NULL));
    

    


    /* argv[0]:     Programin adi
     * argv[1]:     Efekt cesidi: invert, binarize, noise, smooth
     * argv[2] ...  argv[argc-1]: Dosya adi veya adlari
     */

    for (int i = 2; i <argc; i++)
    {
        new_pgm = pgm_read(argv[i]);
        //resim dosyasini okuma     
        if(new_pgm.error>0){

            pgm_print_error(new_pgm);
            exit(1);
        }
        //okumada bir hata varsa programı durdurma.

        pgm_print_header(new_pgm);
        //resim bilgilerini ekrana basma.

        sprintf(new_filename,"%s.%s",argv[i],effect_name);

        if(strcmp(effect_name,"invert")==0){
            
            effect_invert(new_pgm.pixels,new_pgm.width,new_pgm.height);
        }

        else if(strcmp(effect_name,"binarize")==0){

            effect_threshold(new_pgm.pixels,new_pgm.width,new_pgm.height,130);
        }

        else if(strcmp(effect_name,"noise")==0){

            effect_random_noise(new_pgm.pixels,new_pgm.width,new_pgm.height);
        }
        
        
        else if(strcmp(effect_name,"mirror")==0){
            
            effect_mirror(new_pgm.pixels,new_pgm.width,new_pgm.height);
        }
        
        else if(strcmp(effect_name,"turn_90")==0){

            effect_turn_90(new_pgm.pixels,new_pgm.width,new_pgm.height);

            int temp = new_pgm.width;   
			new_pgm.width = new_pgm.height; 
			new_pgm.height = temp; 
        }

        else{
            
            printf("Invalid Effect!\n");
            return 0;
        }
        //uygulanacak efektin saptanmasi ve uygulanmasi

        control = pgm_write(new_filename,new_pgm);

        if(control){
            
            printf("Error writing PGM file!\n");
            exit(1);
        }

        free(new_pgm.pixels);

    }
    
      

      
      
    

    

    return 0;
}
