all : \
mocklib \
mocklib_common \
mocklib_expfun \

clean : \
mocklib_clean \
mocklib_common_clean \
mocklib_expfun_clean \

mocklib:
	make -C mocklib -f conf.mk

mocklib_clean:
	make -C mocklib -f conf.mk clean

mocklib_common:
	make -C mocklib_common -f conf.mk

mocklib_common_clean:
	make -C mocklib_common -f conf.mk clean
	
mocklib_expfun:
	make -C mocklib_expfun -f conf.mk

mocklib_expfun_clean:
	make -C mocklib_expfun -f conf.mk clean
	
.PHONY: all clean

.PHONY: mocklib mocklib_clean
.PHONY: mocklib_common mocklib_common_clean
.PHONY: mocklib_expfun mocklib_expfun_clean
