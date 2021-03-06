#include "AEAD_Poly1305_64.h"

static Prims_nat Hacl_Spec_Bignum_Bigint_seval(void *b)
{
  return (Prims_nat )(void *)(uint8_t )0;
}

static Prims_nat Hacl_Spec_Poly1305_64_State_seval(void *x0)
{
  return Hacl_Spec_Bignum_Bigint_seval(x0);
}

static Prims_int Hacl_Spec_Poly1305_64_State_selem(void *s)
{
  return (Prims_int )(void *)(uint8_t )0;
}

inline static void Hacl_Bignum_Modulo_reduce(uint64_t *b)
{
  uint64_t b0 = b[0];
  b[0] = (b0 << (uint32_t )4) + (b0 << (uint32_t )2);
}

inline static void Hacl_Bignum_Modulo_carry_top(uint64_t *b)
{
  uint64_t b2 = b[2];
  uint64_t b0 = b[0];
  uint64_t b2_42 = b2 >> (uint32_t )42;
  b[2] = b2 & (uint64_t )0x3ffffffffff;
  b[0] = (b2_42 << (uint32_t )2) + b2_42 + b0;
}

inline static void Hacl_Bignum_Modulo_carry_top_wide(FStar_UInt128_t *b)
{
  FStar_UInt128_t b2 = b[2];
  FStar_UInt128_t b0 = b[0];
  FStar_UInt128_t b2_;
  FStar_UInt128_t ret0;
  FStar_Int_Cast_uint64_to_uint128((uint64_t )0x3ffffffffff, &ret0);
  FStar_UInt128_t s1 = ret0;
  FStar_UInt128_logand(&b2, &s1, &b2_);
  FStar_UInt128_t ret1;
  FStar_UInt128_shift_right(&b2, (uint32_t )42, &ret1);
  FStar_UInt128_t s0 = ret1;
  uint64_t b2_42 = FStar_Int_Cast_uint128_to_uint64(&s0);
  FStar_UInt128_t b0_;
  FStar_UInt128_t ret;
  FStar_Int_Cast_uint64_to_uint128((b2_42 << (uint32_t )2) + b2_42, &ret);
  FStar_UInt128_t s10 = ret;
  FStar_UInt128_add(&b0, &s10, &b0_);
  b[2] = b2_;
  b[0] = b0_;
}

inline static void
Hacl_Bignum_Fproduct_copy_from_wide_(uint64_t *output, FStar_UInt128_t *input)
{
  {
    FStar_UInt128_t uu____389 = input[0];
    uint64_t uu____388 = FStar_Int_Cast_uint128_to_uint64(&uu____389);
    output[0] = uu____388;
  }
  {
    FStar_UInt128_t uu____389 = input[1];
    uint64_t uu____388 = FStar_Int_Cast_uint128_to_uint64(&uu____389);
    output[1] = uu____388;
  }
  {
    FStar_UInt128_t uu____389 = input[2];
    uint64_t uu____388 = FStar_Int_Cast_uint128_to_uint64(&uu____389);
    output[2] = uu____388;
  }
}

inline static void Hacl_Bignum_Fproduct_shift(uint64_t *output)
{
  uint64_t tmp = output[2];
  {
    uint32_t ctr = (uint32_t )3 - (uint32_t )0 - (uint32_t )1;
    uint64_t z = output[ctr - (uint32_t )1];
    output[ctr] = z;
  }
  {
    uint32_t ctr = (uint32_t )3 - (uint32_t )1 - (uint32_t )1;
    uint64_t z = output[ctr - (uint32_t )1];
    output[ctr] = z;
  }
  output[0] = tmp;
}

