
ifdef OS
   RM = del /Q
   DAY = $(cmd set /p input=chose day)
else
   ifeq ($(shell uname), Linux)
      RM = rm -f
      DAY := $(shell read -p "chose day: " input; echo$(input))
   endif
endif

@echo $(DAY)

BUILD_DIR := $(CURDIR)/day$(DAY)

build:
	@echo $(build_dir)
