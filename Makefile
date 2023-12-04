all: old-photo-paral

old-photo-paral: old-photo-paral.c image-lib.c image-lib.h
	gcc old-photo-paral.c image-lib.c image-lib.h -g -o old-photo-paral -lgd

clean:
	rm -rf old-photo-paral