inline static void
Hacl_Bignum_Fproduct_sum_scalar_multiplication_(
  FStar_UInt128_t *output,
  uint64_t *input,
  uint64_t s
)
{
  {
    FStar_UInt128_t uu____795 = output[0];
    uint64_t uu____798 = input[0];
    FStar_UInt128_t uu____794;
    FStar_UInt128_t ret;
    FStar_UInt128_mul_wide(uu____798, s, &ret);
    FStar_UInt128_t s1 = ret;
    FStar_UInt128_add_mod(&uu____795, &s1, &uu____794);
    output[0] = uu____794;
  }
  {
    FStar_UInt128_t uu____795 = output[1];
    uint64_t uu____798 = input[1];
    FStar_UInt128_t uu____794;
    FStar_UInt128_t ret;
    FStar_UInt128_mul_wide(uu____798, s, &ret);
    FStar_UInt128_t s1 = ret;
    FStar_UInt128_add_mod(&uu____795, &s1, &uu____794);
    output[1] = uu____794;
  }
  {
    FStar_UInt128_t uu____795 = output[2];
    uint64_t uu____798 = input[2];
    FStar_UInt128_t uu____794;
    FStar_UInt128_t ret;
    FStar_UInt128_mul_wide(uu____798, s, &ret);
    FStar_UInt128_t s1 = ret;
    FStar_UInt128_add_mod(&uu____795, &s1, &uu____794);
    output[2] = uu____794;
  }
}

inline static void Hacl_Bignum_Fproduct_carry_wide_(FStar_UInt128_t *tmp)
{
  {
    uint32_t ctr = (uint32_t )0;
    FStar_UInt128_t tctr = tmp[ctr];
    FStar_UInt128_t tctrp1 = tmp[ctr + (uint32_t )1];
    uint64_t
    r0 = FStar_Int_Cast_uint128_to_uint64(&tctr) & (((uint64_t )1 << (uint32_t )44) - (uint64_t )1);
    FStar_UInt128_t c;
    FStar_UInt128_shift_right(&tctr, (uint32_t )44, &c);
    FStar_Int_Cast_uint64_to_uint128(r0, &tmp[ctr]);
    FStar_UInt128_add(&tctrp1, &c, &tmp[ctr + (uint32_t )1]);
  }
  {
    uint32_t ctr = (uint32_t )1;
    FStar_UInt128_t tctr = tmp[ctr];
    FStar_UInt128_t tctrp1 = tmp[ctr + (uint32_t )1];
    uint64_t
    r0 = FStar_Int_Cast_uint128_to_uint64(&tctr) & (((uint64_t )1 << (uint32_t )44) - (uint64_t )1);
    FStar_UInt128_t c;
    FStar_UInt128_shift_right(&tctr, (uint32_t )44, &c);
    FStar_Int_Cast_uint64_to_uint128(r0, &tmp[ctr]);
    FStar_UInt128_add(&tctrp1, &c, &tmp[ctr + (uint32_t )1]);
  }
}

inline static void Hacl_Bignum_Fproduct_carry_limb_(uint64_t *tmp)
{
  {
    uint32_t ctr = (uint32_t )0;
    uint64_t tctr = tmp[ctr];
    uint64_t tctrp1 = tmp[ctr + (uint32_t )1];
    uint64_t r0 = tctr & (((uint64_t )1 << (uint32_t )44) - (uint64_t )1);
    uint64_t c = tctr >> (uint32_t )44;
    tmp[ctr] = r0;
    tmp[ctr + (uint32_t )1] = tctrp1 + c;
  }
  {
    uint32_t ctr = (uint32_t )1;
    uint64_t tctr = tmp[ctr];
    uint64_t tctrp1 = tmp[ctr + (uint32_t )1];
    uint64_t r0 = tctr & (((uint64_t )1 << (uint32_t )44) - (uint64_t )1);
    uint64_t c = tctr >> (uint32_t )44;
    tmp[ctr] = r0;
    tmp[ctr + (uint32_t )1] = tctrp1 + c;
  }
}

static uint64_t
*Hacl_Impl_Poly1305_64_State___proj__MkState__item__r(
  Hacl_Impl_Poly1305_64_State_poly1305_state *projectee
)
{
  Hacl_Impl_Poly1305_64_State_poly1305_state scrut = projectee[0];
  uint64_t *r = scrut.x00;
  return r;
}

