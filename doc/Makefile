CC = g++
CFLAGS = -DNOCOLOR -std=c++20 -I../src/

README.md : README.md.tt hello-world.log vector-int.log vector-struct.log containers.cut nuke-perr.exe
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

containers.exe : containers.cpp ../src/perr.h
	$(CC) $(CFLAGS) -o $@ $<

containers.log : containers.exe
	./$< 2> $@

containers.cut : containers.log
	cut -b 25- $< > $@

nuke-perr.exe : nuke-perr.hpp nuke-perr.cpp ../src/perr.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -fv *.exe *.log containers.cut README.md

install: README.md
	mv -v README.md ..

.DELETE_ON_ERROR:
