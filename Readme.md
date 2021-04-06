Antonis Kalamakis SDI1800056

TODO: add how it works

This project is organized in 4 sections.
<-*-*-*-*->
    First section is the main.cpp file. The main.cpp file has our main function in which 
first of all we are reading the input provided in the command line from the user. 
After that we're creating a GlistHeader header list from the generalList files that 
i will explain later and read each line of the file provided from the input and 
insert the data read into the main_list with the help of the insertRecord function. 
This function is used to insert a record inside our database and it received 2 arguments. 
The first one is the full line that we've read (or created in case we use some of the 
commands explained later) and a boolean argument that determines if (In case) we have a 
citizen that was previously marked as not-vaccinated for a virus we want to make the 
citizen marked as vaccinated. This is not allowed when we parsing from the input file 
so we set that argument to false.
    After finishing with all the data parsing from the input file because of the fact 
that everything is stored inside the main_list's list there is no need to keep the 
file open or keep any memory used for saving the string for the path to input file 
so we deallocate the memory and close the opened file.
    Finally the last section of the main file in which we receive input from the user 
with the commands until the user runs the command "/exit" and deallocate any necessary 
memory and exits the program. It's good to mention that after we read the line with the 
command that the user wants us to run we check and format the date (if provided) and 
make it into a "yyyy-mm-dd" formated date for comparing reasons. The user can provide 
a date like "d-m-yyyy" etc. As instructed in piazza the commands that include providing 
2 dates must provide the dates. Dates arguments are not optional. 
If the user makes an error and provides only one date then an error will be printed 
and skip the command that the user provided.


<-*-*-*-*->
    The second section of the project is the classes.cpp/.hpp files. Here we have one 
class that each object of this class is a citizen with all the data that we need 
to store for the citizen. Also in this files we have a flipDate and checkAndFormatDate 
function that error checks the provided date and fixes is if possible or returns 
an empty string to tell the caller function that there is an error with the date and 
cant continue.


<-*-*-*-*->
    The third section of the project is the generalList.cpp/.hpp files. Here, we have 2 classes. 
The first class is the list header that has the start and end node of our list, a list 
header with a list with all the countries that our program has read and a header with a list 
with all the viruses and any data needed to be stored for each virus. This list is a list 
for the citizen so we will not have any duplicate citizens stored in our memory. Since this 
is actually the "front" of the program we also have functions used to run the commands and 
insert and search functions used to control the list.

    The function insertRecord first of all reads the line and breaks it into an array of strings 
called temp with 8 cells. After that we are checking the input if its correct by seeing if 
the age is in the desired range, if the record is specifying if its vaccinated or not and 
if yes there is a date provided or if no there is no date provided.
    Since we are not interested into having duplicate data inside our list we must pay O(N) to first 
search if there is the citizen the record is referring to already in the system by searching 
with the id number, if yes simply returns the node of the citizen in the tmp variable and 
checks if its really the same citizen(in case we have two citizens with the same id). If the 
search function returned NULL this means that the citizen is not inside our database and we 
need to create a new node at the end of the list. For the scenario that the citizen isn't inside 
our database first, we need to make sure that the country that the citizen is from isn't already 
inside the countries list so we wont have any duplicate, after that we simply create a new 
citizenRecord object and a new list node and add it at the end of the list.
    In every scenario we must do the same thing(as we did for the citizen and for the countries) 
for the viruses too! simply check if the virus referring in the record already exists in the 
system, if not creates a new virus and inserts the record in the virus node so it will do the 
necessary actions there(bloom filters, skip lists etc).

    Some functions that exists in generalList files are simply interface functions that calls 
more specific functions inside the for example viruses lists, these functions will be 
explained in the fourth section of the project. Some functions like populationStatus functions 
or vaccinate now are needed to be doing more things.

    For the populationStatus command we have 2 functions, in case we have a country specified or we don't. 
