from csv import reader, DictReader
from sys import argv, exit

seqs = {}

#check input
if len(argv) < 3:
    print("Usage:", "python dna.py data.csv sequence.txt")
    exit(1);

# ma STR seq
def get_max(dna, STR):
    y = len(STR)
    x = 0
    ma = 0;
    for x in range(len(dna)):
        if dna[x:y] == STR:
            temp = 0;
            while dna[x:y] == STR:
                temp += 1
                x+= len(STR)
                y+= len(STR)
                if(temp > ma):
                    ma = temp
        else:
            x+=1
            y+=1
    return ma


with open(argv[2], 'r') as dnafile:
    dna = dnafile.read()

# read people
with open(argv[1], "r") as peopleFile:
    peopleReader = reader(peopleFile)
    for row in peopleReader:
        peopleRow = row
        peopleRow.pop(0)
        for item in peopleRow:
            seqs[item] = 0;
        break

for item in seqs:
    ans = get_max(dna, item)
    seqs[item] = ans

# print people
with open(argv[1], "r") as peopleFile:
    people = DictReader(peopleFile)
    for person in people:
        c = 0
        for item in seqs:
            if int(person[item]) == seqs[item]:
                c += 1
        if c == len(seqs):
            print(person["name"])
            exit(0)

    print("No Match")