all : \
mocklib \

clean : \
mocklib_clean \

mocklib:
	make -C mocklib -f conf.mk

mocklib_clean:
	make -C mocklib -f conf.mk clean

.PHONY: all clean

.PHONY: mocklib mocklib_clean
