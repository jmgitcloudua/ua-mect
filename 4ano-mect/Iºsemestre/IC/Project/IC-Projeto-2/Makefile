all:
	@(if [ ! -d build ]; then mkdir build; fi; cd build;\
	  if [ ! -d project2-example-bin ]; then mkdir project2-example-bin; fi; cmake ..; make)

clean:
	rm -rf build ../project2-example-bin
