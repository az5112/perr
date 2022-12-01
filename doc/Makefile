CC = g++
CFLAGS = -DNOCOLOR -std=c++20 -I../src/

README.md : README.md.tt hello-world.log vector-int.log vector-struct.log
	rts README.md.tt > $@


hello-world.exe : hello-world.cpp ../src/perr.h
	$(CC) $(CFLAGS) -o $@ $<

hello-world.log : hello-world.exe
	./$< 2> $@

vector-int.exe : vector-int.cpp ../src/perr.h
	$(CC) $(CFLAGS) -o $@ $<

vector-int.log : vector-int.exe
	./$< 2> $@

vector-struct.exe : vector-struct.cpp ../src/perr.h
	$(CC) $(CFLAGS) -o $@ $<

vector-struct.log : vector-struct.exe
	./$< 2> $@


clean:
	rm -fv *.exe *.log README.md

install: README.md
	mv -v README.md ..

.DELETE_ON_ERROR:
