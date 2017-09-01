all : \
test \

clean : \
test_clean \

test:
	make -C test

test_clean:
	make -C test clean
	
.PHONY: all clean

.PHONY: test test_clean
