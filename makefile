CC = g++
PROGRAM = mandelbrot

$(PROGRAM).out : main.cpp
	$(CC) main.cpp -o $(PROGRAM).out

run:
	./$(PROGRAM).out

clean:
	rm *.out
	rm *.o
