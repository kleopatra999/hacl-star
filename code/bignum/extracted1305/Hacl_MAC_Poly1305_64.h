/* This file auto-generated by KreMLin! */
#ifndef __Hacl_MAC_Poly1305_64_H
#define __Hacl_MAC_Poly1305_64_H


#include "Prims.h"
#include "FStar_Mul.h"
#include "FStar_Squash.h"
#include "FStar_StrongExcludedMiddle.h"
#include "FStar_List_Tot.h"
#include "FStar_Classical.h"
#include "FStar_ListProperties.h"
#include "FStar_SeqProperties.h"
#include "FStar_Math_Lemmas.h"
#include "FStar_BitVector.h"
#include "FStar_UInt.h"
#include "FStar_Int.h"
#include "FStar_FunctionalExtensionality.h"
#include "FStar_PropositionalExtensionality.h"
#include "FStar_PredicateExtensionality.h"
#include "FStar_TSet.h"
#include "FStar_Set.h"
#include "FStar_Map.h"
#include "FStar_Ghost.h"
#include "FStar_All.h"
#include "Hacl_UInt64.h"
#include "Hacl_UInt128.h"
#include "Hacl_UInt32.h"
#include "Hacl_UInt8.h"
#include "Hacl_Cast.h"
#include "Hacl_Bignum_Constants.h"
#include "FStar_Buffer.h"
#include "Hacl_Bignum_Parameters.h"
#include "Hacl_Bignum_Limb.h"
#include "Hacl_Bignum_Wide.h"
#include "Hacl_Bignum_Bigint.h"
#include "Hacl_Bignum_Fsum_Spec.h"
#include "Hacl_Bignum_Fsum.h"
#include "Hacl_Bignum_Fproduct_Spec.h"
#include "Hacl_Bignum_Fmul_Lemmas.h"
#include "Hacl_Bignum_Modulo.h"
#include "Hacl_Bignum_Fproduct.h"
#include "Hacl_Bignum_Fmul_Spec.h"
#include "Hacl_Bignum_Fmul.h"
#include "kremlib.h"
#include "testlib.h"

typedef void *Hacl_MAC_Poly1305_64_log_t;

typedef uint64_t *Hacl_MAC_Poly1305_64_bigint;

typedef uint8_t *Hacl_MAC_Poly1305_64_uint8_p;

typedef uint64_t *Hacl_MAC_Poly1305_64_elemB;

typedef uint8_t *Hacl_MAC_Poly1305_64_wordB;

typedef uint8_t *Hacl_MAC_Poly1305_64_wordB_16;

typedef struct {
  uint64_t *x00;
  uint64_t *x01;
}
Hacl_MAC_Poly1305_64_poly1305_state;

uint64_t
*Hacl_MAC_Poly1305_64___proj__MkState__item__r(Hacl_MAC_Poly1305_64_poly1305_state projectee);

uint64_t
*Hacl_MAC_Poly1305_64___proj__MkState__item__h(Hacl_MAC_Poly1305_64_poly1305_state projectee);

uint64_t Hacl_MAC_Poly1305_64_load64_le(uint8_t *b);

void Hacl_MAC_Poly1305_64_store64_le(uint8_t *b, uint64_t z);

void *Hacl_MAC_Poly1305_64_sel_word(FStar_HyperStack_mem h, uint8_t *b);

Prims_nat Hacl_MAC_Poly1305_64_sel_int(FStar_HyperStack_mem h, uint64_t *b);

typedef uint64_t Hacl_MAC_Poly1305_64_limb_44;

typedef uint64_t Hacl_MAC_Poly1305_64_limb_45;

typedef uint64_t Hacl_MAC_Poly1305_64_limb_44_20;

uint64_t Hacl_MAC_Poly1305_64_mk_mask(uint32_t nbits);

void Hacl_MAC_Poly1305_64_poly1305_encode_r(uint64_t *r, uint8_t *key);

void Hacl_MAC_Poly1305_64_toField(uint64_t *b, uint8_t *m);

void Hacl_MAC_Poly1305_64_toField_plus_2_128(uint64_t *b, uint8_t *m);

void Hacl_MAC_Poly1305_64_toField_plus(uint32_t len, uint64_t *b, uint8_t *m_);

void Hacl_MAC_Poly1305_64_add_and_multiply(uint64_t *acc, uint64_t *block, uint64_t *r);

void Hacl_MAC_Poly1305_64_poly1305_finish(uint8_t *mac, uint64_t *acc, uint8_t *key_s);

void Hacl_MAC_Poly1305_64_poly1305_start(uint64_t *a);

void Hacl_MAC_Poly1305_64_poly1305_init(uint64_t *r, uint8_t *s, uint8_t *key);

void Hacl_MAC_Poly1305_64_poly1305_init_(Hacl_MAC_Poly1305_64_poly1305_state st, uint8_t *key);

void
Hacl_MAC_Poly1305_64_poly1305_update(
  void *log,
  Hacl_MAC_Poly1305_64_poly1305_state st,
  uint8_t *m
);

void
Hacl_MAC_Poly1305_64_poly1305_blocks(
  void *log,
  Hacl_MAC_Poly1305_64_poly1305_state st,
  uint8_t *m,
  uint64_t len
);

void
Hacl_MAC_Poly1305_64_poly1305_finish_(
  void *log,
  Hacl_MAC_Poly1305_64_poly1305_state st,
  uint8_t *mac,
  uint8_t *m,
  uint64_t len,
  uint8_t *key_s
);

void
Hacl_MAC_Poly1305_64_crypto_onetimeauth(
  uint8_t *output,
  uint8_t *input,
  uint64_t len,
  uint8_t *k
);
#endif