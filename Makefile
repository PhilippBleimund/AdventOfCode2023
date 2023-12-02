
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
	gcc $(BUILD_DIR)/main.c -o $(BUILD_DIR)/main
	@echo "Programm output\n -------------------- \n\n"
	cd $(BUILD_DIR); ./main