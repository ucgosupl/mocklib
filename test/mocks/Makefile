all : \
mock_manual \

clean : \
mock_manual_clean \

mock_manual:
	make -C mock_manual -f conf.mk

mock_manual_clean:
	make -C mock_manual -f conf.mk clean

.PHONY: all clean

.PHONY: mock_manual mock_manual_clean