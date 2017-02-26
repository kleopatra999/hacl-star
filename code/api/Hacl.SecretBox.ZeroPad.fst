module Hacl.SecretBox.ZeroPad

open FStar.Buffer
open FStar.ST
open Hacl.Constants
open Hacl.Policies
open Hacl.Cast

(* Module abbreviations *)
module HS  = FStar.HyperStack
module B   = FStar.Buffer
module U8  = FStar.UInt8
module U32 = FStar.UInt32
module U64 = FStar.UInt64
module H8  = Hacl.UInt8
module H32 = Hacl.UInt32
module H64 = Hacl.UInt64

private val set_zero_bytes:
  b:uint8_p{length b >= 32} ->
  Stack unit
    (requires (fun h -> live h b))
    (ensures  (fun h0 _ h1 -> live h1 b /\ modifies_1 b h0 h1))
let set_zero_bytes b =
  let zero = uint8_to_sint8 0uy in
  b.(0ul)  <- zero; b.(1ul)  <- zero; b.(2ul)  <- zero; b.(3ul)  <- zero;
  b.(4ul)  <- zero; b.(5ul)  <- zero; b.(6ul)  <- zero; b.(7ul)  <- zero;
  b.(8ul)  <- zero; b.(9ul)  <- zero; b.(10ul) <- zero; b.(11ul) <- zero;
  b.(12ul) <- zero; b.(13ul) <- zero; b.(14ul) <- zero; b.(15ul) <- zero;
  b.(16ul) <- zero; b.(17ul) <- zero; b.(18ul) <- zero; b.(19ul) <- zero;
  b.(20ul) <- zero; b.(21ul) <- zero; b.(22ul) <- zero; b.(23ul) <- zero;
  b.(24ul) <- zero; b.(25ul) <- zero; b.(26ul) <- zero; b.(27ul) <- zero;
  b.(28ul) <- zero; b.(29ul) <- zero; b.(30ul) <- zero; b.(31ul) <- zero

#reset-options "--initial_fuel 0 --max_fuel 0 --z3rlimit 50"
(* We assume that the first 32 bytes of c and m are 0s and will remain 0s *)
val crypto_secretbox_detached:
  c:uint8_p ->
  mac:uint8_p{length mac = crypto_secretbox_MACBYTES /\ disjoint mac c} ->
  m:uint8_p ->
  mlen:u64{let len = U64.v mlen in len = length m /\ len = length c}  ->
  n:uint8_p{length n = crypto_secretbox_NONCEBYTES} ->
  k:uint8_p{length k = crypto_secretbox_KEYBYTES} ->
  Stack u32
    (requires (fun h -> live h c /\ live h mac /\ live h m /\ live h n /\ live h k))
    (ensures  (fun h0 z h1 -> modifies_2 c mac h0 h1 /\ live h1 c /\ live h1 mac))
let crypto_secretbox_detached c mac m mlen n k =
  let hinit = ST.get() in
  push_frame();
  let h0 = ST.get() in
  let subkey = create (uint8_to_sint8 0uy) 32ul in
  let h0' = ST.get() in
  Hacl.Symmetric.HSalsa20.crypto_core_hsalsa20 subkey (sub n 0ul 16ul) k;
  Salsa20.crypto_stream_salsa20_xor c
                                    m
                                    U64.(mlen +^ 32uL)
                                    (sub n 16ul 8ul)
                                    subkey;
  let mlen_ = Int.Cast.uint64_to_uint32 mlen in
  Poly1305_64.crypto_onetimeauth mac (sub c 32ul mlen_) mlen (sub c 0ul 32ul);
  set_zero_bytes(c);
  set_zero_bytes(subkey);
  pop_frame();
  0ul


#reset-options "--initial_fuel 0 --max_fuel 0 --z3rlimit 200"

