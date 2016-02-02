
all: gethttp webcrawl

gethttp: gethttp.cpp openhttp.cpp
	g++ -o gethttp -g gethttp.cpp openhttp.cpp -lnsl -lsocket

webcrawl: webcrawler.cpp openhttp.cpp gethttp.cpp
	g++ -o webcrawl webcrawler.cpp openhttp.cpp -lnsl -lsocket

clean:
	rm -f *.o gethttp core
	rm -f *.o webcrawler core
	rm -f *.txt


