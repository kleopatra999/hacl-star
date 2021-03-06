module Spec.SHA256

open FStar.Mul
open FStar.Seq
open FStar.UInt32

open Spec.Loops
open Spec.Lib

#set-options "--max_fuel 0 --z3rlimit 25"

let uint32_t = t
let uint32x16 = b:seq uint32_t{length b = 16}
let uint32x8  = b:seq uint32_t{length b = 8}

let op_Greater_Greater_Greater (a:uint32_t) (s:uint32_t{v s<32}) =
  ((a >>^ s) |^ (a <<^ (32ul -^ s)))

(* [FIPS 180-4] section 4.1.2 *)
let _Ch x y z = (x &^ y) ^^ ((lognot x) &^ z)
let _Maj x y z = (x &^ y) ^^ ((x &^ z) ^^ (y &^ z))
let _Sigma0 x = (x >>> 2ul) ^^ ((x >>> 13ul) ^^ (x >>> 22ul))
let _Sigma1 x = (x >>> 6ul) ^^ ((x >>> 11ul) ^^ (x >>> 25ul))
let _sigma0 x = (x >>> 7ul) ^^ ((x >>> 18ul) ^^ (x >>^ 3ul))
let _sigma1 x = (x >>> 17ul) ^^ ((x >>> 19ul) ^^ (x >>^ 10ul))

let k : k:seq uint32_t{length k = 64} =
  Seq.Create.create_64
  0x428a2f98ul 0x71374491ul 0xb5c0fbcful 0xe9b5dba5ul
  0x3956c25bul 0x59f111f1ul 0x923f82a4ul 0xab1c5ed5ul
  0xd807aa98ul 0x12835b01ul 0x243185beul 0x550c7dc3ul
  0x72be5d74ul 0x80deb1feul 0x9bdc06a7ul 0xc19bf174ul
  0xe49b69c1ul 0xefbe4786ul 0x0fc19dc6ul 0x240ca1ccul
  0x2de92c6ful 0x4a7484aaul 0x5cb0a9dcul 0x76f988daul
  0x983e5152ul 0xa831c66dul 0xb00327c8ul 0xbf597fc7ul
  0xc6e00bf3ul 0xd5a79147ul 0x06ca6351ul 0x14292967ul
  0x27b70a85ul 0x2e1b2138ul 0x4d2c6dfcul 0x53380d13ul
  0x650a7354ul 0x766a0abbul 0x81c2c92eul 0x92722c85ul
  0xa2bfe8a1ul 0xa81a664bul 0xc24b8b70ul 0xc76c51a3ul
  0xd192e819ul 0xd6990624ul 0xf40e3585ul 0x106aa070ul
  0x19a4c116ul 0x1e376c08ul 0x2748774cul 0x34b0bcb5ul
  0x391c0cb3ul 0x4ed8aa4aul 0x5b9cca4ful 0x682e6ff3ul
  0x748f82eeul 0x78a5636ful 0x84c87814ul 0x8cc70208ul
  0x90befffaul 0xa4506cebul 0xbef9a3f7ul 0xc67178f2ul

let h_0 : h0:seq uint32_t{length h0 = 8} =
  Seq.Create.create_8
  0x6a09e667ul 0xbb67ae85ul 0x3c6ef372ul 0xa54ff53aul
  0x510e527ful 0x9b05688cul 0x1f83d9abul 0x5be0cd19ul

let rec ws (b:uint32x16) (t:nat{t < 64}) =
  if t < 16 then b.[t]
  else
    let t16 = ws b (t - 16) in
    let t15 = ws b (t - 15) in
    let t7  = ws b (t - 7) in
    let t2  = ws b (t - 2) in
    let s1 = _sigma1 t2 in
    let s0 = _sigma0 t15 in
    (s1 +%^ (t7 +%^ (s0 +%^ t16)))

let shuffle_core (block:uint32x16) (hash:uint32x8) (t:nat{t < 64}) : Tot uint32x8 =
  let a = hash.[0] in
  let b = hash.[1] in
  let c = hash.[2] in
  let d = hash.[3] in
  let e = hash.[4] in
  let f = hash.[5] in
  let g = hash.[6] in
  let h = hash.[7] in
  let t1:uint32_t = h +%^ (_Sigma1 e) +%^ (_Ch e f g) +%^ k.[t] +%^ ws block t in
  let t2 = (_Sigma0 a) +%^ (_Maj a b c) in
  Seq.Create.create_8 #uint32_t (t1 +%^ t2) a b c (d +%^ t1) e f g

let shuffle (hash:uint32x8) (block:uint32x16) =
  Spec.Loops.repeat_range_spec 0 64 (shuffle_core block) hash

let update (hash:uint32x8) (block:bytes{length block = 64}) : Tot uint32x8 =
  let b = uint32s_from_be 16 block in
  let hash_1 = shuffle hash b in
  Spec.Lib.map2 (fun x y -> x +%^ y) hash hash_1

