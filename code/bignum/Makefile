include ../Makefile.include

BIGNUM_FILES= \
	Hacl.Bignum.Limb.fst \
	Hacl.Bignum.Wide.fst \
	Hacl.Spec.Bignum.Field.fst \
	Hacl.Spec.Bignum.Bigint.fst \
	Hacl.Spec.Bignum.Fsum.fst \
	Hacl.Spec.Bignum.Fdifference.fst  \
	Hacl.Spec.Bignum.Fscalar.fst \
	Hacl.Spec.Bignum.Fproduct.fst \
	Hacl.Spec.Bignum.Fmul.fst \
	Hacl.Spec.Bignum.fst \
	Hacl.Bignum.Fsum.fst \
	Hacl.Bignum.Fdifference.fst  \
	Hacl.Bignum.Fscalar.fst \
	Hacl.Bignum.Fproduct.fst \
	Hacl.Bignum.Fmul.fst \
	Hacl.Bignum.fst 
#	Hacl.Bignum.Constants.fsti \
	Hacl.Bignum.Parameters.fsti \
	Hacl.Bignum.Modulo.fsti \
	Hacl.Bignum.Crecip.fsti \

BIGNUM_MODULES=$(basename $(BIGNUM_FILES))

%.fst-ct: %.fst
	$(FSTAR_BASE) --include interfaces --include ../lib --lax --include $(KREMLIN_HOME)/kremlib $^

all-ct:
	$(FSTAR_HOME)/bin/fstar.exe --include $(FSTAR_HOME)/ulib/hyperstack --include interfaces \
		--include ../lib $^ --lax --include $(KREMLIN_HOME)/kremlib $(BIGNUM_FILES)

%.fst-verify: %.fst
	$(FSTAR_BASE) --include interfaces --include ../lib --include $(KREMLIN_HOME)/kremlib $^

verify: $(addsuffix -verify, $(BIGNUM_FILES))

all-ci: verify

all-ver: verify

%-hints: %.fst
	-$(FSTAR_BASE) --include interfaces --include ../lib --include $(KREMLIN_HOME)/kremlib --record_hints $^

ALL_HINTS=$(addsuffix -hints, $(BIGNUM_MODULES))

all-hints2: $(ALL_HINTS)
all-hints:
	cp ./bignum_hints/* .
	$(MAKE) all-hints2
	mv *.hints ./bignum_hints

count-line:
	cloc --force-lang=ocaml $(BIGNUM_FILES)

clean:
	rm -rf *.exe *.out *~ x25519/*~ poly1305/*~ interfaces/*~ tmp tmppoly
