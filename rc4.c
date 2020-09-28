
#include "rc4.h"

void rc4_init(rc4_state_t *state, const unsigned char *key, unsigned int keylen)
{
   unsigned char j;
   unsigned char tmp;
   int i;
   
   for (i = 0; i < 256; i++)
       state->buffer[i] = i;
   state->x = 0;
   state->y = 0;

   if (keylen > 0) { /* 0 modulo 0 is undefined anyway. */
       for (i = j = 0; i < 256; i++) {
           j += state->buffer[i] + key[i%keylen];           
           tmp = state->buffer[i];
           state->buffer[i] = state->buffer[j];
           state->buffer[j] = tmp;   
       }      
   }

}

void rc4_encrypt(rc4_state_t *state, const unsigned char *in, unsigned char *out, unsigned long len)
{
   register unsigned char x, y;
   register unsigned char tmp;
   register unsigned char k; /* Keystream. */
   unsigned long i;

   x = state->x;
   y = state->y;

   for (i = 0; i < len; i++) {
       x++;
       y += state->buffer[x];
       tmp = state->buffer[x];
       state->buffer[x] = state->buffer[y]; 
       state->buffer[y] = tmp;
       k = state->buffer[(state->buffer[x] + state->buffer[y]) & 0xff];
       out[i] = in[i] ^ k; 
   }      
 
   state->x = x;
   state->y = y;

}


void rc4_encrypt_skip(rc4_state_t *state, const unsigned char *in, unsigned char *out, unsigned long len, unsigned long skip)
{
   register unsigned char x, y;
   register unsigned char tmp;
   register unsigned char k; /* Keystream. */
   unsigned long i;

   x = state->x;
   y = state->y;

   for (i = 0; i < skip; i++) {
       x++;
       y += state->buffer[x];
       tmp = state->buffer[x];
       state->buffer[x] = state->buffer[y]; 
       state->buffer[y] = tmp;
   } 
 
   for (i = 0; i < len; i++) {
       x++;
       y += state->buffer[x];
       tmp = state->buffer[x];
       state->buffer[x] = state->buffer[y]; 
       state->buffer[y] = tmp;
       k= state->buffer[(state->buffer[x] + state->buffer[y]) & 0xff];
       out[i] = in[i] ^ k; 
   }      


   state->x = x;
   state->y = y;

}


