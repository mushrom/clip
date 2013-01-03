all: clip

clip:
	cd src; make

clean:
	cd src; make clean
	rm bin/*

.PHONY: clip
