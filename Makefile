.PHONEY: clean run

maccopy: maccopy.c
	gcc -O2 -framework ApplicationServices -o maccopy maccopy.c

help: 
	@echo make [ clean maccopy run ]

clean:
	-rm -f maccopy

run:
	./maccopy
