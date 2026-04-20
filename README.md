# 🚀 Key-Value Store in C++ (with TTL)

A lightweight in-memory key-value database built in C++ that supports basic CRUD operations along with TTL (Time-To-Live) functionality.

This project simulates core features of systems like Redis.

---

## 📌 Features

- Store key-value pairs
- Retrieve stored values
- Delete keys
- TTL (auto-expiry of keys)
- Command-line interface (CLI)
- Simple and fast in-memory storage

---

## 🧠 How It Works

- Uses `unordered_map` (hash table) for fast O(1) operations
- Each key stores:
  - Value
  - Expiry time (optional)
- On `GET`, system checks:
  - If key exists
  - If expired → deletes automatically

---

## 🛠️ Tech Stack

- Language: C++
- Concepts:
  - Hash Maps
  - Time-based expiration (TTL)
  - CLI parsing
  - Memory management

---
