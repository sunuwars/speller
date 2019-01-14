The dictionary is built using the trie data structure and is loaded in memory.

This is much efficient compared to expensive process of comparing against individual entries in an array.

In trie, searching a word of length n takes a predictible n number of steps which is the reason I chose to implement trie.

# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

It is the longest word entry in dictionary of length 45.

## According to its man page, what does `getrusage` do?
`getrusage` will time my implemantation of `check`, `load`, `size` and `unload`.


## Per that same man page, how many members are in a variable of type `struct rusage`?

TODO

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

`before` and `after` are structs which are referred by pointer(address), so we are passing by reference(value in that address).

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

 To spell check each word in text, first each character is iterated until the end of file,

 : the character is tested against alphabet or apostrophe(not the first letter of word), if true, the character is appended to word and index
 count is incremented. If the index count of a word is greater than max-length(defined maximum length of a word), then the rest of the characters
 of the word is consumed and index is set to zero. then onto next iteration

 :if the first test fails, the character is tested against, numerical value. If it matches then the word is consumed until it finds numeric characters
 and index is set to zero.  then onto next iteration

 : if both above test fails and index is greater than zero then it must be an end of a word then '\0' is appended
 at the end of word to make it a string, index is set to zero and words count is incremented. then onto next iteration



## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

`fscanf` with format string like `"%s"` would only check for strings but it will miss word longer than max word length or word with numeric characters.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

TODO
