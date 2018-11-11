all: ipv4c
ipv4c: ipv4c.c
	gcc -o ipv4c ipv4c.c -lm
clean:
	  $(RM) ipv4c
