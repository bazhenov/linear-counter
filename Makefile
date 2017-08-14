GCC=g++
TARGET_DIR=./target
all:
	mkdir -p ${TARGET_DIR}
	${GCC} -o ${TARGET_DIR}/cardinality -l boost_program_options src/*.cpp