static uint64_t
*Hacl_Impl_Poly1305_64_State___proj__MkState__item__h(
  Hacl_Impl_Poly1305_64_State_poly1305_state *projectee
)
{
  Hacl_Impl_Poly1305_64_State_poly1305_state scrut = projectee[0];
  uint64_t *h = scrut.x01;
  return h;
}

inline static void Hacl_Bignum_Fmul_shift_reduce(uint64_t *output)
{
  Hacl_Bignum_Fproduct_shift(output);
  Hacl_Bignum_Modulo_reduce(output);
  return;
}

static void
Hacl_Bignum_Fmul_mul_shift_reduce_(FStar_UInt128_t *output, uint64_t *input, uint64_t *input2)
{
  {
    uint32_t ctr = (uint32_t )3 - (uint32_t )0 - (uint32_t )1;
    uint32_t i1 = ctr;
    uint32_t j = (uint32_t )2 - i1;
    uint64_t input2i = input2[j];
    Hacl_Bignum_Fproduct_sum_scalar_multiplication_(output, input, input2i);
    if (ctr > (uint32_t )0)
      Hacl_Bignum_Fmul_shift_reduce(input);
  }
  {
    uint32_t ctr = (uint32_t )3 - (uint32_t )1 - (uint32_t )1;
    uint32_t i1 = ctr;
    uint32_t j = (uint32_t )2 - i1;
    uint64_t input2i = input2[j];
    Hacl_Bignum_Fproduct_sum_scalar_multiplication_(output, input, input2i);
    if (ctr > (uint32_t )0)
      Hacl_Bignum_Fmul_shift_reduce(input);
  }
  {
    uint32_t ctr = (uint32_t )3 - (uint32_t )2 - (uint32_t )1;
    uint32_t i1 = ctr;
    uint32_t j = (uint32_t )2 - i1;
    uint64_t input2i = input2[j];
    Hacl_Bignum_Fproduct_sum_scalar_multiplication_(output, input, input2i);
    if (ctr > (uint32_t )0)
      Hacl_Bignum_Fmul_shift_reduce(input);
  }
}

inline static void Hacl_Bignum_Fmul_fmul_(uint64_t *output, uint64_t *input, uint64_t *input2)
{
  FStar_UInt128_t ret;
  FStar_Int_Cast_uint64_to_uint128((uint64_t )0, &ret);
  KRML_CHECK_SIZE(ret, (uint32_t )3);
  FStar_UInt128_t t[3];
  for (uintmax_t _i = 0; _i < (uint32_t )3; ++_i)
    t[_i] = ret;
  Hacl_Bignum_Fmul_mul_shift_reduce_(t, input, input2);
  Hacl_Bignum_Fproduct_carry_wide_(t);
  Hacl_Bignum_Modulo_carry_top_wide(t);
  Hacl_Bignum_Fproduct_copy_from_wide_(output, t);
  uint64_t i0 = output[0];
  uint64_t i1 = output[1];
  uint64_t i0_ = i0 & (((uint64_t )1 << (uint32_t )44) - (uint64_t )1);
  uint64_t i1_ = i1 + (i0 >> (uint32_t )44);
  output[0] = i0_;
  output[1] = i1_;
}

inline static void Hacl_Bignum_Fmul_fmul(uint64_t *output, uint64_t *input, uint64_t *input2)
{
  uint64_t tmp[3] = { 0 };
  memcpy(tmp, input, (uint32_t )3 * sizeof input[0]);
  Hacl_Bignum_Fmul_fmul_(output, tmp, input2);
}

