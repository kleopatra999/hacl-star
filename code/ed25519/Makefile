HACL_HOME=../..
FSTAR_HOME?=$(HACL_HOME)/dependencies/FStar
KREMLIN_HOME?=$(FSTAR_HOME)/../kremlin
include $(HACL_HOME)/code/Makefile.include


BIGNUM= \
	../bignum/Hacl.Bignum.Limb.fst \
	../bignum/Hacl.Spec.Bignum.Field.fst \
	../bignum/Hacl.Bignum.Wide.fst \
	../bignum/Hacl.Spec.Bignum.Bigint.fst \
	../bignum/Hacl.Spec.Bignum.Fproduct.fst \
	../bignum/Hacl.Spec.Bignum.Fsum.fst \
	../bignum/Hacl.Spec.Bignum.Fdifference.fst \
	../bignum/Hacl.Spec.Bignum.Fmul.fst \
	../bignum/Hacl.Spec.Bignum.Fscalar.fst \
	../bignum/Hacl.Spec.Bignum.fst \
	../bignum/Hacl.Bignum.Fscalar.fst \
	../bignum/Hacl.Bignum.Fproduct.fst \
	../bignum/Hacl.Bignum.Fmul.fst \
	../bignum/Hacl.Bignum.fst

ED25519_SPECIFIC= \
	Hacl.Impl.BignumQ.Mul.fst \
	Hacl.Spec.BignumQ.Mul.fst \
	Hacl.Lib.Create64.fst \
	Hacl.Bignum25519.fsti \
	Hacl.Bignum25519.fst \
	Hacl.Impl.Ed25519.ExtPoint.fst \
	Hacl.Impl.Ed25519.SwapConditional.fst \
	Hacl.Impl.Ed25519.PointDouble.fsti \
	Hacl.Impl.Ed25519.PointDouble.fst \
	Hacl.Impl.Ed25519.PointAdd.fsti \
	Hacl.Impl.Ed25519.PointAdd.fst \
	Hacl.Impl.Ed25519.Ladder.Step.fsti \
	Hacl.Impl.Ed25519.Ladder.Step.fst \
	Hacl.Impl.Ed25519.Ladder.fsti \
	Hacl.Impl.Ed25519.Ladder.fst \
	Hacl.Impl.Store51.fsti \
	Hacl.Impl.Store51.fst \
	Hacl.Impl.Ed25519.PointCompress.fst \
	Hacl.Impl.Ed25519.G.fst \
	Hacl.Impl.Ed25519.SecretExpand.fsti \
	Hacl.Impl.Ed25519.SecretExpand.fst \
	Hacl.Spec.BignumQ.Eval.fst \
	Hacl.Spec.BignumQ.Mul.Lemmas_1.fst \
	Hacl.Spec.BignumQ.Mul.Lemmas_3.fst \
	Spec.BarrettReduction.fst \
	Hacl.Lib.Create128.fst \
	Hacl.Impl.BignumQ.Mul.fsti \
	Hacl.Impl.Sha512.fst \
	Hacl.Impl.Load56.fsti \
	Hacl.Impl.Load56.fst \
	Hacl.Impl.SHA512.ModQ.fsti \
	Hacl.Impl.SHA512.ModQ.fst \
	Hacl.Impl.Store56.fst \
	Hacl.Impl.Ed25519.Sign.Steps.fst \
	Hacl.Impl.Ed25519.Sign.fst \
	Hacl.Impl.Load51.fsti \
	Hacl.Impl.Load51.fst \
	Hacl.Impl.Ed25519.Pow2_252m2.fsti \
	Hacl.Impl.Ed25519.Pow2_252m2.fst \
	Hacl.Impl.Ed25519.RecoverX.fsti \
	Hacl.Impl.Ed25519.RecoverX.fst \
	Hacl.Impl.Ed25519.PointDecompress.fsti \
	Hacl.Impl.Ed25519.PointDecompress.fst \
	Hacl.Impl.Ed25519.Verify.Lemmas.fst \
	Hacl.Impl.Ed25519.PointEqual.fsti \
	Hacl.Impl.Ed25519.PointEqual.fst \
	Hacl.Impl.Ed25519.Verify.Steps.fst \
	Hacl.Impl.Ed25519.Verify.fst \
	Hacl.Impl.Ed25519.SecretToPublic.fsti \
	Hacl.Impl.Ed25519.SecretToPublic.fst \
	Ed25519.fsti \
	Ed25519.fst

