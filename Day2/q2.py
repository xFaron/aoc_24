def isInc(a, b):
    return b > a

with open("input1.txt") as file:
    ans = 0

    for line in file:
        levels = [int(i) for i in line.split()]

        shouldLevelInc = isInc(levels[0], levels[-1])
        length = len(levels)

        temp = 0
        skipAvailible = 1
        i = 0
        while i < length - 1:
            val1 = levels[i]
            val2 = levels[i+1]
            if not (isInc(val1, val2) == shouldLevelInc and abs(val1 - val2) <= 3 and val1 != val2):
                if skipAvailible == 1:
                    temp = (levels[i], i)
                    levels = levels[:i] + levels[i+1:]
                    i = -1
                    length -= 1
                    skipAvailible -= 1
                elif skipAvailible == 0:
                    levels[temp[1]:temp[1]] = [temp[0]]
                    levels = levels[:temp[1]+1] + levels[temp[1]+2:]
                    skipAvailible -= 1
                    i = -1
                else:
                    ans -= 1
                    break
            
            i += 1

        ans += 1



print("Ans: ", ans)