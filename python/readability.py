# Gets user input
text = input("Text: ").lower()

# Splits text into words array
words = text.split()

# Count letters
letters = 0
for word in words:
    for letter in word:
        if letter >= "a" and letter <= "z":
            letters += 1

# Average letters per 100 words
L = letters / (len(words) / 100)

# Count sentences
sntc = 0
for char in text:
    if char == "." or char == "?" or char == "!":
        sntc += 1

# Average sentences per 100 words
S = sntc / (len(words) / 100)

# Calculate grade
grade = (0.0588 * L) - (0.296 * S) - 15.8

if (grade >= 16):
    print("Grade 16+\n")
elif (grade < 1):
    print("Before Grade 1\n")
else:
    print(f"Grade {round(grade)}\n")
