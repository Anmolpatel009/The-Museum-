#!/bin/bash

# C++ Build Script
# =================
# This script compiles all C++ examples in the repository

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Directories
SOURCES=(
    "STL/vector_example.cpp"
    "STL/list_example.cpp"
    "STL/stack_queue_example.cpp"
    "STL/map_set_example.cpp"
    "Data-Structures/linked_list.cpp"
    "Data-Structures/binary_search_tree.cpp"
    "Data-Structures/graph.cpp"
    "Algorithms/sorting_algorithms.cpp"
    "Algorithms/searching_algorithms.cpp"
    "Dynamic-Programming/dynamic_programming.cpp"
    "Concepts/oop_concepts.cpp"
    "Concepts/memory_management.cpp"
)

OUTPUT_DIR="build"

# Check if compiler is available
if ! command -v g++ &> /dev/null; then
    if ! command -v clang++ &> /dev/null; then
        echo -e "${RED}Error: No C++ compiler found (g++ or clang++)${NC}"
        echo -e "${YELLOW}Please install a C++ compiler first${NC}"
        echo -e "Ubuntu/Debian: sudo apt-get install g++"
        echo -e "CentOS/RHEL: sudo yum install gcc-c++"
        echo -e "macOS (Homebrew): brew install gcc"
        exit 1
    fi
    COMPILER="clang++"
else
    COMPILER="g++"
fi

# Create build directory
mkdir -p "$OUTPUT_DIR"

# Compile each file
echo -e "${BLUE}Compiling C++ examples...${NC}"

for source in "${SOURCES[@]}"; do
    if [ -f "$source" ]; then
        filename=$(basename "$source" .cpp)
        output="$OUTPUT_DIR/$filename"
        
        echo -e "${YELLOW}Compiling $source...${NC}"
        
        if $COMPILER -std=c++11 "$source" -o "$output"; then
            echo -e "${GREEN}✓ Successfully compiled $filename${NC}"
        else
            echo -e "${RED}✗ Failed to compile $source${NC}"
            continue
        fi
    else
        echo -e "${RED}✗ Source file not found: $source${NC}"
    fi
done

echo -e "${BLUE}\n=== Build Summary ===${NC}"
SUCCESS_COUNT=$(find "$OUTPUT_DIR" -type f -executable | wc -l)
TOTAL_COUNT=${#SOURCES[@]}
echo -e "Successfully compiled: ${GREEN}$SUCCESS_COUNT${NC}"
echo -e "Total files: ${YELLOW}$TOTAL_COUNT${NC}"

if [ $SUCCESS_COUNT -ne $TOTAL_COUNT ]; then
    echo -e "${RED}Some files failed to compile${NC}"
else
    echo -e "${GREEN}All files compiled successfully!${NC}"
fi

echo -e "\n${BLUE}=== Available Executables ===${NC}"
for file in "$OUTPUT_DIR"/*; do
    if [ -x "$file" ]; then
        echo -e "  ${YELLOW}$(basename "$file")${NC}"
    fi
done

echo -e "\n${BLUE}=== Usage Examples ===${NC}"
echo -e "Run vector example: ${YELLOW}./$OUTPUT_DIR/vector_example${NC}"
echo -e "Run linked list example: ${YELLOW}./$OUTPUT_DIR/linked_list${NC}"
echo -e "Run sorting algorithms: ${YELLOW}./$OUTPUT_DIR/sorting_algorithms${NC}"

echo -e "\n${BLUE}=== Cleanup ===${NC}"
echo -e "To clean up build files: ${YELLOW}rm -rf $OUTPUT_DIR${NC}"
