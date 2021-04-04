Antonis Kalamakis SDI1800056

This project is organized in 4 sections.
First section is the main.cpp file. The main.cpp file has our main function in which first
of all we are reading the input provided in the command line from the user. After that we're
creating a GlistHeader header list from the generalList files that i will explain later and 
read each line of the file provided from the input and insert the data read into the main_list 
with the help of the insertRecord function. This function is used to insert a record inside our 
database and it received 2 arguments. The first one is the full line that we've read (or created 
in case we use some of the commands explained later) and a boolean argument that determines if 
(In case) we have a citizen that was previously marked as not-vaccinated for a virus we want 
to make the citizen marked as vaccinated. This is not allowed when we parsing from the input 
file so we set that argument to false.
After finishing with all the data parsing from the input file because of the fact that everything 
is stored inside the main_list's list there is no need to keep the file open or keep any memory 
used for saving the string for the path to input file so we deallocate the memory and close the 
opened file.
Finally the last section of the main file in which we receive input from the user with the 
commands until the user runs the command "/exit" and deallocate any necessary memory and 
exits the program. It's good to mention that after we read the line with the command that 
the user wants us to run we check and format the date (if provided) and make it into a "yyyy-mm-dd" 
formated date for comparing reasons. The user can provide a date like "d-m-yyyy" etc. As instructed 
in piazza the commands that include providing 2 dates must provide the dates. Dates arguments are not optional. 
If the user makes an error and provides only one date then an error will be printed and skip the command 
that the user provided.

The second section of the project is the classes.cpp/.hpp files. Here we have one class that each 
object of this class is a citizen with all the data that we need to store for the citizen. 
Also in this files we have a flipDate and checkAndFormatDate function that error checks the 
provided date and fixes is if possible or returns an empty string to tell the caller function 
that there is an error with the date and cant continue.

The third section of the project is the generalList.cpp/.hpp files. Here we have 2 classes. 
The first class is the list header that has the start and end node of our list, a list header with 
a list with all the countries that our program has read and a header with a list with all the 
viruses and any data needed to be stored for each virus.
This list is a list for the citizen so we will not have any duplicate citizens stored in our 
memory. Since this is actually the "front" of the program we also have functions used to 
run the commands and insert and search functions used to control the list.
The function insertRecord first of all reads the line and breaks it into an array of strings 
called temp with 8 cells. After that we are checking the input if its correct by seeing if 
the age is in the desired range, if the record is specifying if its vaccinated or not and 
if yes there is a date provided or if no there is no date provided.
Since we are not interested into having duplicate data inside our list we must pay O(N) to 
first search if there is the citizen the record is referring to already in the system 
by searching with the id number, if yes simply returns the node of the citizen in the 
tmp variable and checks if its really the same citizen(in case we have two citizens 
with the same id). If the search function returned NULL this means that the citizen 
is not inside our database and we need to create a new node at the end of the list. 
For the scenario that the citizen isn't inside our database first, we need to make sure that 
the country that the citizen is from isn't already inside the countries list so we wont 
have any duplicate, after that we simply create a new citizenRecord object and a new list 
node and add it at the end of the list.
In every scenario we must do the same thing(as we did for the citizen and for the countries) 
for the viruses too! simply check if the virus referring in the record already exists in the 
system, if not creates a new virus and inserts the record in the virus node so it will do the 
necessary actions there(bloom filters, skip lists etc).
Some functions that exists in generalList files are simply interface functions that calls 
more specific functions inside the for example viruses lists, these functions will be explained 
in the fourth section of the project. Some functions like populationStatus functions or 
vaccinate now are needed to be doing more things.
For populationStatus command we have 2 functions, in case we have a country specified or 
we don't. These functions are exactly the same but when we call the more specific functions 
of the statistics classes(more on populationStatistics files) we also provide the country we need.
For the vaccinateNow command because of the fact that we need to vaccinate an already 
existing citizen(or not) we first need to check if the citizen is already vaccinated or 
not. If not we get the current date from the time library and create a full string and 
call the insert function like if we are reading a record from a file and passing it to this 
function. If the citizen is already set to not-vaccinated for this virus before, as we will see 
in the virusesList files the program simply does all necessary actions and removes the citizen 
from the not-vaccinated skip list and adds the citizen to the vaccinated skip list.
Side note for insertCitizenRecord function we use the insertRecord function to insert the read 
line with the boolean variable set to true so its going to be possible to vaccinate one citizen 
even if its already set to not-vaccinated in a previous state and setting the vaccination date 
to what ever we wont(on the contrary with vaccinateNow function that sets as vaccination date 
the current date).