CC = gcc
BUILD_DIR = client/bin/
BUILD_NAME = a.out
ARTIFACT = $(BUILD_DIR)$(BUILD_NAME)

client : client/src/main.c
	mkdir -p $(BUILD_DIR)
	$(CC) client/src/main.c -o $(ARTIFACT) -lncurses -lcurl

fmt :
	clang-format -i --style=llvm client/src/main.c

server : server/main.py
	@which fastapi > /dev/null && echo "FastAPI found, running ..." && ( \
		fastapi dev server/main.py \
	)

.PHONY : clean
clean :
	- rm -rf $(BUILD_DIR)
	- rm -rf **/__pycache__

run: $(ARTIFACT)
	./$(ARTIFACT)
