all : \
mocklib \
mocklib_expfun \

clean : \
mocklib_clean \
mocklib_expfun_clean \

mocklib:
	make -C mocklib -f conf.mk

mocklib_clean:
	make -C mocklib -f conf.mk clean

mocklib_expfun:
	make -C mocklib_expfun -f conf.mk

mocklib_expfun_clean:
	make -C mocklib_expfun -f conf.mk clean
	
.PHONY: all clean

.PHONY: mocklib mocklib_clean
.PHONY: mocklib_expfun mocklib_expfun_clean
