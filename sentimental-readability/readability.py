text = str(input("Enter text: "))
words, sentences, letters = 1, 0, 0

for i in range(len(text)):
    # check for blank space
    if text[i] == ' ':
        words += 1
    # check for sentence ending chars
    elif text[i] in ['?', '.', '!']:
        sentences += 1
    # check for letters
    if text[i].isalpha():
        letters += 1

readability = round(0.0588*(letters*100)/words-0.296*(sentences*100)/words-15.8)

if readability > 16:
    print("Grade 16+")
elif readability < 1:
    print("Before Grade 1")
else:
    print(f"Grade {readability}")