These functions are exactly the same but when we call the more specific functions of the 
statistics classes(more on populationStatistics files) we also provide the country we need. 
Here its good to add that in this implementation we first add data from the vaccinated skip 
list and then we append data from the not-vaccinated skip list so we pass the already created 
node(or header) to the skipList::PopulationStatus(or StatusAge) function to append that data.

    For the vaccinateNow command because of the fact that we need to vaccinate an already existing 
citizen(or not) we first need to check if the citizen is already vaccinated or not. If not we 
get the current date from the time library and create a full string and call the insert 
function like if we are reading a record from a file and passing it to this function. If 
the citizen is already set to not-vaccinated for this virus before, as we will see in the 
virusesList files the program simply does all necessary actions and removes the citizen from 
the not-vaccinated skip list and adds the citizen to the vaccinated skip list.
    Side note for insertCitizenRecord function we use the insertRecord function to insert the 
read line with the boolean variable set to true so its going to be possible to vaccinate one 
citizen even if its already set to not-vaccinated in a previous state and setting the vaccination 
date to what ever we wont(on the contrary with vaccinateNow function that sets as vaccination date the current date).

<-*-*-*-*->
    For the fourth and finale section of the project we have the folder Structures in which we 
have all the types that we need to use to implement the assignment and can use them in a library 
like way so its easier to debug and organized as much as possible.


<-*->
    First with the simple things, we have country.cpp/.hpp. These files implement a simple 
linked-list that stores one string* member in each node. This is used so its possible for us 
to check if we already used this country in a previous record and use the same memory as used 
before instead of having multiple memory segments with the same information.



<-*->
    Files virusesList.cpp/.hpp are used to implement our viruses linked list and store all the 
information we need for the specifications of this assignment first of all we have a string 
member that we store the name of the virus, then we have one bloomFilter member that is the 
bloom filter of the specific virus and stores information only for those who are recorded as 
vaccinated(while reading the input file or even by adding it later from the commands) and finaly 
we have two skip lists for those who are recorded as vaccinated and for those who are recorded 
as not-vaccinated, its good to mention that in this implementation we only store as not-vaccinated 
those who have a specific record saying that they are not vaccinated(not those who we don't have 
any information if they are vaccinated or not).

    Same with before we have one header class and the node class. Inside the node class besides the 
setter and getter functions we have one insertRecord function that inserts a record in the skip 
lists or if needed in the bloom filter in the specific virus node. Chose this way because its 
easier to have one variable with the specific virus node in the functions that use this so i wont 
need to pay O(N) multiple times if i need to do multiple things inside a virus and so for that when 
i need to add a new virus i just create it and push data in it with 2 separate functions.
    In the header class we simply store the start and end nodes so inserting is O(1) and a integer 
variable that is set at the constructor of the class with the length of the bloom filter's array. 
Since this is needed by every node in the list we just pass it to the node at its creation.
    For the vaccinateNow function is used by the generalList.cpp/vaccinateNow function and is simply 
doing everything needed for searching if the citizen is marked as vaccinated or not before, if any 
of those were the case simply does the necessary work but if the citizen doesn't have any previous 
records referring to this virus returns false and generalList.cpp function does all the work.
    The other 4 functions inside the header class are self-explained only thing is good to mention is 
the usage of the flipDate function that makes sure that the user sees the date in the correct 
format and not the format the program is storing it.

<-*->
    For populationStatistics.cpp/.hpp files, here we have one simple linked list used for the 
populationStatus and popStatusByAge commands. For simplicity reasons and for not having 
multiple linked lists for each command I've used this list for both files. 
    Each node has multiple integer variables used to store data for each category. The Datevacced, v, pl variables 
are used for populationStatus and the other ones are used for popStatusByAge but 
these variables are only like the populationStatus's variables but for each category.
    Because of the fact that each command could be used with or without specifying the 
country, in both commands, if the country is specified i just use one node but if 
not I simply use the header class of the list and pass to it data with the insert function.
    Its good to mention that the different usage for each command is by using the specified 
function (etc, insertItem and insertItemAge). topCorrectCat is used to top the variables 
in a specific category for the Age function. 

    In this implementation to specify with a simple way what variables we need to top we use a 
