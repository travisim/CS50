from csv import reader, DictReader
from sys import argv

# if len(argv) != 3:
# print("error")
# exit()


def find_occurance(seq, Str):
   
    max = 0
    start_scan = 0
    mirror = [0] * len(seq)
    end_scan = start_scan + len(Str) 
    for i in range(len(seq)):
        block = seq[start_scan: end_scan]
        if block == Str:
            if i < len(Str):
                mirror[i] = 1 
            elif i > len(seq) - len(Str) + 1:
                break
            else:
                mirror[i] = 1 + mirror[i-len(Str)]
        start_scan += 1
        end_scan += 1
    largest = 0
    for cu in mirror:
        if cu > largest:
            largest = cu
    return largest
        
              
# DB .csv to dict
DB = dict()
with open(argv[1]) as DB_csv:
    DB_temp = reader(DB_csv)
    header = next(DB_temp)
    DB = dict()
    for row in DB_temp:
        counter = 0
        for i in row:
            if counter == 0:
                name = i
                DB[i] = []
            else:
                DB[name].append(int(i))
            counter += 1
# dna .txt to str
with open(argv[2]) as person_dna_txt:
    person_dna = person_dna_txt.read()
    

alllargest = []
for i in header[1:]:
    alllargest.append(find_occurance(person_dna, i))
    
# i f person_dna.find() == True


# print(DB)
# print(header)
# check50 cs50/problems/2021/x/dnaprint(alllargest)
printl = -1
for n, x in DB.items():
    if x == alllargest:
        printl = n
if printl == -1:
    print("No match")
else:
    for n, x in DB.items():
        if x == alllargest:
            print(n)