all : \
mock_manual \
mock_define \

clean : \
mock_manual_clean \
mock_define_clean \

mock_manual:
	make -C mock_manual -f conf.mk

mock_manual_clean:
	make -C mock_manual -f conf.mk clean

mock_define:
	make -C mock_define -f conf.mk

mock_define_clean:
	make -C mock_define -f conf.mk clean

.PHONY: all clean

.PHONY: mock_manual mock_manual_clean
.PHONY: mock_define mock_define_clean