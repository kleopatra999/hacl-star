/* This file was auto-generated by KreMLin! */
#ifndef __Poly1305_64_H
#define __Poly1305_64_H

#include "kremlib.h"
#include "testlib.h"


typedef struct {
  uint64_t *x00;
  uint64_t *x01;
}
Hacl_Impl_Poly1305_64_poly1305_state;

void
Hacl_Impl_Poly1305_64_mac_blocks_init(
				      Hacl_Impl_Poly1305_64_poly1305_state st,
				      uint8_t *input,
				      uint64_t len,
				      uint8_t *k
				      );

void
Hacl_Impl_Poly1305_64_mac_blocks_continue(
					  Hacl_Impl_Poly1305_64_poly1305_state st,
					  uint8_t *input,
					  uint64_t len
					  );

void
Hacl_Impl_Poly1305_64_mac_blocks_finish(
					Hacl_Impl_Poly1305_64_poly1305_state st,
					uint8_t *output,
					uint8_t *input,
					uint64_t len,
					uint8_t *k
					);

#endif