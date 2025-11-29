# Mini Instagram Console Application

A C++ console-based simulation of a social media platform. This project mimics core functionality of Instagram, allowing users to sign up, connect, post updates, and message each other. It demonstrates the implementation of custom data structures (BST, Stack, Queue, Linked Lists) without relying on standard library containers.

## 📋 Table of Contents

  - [Features](https://www.google.com/search?q=%23features)
  - [Data Structures Used](https://www.google.com/search?q=%23data-structures-used)
  - [Prerequisites](https://www.google.com/search?q=%23prerequisites)
  - [How to Run](https://www.google.com/search?q=%23how-to-run)
  - [Usage Guide](https://www.google.com/search?q=%23usage-guide)
  - [Author](https://www.google.com/search?q=%23author)

## ✨ Features

  * **User Authentication:** Secure Signup and Login system with username validation.
  * **Profile Management:** View followers, following lists, and user details.
  * **Posting System:** Create text-based posts with automatic timestamps.
  * **News Feed:** View posts from users you follow in a chronological feed.
  * **Friend/Follow System:**
      * Send friend requests.
      * Accept requests (automatically follows back).
      * Notification system for incoming requests.
  * **Messaging System:**
      * Send private messages to other users.
      * Reply to specific messages.
      * View message history.
  * **Search:** Efficiently search for other users by username.
  * **Interactive UI:** Console-based interface with color coding and menu navigation.

## ⚙️ Data Structures Used

This project is built to demonstrate the practical application of Data Structures and Algorithms (DSA):

1.  **Binary Search Tree (BST):**

      * **Usage:** Used to store all `User` objects.
      * **Reason:** Allows for efficient searching ($O(\log n)$) of usernames during login, search, and sending requests.

2.  **Stack (LIFO):**

      * **Usage:** Manages the `Message` inbox.
      * **Reason:** The most recent message is displayed at the top, and users reply to the most recent context first.

3.  **Queue (FIFO):**

      * **Usage:** Manages `FriendRequest` objects.
      * **Reason:** Requests are processed in the order they were received (First In, First Out).

4.  **Singly Linked Lists:**

      * **Usage:** Used extensively for:
          * User Posts (Each user has a linked list of posts).
          * Followers & Following lists.
          * Notifications.
          * Message Replies (Threaded conversations).

## 💻 Prerequisites

  * **Operating System:** Windows (The code uses `<Windows.h>` for `system("color")`, `Sleep()`, and `CLS`).
  * **Compiler:** Any C++ compiler that supports C++98 or later (e.g., G++, MinGW, MSVC).

## 🚀 How to Run

1.  **Clone or Download** the `Mini_Instagram.cpp` file.
2.  **Open your terminal** or command prompt.
3.  **Compile** the code using G++:
    ```bash
    g++ Mini_Instagram.cpp -o MiniInstagram.exe
    ```
4.  **Run** the executable:
    ```bash
    MiniInstagram.exe
    ```

## 📖 Usage Guide

Upon running the application, you will see a welcome screen followed by the main menu:

1.  **Signup:** Create a new account (Username must be unique).
2.  **Login:** Access your account to use features.
3.  **Send Friend Request:** Input a username to connect.
4.  **Accept Friend Request:** Process pending requests from the Queue.
5.  **Create Post:** Share your thoughts.
6.  **View Posts:** See your own timeline.
7.  **Newsfeed:** See posts from people you follow.
8.  **Send/View Messages:** Chat with friends using the Stack-based inbox.
9.  **Search:** Check if a specific user exists in the BST.

> **Note:** This application runs in volatile memory (RAM). Data is not saved to a file and will be lost once the program is closed.

## 👤 Author

**Muhammad Zaid Hassan**

  * *Project Type:* DSA Semester Project / Portfolio
  * *Language:* C++

-----
