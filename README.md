# 🏦 Mini Banking System

A simple yet powerful **console-based banking system** written in **C**, featuring unlimited accounts, secure PIN authentication, and a clean user interface.

---

## ✨ Features

| Feature | Description |
|--------|-------------|
| 🔓 **PIN Authentication** | 4-digit PIN with 3 attempt limit |
| 👤 **Unlimited Accounts** | Dynamic memory — no account limit |
| 💰 **Deposit** | Add money to your account instantly |
| 💸 **Withdraw** | Withdraw with balance validation |
| 📊 **Balance Check** | View your current balance anytime |
| 🪪 **Unique ID** | Every account has a custom user ID |
| 🖼️ **Photo Support** | Auto-opens your photo on login |

---

## 🚀 Getting Started

### Prerequisites
- GCC compiler
- Any Linux / Windows / macOS terminal

### Compile & Run

```bash
gcc banking_system.c -o banking -lm
./banking
```

On Windows:
```bash
gcc banking_system.c -o banking.exe -lm
banking.exe
```

---

## 🖥️ How It Works

```
================================
    MINI BANKING SYSTEM
================================
[1] Create New Account
[2] Login
[3] Exit
================================
```

1. **Create Account** — Enter your name, PIN, balance, photo path, and custom ID
2. **Login** — Enter name + ID, then verify PIN
3. **Access Menu** — Deposit, withdraw, view balance, or open photo

---

## 📁 Project Structure

```
📦 mini-banking-system
 ┣ 📄 banking_system.c   # Main source code
 ┗ 📄 README.md          # Project documentation
```

---

## 🧠 Technical Highlights

- Written in **pure C** (C99 standard)
- Uses **`realloc()`** for dynamic memory — supports unlimited accounts
- Cross-platform photo open support (`start`, `open`, `xdg-open`)
- PIN lockout after **3 failed attempts**

---

## 📌 Limitations

- Data is **not saved** after the program exits (no file storage yet)
- PIN is stored as plain integer (no encryption)

---

## 🔮 Future Plans

- [ ] Save/load accounts from a file
- [ ] PIN encryption
- [ ] Transaction history
- [ ] Admin panel

---

## 👨‍💻 About the Developer

**Md Shifat Uz Zaman**

- 💻 Passionate C programmer
- 🎯 Loves building real-world console applications
- 🌱 Currently learning and growing in software development
- 📧 Gmail: [shifatuszamun@gmail.com](mailto:shifatuszamun@gmail.com)

📄 License
This project is open source and available under the MIT License.
