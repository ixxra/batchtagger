batchtagger
===========

Command line program which tags multimedia files based on taglib.

Dependencies:
Taglib for reading/writing files.

KDE* 

*Note that the program uses KCmdLineArgs for parsing options. This dependencie is easily avoidable, 
but you would need to get another command line parser, or write your own.

Usage:

batchtagger [-t title] [-a artist] [-l album] [-r tracknr] [file1 ...]

if you invoke the program only with the file names, it will print the metadata of each file.
