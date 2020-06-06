# spellchecker
A command-line program that loads a dictionary file into memory and constructs a hash table using the [djb2 Hash Function](http://www.cse.yorku.ca/~oz/hash.html), which is then used to spell-check text and print all misspelled words to the user.

Example usage:
```
$ ./speller dictionaries/large texts/austen.txt
```
or
```
$ ./speller texts/austen.txt
```

If no argument is passed for the dictionary to be used, it will default to using dictionaries/large which contains 143,091 words.

Example performance (in seconds) for Pride and Prejudice, by Jane Austen:
```
./speller texts/austen.txt

...

WORDS MISSPELLED:     1614
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        125203
TIME IN load:         0.02
TIME IN check:        0.09
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.12
```