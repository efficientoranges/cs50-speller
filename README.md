# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

an invented long word said to mean a lung disease caused by inhaling very fine ash and sand dust.

## According to its man page, what does `getrusage` do?

Returns resource usage measures.
When used with RUSAGE_SELF, returns resourse usage statistics for the calling process.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by
## value) to `calculate`, even though we're not changing their contents?

So that `before` and `after` are altered in the calling scope instead of being
copied and changing the copies.

## Explain as precisely as possible, in a paragraph or more, how `main` goes
## about reading words from a file. In other words, convince us that you
## indeed understand how that function's `for` loop works.

Main first creates a pointer to a file open for reading using FILE *file = fopen(text, "r").
Main then checks if the file was successfully opened and returns an error if it was not.

Main then loops through the file one character at a time using fgetc() until the EOF character is reached.
At the end of each loop iteration the counter c is set to fgetc(file) which advances the pointer to the next character.
If the character is alphabetical or an apostrophe, it is added to a 'word' array and the word array index is advanced.
If index is longer than the maximum length of a word, the rest of the word is ignored and the index is reset to 0.
Similarly if a word contains a digit, it is ignored for spell checking by scanning over the rest of the word and resetting the index to 0.
If index > 0 but c is not alphabetical or an apostrophe this means the end of a word,
so the spelling of the word is then checked, the word is handled appropriately and the index is reset to 0 to prepare for a new word.
Finally reaching the EOF character terminates the loop. If any errors occured these are handled by checking ferror() for the file.

## Why do you think we used `fgetc` to read each word's characters one at a
## time rather than use `fscanf` with a format string like `"%s"` to read whole
## words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

Using `fscanf` does not allow control over how apostrophes and numeric
characters are handled. We want to include apostrophes as part of strings, but
only when after a letter, and we want to ignore words with numeric characters.
Using `fscanf` with the `"%s"` format string doesn't take this into acccount.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

The parameter is a pointer pointing to one word or dictionary respectively.
This pointer should not be able to change the data in the word or dictionary,
it should be 'read only'. Declaring the pointer as const means that attempting
to deference the pointer and assign a new value to the word/dictionary will fail.
However the pointer itself is not a constant and can be assigned a new value
so it points to a different location.