(* We assume that the first 32 bytes of m and c are 0 *)
val crypto_secretbox_open_detached:
  m:uint8_p ->
  c:uint8_p ->
  mac:uint8_p{length mac = crypto_secretbox_MACBYTES /\ declassifiable mac} ->
  clen:u64{let len = U64.v clen in len = length m /\ len = length c}  ->
  n:uint8_p{length n = crypto_secretbox_NONCEBYTES} ->
  k:uint8_p{length k = crypto_secretbox_KEYBYTES} ->
  Stack u32
    (requires (fun h -> live h m /\ live h c /\ live h mac /\ live h n /\ live h k))
    (ensures  (fun h0 z h1 -> modifies_1 m h0 h1 /\ live h1 m))
let crypto_secretbox_open_detached m c mac clen n k =
  let hinit = ST.get() in
  push_frame();
  let h0 = ST.get() in
  let subkey = create (uint8_to_sint8 0uy) 32ul in
  let mackey = create (uint8_to_sint8 0uy) 64ul in
  let cmac   = create (uint8_to_sint8 0uy) 16ul in
  let h0' = ST.get() in
  Hacl.Symmetric.HSalsa20.crypto_core_hsalsa20 subkey (sub n 0ul 16ul) k;
  Salsa20.crypto_stream_salsa20 mackey 32uL (sub n 16ul 8ul) subkey;
  let clen_ = Int.Cast.uint64_to_uint32 clen in
  Poly1305_64.crypto_onetimeauth cmac (sub c 32ul clen_) clen mackey;
  assume (Hacl.Policies.declassifiable cmac);
  let verify = cmp_bytes mac cmac 16ul in
  let z = 
    if U8.(verify =^ 0uy) then (
      Salsa20.crypto_stream_salsa20_xor m
                                        c
					U64.(clen +^ 32uL)
 					(sub n 16ul 8ul)
                                    	subkey;
      set_zero_bytes subkey;
      set_zero_bytes m;
      0ul)
    else 0xfffffffful in
  pop_frame();
  z

#reset-options "--initial_fuel 0 --max_fuel 0 --z3rlimit 5"

val crypto_secretbox_easy:
  c:uint8_p ->
  m:uint8_p ->
  mlen:u64{let len = U64.v mlen in len <= length m /\ len + crypto_secretbox_MACBYTES <= length c}  ->
  n:uint8_p{length n = crypto_secretbox_NONCEBYTES} ->
  k:uint8_p{length k = crypto_secretbox_KEYBYTES} ->
  Stack u32
    (requires (fun h -> live h c /\ live h m /\ live h n /\ live h k))
    (ensures  (fun h0 z h1 -> modifies_1 c h0 h1 /\ live h1 c))
let crypto_secretbox_easy c m mlen n k =
  push_frame ();  
  let mlen_ = FStar.Int.Cast.uint64_to_uint32 mlen in
  Math.Lemmas.modulo_lemma (U64.v mlen) (pow2 32);
  let cmac   = create (uint8_to_sint8 0uy) 16ul in
  let res = crypto_secretbox_detached c cmac m mlen n k in
  blit cmac 0ul c 16ul 16ul;
  pop_frame();
  res

val crypto_secretbox_open_easy:
  m:uint8_p ->
  c:uint8_p ->
  clen:u64{let len = U64.v clen in len = length m + crypto_secretbox_MACBYTES /\ len = length c}  ->
  n:uint8_p{length n = crypto_secretbox_NONCEBYTES} ->
  k:uint8_p{length k = crypto_secretbox_KEYBYTES} ->
  Stack u32
    (requires (fun h -> live h c /\ live h m /\ live h n /\ live h k))
    (ensures  (fun h0 z h1 -> modifies_1 m h0 h1 /\ live h1 m))
let crypto_secretbox_open_easy m c clen n k =
  let mac = sub c 16ul 16ul in
  (* Declassification assumption (non constant-time operations may happen on the 'mac' buffer *)
  assume (declassifiable mac);
  crypto_secretbox_open_detached m c mac U64.(clen -^ 16uL) n k