FLAGS = -std=c++11 -Wall -g -o
SOURCE = main.cpp Structures/skipList.cpp Structures/bloomFilter.cpp classes.cpp generalList.cpp Structures/countryList.cpp Structures/virusesList.cpp Structures/populationStatistics.cpp
ITEM = vaccineMonitor
ARGS = -c input.txt -b 100000

compile : $(SOURCE)
	g++ $(FLAGS) $(ITEM) $(SOURCE)

run : compile
	./$(ITEM) $(ARGS)

mem: compile
	valgrind --leak-check=full ./$(ITEM) $(ARGS)

debug : $(ITEM)
	gdb $(ITEM)

clean :
	-rm $(ITEM)

compress: $(SOURCE)
	mkdir $(ITEM)_$(USER)
	cp $(SOURCE) $(ITEM)_$(USER)
	tar -cvzf $(ITEM)_$(USER).tar.gz $(ITEM)_$(USER)
	rm -r $(ITEM)_$(USER)
