PROJECT_NAME = computer-clab-manager

CPPCHECK_OPTIONS = --language=c++ --enable=all --inconclusive --suppress=missingIncludeSystem 
SAN_OPTIONS = -D UBSAN=ON -D ASAN=ON

SOURCES = $(wildcard src/*.cc)
HEADERS = $(wildcard include/*.h)

TEST_DIR = tests
TEST_SOURCES = $(wildcard tests/*.cc)
TEST_HEADERS = $(wildcard tests/*.h)

BUILD_DEBUG_DIR = build_debug
BUILD_RELEASE_DIR = build_release

.PHONY: all clean check_format apply_format

all: build_release

build_release:
	@cmake . -B ${BUILD_RELEASE_DIR} -D CMAKE_BUILD_TYPE=Release
	@cmake --build ${BUILD_RELEASE_DIR}

build_debug:
	@cmake . -B ${BUILD_RELEASE_DIR} -D CMAKE_BUILD_TYPE=Debug $(SAN_OPTIONS)
	@cmake --build ${BUILD_RELEASE_DIR}

check_format:
	@clang-format -n ${SOURCES} ${HEADERS} ${TEST_SOURCES} ${TEST_HEADERS}
	cppcheck $(CPPCHECK_OPTIONS) $(SOURCES) $(HEADERS)

apply_format:
	@clang-format -i ${SOURCES} ${HEADERS} ${TEST_SOURCES} ${TEST_HEADERS}

test_release:
	@cmake . -B ${BUILD_RELEASE_DIR} -D CMAKE_BUILD_TYPE=Release $(SAN_OPTIONS) -D BUILD_TESTS=ON
	@cmake --build ${BUILD_RELEASE_DIR}
	${BUILD_RELEASE_DIR}/$(PROJECT_NAME)-test

test_debug:
	@cmake . -B ${BUILD_RELEASE_DIR} -D DCMAKE_BUILD_TYPE=Debug $(SAN_OPTIONS) -D BUILD_TESTS=ON
	@cmake --build ${BUILD_RELEASE_DIR}
	${BUILD_RELEASE_DIR}/$(PROJECT_NAME)-test

clean:
	rm -rf $(BUILD_RELEASE_DIR) $(BUILD_DEBUG_DIR) 
