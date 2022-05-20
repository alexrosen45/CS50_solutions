import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Read database file into a variable
    database = []

    with open(sys.argv[1]) as csv_file:
        reader = csv.reader(csv_file, delimiter=',')

        for row in reader:
            database.append(row)

    # Read DNA sequence file into a variable
    sequence_file = open(sys.argv[2], "r")
    sequence = sequence_file.read()
    sequence_file.close()

    # Find longest match of each STR in DNA sequence
    longest_matches = []
    for i in range(1, len(database[0])):
        longest_matches.append(longest_match(sequence, database[0][i]))

    # Check database for matching profiles
    # iterate through database rows data
    for i in range(1, len(database)):
        # track for match
        match = ""

        # iterate through database columns data
        for j in range(1, len(database[0])):
            # chekc if subsequence lengths are equal
            if longest_matches[j-1] == int(database[i][j]):
                # set match to identity of subsequence length match
                match = database[i][0]
            else:
                match = ""
                break

        if match != "":
            print(match)
            sys.exit(0)

    print("No match")
    sys.exit(0)


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
