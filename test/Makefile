all : \
lib \
mocks \

clean : \
lib_clean \
mocks_clean \

lib:
	make -C lib

lib_clean:
	make -C lib clean

mocks:
	make -C mocks

mocks_clean:
	make -C mocks clean
	
.PHONY: all clean

.PHONY: lib lib_clean
.PHONY: mocks mocks_clean
