module HMAC.Pure

open FStar.UInt32
open Hacl.UInt32
open Hacl.SBuffer
open Hacl.Operations.Pure



(* Define base types *)
let u32 = FStar.UInt32.t
let uint32s = Hacl.SBuffer.u32s
let bytes = Seq.seq Hacl.UInt8.t


(* Define algorithm parameters *)
let hash = Hash.Sha256.Pure.sha256
let hl = Hash.Sha256.Pure.hl
let bl = Hash.Sha256.Pure.bl
let hashsize = hl
let blocksize = bl


(* Define operators *)
let op_At_Plus = FStar.UInt32.add
let op_At_Subtraction = FStar.UInt32.sub



(* Define a function to wrap the key length after bl bits *)
let wrap_key (key:bytes) (keylen:u32{Seq.length key = v keylen}) : GTot (okey:bytes{Seq.length okey = v bl}) =
  if gt keylen bl then
    let okey = hash key keylen in
    Seq.append okey (Seq.create (v bl - v hl) 0uy)
  else
    Seq.append key (Seq.create (v bl - v keylen) 0uy)


(* Define the internal function *)
val hmac_core : (key     :bytes) ->
                (keylen  :u32{Seq.length key = v keylen}) ->
                (data    :bytes) ->
                (datalen :u32{Seq.length data = v datalen /\ v bl + v datalen < pow2 32})
  -> GTot (mac:bytes{Seq.length mac = v hl})

let hmac_core key keylen data datalen =
  
  (* Define ipad and opad *)
  let ipad = Seq.create (v bl) 0x36uy in
  let opad = Seq.create (v bl) 0x5cuy in
  
  (* Step 1: make sure the key has the proper length *)
  let okey = wrap_key key keylen in

  (* Step 2: xor "result of step 1" with ipad *)
  let s2 = xor_bytes ipad okey bl in
  
  (* Step 3: append data to "result of step 2" *)
  let s3 = Seq.append s2 data in
  
  (* Step 4: apply H to "result of step 3" *)
  let s4 = hash s3 (bl @+ datalen) in
 
  (* Step 5: xor "result of step 1" with opad *)
  let s5 = xor_bytes okey opad bl in
  
  (* Step 6: append "result of step 4" to "result of step 5" *)
  let s6 = Seq.append s5 s4 in

  (* Step 7: apply H to "result of step 6" *)
  hash s6 (bl @+ hl)
  