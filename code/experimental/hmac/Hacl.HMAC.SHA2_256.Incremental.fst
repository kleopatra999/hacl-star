module Hacl.HMAC.SHA2_256.Incremental

open FStar.Mul
open FStar.Ghost
open FStar.HyperStack
open FStar.ST
open FStar.Buffer

open Hacl.Cast
open Hacl.UInt8
open Hacl.UInt32
open FStar.UInt32

open Hacl.Utils.Experimental


(* Definition of aliases for modules *)
module U8 = FStar.UInt8
module U32 = FStar.UInt32
module U64 = FStar.UInt64

module S8 = Hacl.UInt8
module S32 = Hacl.UInt32
module S64 = Hacl.UInt64

module Buffer = FStar.Buffer
module Cast = Hacl.Cast
module Utils = Hacl.Utils.Experimental

module Hash = Hacl.Hash.SHA2.L256


(* Definition of base types *)
let uint8_t   = FStar.UInt8.t
let uint32_t  = FStar.UInt32.t
let uint64_t  = FStar.UInt64.t

let suint8_t  = Hacl.UInt8.t
let suint32_t = Hacl.UInt32.t
let suint64_t = Hacl.UInt64.t

let suint32_p = Buffer.buffer suint32_t
let suint8_p  = Buffer.buffer suint8_t


(* Definitions of aliases for functions *)
let u8_to_s8 = Cast.uint8_to_sint8
let u32_to_s32 = Cast.uint32_to_sint32
let u32_to_s64 = Cast.uint32_to_sint64
let s32_to_s8  = Cast.sint32_to_sint8
let s32_to_s64 = Cast.sint32_to_sint64
let u64_to_s64 = Cast.uint64_to_sint64



//
// HMAC
//

(* Define parameters *)
inline_for_extraction let size_hash = Hash.size_hash
inline_for_extraction let size_hash_w = Hash.size_hash_w
inline_for_extraction let size_block = Hash.size_block
inline_for_extraction let size_block_w = Hash.size_block_w


(* Size and positions of objects in the state *)
inline_for_extraction let size_ipad = size_block
inline_for_extraction let size_opad = size_block
inline_for_extraction let size_okey_w = size_block_w
inline_for_extraction let size_okey_8 = size_okey_w *^ 4ul
inline_for_extraction let size_state = size_okey_w +^ Hash.size_state

inline_for_extraction let pos_okey = 0ul
inline_for_extraction let pos_state_hash_0 = pos_okey +^ size_okey_w



(* Define a function to wrap the key length after size_block *)
(* Threat model : the length of the key is considered public here *)
[@"c_inline"]
private val hmac_wrap_key:
  okey :suint8_p{length okey = v size_okey_8} ->
  key  :suint8_p{disjoint okey key} ->
  len  :uint32_t{v len = length key} ->
  Stack unit
        (requires (fun h0 -> live h0 okey /\ live h0 key))
        (ensures  (fun h0 _ h1 -> live h1 okey /\ modifies_1 okey h0 h1))

[@"c_inline"]
let hmac_wrap_key okey key len =
  if U32.(len >^ size_block) then
    let okey = Buffer.sub okey 0ul Hash.size_hash in
    Hash.hash okey key len
  else
    let okey = Buffer.sub okey 0ul len in
    Buffer.blit key 0ul okey 0ul len



val alloc:
  unit ->
  StackInline (state:suint32_p{length state = v size_state})
        (requires (fun h0 -> True))
        (ensures  (fun h0 state h1 -> modifies_0 h0 h1 /\ live h1 state))

let alloc () = Buffer.create (u32_to_s32 0ul) size_state



val init:
  state :suint32_p{length state = v size_state} ->
  key   :suint8_p ->
  len   :uint32_t {v len = length key} ->
  Stack unit
        (requires (fun h0 -> live h0 state /\ live h0 key))
        (ensures  (fun h0 r h1 -> live h1 state /\ modifies_1 state h0 h1))

let init state key len =

  (* Push a new memory frame *)
  (**) push_frame();

  (* Allocate and set initial values for ipad *)
  let ipad = Buffer.create (uint8_to_sint8 0x36uy) size_ipad in

  (* Retrive and allocate memory for the wrapped key location *)
  let okey_w = Buffer.sub state pos_okey size_okey_w in
  let okey_8 = Buffer.create (uint8_to_sint8 0x00uy) size_okey_8 in

  (* Retreive memory for the inner hash state *)
  let ctx_hash_0 = Buffer.sub state pos_state_hash_0 Hash.size_state in

  (* Initialize the inner hash state *)
  Hash.init ctx_hash_0;

  (* Step 1: make sure the key has the proper length *)
  hmac_wrap_key okey_8 key len;

  (**) assert_norm(v size_okey_8 % 4 = 0);
  (**) assert_norm(v size_okey_8 <= (4 * v size_okey_w));
  Hacl.Utils.Experimental.load32s_be okey_w okey_8 size_okey_8;

  (* Step 2: xor "result of step 1" with ipad *)
  Utils.xor_bytes ipad okey_8 size_block;
  let s2 = ipad in

  (* Step 3a: feed s2 to the inner hash function *)
  Hash.update ctx_hash_0 s2;

  (* Pop the memory frame *)
  (**) pop_frame();
  admit()



val update :
  state :suint32_p{length state = U32.v size_state} ->
  data  :suint8_p {length data = U32.v size_block} ->
  Stack unit
        (requires (fun h0 -> live h0 state /\ live h0 data))
        (ensures  (fun h0 r h1 -> live h1 state /\ modifies_1 state h0 h1))

