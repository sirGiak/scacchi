CC = gcc
CFLAGS = -g -Wall
TARGET = scacchi
OBJS = scacchi.o utils.o
VERS = 1.0
PACKAGE = $(TARGET)-$(VERS)
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET)
	
package:
	#eseguire come root
	sudo mkdir -p $(PACKAGE)/usr/bin
	#mkdir -p scacchi/usr/bin
	
	sudo cp $(TARGET) $(PACKAGE)/usr/bin/$(TARGET)
	sudo chown root:root $(PACKAGE)/usr/bin/$(TARGET)
	sudo mkdir -p $(PACKAGE)/DEBIAN
	
	echo "Package: $(PACKAGE)\nArchitecture: all\nVersion: $(VERS)\nSection: games\nMaintainer: Local user <root@localhost>\nPriority: optional\nStandards-Version: 4.7.0\nDescription: Scacchi sul terminale\n" > $(PACKAGE)/DEBIAN/control
	
	
	dpkg-deb -b $(PACKAGE)
	

.PHONY: all clean package
