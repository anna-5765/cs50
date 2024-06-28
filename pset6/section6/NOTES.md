Python
    Strings
        - no pointer to character needed (char *)
        - no need to declare datatype
        - can use equality operator to compare strings (==)
        - text[i] gives character of string (0 indexed)
        - built in function input() to get string
        - strings come with methods using dot notation
            eg. text.strip() cleans leading and trailing spaces, text.lower() transforms to lowercase, text.capitalize() makes the first letter uppercase
            - still need to assign method to variable
        - a str in python is an object with methods built in
        - words = text.split() will convert string to list
    Loops
        - for _ in _ loop simple way to loop through elements of an object (iterable)
        - if _ in _ can perform linear search
        - [2:] index a list starting at element 2 through the end [inclusive:exclusive]
    Dictionaries
        - key - value pairs
            eg. title - author or both a key
            book = dict()
            book["title"] = "Corduroy"
            book["author"] = "Don Freeman"
            print(book["title"])
        - key errors occur when you try and look something up using the value instead of the key
        - define using curly braces in lecture
Libraries and Modules
    - csv file module
        import csv then use csv.fxn()
    - can import entire library or only import a few functions that you're using
File I/O
    with open(FILENAME, mode) as file:
        file_reader = csv.DictReader(file)
        # text = file.read()
        for row in file_reader:
            ...
    - using with open, the file will close outside of indented lines automatically
