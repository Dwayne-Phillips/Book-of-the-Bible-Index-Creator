# Book-of-the-Bible-Index-Creator
Tools to create chapter:verse index of words for books of the Bible

# The Desire

One of the things I recently discovered was how difficult it was to created an Index for one single book of the Bible. 
Indexes exist for a single word as it occurs in the entire Bible. Those are called concordances.
In the day of the Bible online and the Bible in word processors, the concordance is not as necessary.
Simply search for a word.

Regardless, I wanted an index for a single book of the Bible.
For example, "list all the places in the Gospel of Matthew that the world 'Galilee' appears." 

Simple, right? Wrong.
I had to open a copy of Matthew in a word processor, search for "Galilee," and manually type each chapter:verse where "Galilee" appeared.

While this is not an impossible task, being a computing person I figured, "There must be a simpler way."

Well, I couldn't find a simpler way, so being a computer programmer, or I used to be a computer programmer, I thought, "I will write a simple way."

This is the result of writing a computer program to make this simpler.

# The Result (for now)

I wrote two little C programs: indexf and indexg. 
The source code is included in this repository.
I made these C programs into executables on a Mac using the commands `make indexf` and `make indexg`.
The `make` command used the default `cc` or C compiler. I don't know which specific version it used,
but if you read the C code (and you finish laughing at its old style) you will see that there isn't a lot to it.
I have no doubt that the programming logic could be expressed in a cleaner style, but it seems to work.

# The Basic Steps

Perhaps this can be made even simpler in the future, but for now, here is how I do it:

- Obtain a MS Word file for the New English Translation Noteless Bible
  - Go to [the NET Bible Download Page](https://bible.org/article/net-bible-download) 
  - This downloads a .zip file that, when decompressed, provides a NETBible_Noteless.doc file
- Copy the book of the Bible of interest to another MS Word file.
- Save that file, e.g., NET-Matthew.docx and keep for future use.
- While editing NET-Matthew.docx (in MS Word for Mac)
  -  In Word, Save As, .txt, Mac OS, CR only, and Allow Character Substitution.
  -  Save to a .txt file such as NET-Matthew-ASCII.txt.
  -  Keep that .txt file for future use. You will use it in a command every time you index a work.
- Run the `indexf` program to create a .txt file that has one verse per paragraph.
  - `indexf NET-Matthew-ASCII.txt NET-Matthew-ASCII-formatted.txt`
  - The result file has lines that appear like: `28:20] teaching them to obey everything I have commanded you...`
  - The above shows the words of chapter 28, verse 20 in a single paragraph.
- Run the `indexg` program to find the instances of a word and produce the chapter:verse for every instance.
  - `indexg Galilee NET-Matthew-ASCII-formatted.txt out.txt`
  - The file out.txt appears like
  - `Galilee, 2:22, 3:13, 4:12, 4:13, 4:14, 4:18, 4:23, 4:25, 15:29, 17:22, 19:1, 21:11, 27:55, 28:7, 28:10, 28:16,`
- That provides the "Galilee" entry for the Index of Matthew.
- Run the `indexg` program for each individual word you wish to index and copy the result to your Index file.

Again, I can probably make this simpler in the future. Suggestions are welcome.


# The End
