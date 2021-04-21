from csv import DictReader, reader
from sys import argv

if len(argv) < 3:
    print("USAGE --> python dna.py <database>.csv <sequence>.txt")
    exit(1)
    
with open(argv[1]) as peoplefile:
    people = reader(peoplefile)
    for row in people:
        dnaData = row
        dnaData.pop(0)
        break

with open(argv[2]) as seqfile:
    seqreader = reader(seqfile)
    for row in seqreader:
        seqlist = row

seq = seqlist[0]

sequences = {}

for item in dnaData:
    sequences[item] = 1

for key in sequences:
    length = len(key)
    max = 0
    temp = 0
    for i in range(len(seq)):
        while temp > 0:
            temp -= 1
            continue

        if seq[i: i + length] == key:
            while seq[i - length: i] == seq[i: i + length]:
                temp += 1
                i += length

            if temp > max:
                max = temp

    sequences[key] += max

with open(argv[1], newline='') as peoplefile:
    people = DictReader(peoplefile)
    for person in people:
        match = 0
        for dna in sequences:
            if sequences[dna] == int(person[dna]):
                match += 1
        if match == len(sequences):
            print(person['name'])
            exit(0)

    print("No match")
