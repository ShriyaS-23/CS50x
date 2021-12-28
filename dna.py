from csv import reader, DictReader
from sys import argv

if len(argv) < 3:
    print("Usage:dna.py sequence.txt database.csv")
    exit()

with open(argv[2]) as DNAfile:
    readDNA = reader(dnafile)
    for row in readDNA:
        DNArow = row

DNA = DNArow[0]

seq = {}

with open(argv[1]) as peoplefile:
    readPeople = reader(peoplefile)
    for row in readPeople:
        DNAseq = row
        DNAseq.pop(0)
        break

for item in DNAseq:
    seq[item] = 1

for key in seq:
    l = len(key)
    tMax = 0
    t = 0
    for i in range(len(DNA)):
        while t > 0:
            t -= 1
            continue

        if DNA[i: i + l] == key:
            while DNA[i - l: i] == DNA[i: i + l]:
                t += 1
                i += l

            if t > tMax:
                tMax = t

    seq[key] += tMax

with open(argv[1], newline='') as peoplefile:
    readPeople = DictReader(peoplefile)
    for person in readPeople:
        match = 0
        for DNA in seq:
            if seq[DNA] == int(person[DNA]):
                match += 1
        if match == len(seq):
            print(person['name'])
            exit()

    print("No match")