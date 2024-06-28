# Determine the Grade Level of a Text Using the Coleman-Liau Formula
from cs50 import get_string


def main():

    # Get Text Input From User
    text = get_string("Text: ")

    # Calculate Number of Letter, Words, and Sentences in Text
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # Calculate the Coleman-Liau Index
    L = letters * 100 / words  # average number of letters per 100 words in text
    S = sentences * 100 / words  # average number of sentences per 100 words in text
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Identify and Print Reading Level
    if index < 1:
        print("Before Grade 1")
    elif index >= 1 and index <= 16:
        print(f"Grade {index}")
    else:
        print("Grade 16+")


# Count Number of Letters in Input String
def count_letters(text):
    letters = 0
    for char in text:
        if char.isalpha():
            letters += 1
    return letters


# Count Number of Words in Input String
def count_words(text):
    words = len(text.split())
    return words


# Count Number of Sentences in Input String
def count_sentences(text):
    sentences = 0
    for char in text:
        if char in [".", "!", "?"]:  # identify ending punctuation
            sentences += 1
    return sentences


main()
