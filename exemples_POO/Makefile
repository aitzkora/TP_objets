#Purge implicites rules 
.SUFFIXES:
.SUFFIXES: .cpp

# Outils
CXX=g++ -std=c++11
# name of Pdf File 

all: polymorphisme

polymorphisme: polymorphisme.cpp
	$(CXX) -o $@ $<

# Nettoie le repertoire
clean: 
	@echo supprime les executables
	@rm -f polymorphisme
