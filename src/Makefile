# Makefile of cpp program
#

CC = g++
INCLUDES:=.

all: katen_shell

all_test:all
	../bin/katen_shell


katen_shell: 
	$(CC) shell/*.cpp -o ../bin/katen_shell

neural_network: neural_network/*.cpp
	$(CC) neural_network/*.cpp -o ../bin/neural_network_test

neural_network_test: neural_network
	../bin/neural_network_test

dynamic_network: dynamic_network/* dmath/*
	$(CC) dynamic_network/*.cpp dmath/util.cpp -o ../bin/dynamic_network_test -I $(INCLUDES)

dynamic_network_test: dynamic_network
	../bin/dynamic_network_test

math_util_test: math_util
	$(CC) dmath/*.cpp -o ../bin/math_util_test
	../bin/math_util_test
