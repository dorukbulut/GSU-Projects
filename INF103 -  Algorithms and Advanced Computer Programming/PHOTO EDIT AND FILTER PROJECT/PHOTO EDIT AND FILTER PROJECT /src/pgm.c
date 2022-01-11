#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#include "pgm.h"

/* PGM dosyasinin baslik bilgilerini ekrana yazdiran fonksiyon */
void pgm_print_header(PGMInfo pgm_info) {
    printf("This is a %s type PGM image containing %d x %d pixels\n",
           pgm_info.signature,
           pgm_info.width,
           pgm_info.height);
}

PGMInfo pgm_read(const char *filename) {
    /* Bu fonksiyon filename stringi ile verilen dosyayi fopen()
     * ile read kipinde acmali ve PGM dosyasinin basligini ve
     * piksellerini PGMInfo turunden bir struct'a atmalidir.
     *
     * Fonksiyon geriye bu struct'i dondurmelidir.
     */

    /* PGMInfo turunden bir degisken yaratip, error uyesini 0 yaptik. */
    PGMInfo pgm_info = {.error = 0};

    /* Dosyadaki satirlari okumak icin bir tampon. */
    char line[LINE_MAX];
    int i = 0;
    int read = 0;
   //uyarilari yok edebilmek icin struct tipi olusturdum
    struct a {
	int value_i;  
	char *value_c;
    } A;


    /* TODO: Dosyayi acin. Eger dosya acilamazsa pgm_info'nun error
     * uyesini PGM_ERROR_READ yapip fonksiyonu sonlandirin. */
    FILE *fp = fopen(filename,"r");
    if (fp == NULL){
    	pgm_info.error = PGM_ERROR_READ;
	exit(1);
    }


    /* TODO: PGM imzasi P2 veya P5 degilse dosyayi kapatin, error'u
     * PGM_ERROR_SIGNATURE yapip fonksiyonu sonlandirin. */
    A.value_i = fscanf(fp,"%s\n",pgm_info.signature);
   //uyarıyı yok etmek icin struct'a atadim yoksa gereksiz

    if (strcmp(pgm_info.signature,"P2")!=0) {
	if (strcmp(pgm_info.signature,"P5")!=0) {
		fclose(fp);
		pgm_info.error = PGM_ERROR_SIGNATURE;
		exit(1);
    	}
    }
   

    /* TODO Comment satirini oku. */ 
    A.value_c = fgets(pgm_info.comment,LINE_MAX,fp);;
    

    /* TODO: En ve boyu oku */
    A.value_i = fscanf(fp,"%d %d\n",&(pgm_info.width), &(pgm_info.height));


    /* TODO Max piksel degerini oku */
    char temp[LINE_MAX];  //saklamak icin olusturduk
    A.value_i = fscanf(fp,"%s\n",temp); //temp icine okuduk
    pgm_info.max_pixel_value = (char) atoi(temp); //gerekli tip donusumu yapip atadik

    /* TODO: pgm_info.pixels icin malloc() ile yer ayiralim.
     * Bir piksel bellekte 1 bayt yer istiyor, unutmayalim. */
    int size = (pgm_info.width)*(pgm_info.height);
    pgm_info.pixels = malloc(size);


    /* TODO: malloc() ile yer ayrilamazsa dosyayi kapatin, error'u
     * PGM_ERROR_MALLOC yapip fonksiyonu sonlandirin.*/
    if (!pgm_info.pixels) {
    	pgm_info.error = PGM_ERROR_MALLOC;
	fclose(fp);
        exit(1);
    }


    /* 2 farkli dosya bicimi, 2 farkli okuma bicimi.
     * P2 yani ASCII olanda dosyayi fgets() ile satir satir okuyoruz.
     * Okudugumuz satirin sonundaki '\n' karakterini kaldiriyoruz
     * ve elimizde kalan string'i atoi() ile sayiya cevirip pixels
     * dizisine kaydediyoruz.
     *
     * P5 yani binary olanda ise dogrudan fread() ile bir kerede pixels'in icerisine
     * okuma yapiyoruz.
     */

    /* Eger dogru okuma yapamadiysaniz programiniz assert() sayesinde
     * yarida kesilecek. */
    if (strcmp(pgm_info.signature, "P5") == 0) {  //Binary
    	read = fread(pgm_info.pixels,1,size,fp);
    }
    else { //ASCII
        for (i=0; i<size; i=i+1) { 
       		A.value_c = fgets(line,LINE_MAX,fp); //line icine okuduk
        	line[strlen(line)-1] = '\0'; //sondaki \n karakterini bosluk ile degistirdik
        	pgm_info.pixels[i] = (char)atoi(line); //gerekli tip donusumlerini yapip atadik
        }
        read = i;
        }
	
    
    fclose(fp); 
    
    printf("Read %d bytes. (Should be: %d)\n", read, pgm_info.width * pgm_info.height);
    assert(read == (size));

    return pgm_info;
}

int pgm_write(const char *filename, PGMInfo pgm_info) {
    /* Bu fonksiyon filename stringiyle verilen dosyayi write kipinde acarak
     * pgm_info'nun icindeki baslik ve piksel bilgilerini dosyaya yazar.
     * Boylece yeni bir PGM resim dosyasi diske kaydedilmis olur.
     *
     * Fonksiyon herhangi bir hatada 1, basari durumunda 0 dondurmelidir.
     */

    int i;
    FILE *pgm;
    

    /* TODO: Dosyayi write kipinde acin. Acma basarisiz olursa fonksiyon
     * 1 dondurerek sonlanmalidir. */
    pgm = fopen(filename,"w");
    if (!pgm) return 1;

    /* TODO: Baslik yapisini fprintf() ile dosyaya yazin */
    fprintf(pgm,"%s\n%s\n%d %d\n%d\n",pgm_info.signature,pgm_info.comment, pgm_info.width,pgm_info.height,pgm_info.max_pixel_value);

    /* TODO: 2 farkli dosya bicimi, 2 farkli yazma bicimi */
    int size = (pgm_info.width)*(pgm_info.height);
    if (strcmp(pgm_info.signature,"P5") == 0) {  //BINARY
    	fwrite(pgm_info.pixels,sizeof(char),size,pgm);
    }
    else {
        for (i=0; i<size; i=i+1) {
    		fprintf(pgm,"%d\n",pgm_info.pixels[i]);  //ASCII
	}
    }

    
    /* Dosyayi kapatalim. */
    fclose(pgm);
    return 0;
}

