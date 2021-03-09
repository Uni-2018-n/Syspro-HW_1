FLAGS = -std=c++11 -Wall -g -o
SOURCE = main.cpp skipList.cpp
ITEM = main

run : compile
	./$(ITEM)

mem : compile
	valgrind --leak-check=full ./$(ITEM)

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
