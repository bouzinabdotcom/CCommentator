# CCommentator
Removes all code except c/c++ type comments from source files.
The idea is to see how well commented your source files are.
If they tell a story without the need to understand the code, you're good to go.
If not, somebody needs write a story.

This program is also an exercice to get introduced to Finite State Machine and their use in syntax analysis.

### State Machine Diagram
![Diagram](diagram.jpeg)

### Compile
Clone project:

    $ git clone https://github.com/bouzinabdotcom/CCommentator

Go to directory:

    $ cd CCommetator

Make:

    $ make

### Run
To run to tool:

    $ ./ccommentator filename [newfilename]
The brackets mean that newfilename is optional the output file will automatically be comments.filename

Example:

    $ ./ccommentator source.c


Outputs comments.source.c on the same directory.

### Let's get meta
Let's use ccommentator on it's source code!

    $ ./ccommentator main.c

main.c

```c
# ./main.c
```

comments.main.c:

```c
# ./comments.main.c
```

Can you understand what it does ?

### A little story :
This tool came to be after I saw one of my progamming profs. use a [python script](https://github.com/thierryseegers/Commentator) to strip source files out of their code leaving just the comments and as always I got curious about it. So I tried to replicate it using basic tests to search for comments and leave them while replacing characters outside the comments with whitespace. I got lost in the complexity and was sure there was a better way to doing it. 
The better (and easier) route was to ask for the script's source code, read it, understand it and then try to replicate it.
So I did that and got a detailed response containing, in addition to the source code (that turned out to be using libclang through python), a roadmap to illuminate the pathway leading to creating my own version (Thanks a lot!). 



