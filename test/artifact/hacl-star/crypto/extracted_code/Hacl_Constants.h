/* This file auto-generated by KreMLin! */
#ifndef __Hacl_Constants_H
#define __Hacl_Constants_H


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
#include "FStar_Buffer.h"
#include "FStar_Buffer_Quantifiers.h"
#include "Hacl_EC_Curve25519_Parameters.h"
#include "Hacl_EC_Curve25519_Bigint.h"
#include "Hacl_EC_Curve25519_Utils.h"
#include "Hacl_EC_Curve25519_Bignum_Fproduct.h"
#include "Hacl_EC_Curve25519_Bignum_Fscalar.h"
#include "Hacl_EC_Curve25519_Bignum_Fdifference.h"
#include "Hacl_EC_Curve25519_Bignum_Fsum.h"
#include "Hacl_EC_Curve25519_Bignum_Modulo.h"
#include "Hacl_EC_Curve25519_Bignum.h"
#include "Hacl_EC_Curve25519_PPoint.h"
#include "Hacl_EC_Curve25519_AddAndDouble.h"
#include "Hacl_UInt16.h"
#include "Hacl_Types.h"
#include "Hacl_Symmetric_Poly1305_64_Parameters.h"
#include "Hacl_Symmetric_Poly1305_64_Bigint.h"
#include "Hacl_Symmetric_HSalsa20.h"
#include "Hacl_Symmetric_Poly1305_64.h"
#include "Hacl_Symmetric_Salsa20.h"
#include "Hacl_Policies.h"
#include "kremlib.h"

typedef uint8_t Hacl_Constants_u8;

typedef uint32_t Hacl_Constants_u32;

typedef uint64_t Hacl_Constants_u64;

typedef uint8_t Hacl_Constants_h8;

typedef uint32_t Hacl_Constants_h32;

typedef uint64_t Hacl_Constants_h64;

typedef uint8_t *Hacl_Constants_uint8_p;

extern Prims_int Hacl_Constants_crypto_box_NONCEBYTES;

extern Prims_int Hacl_Constants_crypto_box_PUBLICKEYBYTES;

extern Prims_int Hacl_Constants_crypto_box_SECRETKEYBYTES;

extern Prims_int Hacl_Constants_crypto_box_MACBYTES;

extern Prims_int Hacl_Constants_crypto_secretbox_NONCEBYTES;

extern Prims_int Hacl_Constants_crypto_secretbox_KEYBYTES;

extern Prims_int Hacl_Constants_crypto_secretbox_MACBYTES;
#endif