all : \
mock_define \
mock_manual \
mock_scripts \

clean : \
mock_define_clean \
mock_manual_clean \
mock_scripts_clean \

mock_define:
	make -C mock_define -f conf.mk

mock_define_clean:
	make -C mock_define -f conf.mk clean
	
mock_manual:
	make -C mock_manual -f conf.mk

mock_manual_clean:
	make -C mock_manual -f conf.mk clean

mock_scripts:
	make -C mock_scripts -f generate.mk
	make -C mock_scripts -f conf.mk

mock_scripts_clean:
	make -C mock_scripts -f generate.mk clean
	make -C mock_scripts -f conf.mk clean

.PHONY: all clean

.PHONY: mock_define mock_define_clean
.PHONY: mock_manual mock_manual_clean
.PHONY: mock_scripts mock_scripts_clean