inline static void
Hacl_Bignum_AddAndMultiply_add_and_multiply(uint64_t *acc, uint64_t *block, uint64_t *r)
{
  {
    uint64_t uu____795 = acc[0];
    uint64_t uu____798 = block[0];
    uint64_t uu____794 = uu____795 + uu____798;
    acc[0] = uu____794;
  }
  {
    uint64_t uu____795 = acc[1];
    uint64_t uu____798 = block[1];
    uint64_t uu____794 = uu____795 + uu____798;
    acc[1] = uu____794;
  }
  {
    uint64_t uu____795 = acc[2];
    uint64_t uu____798 = block[2];
    uint64_t uu____794 = uu____795 + uu____798;
    acc[2] = uu____794;
  }
  Hacl_Bignum_Fmul_fmul(acc, acc, r);
  return;
}

inline static void
Hacl_Impl_Poly1305_64_poly1305_update(
  Hacl_Impl_Poly1305_64_State_poly1305_state *st,
  uint8_t *m
)
{
  uint64_t *acc = Hacl_Impl_Poly1305_64_State___proj__MkState__item__h(&st[0]);
  uint64_t *r = Hacl_Impl_Poly1305_64_State___proj__MkState__item__r(&st[0]);
  uint64_t tmp[3] = { 0 };
  FStar_UInt128_t m0;
  load128_le(m, &m0);
  uint64_t r0 = FStar_Int_Cast_uint128_to_uint64(&m0) & (uint64_t )0xfffffffffff;
  FStar_UInt128_t ret0;
  FStar_UInt128_shift_right(&m0, (uint32_t )44, &ret0);
  FStar_UInt128_t s0 = ret0;
  uint64_t r1 = FStar_Int_Cast_uint128_to_uint64(&s0) & (uint64_t )0xfffffffffff;
  FStar_UInt128_t ret;
  FStar_UInt128_shift_right(&m0, (uint32_t )88, &ret);
  FStar_UInt128_t s00 = ret;
  uint64_t r2 = FStar_Int_Cast_uint128_to_uint64(&s00);
  tmp[0] = r0;
  tmp[1] = r1;
  tmp[2] = r2;
  uint64_t b2 = tmp[2];
  uint64_t b2_ = (uint64_t )0x10000000000 | b2;
  tmp[2] = b2_;
  Hacl_Bignum_AddAndMultiply_add_and_multiply(acc, tmp, r);
}

inline static void
Hacl_Impl_Poly1305_64_poly1305_process_last_block_(
  uint8_t *block,
  Hacl_Impl_Poly1305_64_State_poly1305_state *st,
  uint8_t *m,
  uint64_t rem_
)
{
  uint64_t tmp[3] = { 0 };
  FStar_UInt128_t m0;
  load128_le(block, &m0);
  uint64_t r0 = FStar_Int_Cast_uint128_to_uint64(&m0) & (uint64_t )0xfffffffffff;
  FStar_UInt128_t ret0;
  FStar_UInt128_shift_right(&m0, (uint32_t )44, &ret0);
  FStar_UInt128_t s0 = ret0;
  uint64_t r1 = FStar_Int_Cast_uint128_to_uint64(&s0) & (uint64_t )0xfffffffffff;
  FStar_UInt128_t ret;
  FStar_UInt128_shift_right(&m0, (uint32_t )88, &ret);
  FStar_UInt128_t s00 = ret;
  uint64_t r2 = FStar_Int_Cast_uint128_to_uint64(&s00);
  tmp[0] = r0;
  tmp[1] = r1;
  tmp[2] = r2;
  Hacl_Bignum_AddAndMultiply_add_and_multiply(Hacl_Impl_Poly1305_64_State___proj__MkState__item__h(&st[0]),
    tmp,
    Hacl_Impl_Poly1305_64_State___proj__MkState__item__r(&st[0]));
}

