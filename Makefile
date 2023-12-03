
ifdef OS
   RM = del /Q
else
   ifeq ($(shell uname), Linux)
      RM = rm -f -r
      DAY ?= $(shell bash -c 'read -p "chose day: " input; echo $$input')
   endif
endif

BUILD_DIR := $(CURDIR)/day$(DAY)

create:
	mkdir $(BUILD_DIR)
	touch $(BUILD_DIR)/main.c
	touch $(BUILD_DIR)/makefile
	cat makefile_template >> $(BUILD_DIR)/makefile
	chmod +x $(BUILD_DIR)/makefile

build: $(BUILD_DIR)/makefile
	cd $(BUILD_DIR); ./makefile build

clean:
	$(RM) $(BUILD_DIR)