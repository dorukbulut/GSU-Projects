#ifndef _EFFECTS_H_
#define _EFFECTS_H_

/* Efekt fonksiyonlari icin bildirimler */

void effect_invert(unsigned char *pixels, int width, int height);
void effect_threshold(unsigned char *pixels, int width, int height, int threshold);
void effect_random_noise(unsigned char *pixels, int width, int height);
void swap_position(unsigned char* pixels,int index1,int index2);
void effect_mirror(unsigned char* pixels,int width,int height);
void effect_turn_90 (unsigned char *pixels, int width, int height);

#endif