inline static void
Hacl_Impl_Poly1305_64_poly1305_process_last_block(
  Hacl_Impl_Poly1305_64_State_poly1305_state *st,
  uint8_t *m,
  uint64_t rem_
)
{
  uint8_t zero1 = (uint8_t )0;
  KRML_CHECK_SIZE(zero1, (uint32_t )16);
  uint8_t block[16];
  for (uintmax_t _i = 0; _i < (uint32_t )16; ++_i)
    block[_i] = zero1;
  uint32_t i0 = (uint32_t )rem_;
  uint32_t i = (uint32_t )rem_;
  memcpy(block, m, i * sizeof m[0]);
  block[i0] = (uint8_t )1;
  Hacl_Impl_Poly1305_64_poly1305_process_last_block_(block, &st[0], m, rem_);
  return;
}

static void Hacl_Impl_Poly1305_64_poly1305_last_pass(uint64_t *acc)
{
  Hacl_Bignum_Fproduct_carry_limb_(acc);
  Hacl_Bignum_Modulo_carry_top(acc);
  uint64_t a0 = acc[0];
  uint64_t a10 = acc[1];
  uint64_t a20 = acc[2];
  uint64_t a0_ = a0 & (uint64_t )0xfffffffffff;
  uint64_t r0 = a0 >> (uint32_t )44;
  uint64_t a1_ = (a10 + r0) & (uint64_t )0xfffffffffff;
  uint64_t r1 = (a10 + r0) >> (uint32_t )44;
  uint64_t a2_ = a20 + r1;
  acc[0] = a0_;
  acc[1] = a1_;
  acc[2] = a2_;
  Hacl_Bignum_Modulo_carry_top(acc);
  uint64_t i0 = acc[0];
  uint64_t i1 = acc[1];
  uint64_t i0_ = i0 & (((uint64_t )1 << (uint32_t )44) - (uint64_t )1);
  uint64_t i1_ = i1 + (i0 >> (uint32_t )44);
  acc[0] = i0_;
  acc[1] = i1_;
  uint64_t a00 = acc[0];
  uint64_t a1 = acc[1];
  uint64_t a2 = acc[2];
  uint64_t mask0 = FStar_UInt64_gte_mask(a00, (uint64_t )0xffffffffffb);
  uint64_t mask1 = FStar_UInt64_eq_mask(a1, (uint64_t )0xfffffffffff);
  uint64_t mask2 = FStar_UInt64_eq_mask(a2, (uint64_t )0x3ffffffffff);
  uint64_t mask = mask0 & mask1 & mask2;
  uint64_t a0_0 = a00 - ((uint64_t )0xffffffffffb & mask);
  uint64_t a1_0 = a1 - ((uint64_t )0xfffffffffff & mask);
  uint64_t a2_0 = a2 - ((uint64_t )0x3ffffffffff & mask);
  acc[0] = a0_0;
  acc[1] = a1_0;
  acc[2] = a2_0;
}

static void
Hacl_Impl_Poly1305_64_mk_state(
  uint64_t *r,
  uint64_t *h,
  Hacl_Impl_Poly1305_64_State_poly1305_state *ret
)
{
  ret[0] = ((Hacl_Impl_Poly1305_64_State_poly1305_state ){ .x00 = r, .x01 = h });
}

static void
Hacl_Standalone_Poly1305_64_poly1305_blocks(
  Hacl_Impl_Poly1305_64_State_poly1305_state *st,
  uint8_t *m,
  uint64_t len1
)
{
  if (len1 == (uint64_t )0)
    return;
  else
  {
    uint8_t *block = m;
    uint8_t *tail1 = m + (uint32_t )16;
    Hacl_Impl_Poly1305_64_poly1305_update(&st[0], block);
    uint64_t len2 = len1 - (uint64_t )1;
    Hacl_Standalone_Poly1305_64_poly1305_blocks(&st[0], tail1, len2);
    return;
  }
}