let rec update_multi (hash:uint32x8) (blocks:bytes{length blocks % 64 = 0}) : Tot uint32x8 (decreases (Seq.length blocks)) =
  if Seq.length blocks = 0 then hash
  else
    let (block,rem) = Seq.split blocks 64 in
    let hash = update hash block in
    update_multi hash rem

let pad0_length (len:nat) : Tot (n:nat{(len + 1 + n + 8) % 64 = 0}) =
  (64 - ((len + 8 + 1) % 64)) % 64

let pad (prevlen:nat{prevlen % 64 = 0}) (len:nat{prevlen + len < pow2 61}) : Tot (b:bytes{(length b + len) % 64 = 0}) =
  assert_norm(pow2 61 = 0x2000000000000000);
  let tlen = prevlen + len in
  let firstbyte = Seq.create 1 0x80uy in
  let zeros = Seq.create (pad0_length len) 0uy in
  let encodedlen = Endianness.big_bytes 8ul (tlen * 8) in
  firstbyte @| zeros @| encodedlen

let update_last (hash:uint32x8) (prevlen:nat{prevlen % 64 = 0}) (input:bytes{(Seq.length input) + prevlen < pow2 61}) : Tot uint32x8 =
  assert_norm(pow2 61 > pow2 32);
  let blocks = pad prevlen (Seq.length input) in
  update_multi hash (input @| blocks)

let finish (hashw:uint32x8) : Tot (hash:bytes{length hash = 32}) = uint32s_to_be 8 hashw

let hash (input:bytes{Seq.length input < pow2 61}) : Tot (hash:bytes{length hash = 32}) =
  let n = Seq.length input / 64 in
  let (bs,l) = Seq.split input (n * 64) in
  let hash = update_multi h_0 bs in
  let hash = update_last hash (n * 64) l in
  finish hash


//
// Test 1
//

let test_plaintext1 = [
  0x61uy; 0x62uy; 0x63uy;
]

let test_expected1 = [
  0xbauy; 0x78uy; 0x16uy; 0xbfuy; 0x8fuy; 0x01uy; 0xcfuy; 0xeauy;
  0x41uy; 0x41uy; 0x40uy; 0xdeuy; 0x5duy; 0xaeuy; 0x22uy; 0x23uy;
  0xb0uy; 0x03uy; 0x61uy; 0xa3uy; 0x96uy; 0x17uy; 0x7auy; 0x9cuy;
  0xb4uy; 0x10uy; 0xffuy; 0x61uy; 0xf2uy; 0x00uy; 0x15uy; 0xaduy
]

//
// Test 2
//

let test_plaintext2 = []

let test_expected2 = [
  0xe3uy; 0xb0uy; 0xc4uy; 0x42uy; 0x98uy; 0xfcuy; 0x1cuy; 0x14uy;
  0x9auy; 0xfbuy; 0xf4uy; 0xc8uy; 0x99uy; 0x6fuy; 0xb9uy; 0x24uy;
  0x27uy; 0xaeuy; 0x41uy; 0xe4uy; 0x64uy; 0x9buy; 0x93uy; 0x4cuy;
  0xa4uy; 0x95uy; 0x99uy; 0x1buy; 0x78uy; 0x52uy; 0xb8uy; 0x55uy
]

//
// Test 3
//

let test_plaintext3 = [
  0x61uy; 0x62uy; 0x63uy; 0x64uy; 0x62uy; 0x63uy; 0x64uy; 0x65uy;
  0x63uy; 0x64uy; 0x65uy; 0x66uy; 0x64uy; 0x65uy; 0x66uy; 0x67uy;
  0x65uy; 0x66uy; 0x67uy; 0x68uy; 0x66uy; 0x67uy; 0x68uy; 0x69uy;
  0x67uy; 0x68uy; 0x69uy; 0x6auy; 0x68uy; 0x69uy; 0x6auy; 0x6buy;
  0x69uy; 0x6auy; 0x6buy; 0x6cuy; 0x6auy; 0x6buy; 0x6cuy; 0x6duy;
  0x6buy; 0x6cuy; 0x6duy; 0x6euy; 0x6cuy; 0x6duy; 0x6euy; 0x6fuy;
  0x6duy; 0x6euy; 0x6fuy; 0x70uy; 0x6euy; 0x6fuy; 0x70uy; 0x71uy
]

let test_expected3 = [
  0x24uy; 0x8duy; 0x6auy; 0x61uy; 0xd2uy; 0x06uy; 0x38uy; 0xb8uy;
  0xe5uy; 0xc0uy; 0x26uy; 0x93uy; 0x0cuy; 0x3euy; 0x60uy; 0x39uy;
  0xa3uy; 0x3cuy; 0xe4uy; 0x59uy; 0x64uy; 0xffuy; 0x21uy; 0x67uy;
  0xf6uy; 0xecuy; 0xeduy; 0xd4uy; 0x19uy; 0xdbuy; 0x06uy; 0xc1uy
]