int variable b that gets 2, 1 or 0 value. If b== 2 it means that the citizen is vaccinated 
inside the date range specified so we need to top all 3 variables, if b== 1 it means that 
the citizen is vaccinated but outside of the range so we need to top 2 variables and finally 
if b== 0 it means that the citizen is marked as not-vaccinated so we only top 1 variable.
    For printing the statistics we just do the math and calculate the outcome specified for 
the assignment.

<-*->
    For the skipList.cpp/.hpp files, for my implementation i decided that the skip list 
could be a list of lists having one list header for all the layers and each node of 
the header will have one header with the list of items that are in the specific layer. 
    Also decided to put a defined number of layers so the program at the creation of the skip 
list will automatically create n layers set to NULL. Since this list is very complicated 
I've included some briefing comments inside the code that specify how the list works in 
every type of usage.

    Its good to mention that for this implementation because of the fact that we are going to 
use the skip list for seeing who is vaccinated(in vaccinated skip list case) we need to 
store in each node of the layer-linked list the item (id of the citizen), its a pointer 
so we wont have duplicates(same number in citizenRecord or in top layers of the list etc), 
a citizenRecord* from the generalList, a string* named date_vaccinated used to set the date 
of vaccination IF the citizen is vaccinated, if not we simply set it to NULL and 3 members 
used to go to the next, prev or even the same node in the next lower level that we are currently 
in. Finally for these nodes we have multiple constructors specified each one of them why we 
need it, to make it more simple in the insert, search, delete etc functions.

    Generally speaking in this implementation because of the fact that its a list of list I've 
used a technique that allows me to keep things as simple as possible and keep the cost O(logN). 
Simply when i search, insert or delete a node from the skip list i firstly go to the first 
not NULL layer(starting from the end of the list with the end layer the list with the less items) 
and starting searching(inserting or deleting) the item from there. The SkiplistHeader::searchItem 
(again insertItem, deleteItem i wont keep specifying this) could go from the very top layer 
and work its way to the bottom and return the found node if it exists but it may return also 
NULL or a completely different node. If the function returns the node with the same id as the 
one we want it means that we found the node, if the function returns NULL it means that the node 
doesn't exist but if the function returns a different node it means that we cant find this from 
this layer so we need to go to the next one and search again(because the first item of the layer 
is > than the item we search). Finally keep doing that until we have found the item or we get NULL.

    Insert and search in the way it works is generally the same but the main difference is that in 
the skipHeader::insertItem function first we need to determine how many layers will the item go 
by doing a coin toss until we hit something different than one or hit the maximum layers allowed. 
Also we have a skiped_layers variable to count how many layers were empty or were skipped because 
the first item was > than the item we have. So we could add the item in those layers (if needed) 
because there is no way for the function SkiplistHeader::insertItem to do it(this function does 
it for the layers that it gone lower from inside the function NOT the layers we've skipped).

    Delete function is pretty much same with search but deletes the nodes with the specific id we 
have and fixes all the connections for the lists to work. Here is the main reason why we use a 
dual linked list instead of a one way linked list because we need to be able to remove the node 
and still make sure the connections are good.

    In SkiplistHeader we use the 3 functions talked about before and also at the comments of the code 
but its good to include here some implementation specifications for the insertItem function.
    Here to make sure that we add in the correct position in the top layers of the skip list the 
added node we have an array called level_array with the nodes that we were right before we jump 
one layer down and with the help of the lvl_counter variable we have the len of the array right 
away to be jumped back to the layer we like to append if needed the node. Also its good to mention 
that here we only create one main node with all the necessary data and add it to the layer with 
all the items and also we create multiple nodes with only prev-next-lower_level(if needed) and 
the item members filled because those are "dummy" nodes and if we go in a dummy node that has the 
item we are trying to find or insert or delete we loop to the last layer and do necessary actions there.

    Finally at the end of skipList.cpp/.hpp files we have the functions used by the commands 
populationStatus and popStatusByAge that we explained before, also here we see more in 
depth the way we tell the statistics functions how to handle the information we have(with date
compares etc). More information in the comments inside the code.
