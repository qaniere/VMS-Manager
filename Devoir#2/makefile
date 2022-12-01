vms-manager-server: 
	gcc -o vms-manager-server server.c && chmod +x vms-manager-server

#Compilation of server sources files and making the file executable (Linux)

vms-manager-client: 
	gcc -lncurses -o vms-manager-client client.c && chmod +x vms-manager-client

#Compilation of client sources files and making the file executable (Linux)

launch-server: vms-manager-server
	./vms-manager-server

#Launch the server

launch-client: vms-manager-client
	./vms-manager-client

#Launch the client

clean:
	rm -f vms-manager-server vms-manager-client

#Removing the server and client executables

.PHONY: vms-manager-server vms-manager-client laucnh-client launch-server run clean
#Making the targets phony to avoid conflicts with files with the same name
