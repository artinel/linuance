compile:
	gcc -o app main.c $(shell pkg-config --cflags --libs gtk4)
execute:
	./app
clean:
	rm app
run:compile execute clean
