import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py \"DB FILENAME\" \"SEQUENCE FILENAME\"")

    # TODO: Read database file into a variable
    str_list=[]
    database = []
    test = ['agat','tbf','sdf']
    with open(sys.argv[1]) as db_file:
        h_reader = csv.reader(db_file)
        str_list = next(h_reader)[1::]
        db_file.seek(0)
        reader = csv.DictReader(db_file)
        for row in reader:
            for key in row:
                if (key != 'name'):
                    row[key] = int(row[key])
            database.append(row)


    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as seq_file:
        sequence = seq_file.read().rstrip()
    # TODO: Find longest match of each STR in DNA sequence
    candidate = {}
    for seq in str_list:
        candidate[seq] = longest_match(sequence,seq)

    # TODO: Check database for matching profiles

    for person in database:
        match_count=0
        for key in candidate:
            if(candidate[key]==person[key]):
                match_count +=1
        if (match_count == len(str_list)):
            return print(f"{person['name']}")

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
