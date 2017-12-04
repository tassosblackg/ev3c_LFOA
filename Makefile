CFLAGS += -O3
ifndef RANLIB
	RANLIB = ranlib
endif

all: lib/ev3_all.a bin/lfoa_r

obj/%.o: src/%.c include/%.h include/ev3_all.h Makefile
	mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS) -Iinclude

lib/ev3_all.a: obj/ev3_file.o  obj/ev3_sensor.o obj/ev3_dcmotor.o obj/ev3_servo.o obj/ev3_button.o
	mkdir -p $(@D)
	$(AR) rc $@ $^ && $(RANLIB) $@

bin/lfoa_r: src/lfoa.c lib/ev3_all.a
	mkdir -p $(@D)
	$(CC) -o $@ $< lib/ev3_all.a $(CFLAGS) -Iinclude




.PHONY: all clean

clean:
	rm -rf obj lib bin
	rm -f *~
