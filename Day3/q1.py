# Not cheezing this time
with open("input1.txt") as file:
    corrupt_string = file.read()
    ans = 0

    doing = 1
    processing = 0

    temp1 = 0
    temp2 = 0
    for index in range(len(corrupt_string)):
        if processing:
            if processing == 3 and corrupt_string[index] == "(":
                processing = 2
                temp1 = 0
                continue
            elif processing == 3 and corrupt_string[index] != "(":
                processing = 0
            
            
            if processing == 2 and corrupt_string[index] == ",":
                processing = 1
                temp2 = 0
                continue
            elif processing == 1 and corrupt_string[index] == ")":
                processing = 0
                ans += temp1 * temp2
                continue

            try:
                if processing == 2:
                    temp1 *= 10
                    temp1 += int(corrupt_string[index])

                    if temp1 >= 1000: processing = 0
                elif processing == 1:
                    temp2 *= 10
                    temp2 += int(corrupt_string[index])

                    if temp2 >= 1000: processing = 0
            except:
                processing = 0

        else:
            if doing and corrupt_string[index-2: index+1] == "mul":
                processing = 3

print(f"Ans: {ans}")