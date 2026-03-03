DIST_DIR := dist
ISO_DIR := iso
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
SCRIPTS_DIR := scripts

CXX := g++
CXXFLAGS := -m32 -nostdlib -ffreestanding -I$(INCLUDE_DIR) -O2 -Wall -Wextra

LD := gcc
LDFLAGS := -m32 -nostdlib -T $(SCRIPTS_DIR)/linker.ld

SRC := $(shell find $(SRC_DIR) -name "*.cpp")
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))
