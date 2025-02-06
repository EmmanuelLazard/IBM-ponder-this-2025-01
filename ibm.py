from math import sqrt

goal = 1.0
epsilon = 0.0003

VA = sqrt(5)
VB = sqrt(3)
VC = sqrt(2)

def check(etat):
    for V in etat:
        if abs(goal-V) <= epsilon:
            return 1
    return 0

def isInCycle(etat, depth):
	for (e,d) in cycle:
		if (e == etat and d>=depth):
			return 1
	return 0

def operation (etat, depth, op):
    save = etat.copy()
#    print (depth, etat, op)
    if check(etat):
        print(etat, ":", op)
        return 1
    if depth == 0:
        return 0
    if isInCycle(etat, depth):
#        print('cycle:', etat)
        return 0
    cycle.append((etat.copy(), depth))
# First we fill the jugs
    if etat[0] != VA:
        etat[0] = VA
        operation(etat, depth-1, op+" TA")
        etat = save.copy()
    if etat[1] != VB:
        etat[1] = VB
        operation(etat, depth-1, op+" TB")
        etat = save.copy()
    if etat[2] != VC:
        etat[2] = VC
        operation(etat, depth-1, op+" TC")
        etat = save.copy()
# We empty the jugs
    if etat[0] != 0:
        etat[0] = 0
        operation(etat, depth-1, op+" AS")
        etat = save.copy()
    if etat[1] != 0:
        etat[1] = 0
        operation(etat, depth-1, op+" BS")
        etat = save.copy()
    if etat[2] != 0:
        etat[2] = 0
        operation(etat, depth-1, op+" CS")
        etat = save.copy()

# We transfer A into B
    if etat[0]>0:
        if (etat[0] > (VB-etat[1])): # more in A to fill B
            etat[0] -= (VB-etat[1])
            etat[1] = VB
        else:
            etat[1] += etat[0]
            etat[0] = 0
        operation(etat, depth-1, op+ " AB")
        etat = save.copy()
# We transfer A into C
        if (etat[0] > (VC-etat[2])): # more in A to fill C
            etat[0] -= (VC-etat[2])
            etat[2] = VC
        else:
            etat[2] += etat[0]
            etat[0] = 0
        operation(etat, depth-1, op+ " AC")
        etat = save.copy()

# We transfer B into A
    if etat[1]>0:
        if (etat[1] > (VA-etat[0])): # more in B to fill A
            etat[1] -= (VA-etat[0])
            etat[0] = VA
        else:
            etat[0] += etat[1]
            etat[1] = 0
        operation(etat, depth-1, op+ " BA")
        etat = save.copy()
# We transfer B into C
        if (etat[1] > (VC-etat[2])): # more in B to fill C
            etat[1] -= (VC-etat[2])
            etat[2] = VC
        else:
            etat[2] += etat[1]
            etat[1] = 0
        operation(etat, depth-1, op+ " BC")
        etat = save.copy()

# We transfer C into A
    if etat[2]>0:
        if (etat[2] > (VA-etat[0])): # more in C to fill A
            etat[2] -= (VA-etat[0])
            etat[0] = VA
        else:
            etat[0] += etat[2]
            etat[2] = 0
        operation(etat, depth-1, op+ " CA")
        etat = save.copy()
# We transfer C into B
        if (etat[2] > (VB-etat[1])): # more in C to fill B
            etat[2] -= (VB-etat[1])
            etat[1] = VB
        else:
            etat[1] += etat[2]
            etat[2] = 0
        operation(etat, depth-1, op+ " CB")
        etat = save.copy()

cycle = []
for d in range(1,20):
    print ('Trying depth', d)
    etat = [0,0,0]
    operation(etat, d, "")