static void
Hacl_Standalone_Poly1305_64_poly1305_partial(
  Hacl_Impl_Poly1305_64_State_poly1305_state *st,
  uint8_t *input,
  uint64_t len1,
  uint8_t *kr
)
{
  uint64_t *x0 = Hacl_Impl_Poly1305_64_State___proj__MkState__item__r(&st[0]);
  uint8_t *x1 = kr;
  FStar_UInt128_t k1;
  load128_le(x1, &k1);
  FStar_UInt128_t k_clamped;
  FStar_UInt128_t ret0;
  FStar_UInt128_t ret1;
  FStar_Int_Cast_uint64_to_uint128((uint64_t )0x0ffffffc0fffffff, &ret1);
  FStar_UInt128_t s1 = ret1;
  FStar_UInt128_t ret2;
  FStar_UInt128_t ret3;
  FStar_Int_Cast_uint64_to_uint128((uint64_t )0x0ffffffc0ffffffc, &ret3);
  FStar_UInt128_t s0 = ret3;
  FStar_UInt128_shift_left(&s0, (uint32_t )64, &ret2);
  FStar_UInt128_t s00 = ret2;
  FStar_UInt128_logor(&s00, &s1, &ret0);
  FStar_UInt128_t s10 = ret0;
  FStar_UInt128_logand(&k1, &s10, &k_clamped);
  uint64_t r0 = FStar_Int_Cast_uint128_to_uint64(&k_clamped) & (uint64_t )0xfffffffffff;
  FStar_UInt128_t ret4;
  FStar_UInt128_shift_right(&k_clamped, (uint32_t )44, &ret4);
  FStar_UInt128_t s01 = ret4;
  uint64_t r1 = FStar_Int_Cast_uint128_to_uint64(&s01) & (uint64_t )0xfffffffffff;
  FStar_UInt128_t ret;
  FStar_UInt128_shift_right(&k_clamped, (uint32_t )88, &ret);
  FStar_UInt128_t s02 = ret;
  uint64_t r2 = FStar_Int_Cast_uint128_to_uint64(&s02);
  x0[0] = r0;
  x0[1] = r1;
  x0[2] = r2;
  uint64_t *x00 = Hacl_Impl_Poly1305_64_State___proj__MkState__item__h(&st[0]);
  x00[0] = (uint64_t )0;
  x00[1] = (uint64_t )0;
  x00[2] = (uint64_t )0;
  Hacl_Standalone_Poly1305_64_poly1305_blocks(&st[0], input, len1);
  return;
}

Prims_nat AEAD_Poly1305_64_seval(void *x0)
{
  return Hacl_Spec_Poly1305_64_State_seval(x0);
}

Prims_int AEAD_Poly1305_64_selem(void *x0)
{
  return Hacl_Spec_Poly1305_64_State_selem(x0);
}

void
AEAD_Poly1305_64_mk_state(
  uint64_t *r,
  uint64_t *acc,
  Hacl_Impl_Poly1305_64_State_poly1305_state *ret
)
{
  Hacl_Impl_Poly1305_64_State_poly1305_state ret0;
  Hacl_Impl_Poly1305_64_mk_state(r, acc, &ret0);
  ret[0] = ret0;
}

uint32_t AEAD_Poly1305_64_mul_div_16(uint32_t len1)
{
  return (uint32_t )16 * (len1 >> (uint32_t )4);
}

void
AEAD_Poly1305_64_pad_last(
  Hacl_Impl_Poly1305_64_State_poly1305_state *st,
  uint8_t *input,
  uint32_t len1
)
{
  void *ite;
  uint8_t b[16];
  if (len1 == (uint32_t )0)
    ite = (void *)(uint8_t )0;
  else
  {
    memset(b, 0, (uint32_t )16 * sizeof b[0]);
    memcpy(b, input, len1 * sizeof input[0]);
    uint8_t *b0 = b;
    Hacl_Impl_Poly1305_64_poly1305_update(&st[0], b0);
    ite = (void *)(uint8_t )0;
  }
  return;
}

