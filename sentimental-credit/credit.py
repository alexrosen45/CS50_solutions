try:
    inp = str(input("Number: "))
    card = [int(num) for num in inp]
    card_type = ""

    if len(inp) == 15 and int(inp[:2]) in [34, 37]:
        card_type = "AMEX"

    if len(inp) == 13 or len(inp) == 16 and card[0] == 4:
        card_type = "VISA"

    if len(inp) == 16 and int(inp[:2]) in [51, 52, 53, 54, 55]:
        card_type = "MASTERCARD"

    vals = []
    card = [val for val in card[::-1]]
    print(*card)

    for i in range(len(inp)):
        if i%2 == 0:
            vals.append(card[i])
        else:
            if card[i]*2 >= 10:
                vals.append(1)
                vals.append(card[i]*2-10)
            else:
                vals.append(card[i]*2)

    print(*vals)

    if sum(vals)%10 != 0:
        print("INVALID")
    else:
        print(card_type)

except:
    print("INVALID")