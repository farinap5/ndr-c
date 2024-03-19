GREEN  := $(shell tput -Txterm setaf 2)
YELLOW := $(shell tput -Txterm setaf 3)
WHITE  := $(shell tput -Txterm setaf 7)
CYAN   := $(shell tput -Txterm setaf 6)
RESET  := $(shell tput -Txterm sgr0)

UNAME := $(shell uname) ## Prone to error (in windows)
ARCHT := $(shell uname -m)
UNAMEP:= $(shell uname -smr)

CC=gcc
NM="ndrc"
all: help

## Run
run: ## Build project in volatile mode
	@echo "Test"

## Build
build: ## Build project and and link all files (run & clear)
	@echo "Test"

build-vm: ## Build the virtual machine
	@cd vm;gcc -o ../comp/ndrvm main.c

build-vm-run: ## Build the virtual machine and run it
	@cd vm;gcc -o ../comp/ndrvm main.c && ../comp/ndrvm

build-asm: ## Build assembler
	@cd assembler;gcc -o ../comp/ndrasm main.c

build-asm-run: ## Build assembler and run it
	@cd assembler;gcc -o ../comp/ndrasm main.c && ../comp/ndrasm

## Test
test: ## Run tests of the project
	@echo "Test"

## Clear
clear: ## Clear compilation garbage
	@rm comp/*

## Help
help: ## Show this help
	@echo ''
	@echo 'Usage:'
	@echo '  ${YELLOW}make${RESET} ${GREEN}<target>${RESET}'
	@echo ''
	@echo 'Targets:'
	@awk 'BEGIN {FS = ":.*?## "} { \
		if (/^[a-zA-Z_-]+:.*?##.*$$/) {printf "    ${YELLOW}%-20s${GREEN}%s${RESET}\n", $$1, $$2} \
		else if (/^## .*$$/) {printf "  ${CYAN}%s${RESET}\n", substr($$1,4)} \
		}' $(MAKEFILE_LIST)