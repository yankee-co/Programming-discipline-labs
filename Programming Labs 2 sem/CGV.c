#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void draw_word(char* word, int* guessed_letters) {
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        if (guessed_letters[i]) {
            printf("%c ", word[i]);
        }
        else {
            printf("_ ");
        }
    }
    printf("\n");
}

int is_game_won(int* guessed_letters, int len) {
    for (int i = 0; i < len; i++) {
        if (!guessed_letters[i]) {
            return 0;
        }
    }
    printf("Congratulations! You've guessed the word.");
    return 1;
}

int main() {
    char* words[] = {"apple", "banana", "cherry", "durian", "elderberry", "fig",
                    "grape", "honeydew", "indian", "jujube", "kiwi",
                    "lemon", "mango", "nectarine", "orange", "peach", "quince",
                    "raspberry", "strawberry", "tangerine", "ugli", "vanilla",
                    "watermelon", "xylocarp", "yellow", "zucchini"};
    int num_words = 26;
    int max_guesses = 15;

    // Seed the random number generator
    srand(time(NULL));

    // Choose a random word from the list
    int word_index = rand() % num_words;
    char* word = words[word_index];
    char tried[30];

    int len = strlen(word);
    int guessed_letters[len];
    for (int i = 0; i < len; i++) {
        guessed_letters[i] = 0;
    }

    int num_guesses = 0;
    int num_wrong_guesses = 0;

    // Start the game
    printf("Welcome to the word guessing game!\n");
    draw_word(word, guessed_letters);

    while (num_wrong_guesses < max_guesses && !is_game_won(guessed_letters, len)) {
        // Get a guess from the user
        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);

        // Check if the guess has already been made
        int already_guessed = 0;
        for (int i = 0; i < len; i++) {
            if (guess == word[i] && guessed_letters[i]) {
                printf("You've already guessed that letter.\n");
                already_guessed = 1;
                break;
            }
        }

        if (!already_guessed) {
            // Check if the guess is in the word
            int found_letter = 0;
            for (int i = 0; i < len; i++) {
                if (guess == word[i]) {
                    guessed_letters[i] = 1;
                    found_letter = 1;
                }
            }

            if (found_letter) {
                printf("Correct!\n");
            }
            else {
                printf("Incorrect!\n");
                num_wrong_guesses++;
            }

            draw_word(word, guessed_letters);
            num_guesses++;
            printf("You have %d guesses left.\n", max_guesses - num_wrong_guesses);

            if(num_wrong_guesses == max_guesses) printf("You lost! It was: '%s'", word);
        }
    }
}

