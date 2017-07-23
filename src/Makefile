# Makefile of cpp program
#

CC = g++

all: katen_shell

all_test:all
	../bin/katen_shell

katen_shell: 
	$(CC) shell/*.cpp -o ../bin/katen_shell

neural_network: neural_network/*.cpp
	$(CC) neural_network/*.cpp -o ../bin/neural_network_test

neural_network_test: neural_network
	../bin/neural_network_test

dynamic_network: dynamic_network/*
	$(CC) dynamic_network/*.cpp -o ../bin/dynamic_network_test

dynamic_network_test: dynamic_network
	../bin/dynamic_network_test

math_util: math/*
	$(CC) math/*.cpp -o ../bin/math_util_test

math_util_test: math_util
	../bin/math_util_test