//
// Test 4
//

let test_plaintext4 = [
  0x61uy; 0x62uy; 0x63uy; 0x64uy; 0x65uy; 0x66uy; 0x67uy; 0x68uy;
  0x62uy; 0x63uy; 0x64uy; 0x65uy; 0x66uy; 0x67uy; 0x68uy; 0x69uy;
  0x63uy; 0x64uy; 0x65uy; 0x66uy; 0x67uy; 0x68uy; 0x69uy; 0x6auy;
  0x64uy; 0x65uy; 0x66uy; 0x67uy; 0x68uy; 0x69uy; 0x6auy; 0x6buy;
  0x65uy; 0x66uy; 0x67uy; 0x68uy; 0x69uy; 0x6auy; 0x6buy; 0x6cuy;
  0x66uy; 0x67uy; 0x68uy; 0x69uy; 0x6auy; 0x6buy; 0x6cuy; 0x6duy;
  0x67uy; 0x68uy; 0x69uy; 0x6auy; 0x6buy; 0x6cuy; 0x6duy; 0x6euy;
  0x68uy; 0x69uy; 0x6auy; 0x6buy; 0x6cuy; 0x6duy; 0x6euy; 0x6fuy;
  0x69uy; 0x6auy; 0x6buy; 0x6cuy; 0x6duy; 0x6euy; 0x6fuy; 0x70uy;
  0x6auy; 0x6buy; 0x6cuy; 0x6duy; 0x6euy; 0x6fuy; 0x70uy; 0x71uy;
  0x6buy; 0x6cuy; 0x6duy; 0x6euy; 0x6fuy; 0x70uy; 0x71uy; 0x72uy;
  0x6cuy; 0x6duy; 0x6euy; 0x6fuy; 0x70uy; 0x71uy; 0x72uy; 0x73uy;
  0x6duy; 0x6euy; 0x6fuy; 0x70uy; 0x71uy; 0x72uy; 0x73uy; 0x74uy;
  0x6euy; 0x6fuy; 0x70uy; 0x71uy; 0x72uy; 0x73uy; 0x74uy; 0x75uy
]

let test_expected4 = [
  0xcfuy; 0x5buy; 0x16uy; 0xa7uy; 0x78uy; 0xafuy; 0x83uy; 0x80uy;
  0x03uy; 0x6cuy; 0xe5uy; 0x9euy; 0x7buy; 0x04uy; 0x92uy; 0x37uy;
  0x0buy; 0x24uy; 0x9buy; 0x11uy; 0xe8uy; 0xf0uy; 0x7auy; 0x51uy;
  0xafuy; 0xacuy; 0x45uy; 0x03uy; 0x7auy; 0xfeuy; 0xe9uy; 0xd1uy
]

//
// Test 5
//

let test_expected5 = [
  0xcduy; 0xc7uy; 0x6euy; 0x5cuy; 0x99uy; 0x14uy; 0xfbuy; 0x92uy;
  0x81uy; 0xa1uy; 0xc7uy; 0xe2uy; 0x84uy; 0xd7uy; 0x3euy; 0x67uy;
  0xf1uy; 0x80uy; 0x9auy; 0x48uy; 0xa4uy; 0x97uy; 0x20uy; 0x0euy;
  0x04uy; 0x6duy; 0x39uy; 0xccuy; 0xc7uy; 0x11uy; 0x2cuy; 0xd0uy
]


//
// Main
//

let test () =
  assert_norm(List.Tot.length test_plaintext1 = 3);
  assert_norm(List.Tot.length test_expected1 = 32);
  assert_norm(List.Tot.length test_expected2 = 32);
  assert_norm(List.Tot.length test_plaintext3 = 56);
  assert_norm(List.Tot.length test_expected3 = 32);
  assert_norm(List.Tot.length test_plaintext4 = 112);
  assert_norm(List.Tot.length test_expected4 = 32);
  assert_norm(List.Tot.length test_expected5 = 32);
  let test_plaintext1 = createL test_plaintext1 in
  let test_expected1 = createL test_expected1 in
  let test_plaintext2 = createL test_plaintext2 in
  let test_expected2 = createL test_expected2 in
  let test_plaintext3 = createL test_plaintext3 in
  let test_expected3 = createL test_expected3 in
  let test_plaintext4 = createL test_plaintext4 in
  let test_expected4 = createL test_expected4 in
  (hash test_plaintext1 = test_expected1) &&
  (hash test_plaintext2 = test_expected2) &&
  (hash test_plaintext3 = test_expected3) &&
  (hash test_plaintext4 = test_expected4)
