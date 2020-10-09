
#ifndef _RC4_H_
#define _RC4_H_

typedef struct rc4_state {
   unsigned char buffer[256];
   unsigned char x;
   unsigned char y; 
} rc4_state_t;

void rc4_init(rc4_state_t *state, const unsigned char *key, unsigned int keylen);
void rc4_encrypt(rc4_state_t *state, const unsigned char *in, unsigned char *out, unsigned long len);
void rc4_encrypt_skip(rc4_state_t *state, const unsigned char *in, unsigned char *out, unsigned long len, unsigned long skip);

#endif /* _RC4_H_ */