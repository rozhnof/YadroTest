CPPCHECK_OPTIONS = --language=c++ --enable=all --inconclusive --suppress=missingIncludeSystem 
CMAKE = CMakeLists.txt

SOURCES = $(wildcard src/*.cc)
HEADERS = $(wildcard include/*.h)
TEST_DIR = tests
BUILD_DEBUG_DIR = build_debug
BUILD_RELEASE_DIR = build_release

PURPLE  	= '\033[0;35m'
YELLOW  	= '\033[1;33m'
BLUE  		= '\033[1;36m'
GREEN 		= '\033[0;32m'
LIGTH_GREEN = '\033[1;32m'
RED  		= '\033[0;31m'
NC  		= '\033[0m'


.PHONY: all clean check_format apply_format

all: build_release

build_release: $(BUILD_RELEASE_DIR)/$(CMAKE)
	cd $(BUILD_RELEASE_DIR) && cmake .. -DCMAKE_BUILD_TYPE=Release && make

build_debug: $(BUILD_DEBUG_DIR)/$(CMAKE)
	cd $(BUILD_DEBUG_DIR) && cmake .. -DCMAKE_BUILD_TYPE=Debug -DUBSAN=ON -DASAN=ON && make

$(BUILD_RELEASE_DIR)/$(CMAKE): $(CMAKE)
	mkdir -p $(BUILD_RELEASE_DIR) && cp $< $@

$(BUILD_DEBUG_DIR)/$(CMAKE): $(CMAKE)
	mkdir -p $(BUILD_DEBUG_DIR) && cp $< $@

check_format:
	clang-format -n $(SOURCES) $(HEADERS)
	cppcheck $(CPPCHECK_OPTIONS) $(SOURCES) $(HEADERS)

apply_format:
	clang-format -i $(SOURCES) $(HEADERS)

test_all: 	test_release \
			test_release_ubsan \
			test_release_asan \ 
			test_release_ubsan_asan \
          	test_debug \ 
			test_debug_ubsan \ 
			test_debug_asan \
			test_debug_ubsan_asan

test_release: $(BUILD_RELEASE_DIR)/$(CMAKE)
	cd $(BUILD_RELEASE_DIR) && cmake -DCMAKE_BUILD_TYPE=Release .. && make
	cd $(BUILD_RELEASE_DIR) && ./computer-clab-manager-test

test_debug: $(BUILD_DEBUG_DIR)/$(CMAKE)
	cd $(BUILD_DEBUG_DIR) && cmake -DCMAKE_BUILD_TYPE=Debug .. && make
	cd $(BUILD_DEBUG_DIR) && ./computer-clab-manager-test

test_release_ubsan: TEST_FLAGS := -DUBSAN=ON
test_release_ubsan: test_release

test_release_asan: TEST_FLAGS := -DASAN=ON
test_release_asan: test_release

test_release_ubsan_asan: TEST_FLAGS := -DUBSAN=ON -DASAN=ON
test_release_ubsan_asan: test_release

test_debug_ubsan: TEST_FLAGS := -DUBSAN=ON
test_debug_ubsan: test_debug

test_debug_asan: TEST_FLAGS := -DASAN=ON
test_debug_asan: test_debug

test_debug_ubsan_asan: TEST_FLAGS := -DUBSAN=ON -DASAN=ON
test_debug_ubsan_asan: test_debug

$(BUILD_RELEASE_DIR)/$(CMAKE):
	mkdir -p $(BUILD_RELEASE_DIR) && cp $(CMAKE) $@

$(BUILD_DEBUG_DIR)/$(CMAKE):
	mkdir -p $(BUILD_DEBUG_DIR) && cp $(CMAKE) $@


clean:
	rm -rf $(BUILD_RELEASE_DIR) $(BUILD_DEBUG_DIR) 
