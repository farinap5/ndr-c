GREEN  := $(shell tput -Txterm setaf 2)
YELLOW := $(shell tput -Txterm setaf 3)
WHITE  := $(shell tput -Txterm setaf 7)
CYAN   := $(shell tput -Txterm setaf 6)
RESET  := $(shell tput -Txterm sgr0)

UNAME := $(shell uname) ## Prone to error (in windows)
ARCHT := $(shell uname -m)
UNAMEP:= $(shell uname -smr)

CC=gcc
RNAME := $(shell cat /dev/random | head -c 32 | md5sum | head -c 12)
NM="ndrc"
all: help

## Run
run: ## Build and run. Use FILE="math file".
	@echo "-> Compiling"
	@cd vm;$(CC) -o ../comp/ndrvm main.c
	@cd assembler;$(CC) -o ../comp/ndrasm main.c
	@cd parser;$(CC) -o ../comp/parser main.c parser.c lexer.c
	@echo "#########-> Running Parser"
	@comp/parser -f $(FILE) -o comp/$(RNAME).as
	@echo "Built on " >> comp/$(RNAME).as
	@date >> comp/$(RNAME).as
	@echo "#########-> Running Assembler"
	@comp/ndrasm comp/$(RNAME).as -o comp/$(RNAME).mem
	@echo "#########-> Running Virtual Machine"
	@comp/ndrvm -f comp/$(RNAME).mem
	

## Build
build: ## Build project and and link all files 
	@cd vm;$(CC) -o ../comp/ndrvm main.c
	@cd assembler;$(CC) -o ../comp/ndrasm main.c
	@cd parser;$(CC) -o ../comp/parser main.c parser.c lexer.c

## Run Build
runb: ## Run a previous made build

build-psr: ## Build the parser
	@cd parser;$(CC) -o ../comp/parser main.c parser.c lexer.c

build-psr-run: ## Build the parser and run it against FILE="math file"
	@cd parser;$(CC) -o ../comp/parser main.c
	@comp/parser -f $(FILE) -o comp/$(RNAME).as


build-vm: ## Build the virtual machine
	@cd vm;$(CC) -o ../comp/ndrvm main.c

build-vm-run: ## Build the virtual machine and run it
	@cd vm;$(CC) -o ../comp/ndrvm main.c && ../comp/ndrvm

build-asm: ## Build assembler
	@cd assembler;$(CC) -o ../comp/ndrasm main.c

build-asm-run: ## Build assembler and run it
	@cd assembler;$(CC) -o ../comp/ndrasm main.c && ../comp/ndrasm

## Test
test: ## Run tests of the project
	@echo "-> Compiling"
	@cd vm;$(CC) -o ../comp/ndrvm main.c
	@cd assembler;$(CC) -o ../comp/ndrasm main.c
	@cd parser;$(CC) -o ../comp/parser main.c parser.c lexer.c
	@echo "#########-> Running Parser"
	@echo "5 + 5 + 5" > comp/$(RNAME).mth
	@comp/parser -f comp/$(RNAME).mth -o comp/$(RNAME).as
	@echo "Built on " >> comp/$(RNAME).as
	@date >> comp/$(RNAME).as
	@echo "#########-> Running Assembler"
	@comp/ndrasm comp/$(RNAME).as -o comp/$(RNAME).mem
	@echo "#########-> Running Virtual Machine"
	@comp/ndrvm -f comp/$(RNAME).mem
	@clear
	@echo "No errors reported! COOL!"

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
