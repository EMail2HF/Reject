TARGET=client

OBJS=main.o client.o moc_client.o processdata.o hash_util.o 

CC=g++
INSTDIR=.
CFLAGS_PIC=
HOST=Linux
CPPFLAGS=${CFLAGS_PIC}
#LDFLAGS=-shared -Wl,-rpath,./ -Wl,-rpath-link,../
LDFLAGS=
SYSTEMPATH=
INCLUDE = -I/usr/local/Trolltech/Qt-4.8.4/include/QtGui -I/usr/local/Trolltech/Qt-4.8.4/include/QtCore -I /usr/local/Trolltech/Qt-4.8.4/include

LIBS= -L /usr/local/Trolltech/Qt-4.8.4/lib -lQtGui -l QtCore





DEBUG= -g
RM=rm -f

$(TARGET):$(OBJS)
	$(CC) $(DEBUG) $(CPPFLAGS) $(OBJS) $(LDFLAGS) -o $@ $(LIBPATH) $(LIBS)
	
%.o:%.cpp
	$(CC) $(DEBUG) $(CPPFLAGS) -c $< -o $@ $(INCLUDE)


.PHONY:clean install
clean:
	$(RM) $(TARGET) *.gdb $(OBJS)

install:$(TARGET)
	cp -f $(TARGET) ../lib/
