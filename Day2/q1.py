def isInc(a, b):
    return b > a

with open("input1.txt") as file:
    ans = 0

    for line in file:
        levels = [int(i) for i in line.split()]

        shouldLevelInc = isInc(levels[0], levels[1])

        for val1, val2 in zip(levels[:-1], levels[1:]):
            if not (isInc(val1, val2) == shouldLevelInc and abs(val1 - val2) <= 3 and val1 != val2):
                ans -= 1
                break
        
        ans += 1

print("Ans: ", ans)