# 🔍 Inverted Search

A **full-text search engine** built in C using an Inverted Index data structure — the same core concept behind Google Search. Maps words to their document locations for lightning-fast text retrieval.

---

## 📌 Features

- Build an inverted index from multiple text files
- **Fast full-text search** — find any word across all indexed documents
- Hash table based index for O(1) average lookup
- Handles uppercase, lowercase, and special characters
- Dynamic memory management with linked list nodes

---

## 🛠️ Tech Stack

| Component | Details |
|---|---|
| Language | Advanced C |
| Data Structures | Hash Table, Linked List |
| Build | GCC, Makefile |
| OS | Linux (Ubuntu) |

---

## 🏗️ How It Works

```
Input Documents
     |
     v
Word Tokenizer
     |
     v
Hash Function → Hash Table
     |
     v
[word] → [doc1:line2] → [doc3:line5] → NULL
[word] → [doc2:line1] → NULL
     |
     v
Search Query
     |
     v
Hash Lookup → Return all locations
```

---

## 📂 Project Structure

```
inverted_search/
├── main.c              # Entry point, menu interface
├── index_creation.c    # Build inverted index from files
├── index_creation.h
├── search.c            # Search query handling
├── search.h
├── hash.c              # Hash function and table management
├── hash.h
└── Makefile
```

---

## 🚀 How to Run

```bash
git clone https://github.com/anaghchandran/inverted_search.git
cd inverted_search
make
./inverted_search
```

### Example Usage

```
1. Create Index
2. Search Word
3. Display Index
4. Exit

Enter choice: 1
Enter filename: sample.txt
Index created successfully!

Enter choice: 2
Enter word to search: embedded
Found in: sample.txt at lines: 3, 7, 12
```

---

## 💡 Key Learnings

- Hash table design and collision handling
- Dynamic linked list manipulation in C
- Full-text indexing concepts
- Special character and case-insensitive handling

---

## 👤 Author

**Anagh CS** — Embedded Systems Engineer  
[GitHub](https://github.com/anaghchandran) | [LinkedIn](https://www.linkedin.com/in/anagh-chandran)
