Small POS


Author: Michael N. Bilgore


Description:

Small POS is a small open source project to keep track of sales
for a small portable sales environment (fairs, craft shows, conventions
, etc.).  It aims to provide a fairly simple and reliable enviroment to
record sales for future review.  It must be very efficient so that it 
can run on cheap portable hardware such as a raspberry pi.


Work so far:

Right now there are a few limited working features.  You can add to the
till, remove from the till, and display the till balance.  You can also
sell an item of a price you then specify.  Selling an item adds the
item's price to the till balance.


Windows testing instructions:

included is a script to test out the program on windows.  to use
open up git bash in the repo directory (gcc.exe must be in the
windows path) run: 

	chmod +x wintest.sh

this only
must be done one time you can then run the script with the following
command:

	./wintest.sh

This will compile the program into a file pos.exe run the file then
remove the file.

How can you help?

Well any contribution is a good one and I appreciate anything from
a friendly comment all the way up to significant coding and design
requests.  That being said if you are looking for a job here are
some things that need immediate attention: 

~revamp the way data is output to the console just to make it easier to look at

~add a feature to add small reason for manual input and outputs

~add a feature to record and print a history of sales and manual input/outputs

~add a feature to save and load data in between program execution

~add a feature to add an item to a "catalogue" of items that all have a short description price and sku number

~add a feature to save/load the product catalogue in between program executions

~add a feature to handle save/load and change tax rate



Contributors:

Author (Michael N. Bilgore (Kaiden1002))



mingw compile:

	gcc pos.c functions.c -o pos.exe
	
	
gcc compile:

	gcc pos.c functions.c -o pos
