vms-manager-server: 
	gcc -o vms-manager-server server.c && chmod +x vms-manager-server

#Compilation of server sources files and making the file executable (Linux)

vms-manager-client: 
	gcc -o vms-manager-client client.c && chmod +x vms-manager-client

#Compilation of client sources files and making the file executable (Linux)

run: vms-manager-server vms-manager-client
	./vms-manager-server & ./vms-manager-client

#Running the server and client with default values (no args)

clean:
	rm -f vms-manager-server vms-manager-client

#Removing the server and client executables

.phony: vms-manager-server vms-manager-client run clean

#Making the targets phony to avoid conflicts with files with the same name
