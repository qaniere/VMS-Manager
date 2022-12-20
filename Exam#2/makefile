server: 
	gcc -o server.out server.c && chmod +x server.out

#Compilation of server sources files and making the file executable (Linux)

client: 
	gcc -lncurses -o client.out client.c && chmod +x client.out

#Compilation of client sources files and making the file executable (Linux)

launch-server: server
ifdef port
	./server.out $(port)
else
	./server.out
endif
#Launch the server

launch-client: client
ifdef port
ifdef ip
	./client.out $(ip) $(port)
else
	./client.out localhost $(port)
endif
else
	./client.out
endif

#Launch the client

pdf:
	pandoc -o RÉPONSES.pdf -f markdown-implicit_figures README.MD

#Generate the pdf file from the README.MD file

clean:
	rm -f server.out client.out

#Removing the server and client executables

count-lines:
	wc -l *.c *.h */**.c */**.h

## Counting the number of lines of the project

.PHONY: server client laucnh-client launch-server run clean
#Making the targets phony to avoid conflicts with files with the same name