void
AEAD_Poly1305_64_poly1305_blocks_init(
  Hacl_Impl_Poly1305_64_State_poly1305_state *st,
  uint8_t *input,
  uint32_t len1,
  uint8_t *k1
)
{
  uint32_t len_16 = len1 >> (uint32_t )4;
  uint32_t rem_16 = len1 & (uint32_t )15;
  uint8_t *kr = k1;
  uint32_t len_ = (uint32_t )16 * (len1 >> (uint32_t )4);
  uint8_t *part_input = input;
  uint8_t *last_block = input + len_;
  Hacl_Standalone_Poly1305_64_poly1305_partial(&st[0], part_input, (uint64_t )len_16, kr);
  AEAD_Poly1305_64_pad_last(&st[0], last_block, rem_16);
  return;
}

void
AEAD_Poly1305_64_poly1305_blocks_continue(
  Hacl_Impl_Poly1305_64_State_poly1305_state *st,
  uint8_t *input,
  uint32_t len1
)
{
  uint32_t len_16 = len1 >> (uint32_t )4;
  uint32_t rem_16 = len1 & (uint32_t )15;
  uint32_t len_ = (uint32_t )16 * (len1 >> (uint32_t )4);
  uint8_t *part_input = input;
  uint8_t *last_block = input + len_;
  Hacl_Standalone_Poly1305_64_poly1305_blocks(&st[0], part_input, (uint64_t )len_16);
  AEAD_Poly1305_64_pad_last(&st[0], last_block, rem_16);
  return;
}

void
AEAD_Poly1305_64_poly1305_blocks_finish_(
  Hacl_Impl_Poly1305_64_State_poly1305_state *st,
  uint8_t *input
)
{
  Hacl_Impl_Poly1305_64_poly1305_update(&st[0], input);
  uint8_t *x2 = input + (uint32_t )16;
  if ((uint64_t )0 == (uint64_t )0)
  {
    
  }
  else
    Hacl_Impl_Poly1305_64_poly1305_process_last_block(&st[0], x2, (uint64_t )0);
  uint64_t *acc = Hacl_Impl_Poly1305_64_State___proj__MkState__item__h(&st[0]);
  Hacl_Impl_Poly1305_64_poly1305_last_pass(acc);
  return;
}

void
AEAD_Poly1305_64_poly1305_blocks_finish(
  Hacl_Impl_Poly1305_64_State_poly1305_state *st,
  uint8_t *input,
  uint8_t *mac,
  uint8_t *key_s
)
{
  Hacl_Impl_Poly1305_64_poly1305_update(&st[0], input);
  uint8_t *x2 = input + (uint32_t )16;
  if ((uint64_t )0 == (uint64_t )0)
  {
    
  }
  else
    Hacl_Impl_Poly1305_64_poly1305_process_last_block(&st[0], x2, (uint64_t )0);
  uint64_t *acc = Hacl_Impl_Poly1305_64_State___proj__MkState__item__h(&st[0]);
  Hacl_Impl_Poly1305_64_poly1305_last_pass(acc);
  uint64_t *acc0 = Hacl_Impl_Poly1305_64_State___proj__MkState__item__h(&st[0]);
  FStar_UInt128_t k_;
  load128_le(key_s, &k_);
  uint64_t h0 = acc0[0];
  uint64_t h1 = acc0[1];
  uint64_t h2 = acc0[2];
  FStar_UInt128_t ret0;
  FStar_UInt128_t ret1;
  FStar_Int_Cast_uint64_to_uint128(h1 << (uint32_t )44 | h0, &ret1);
  FStar_UInt128_t s1 = ret1;
  FStar_UInt128_t ret2;
  FStar_UInt128_t ret;
  FStar_Int_Cast_uint64_to_uint128(h2 << (uint32_t )24 | h1 >> (uint32_t )20, &ret);
  FStar_UInt128_t s0 = ret;
  FStar_UInt128_shift_left(&s0, (uint32_t )64, &ret2);
  FStar_UInt128_t s00 = ret2;
  FStar_UInt128_logor(&s00, &s1, &ret0);
  FStar_UInt128_t acc_ = ret0;
  FStar_UInt128_t mac_;
  FStar_UInt128_add_mod(&acc_, &k_, &mac_);
  store128_le(mac, &mac_);
  return;
}

