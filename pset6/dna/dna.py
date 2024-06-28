# Code using Short Tandem Repeats (STRs) in DNA to identify who a sequence of DNA belongs to
import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py [database.csv] [sequence.txt]")
        sys.exit(1)

    # Read database file into a variable
    # database itself is a list, while each row in database is a dictionary
    database = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)

    # Convert STR lengths in database to integers from strings
    for person in database:
        # inspired by stack overflow list comprehension string/int searches
        person.update({k: int(v) if v.isnumeric() else v for k, v in person.items()})

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as f:
        dna_sequence = f.read()

    # Find longest match of each STR in DNA sequence
    # Create a dictionary to store length of matches
    str_in_dna = dict()

    for STR in reader.fieldnames[1:]:
        str_in_dna[STR] = longest_match(dna_sequence, STR)

    # Check database for matching profiles
    for person in database:
        # check if the STR counts in the sequence is a subset of each person in the database
        # geeksforgeeks check if one dictionary is subset of other
        match = str_in_dna.items() <= person.items()
        if match:
            return print(person["name"])

    return print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