# List of modules which "sign" and "secret_to_public" depend on, to typecheck
# for the constant-time discipline
ED25519_CT_MODULES= \
	Hacl.Lib.Create64.fst \
	Hacl.Bignum25519.fsti \
	Hacl.Bignum25519.fst \
	Hacl.Impl.Ed25519.ExtPoint.fst \
	Hacl.Impl.Ed25519.SwapConditional.fst \
	Hacl.Impl.Ed25519.PointDouble.fsti \
	Hacl.Impl.Ed25519.PointDouble.fst \
	Hacl.Impl.Ed25519.PointAdd.fsti \
	Hacl.Impl.Ed25519.PointAdd.fst \
	Hacl.Impl.Ed25519.Ladder.Step.fsti \
	Hacl.Impl.Ed25519.Ladder.Step.fst \
	Hacl.Impl.Ed25519.Ladder.fsti \
	Hacl.Impl.Ed25519.Ladder.fst \
	Hacl.Impl.Store51.fsti \
	Hacl.Impl.Store51.fst \
	Hacl.Impl.Ed25519.PointCompress.fst \
	Hacl.Impl.Ed25519.G.fst \
	Hacl.Impl.Ed25519.SecretExpand.fsti \
	Hacl.Impl.Ed25519.SecretExpand.fst \
	Hacl.Spec.BignumQ.Eval.fst \
	Hacl.Spec.BignumQ.Mul.Lemmas_1.fst \
	Hacl.Spec.BignumQ.Mul.Lemmas_3.fst \
	Spec.BarrettReduction.fst \
	Hacl.Spec.BignumQ.Mul.fst \
	Hacl.Lib.Create128.fst \
	Hacl.Impl.BignumQ.Mul.fsti \
	Hacl.Impl.BignumQ.Mul.fst \
	Hacl.Impl.Sha512.fst \
	Hacl.Impl.Load56.fsti \
	Hacl.Impl.Load56.fst \
	Hacl.Impl.SHA512.ModQ.fsti \
	Hacl.Impl.SHA512.ModQ.fst \
	Hacl.Impl.Store56.fst \
	Hacl.Impl.Ed25519.Sign.Steps.fst \
	Hacl.Impl.Ed25519.SecretToPublic.fsti \
	Hacl.Impl.Ed25519.SecretToPublic.fst \
	Hacl.Impl.Ed25519.Sign.fst 


# Files that are too slow and for which verification speed must improve
SLOW=

# Files that still have errors
TODO=

ED25519_FILES= $(ED25519_SPECIFIC) # $(BIGNUM) 


HINTS_ENABLED?=--use_hints --record_hints

FSTARB=$(FSTAR_HOME)/bin/fstar.exe --include $(FSTAR_HOME)/ulib/hyperstack \
		--include $(HACL_HOME)/code/lib/kremlin --include $(HACL_HOME)/code/bignum --include $(KREMLIN_HOME)/kremlib \
		 --include $(HACL_HOME)/specs \
		--include $(HACL_HOME)/code/curve25519 --include $(HACL_HOME)/code/hash \
		$(HINTS_ENABLED) $(OTHERFLAGS)

FSTAR_CT=$(FSTAR_HOME)/bin/fstar.exe --include $(FSTAR_HOME)/ulib/hyperstack \
		--include $(HACL_HOME)/code/lib --include $(HACL_HOME)/code/bignum --include $(KREMLIN_HOME)/kremlib \
		--include $(HACL_HOME)/specs \
		--include $(HACL_HOME)/code/curve25519  --include $(HACL_HOME)/code/hash


# Lax typechecking against the restricted integer interface
%.fst-ct: %.fst
	$(FSTAR_CT) --lax $^
%.fsti-ct: %.fsti
	$(FSTAR_CT) --lax $^

all-ct:
	$(FSTAR_CT) --lax --verify_all Hacl.Impl.Ed25519.SecretToPublic.fst Hacl.Impl.Ed25519.Sign.fst 

# Full typechecking against the transparent integer interface
%.fst-verify: %.fst
	$(FSTARB) $^
%.fsti-verify: %.fsti
	$(FSTARB) $^

all-ver: $(addsuffix -verify, $(ED25519_FILES))

# Minimal lax typechecking, pre-requisite to any extraction
%.fst-lax: %.fst
	$(FSTARB) --lax $^
%.fsti-lax: %.fsti
	$(FSTARB) --lax $^

all-lax: $(addsuffix -lax, $(ED25519_FILES))

# Hints regeneration
%.fst-hints: %.fst
	-$(FSTARB) $^
%.fsti-hints: %.fsti
	-$(FSTARB) $^

all-hints2: $(addsuffix -hints, $(ED25519_FILES))

