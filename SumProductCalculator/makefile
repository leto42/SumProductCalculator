run.o : driver.o Real.o 
	g++ -g -o run.o driver.o Real.o 

driver.o : driver.cpp 
	g++ -g -c driver.cpp

Real.o : Real.cpp Real.h
	g++ -g -c Real.cpp

clean : 
	rm *.o
