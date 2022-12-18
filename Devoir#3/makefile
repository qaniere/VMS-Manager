vms-manager-server: 
	gcc -o vms-manager-server server.c && chmod +x vms-manager-server

#Compilation of server sources files and making the file executable (Linux)

vms-manager-client: 
	gcc -lncurses -o vms-manager-client client.c && chmod +x vms-manager-client

#Compilation of client sources files and making the file executable (Linux)

launch-server: vms-manager-server
ifdef port
	./vms-manager-server $(port)
else
	./vms-manager-server
endif
#Launch the server

launch-client: vms-manager-client
ifdef port
ifdef ip
	./vms-manager-client $(ip) $(port)
else
	./vms-manager-client localhost $(port)
endif
else
	./vms-manager-client
endif

#Launch the client

pdf:
	pandoc -o manuel.pdf -f markdown-implicit_figures README.MD

#Generate the pdf file from the README.MD file

clean:
	rm -f vms-manager-server vms-manager-client

#Removing the server and client executables

count-lines:
	wc -l *.c *.h */**.c */**.h

## Counting the number of lines of the project

.PHONY: vms-manager-server vms-manager-client laucnh-client launch-server run clean
#Making the targets phony to avoid conflicts with files with the same name
