from sys import argv, exit
import csv

def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    seqs = []
    people = []

    with open(argv[1], mode="r") as database:
        reader = csv.DictReader(database)
        seqs = reader.fieldnames[1:]
        for row in reader:
            people.append(row)

    seqCount = dict.fromkeys(seqs, 0)

    with open(argv[2], mode="r") as sequence_file:
        sequence = sequence_file.readline()
        for seq in seqs:
            seqCount[seq] = find_repeats(sequence, seq)

    for person in people:
        c = 0

        for seq in seqs:
            if int(person[seq]) != seqCount[seq]:
                continue
            c += 1

        if c == len(seqs):
            print(person['name'])
            exit(0)

    print("No match")
    exit(1)


def find_repeats(sequence, seq):
    l = len(seq)

    ma = 0
    for x in range(len(sequence)):
        count = 0

        if sequence[x: x + l] == seq:
            count += 1
            while sequence[x: x + l] == sequence[x + l: x + (2 * l)]:
                count += 1
                x += l

        if count > ma:
            ma = count

    return ma


if __name__ == "__main__":
    main()