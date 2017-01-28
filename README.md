Data parser - A Personal pet project of mine to help me learn c++,
It is a class libary that parses data formats from files.
Currently supports
- Endianness
- read and write
- data types -- byte, short, long, float, double and arrays
Looking to add support for bitfields, opengl quaternion and opengl vectors.
I will accept any suggestions, questions or criticism 
- either email, through issue submissions, or otherwise. 

I suppose the other thing i must mention here is that I understand that
its much more efficient to read a file and pass the data to structures, however
There are some cases where it is useful to read data from files manually.
such as when endianess matters.

~ Samson

References:
http://stackoverflow.com/questions/12791864/c-program-to-check-little-vs-big-endian#12792301
Marcus's Endianness Test Algorithm was used here.
