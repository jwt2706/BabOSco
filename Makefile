.PHONY: all new-run clean build run setup install-cc install-headers
all: new-run

# ------------------ Build ------------------

# builds the kernel and runs it
new-run: build run

# builds the kernel
build: clean
	./iso.sh

# cleans out the temporary files
clean:
	./clean.sh

# runs the most recent build
run:
	./qemu.sh

# ------------------ Setup ------------------

# you'll only need to run this once, when setting up the dev environment for the first time
setup: install-cc install-headers
	@echo "Setup done :D"

# builds the cross compiler (cc)
install-cc:
	./install-cc.sh

# installs the headers for the cross compiler
install-headers:
	./install-headers.sh