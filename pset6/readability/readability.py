import cs50

# asks user for text.
text = cs50.get_string("Text: ")
characters = 0
words = 1
sentences = 0

# count characters, words and sentences in text.
for i in range(len(text)):
    # count characters.
    if text[i].isalpha():
        characters = characters + 1
    # count words.
    if text[i] == " ":
        if text[i+1].isalpha():
            words = words + 1
        elif ord(text[i+1]) >= 33 and ord(text[i+1]) <= 126:
            words = words + 1
    # count sentences.
    if text[i] == "." or text[i] == "!" or text[i] == "?":
        sentences = sentences + 1

# print("characters: "+str(characters))
# print("words: "+str(words))
# print("sentences: "+str(sentences))

# calculates readability.
Letterofreadability = (float(characters) / float(words)) * 100
Sentenceofreadability = (float(sentences) / float(words)) * 100
readability = 0.0588 * Letterofreadability - 0.296 * Sentenceofreadability - 15.8
readability = round(readability)

# prints readability.
if readability >= 16:
    print("Grade 16+")
elif readability < 1:
    print("Before Grade 1")
else:
    print("Grade " + str(readability))