all-hints:
	cp ./bignum_hints/* ../bignum/
	$(MAKE) all-hints2
	mv ../bignum/*.hints ./bignum_hints
bignum-hints:
	cp bignum_hints/* ../bignum
	$(MAKE) $(addsuffix -hints, $(BIGNUM))
	mv ../bignum/*.hints ./bignum_hints
specific-hints: $(addsuffix -hints, $(ED25519_SPECIFIC))

all-ci:specific-ci
specific-ci: $(addsuffix -verify, $(filter-out $(SLOW) $(TODO), $(ED25519_SPECIFIC)))

KEMLIN_SKIP_COMPILATION=$(KREMLIN_HOME)/krml -tmpdir ed25519-c $(KREMLIN_ARGS) \
		-I ../../bignum -I ../../lib/kremlin -I ../../../specs -I ../../curve25519 \
		-I ../hash \
		-drop 'Hacl.Spec' -drop 'Hacl.Cast' -drop 'Hacl.UInt.\*' -drop 'Hacl.Endianness' \
		-drop 'Hacl.UInt8' -drop 'Hacl.UInt16' -drop 'Hacl.UInt32' -drop 'Hacl.UInt64' -drop 'Hacl.UInt128' -drop 'Seq.\*' \
		-drop Prims -drop FStar -bundle 'Hacl.Bignum25519=Hacl.Bignum,Hacl.Bignum.\*,Hacl.EC,Hacl.EC.\*,Hacl.Impl.\*,Hacl.Lib.\*,Hacl.Bignum25519' \
		-bundle 'Hacl.Spec.\*' -drop "Spec.\*" \
		$(KREMLIN_HOME)/kremlib/testlib.c -add-include '"testlib.h"' \
		-skip-compilation -fsopt '--eager_inference'

../hash/sha2-c/SHA2_512.c:
	$(MAKE) -C ../hash sha2-c/SHA2_512.c

ed25519-c/Ed25519.c: \
	Hacl.Bignum25519.fst \
	../hash/Hacl.Impl.SHA512.Ed25519.fst \
	../hash/SHA2_512.fst \
	Hacl.Impl.Load56.fst \
	Hacl.Impl.Load51.fst \
	Hacl.Impl.Store51.fst \
	Hacl.Impl.BignumQ.Mul.fst \
	Hacl.Impl.SHA512.ModQ.fst \
	Hacl.Impl.Sha512.fst \
	Hacl.Impl.Ed25519.Pow2_252m2.fst \
	Hacl.Impl.Ed25519.PointAdd.fst \
	Hacl.Impl.Ed25519.PointDouble.fst \
	Hacl.Impl.Ed25519.SecretExpand.fst \
	Hacl.Impl.Ed25519.PointCompress.fst \
	Hacl.Impl.Ed25519.PointDecompress.fst \
	Hacl.Impl.Ed25519.RecoverX.fst \
	Hacl.Impl.Ed25519.Ladder.Step.fst \
	Hacl.Impl.Ed25519.Ladder.fst \
	Hacl.Impl.Ed25519.PointEqual.fst \
	Hacl.Impl.Ed25519.SecretToPublic.fst \
	Ed25519.fst
	 $(KREMLIN_HOME)/krml -tmpdir ed25519-c $(KREMLIN_ARGS) \
	 	-I $(HACL_HOME)/code/bignum -I $(HACL_HOME)/code/lib/kremlin -I $(HACL_HOME)/specs -I $(HACL_HOME)/code/curve25519 \
	 	-I $(HACL_HOME)/code/hash \
	 	$^ \
	 	-drop 'Hacl.Spec' -drop 'Hacl.Cast' -drop 'Hacl.UInt.\*' -drop 'Hacl.Endianness' \
	 	-drop 'Hacl.UInt8' -drop 'Hacl.UInt16' -drop 'Hacl.UInt32' -drop 'Hacl.UInt64' -drop 'Hacl.UInt128' -drop 'Seq.\*' \
	 	-drop Prims -drop FStar -bundle 'Ed25519=Ed25519,Hacl.EC,Hacl.EC.\*,Hacl.Impl.\*,Hacl.Lib.\*,Hacl.Bignum.\*,Hacl.Bignum25519,Hacl.Bignum,Hacl.Hash.\*,SHA2_512' \
	 	-bundle 'Hacl.Spec.\*' -drop "Spec.\*" \
	 	$(KREMLIN_HOME)/kremlib/testlib.c -add-include '"testlib.h"' -skip-compilation

extract-c:ed25519-c/Ed25519.c

ed25519.exe: ed25519-c/Ed25519.c
	 $(KREMLIN_HOME)/krml -tmpdir ed25519-c $(KREMLIN_ARGS) \
	 	-I $(HACL_HOME)/code/bignum -I ../../lib/kremlin -I $(HACL_HOME)/code/../specs \
		-I $(HACL_HOME)/code/curve25519 \
	 	$^  Hacl.Test.Ed25519.fst -no-prefix 'Hacl.Test.Ed25519' \
	 	-drop 'Hacl.Spec,Hacl.Cast,Hacl.UInt.\*,Hacl.Endianness' \
	 	-drop 'Hacl.UInt8,Hacl.UInt16,Hacl.UInt32,Hacl.UInt64,Hacl.UInt128,Seq.\*' \
	 	-drop 'Prims,FStar,Hacl.Bignum25519,Hacl.Impl.Ed25519.Pow2_252m2,Ed25519' \
	 	-bundle 'Hacl.Spec.\*' -drop "Spec.\*" \
	 	$(KREMLIN_HOME)/kremlib/testlib.c -add-include '"testlib.h"' \
		-add-include '"Ed25519.h"' -o ed25519.exe -ldopt '-lsodium'
	./ed25519.exe

count-line:
	cloc --force-lang=ocaml $(ED25519_FILES)

clean:
	rm -rf *.exe *.exe.* *.out *~ ed25519-c *.graph
