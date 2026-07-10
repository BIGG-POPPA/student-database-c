*Student Record Management System 

A custom Command Line Interface (CLI) database built from scratch in C. This project implements a parallel file storage architecture and byte-offset manipulation to manage, query, and update student records in real-time.

*Core Features

Parallel File Architecture: Instead of a single monolithic database, data is normalized and distributed across four distinct text files (name.txt, department.txt, SGPA.txt, CGPA.txt).

Direct Byte-Offset Updating: Utilizes low-level C file pointers (fseek, SEEK_SET) to calculate exact memory offsets (101 bytes per line). This allows the system to overwrite specific records instantly without needing to rewrite the entire database file.

Non-Destructive Deletions: Deletion logic is handled safely using a "streaming to temporary file" algorithm, ensuring data is never corrupted during the removal process.

Safe Input Processing: Leverages robust buffer handling (getchar(), strcspn) to strip leftover newline characters, eliminating runtime data corruption and phantom inputs.

*Technical Architecture

User Action: The client selects an operation via an interactive terminal loop.

In-Memory Loading: On boot, the system parses all four parallel text files simultaneously and loads the synchronized data into a unified struct Student array in RAM.

Targeted I/O: When a user updates a record, the system does not waste processing power saving the entire array. Instead, it calculates the exact byte location of the target string on the hard drive and overwrites only that specific sector.


*What I Learned

Building this custom architecture solidified my understanding of low-level computer science fundamentals:

File Pointers & Offsets: I mastered the use of fseek and rewind to navigate through files dynamically rather than just reading them sequentially from top to bottom.

Buffer Management: I learned why high-level languages abstract away input streams. Handling leftover \n characters from scanf and preventing fgets from skipping lines taught me how standard input buffers physically work in C.

Parallel Data Synchronization: Managing 4 separate files taught me the challenges and mechanics of keeping disconnected data sources perfectly synced using index mapping.