let update state data =

  (* Select the part of the state used by the inner hash function *)
  let ctx_hash_0 = Buffer.sub state pos_state_hash_0 Hash.size_state in

  (* Process the rest of the data *)
  Hash.update ctx_hash_0 data



val update_multi:
  state :suint32_p{length state = v size_state} ->
  data  :suint8_p ->
  n     :uint32_t{v n * v size_block <= length data} ->
  idx   :uint32_t{v idx <= v n} ->
  Stack unit
        (requires (fun h0 -> live h0 state /\ live h0 data))
        (ensures  (fun h0 _ h1 -> live h1 state /\ modifies_1 state h0 h1))

let rec update_multi state data n idx =

  if (idx =^ n) then ()
  else

    (* Get the current block for the data *)
    let b = Buffer.sub data (mul_mod idx size_block) size_block in

    (* Call the update function on the current block *)
    update state b;

    (* Recursive call *)
    update_multi state data n (idx +^ 1ul)



val update_last:
  state :suint32_p{length state = v size_state} ->
  data  :suint8_p {length data <= v size_block} ->
  len   :uint32_t {v len = length data} ->
  Stack unit
        (requires (fun h0 -> live h0 state /\ live h0 data))
        (ensures  (fun h0 r h1 -> live h1 state /\ modifies_1 state h0 h1))

let update_last state data len =

  (* Select the part of the state used by the inner hash function *)
  let ctx_hash_0 = Buffer.sub state pos_state_hash_0 Hash.size_state in

  (* Process the rest of the data *)
  Hash.update_last ctx_hash_0 data len



val finish:
  state :suint32_p{length state = U32.v size_state} ->
  mac   :suint8_p {length mac = U32.v size_hash} ->
  Stack unit
        (requires (fun h0 -> live h0 state /\ live h0 mac))
        (ensures  (fun h0 _ h1 -> live h1 state /\ live h1 mac /\ modifies_2 state mac h0 h1))

let finish state mac =

  (* Push a new memory frame *)
  (**) push_frame();

  (* Get the memory *)
  let h0 = ST.get () in

  (* Allocate and set initial values for ipad and opad *)
  let opad = Buffer.create (uint8_to_sint8 0x5cuy) size_opad in

  (* Allocate memory to store the output of the inner hash *)
  let s4 = Buffer.create (uint8_to_sint8 0x00uy) size_hash in

  (* Allocate memory for the outer hash state *)
  let ctx_hash_1 = Buffer.create (uint32_to_sint32 0ul) Hash.size_state in

  let h1 = ST.get () in
  assert(live h1 state /\ live h1 mac /\ modifies_1 state h0 h1);
  admit();

  (* Retrieve the state of the inner hash *)
  let ctx_hash_0 = Buffer.sub state pos_state_hash_0 Hash.size_state in

  (* Retrive and allocate memory for the wrapped key location *)
  let okey_w = Buffer.sub state pos_okey size_okey_w in
  let okey_8 = Buffer.create (uint8_to_sint8 0x00uy) size_okey_8 in

  (**) assert_norm(v size_okey_w * 4 <= v size_okey_8);
  (**) assert_norm(v size_okey_8 <= (4 * v size_okey_w));
  Hacl.Utils.Experimental.store32s_be okey_8 okey_w size_okey_w;

  (* Step 4: apply H to "result of step 3" *)
  Hash.finish ctx_hash_0 s4;

  (* Step 5: xor "result of step 1" with opad *)
  Utils.xor_bytes opad okey_8 size_block;
  let s5 = opad in

  (* Initialize outer hash state *)
  Hash.init ctx_hash_1;

  (* Step 6: append "result of step 4" to "result of step 5" *)
  (* Step 7: apply H to "result of step 6" *)
  Hash.update ctx_hash_1 s5;
  Hash.update_last ctx_hash_1 s4 size_hash;
  Hash.finish ctx_hash_1 mac;

  (* Pop memory frame *)
  (**) pop_frame()



val hmac:
  mac     :suint8_p{length mac = v size_hash} ->
  key     :suint8_p ->
  keylen  :uint32_t{v keylen = length key} ->
  data    :suint8_p ->
  datalen :uint32_t{v datalen = length data /\ v datalen + v size_block <= pow2 32} ->
  Stack unit
        (requires (fun h -> live h mac /\ live h key /\ live h data ))
        (ensures  (fun h0 r h1 -> live h1 mac /\ modifies_1 mac h0 h1))

let hmac mac key keylen data datalen =

  (* Push a new memory frame *)
  (**) push_frame();

  (* Allocate memory for the mac state *)
  let ctx = Buffer.create (u32_to_s32 0ul) size_state in

  (* Compute the number of blocks to process *)
  let n = datalen /^ size_block in
  let r = datalen %^ size_block in
  (**) cut(v datalen % v size_block <= v size_block);
  (**) cut(v r <= v size_block);

  (* Initialize the mac state *)
  init ctx key keylen;

  (* Update the state with data blocks *)
  update_multi ctx data n 0ul;

  (* Get the last block *)
  (**) assert_norm(v n * v size_block <= v datalen);
  let input_last = Buffer.sub data (n *^ size_block) r in

  (* Process the last block of data *)
  update_last ctx input_last r;

  (* Finalize the mac output *)
  finish ctx mac;

  (* Pop the memory frame *)
  (**) pop_frame()
