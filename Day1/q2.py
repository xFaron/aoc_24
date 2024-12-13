with open("input1.txt", "r") as f:
    sum = 0
    freq1 = {}
    freq2 = {}
    while True:
        line = f.readline()
        if not line:
            break

        a, b = (int(i) for i in line.split())
        
        if a in freq1:
            freq1[a] += 1
        else:
            freq1[a] = 1
        
        if b in freq2:
            freq2[b] += 1
        else:
            freq2[b] = 1
    
    for key in freq1:
        if key in freq2:
            sum += key * freq1[key] * freq2[key]

print(f"Ans: {sum}")