
build:
	@read -p "Enter Day: " day; \
	@echo $(day);\
	build_dir := $(CURDIR)/day$(day);\
	@echo $(build_dir)
