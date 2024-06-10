# Section 4

Pointers provide you to access and manipulate data at specific memory locations

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

swap(&a, &b);

Practical use includes opening a file and reading/writing
**fopen** opens file for r/w
**fclose** closes a file - always do this to files you open

FILE *f = fopen("hi.txt", "r"); //r - read, w - write

**fread** reads data from a file into buffer
**fwrite** writes data from butter to file
a buffer is a piece of memory that can temporarily store some data in the file

Reading a file involves answering a few questions:
1. From where are you reading?
2. To where are you reading?
3. What size is each block of data you want to read?
4. How many blocks do you want to read?

fread(to where?, what size? (byte), how many?, from where?)
fread(buffer, 1, 4, f)
fwrite is opposite ends
fwrite(from where?, what size?, how many?, to where?)

As you call fread, f keeps moving to point to whats left of the file

It is important when reading files to know how many bytes the info is.
For pdf example, int buffer will NOT work instead of uint8_t buffer, it is the wrong size. An int is 4 bytes, a pdf is chunked in 1 byte sizes.
