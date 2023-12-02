
ifdef OS
   RM = del /Q
else
   ifeq ($(shell uname), Linux)
      RM = rm -f
      DAY ?= $(shell bash -c 'read -p "chose day: " input; echo $$input')
   endif
endif

BUILD_DIR := $(CURDIR)/day$(DAY)

create:
	mkdir $(BUILD_DIR)
	touch $(BUILD_DIR)/main.c

build: $(BUILD_DIR)/main.c
	mkdir $(BUILD_DIR)/build
	gcc $(BUILD_DIR)/main.c -o main
