while True:
    try:
        height = int(input("Height: "))

        if height in [1, 2, 3, 4, 5, 6, 7, 8]:
            lst = [" "]*(height+2)

            for i in range(height):
                lst[height-1-i] = "#"
                lst.append("#")
                print(''.join(lst))

            break
    except:
        print("ERROR: enter an integer between 1 and 8 inclusive")
