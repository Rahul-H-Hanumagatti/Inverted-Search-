Inverted Search Project Using Hashing in C

This project implements an Inverted Search system using hashing techniques in the C programming language. Inverted search is a powerful method used for fast and efficient text search and information retrieval. By creating an index of words and their occurrences across multiple files, the system enables quick searches and efficient data lookup.

Features:
- File Parsing:Reads multiple text files and extracts unique words.
- Inverted Index Creation:Builds a hash-based index mapping words to their file occurrences and positions.
- Search Functionality: Quickly retrieves files containing a given word.
- Case Sensitivity: Supports case-insensitive or case-sensitive search.
- Dynamic Memory Management: Efficiently allocates and frees memory for scalability.

Technologies Used:
- Programming Language: C
- Data Structures: Hash tables for fast data retrieval.
- Algorithms: Hashing for word indexing and searching.

Usage:
# Compile the project
gcc inverted_search.c -o inverted_search

# Run the project
./inverted_search file1.txt file2.txt ...

# Search for a word
Enter word to search: example

Future Improvements:
- Add support for phrase-based searches.
- Implement fuzzy search for approximate word matches.
- Develop a user-friendly interface.

This project demonstrates efficient use of hashing and data structures in C to implement a robust inverted search engine, ensuring quick and accurate information retrieval from multiple files.


