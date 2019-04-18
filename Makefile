all: build/
	(cd build && cmake .. && make && make build-package)

build/:
	mkdir -p build

run: all
	./build/package/ca-art.app/Contents/MacOS/ca-art

