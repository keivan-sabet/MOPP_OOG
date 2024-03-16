import random

def Generator(fnum,gridx,gridy,obj):
    f = open(format(fnum) + ".csv", "w")
    f.write("Task,MVP\n")
    randomStart(f,gridx,gridy)
    randomGoal(f,gridx,gridy)
    sizeObj(f,gridx,gridy,obj)
    randomObjects(f,gridx,gridy,obj)
    f.write("Rulebook,hierch\n")
    f.write("obstacle clearance\n")
    f.write("shortest path\n")
    f.write("comfort\n")
    f.write("Method,mc1\n")

def sizeObj(f,gridx,gridy,obj):
    f.write("RowCol\n" +format(gridx) + "," + format(gridy) + "\n")
    f.write("Objectives\n"+format(obj)+"\n")

def randomStart(f,gridx,gridy):
    f.write("start,cord\n")
    random.seed()
    x = random.randrange(1,gridx)
    y = random.randrange(1,gridy)
    f.write(format(x) + "," + format(y) + "\n")

def randomGoal(f,gridx,gridy):
    f.write("Goal,cord\n")
    random.seed()
    x = random.randrange(1,gridx)
    y = random.randrange(1,gridy)
    f.write(format(x) + "," + format(y) + "\n")
    
def randomObjects(f,gridx,gridy,obj):
    f.write("Objects,gridList\n")
    generateComfort(f,gridx,gridy,1000)
    generateComfort(f,gridx,gridy,1000)
    for _ in range(obj-3):
        generateComfort(f,gridx,gridy,1000)
    generateShortest(f,gridx,gridy)
    f.write("end\n")


def generateShortest(f,gridx,gridy):
    f.write("obstacle\n")
    for numy in range(0,gridy):
        for numx in range(0,gridx-1):
            f.write("1,")
        f.write("1\n")
    f.write("obstacle\n")
        
        
        
        
def generateObstacle(f,gridx,gridy):
    random.seed()
    obsList = []
    robs = random.randrange(0,(gridx*gridy))
    print("robs: " + format(robs))
    for z in range(0,robs):
        x = random.randrange(0,gridx)
        y = random.randrange(0,gridy)
        obsList.append([x,y])
    
    f.write("obstacle\n")
    for numy in range(0,gridy):
        for numx in range(0,gridx-1):
            if obsCheck(obsList,numx,numy):
                f.write("1,")
            else:
                f.write("0,")
        if obsCheck(obsList,gridx - 1,numy):
            f.write("1\n")
        else:
            f.write("0\n")
    f.write("obstacle\n")

def generateComfort(f,gridx,gridy,cof):
    random.seed()
    f.write("comfort\n")
    for _ in range(0,gridy):
        for _ in range(0,gridx-1):
            com = random.randrange(1,cof + 1)
            f.write(format(com) + ",")
        com = random.randrange(1,cof + 1)
        f.write(format(com) + "\n")
    f.write("comfort\n")

def obsCheck(obsList,numx,numy):
    for x in obsList:
        if x[0] == numx:
            if x[1] == numy:
                return True
    return False

fnum = 0
for x in range(1,11):
    for y in range(1,21):
        for _ in range(500):
            Generator(fnum,10*x,10*x,y*10)
            fnum = fnum + 1