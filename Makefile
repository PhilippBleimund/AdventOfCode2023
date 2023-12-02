
build:
	@read -p "Enter Day: " day;\
	day_dir=./days/day$$day;\
	mkdir -p $$day_build/build
