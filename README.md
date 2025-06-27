# 🔐 Password Strength Tester & Generator 

A C++ console application that helps users assess the strength of their passwords and generate secure passwords based on custom criteria. Developed as a student project to promote better password hygiene and security awareness.

---

## 📌 Overview

This program serves two main purposes:

1. **Password Strength Testing:** Analyze a password's structure to determine if it's weak, average, or strong based on character diversity, length, common word presence, and repetition.
2. **Password Generation:** Create secure, random passwords including uppercase, lowercase, digits, and special symbols.

By using this tool, users can avoid weak passwords and better understand what makes a password more secure.

---

## 🧠 Features

### 1. Password Strength Testing
- Evaluates password based on:
  - Length (min. 8 characters)
  - Mix of uppercase, lowercase, digits, and symbols
  - Repetitive characters
  - Common English words (using external word lists)
- Categorizes as **Weak**, **Average**, or **Strong**

### 2. Password Generation
- Generates a random password with:
  - Digits, lowercase and uppercase letters, and special characters
  - User-defined length (minimum 8 characters)
- Ensures diversity of characters to increase complexity

### 3. Time-to-Crack Estimation
- Estimates how long it might take for a brute-force attack to crack the password

### 4. Common Word Detection
- Cross-checks password against two external word lists (`TEXT.txt` and `words.txt`)
- Flags use of recognizable words which reduce security

### 5. File Handling
- Reads from `TEXT.txt` and `words.txt` to detect common/guessable words

### 6. User-Friendly Interface
- Simple terminal-based interaction with clear prompts and feedback
- Encourages iterative testing and improvement of password choice

---

## 📁 Files

- `NCYS-I.cpp` — Main source file
- `TEXT.txt` — Uppercase word list
- `words.txt` — Lowercase word list

> ⚠️ Make sure `TEXT.txt` and `words.txt` are present in the same directory as the executable for accurate strength testing.

---

## 🛠️ How to Compile & Run

### 🧑‍💻 Windows (using g++)
```bash
g++ -o password_tool NCYS-I.cpp
./password_tool
