FLAGS = -std=c++11 -Wall -g -o
SOURCE = main.cpp classes.cpp
ITEM = vaccineMonitor

run : compile
	./$(ITEM) -c records.txt -b 100000

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
