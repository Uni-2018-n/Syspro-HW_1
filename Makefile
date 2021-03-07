FLAGS = -std=c++11 -Wall -g -o
SOURCE = main.cpp Structures/skipList.cpp Structures/bloomFilter.cpp classes.cpp generalList.cpp Structures/vacList.cpp Structures/countryList.cpp Structures/virusesList.cpp Structures/STRList.cpp
ITEM = vaccineMonitor

run : compile
	./$(ITEM) -c Data/records.txt -b 100000

debug : $(ITEM)
	gdb $(ITEM)

compile : $(SOURCE)
	g++ $(FLAGS) $(ITEM) $(SOURCE)

clean :
	-rm $(ITEM)

compress: $(SOURCE)
	mkdir $(ITEM)_$(USER)
	cp $(SOURCE) $(ITEM)_$(USER)
	tar -cvzf $(ITEM)_$(USER).tar.gz $(ITEM)_$(USER)
	rm -r $(ITEM)_$(USER)
