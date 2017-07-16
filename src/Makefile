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

