.PHONEY: clean run debug

# eliminate “stub file and library file out of sync” warnings
QUIET = -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/

maccopy: maccopy.c Makefile
	gcc -O2 -Wall -framework ApplicationServices -o maccopy maccopy.c $(QUIET)

debug: maccopy.c Makefile
	gcc -O2 -Wall -framework ApplicationServices -o maccopy maccopy.c $(QUIET) -DDEBUG

help: 
	@echo make [ clean maccopy run ]

clean:
	-rm -f maccopy

run:
	./maccopy
