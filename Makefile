COMPILE_COMMANDS = build/compile_commands.json

$(COMPILE_COMMANDS): CMakeLists.txt
	mkdir -p build
	cd build && cmake ../

.PHONY: geotools
geotools: $(COMPILE_COMMANDS)
	cmake --build build --target geotools


.PHONY: test
test: $(COMPILE_COMMANDS)
	cmake --build build --target test
	./build/test

.PHONY: clean
clean:
	rm -rf build
