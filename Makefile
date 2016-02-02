npx:
	gcc --verbose 									\
		`${HOME}/local/install/SDL-1.2.15/bin/sdl-config --cflags --libs`	\
		-Wall									\
		-O3 -msse2 nanopond-2.0.c -o npx	

clean:
	rm -f ./npx

		

