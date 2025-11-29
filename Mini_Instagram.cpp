#include <iostream>
#include <string>
#include <ctime>
#include<Windows.h>
using namespace std;

/*----------------------------- class message ---------------------------*/
class Message
{ // this class is omplemented for replies of user 
private:
    string content;
    string sender;
    Message* next;
    Message* replies;  // linked list of replies to the messages

public:
    Message(string content, string sender) : content(content), sender(sender), next(NULL), replies(NULL) {}

    string getContent() const
    {
        return content;
    }

    string getSender() const
    {
        return sender;
    }

    void addReply(Message* reply)
    {
        reply->next = replies;
        replies = reply;
    }

    Message* getReplies() const
    {
        return replies;
    }

    Message* getNext() const
    {
        return next;
    }

    void setNext(Message* nextMessage)
    {
        next = nextMessage;
    }
};

/*--------------------------- Messgae Stack -----------------------*/
class stack
{// stack class to handle stack of messages
private:
    Message* top;
    int capacity;
    int size;

public:
    stack(int capacity) : capacity(capacity), top(NULL), size(0) {}

    bool isFull()
    {
        return size == capacity;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void push(const string& message, const string& sender) // if there are new messages then they push into stack
    {
        if (!isFull())
        {
            Message* newMessage = new Message(message, sender);
            newMessage->setNext(top);
            top = newMessage;
            size++;
        }
        else
        {
            cout << "Message stack is full!" << endl;
        }
    }

    void printMessages()
    {
        if (isEmpty())
        {
            cout << "No new messages!" << endl;
        }
        else
        {
            Message* temp = top;
            int index = 0;
            while (temp)
            {
                cout << index++ << ". Message from " << temp->getSender() << ": " << temp->getContent() << endl;
                Message* reply = temp->getReplies();
                while (reply)
                {
                    cout << "\tReply : " << reply->getContent() << " ( by " << reply->getSender() << " ) . " << endl;
                    reply = reply->getNext();
                }
                temp = temp->getNext();
            }
        }
    }

    void replyToMessage(Message* message, const string& replyContent, const string& sender)
    {
        Message* reply = new Message(replyContent, sender);
        message->addReply(reply);
    }

    Message* getTop() const
    {
        return top;
    }
};

/*--------------------- Post --------------------*/
class Post
{// Post class to represent a user's post
private:
    string content;
    string timestamp;
    Post* next;

public:
    Post(string content) : content(content), next(NULL)
    {
        timestamp = getCurrentTime();
    }

    string getCurrentTime()
    {
        time_t now = time(0);
        char* dt = ctime(&now);
        return string(dt);
    }

    string getContent() const
    {
        return content;
    }

    string getTimestamp() const
    {
        return timestamp;
    }

    Post* getNext() const
    {
        return next;
    }

    void setNext(Post* nextPost)
    {
        next = nextPost;
    }
};

/*----------------------------- Friend Reqest ------------------------------*/
class FriendRequest
{
private:
    string sender;
    string receiver;
    string status;
    FriendRequest* next;

public:
    FriendRequest(string s, string r, string st) : sender(s), receiver(r), status(st), next(NULL) {}

    string getSender() const
    {
        return sender;
    }

    string getReceiver() const
    {
        return receiver;
    }

    string getStatus() const
    {
        return status;
    }

    FriendRequest* getNext() const
    {
        return next;
    }

    void setNext(FriendRequest* nextRequest)
    {
        next = nextRequest;
    }

    void setStatus(const string& newStatus)
    {
        status = newStatus;
    }
};

/*----------------------------------------- User Class -------------------------------*/
class User
{
private:
    string name;
    string password;
    string city;
    string securityQuestion;
    string securityAnswer;
    Post* posts;
    FriendRequest* notifications;
    User* followers;
    User* following;
    User* next;
    stack* messages;
    time_t lastLogin;
    bool activeStatus;

public:
    User(string n, string p, string c, string secQ, string secA, int stackCapacity = 100) : name(n), password(p), city(c), securityQuestion(secQ), securityAnswer(secA), posts(NULL), notifications(NULL), followers(NULL), following(NULL), next(NULL), lastLogin(time(0)), activeStatus(false)
    {
        messages = new stack(stackCapacity);
    }

    ~User()
    {
        delete messages;
    }

    string getName() const
    {
        return name;
    }

    string getPassword() const
    {
        return password;
    }

    Post* getPosts() const
    {
        return posts;
    }

    User* getFollowers() const
    {
        return followers;
    }

    User* getFollowing() const
    {
        return following;
    }

    FriendRequest* getNotifications() const
    {
        return notifications;
    }

    stack* getMessages() const
    {
        return messages;
    }

    User* getNext() const
    {
        return next;
    }

    void setNext(User* nextUser)
    {
        next = nextUser;
    }

    void setActiveStatus(bool status)
    {
        activeStatus = status;
    }

    bool getActiveStatus() const
    {
        return activeStatus;
    }

    void addPost(string content)
    {
        Post* newPost = new Post(content);
        newPost->setNext(posts);
        posts = newPost;
    }

    void addFollower(User* follower)
    {
        follower->setNext(followers);
        followers = follower;
    }

    void addFollowing(User* follow)
    {
        follow->setNext(following);
        following = follow;
    }

    void addNotification(FriendRequest* request)
    {
        request->setNext(notifications);
        notifications = request;
    }

    void addMessage(const string& message)
    {
        messages->push(message, name);
    }

    void updateLastLogin()
    {
        lastLogin = time(0);
    }

    string getLastLoginTime() const
    {
        char* dt = ctime(&lastLogin);
        return string(dt);
    }
};
/* --------------------------------------- BST CLASS -----------------------------------*/
class UserBST
{
private:
    struct Node
    {
        User* user;
        Node* left;
        Node* right;

        Node(User* user) : user(user), left(NULL), right(NULL) {}
    };

    Node* root;

public:
    UserBST() : root(NULL) {}

    void insert(User* user)
    {
        root = insertRecursive(root, user);
    }

    User* findUser(const std::string& username)
    {
        return findRecursive(root, username);
    }

private:
    Node* insertRecursive(Node* node, User* user)
    {
        if (node == NULL)
        {
            return new Node(user);
        }

        if (user->getName() < node->user->getName())
        {
            node->left = insertRecursive(node->left, user);
        }
        else
        {
            node->right = insertRecursive(node->right, user);
        }

        return node;
    }

    User* findRecursive(Node* node, const std::string& username)
    {
        if (node == NULL)
        {
            return NULL;
        }

        if (username == node->user->getName())
        {
            return node->user;
        }
        else if (username < node->user->getName())
        {
            return findRecursive(node->left, username);
        }
        else
        {
            return findRecursive(node->right, username);
        }
    }
};
/*---------------------------- friends request queue ------------------------------*/
class queue
{
private:
    FriendRequest* front;
    FriendRequest* rear;

public:
    queue() : front(NULL), rear(NULL) {}

    void enqueue(FriendRequest* req)
    {
        if (rear)
        {
            rear->setNext(req);
            rear = req;
        }
        else
        {
            front = rear = req;
        }
    }

    FriendRequest* dequeue()
    {
        if (!front) return NULL;
        FriendRequest* temp = front;
        front = front->getNext();
        if (!front) rear = NULL;
        return temp;
    }

    bool isEmpty()
    {
        return front == NULL;
    }
};

/*--------------------------------- class to mange all realtion/ netwroks of user ------------------------*/
class user_networks
{
private:
    UserBST users;
    queue requests;
    User* currentUser;

public:
    user_networks() : currentUser(NULL) {}

    void signup(string name, string password, string city, string secQ, string secA)
    {
        if (users.findUser(name))
        {
            cout << "Username already exists!" << endl;
            return;
        }
        User* newUser = new User(name, password, city, secQ, secA);
        users.insert(newUser);
        cout << "User signed up successfully!" << endl;
    }

    User* login(string name, string password)
    {
        User* user = users.findUser(name);
        if (user && user->getPassword() == password)
        {
            currentUser = user;
            currentUser->updateLastLogin();
            currentUser->setActiveStatus(true);
            cout << "Login successful!" << endl;
            return user;
        }
        cout << "Invalid username or password!" << endl;
        return NULL;
    }

    void logout()
    {
        if (currentUser)
        {
            currentUser->setActiveStatus(false);
            cout << "Logged out successfully!" << endl;
        }
        currentUser = NULL;
    }

    void sendFriendRequest(string receiver)
    {
        if (!currentUser)
        {
            cout << "Please login first!" << endl;
            return;
        }
        User* receiverUser = users.findUser(receiver);
        if (!receiverUser)
        {
            cout << "Receiver user not found!" << endl;
            return;
        }
        FriendRequest* request = new FriendRequest(currentUser->getName(), receiverUser->getName(), "pending");
        requests.enqueue(request);
        receiverUser->addNotification(request);
        cout << "Friend request sent to " << receiver << "!" << endl;
    }


    void acceptFriendRequest()
    {
        if (!currentUser)
        {
            cout << "Please login first!" << endl;
            return;
        }
        if (requests.isEmpty())
        {
            cout << "No friend requests!" << endl;
            return;
        }
        FriendRequest* req = requests.dequeue();
        req->setStatus("accepted");
        User* senderUser = users.findUser(req->getSender());
        User* receiverUser = users.findUser(req->getReceiver());
        senderUser->addFollowing(receiverUser);
        receiverUser->addFollower(senderUser);
        cout << "Friend request from " << req->getSender() << " accepted!" << endl;

        char followBack;
        cout << "----------------------------------------------------------------------------------" << endl;
        cout << "Do you want to follow back " << req->getSender() << "? \nEnter y for yes otherwise prees any key : ";
        cin >> followBack;
        if (followBack == 'y' || followBack == 'Y')
        {
            senderUser->addFollower(receiverUser);
            receiverUser->addFollowing(senderUser);
            cout << "Followed back " << req->getSender() << "!" << endl;
        }
    }


    void sendMessage()
    {
        if (!currentUser)
        {
            cout << "Please login first!" << endl;
            return;
        }
        string recipient, message;
        cout << "Enter name to send message : ";
        cin >> recipient;
        cout << "Enter your message : ";
        cin.ignore();
        getline(cin, message);

        User* recipientUser = users.findUser(recipient);
        if (!recipientUser)
        {
            cout << "Recipient user not found!" << endl;
            return;
        }

        recipientUser->addMessage(message);
        cout << "Message sent successfully!" << endl;
    }

    void viewMessages()
    {
        if (!currentUser)
        {
            cout << "Please login first!" << endl;
            return;
        }
        currentUser->getMessages()->printMessages();
        cout << "-------------------------------------------------------------" << endl;
        cout << "Do you want to reply to any message? (y/n) : ";
        char replyChoice;
        cin >> replyChoice;

        if (replyChoice == 'y' || replyChoice == 'Y')
        {
            cout << "Enter the number of the message you want to reply to : ";
            int messageIndex;
            cin >> messageIndex;

            Message* message = currentUser->getMessages()->getTop();
            int index = 0;
            while (message && index < messageIndex)
            {
                message = message->getNext();
                index++;
            }

            if (message)
            {
                cout << "Enter your reply: ";
                string replyContent;
                cin.ignore();
                cin >> replyContent;

                currentUser->getMessages()->replyToMessage(message, replyContent, currentUser->getName());
                cout << "Reply sent!" << endl;
            }
            else
            {
                cout << "Invalid message index!" << endl;
            }
        }
    }
    void createPost()
    {
        if (!currentUser)
        {
            cout << "Please login first!" << endl;
            return;
        }
        string content;
        cout << "Enter post content: ";
        cin.ignore();
        getline(cin, content);
        currentUser->addPost(content);
        cout << "Post created!" << endl;
    }

    void viewPosts()
    {
        if (!currentUser)
        {
            cout << "Please login first!" << endl;
            return;
        }
        Post* temp = currentUser->getPosts();
        while (temp)
        {
            cout << "Post : " << temp->getContent() << "\nPosted on: " << temp->getTimestamp() << endl;
            temp = temp->getNext();
        }
    }

    void newsFeed()
    {
        if (!currentUser)
        {
            cout << "Please login first!" << endl;
            return;
        }
        cout << "News Feed for " << currentUser->getName() << " : " << endl;
        User* temp = currentUser->getFollowing();
        while (temp)
        {
            cout << "Posts by " << temp->getName() << ":\n";
            viewPosts();
            temp = temp->getNext();
        }
    }

    void showFollowers()
    {
        if (!currentUser)
        {
            cout << "Please login first!" << endl;
            return;
        }
        cout << "Followers of " << currentUser->getName() << ":" << endl;
        User* temp = currentUser->getFollowers();
        while (temp)
        {
            cout << temp->getName() << endl;
            temp = temp->getNext();
        }
    }

    void showFollowing()
    {
        if (!currentUser)
        {
            cout << "Please login first!" << endl;
            return;
        }
        cout << "Following of " << currentUser->getName() << ":" << endl;
        User* temp = currentUser->getFollowing();
        while (temp)
        {
            cout << temp->getName() << endl;
            temp = temp->getNext();
        }
    }

    void showNotifications()
    {
        if (!currentUser)
        {
            cout << "Please login first!" << endl;
            return;
        }
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "Notifications for " << currentUser->getName() << ":" << endl;
        FriendRequest* temp = currentUser->getNotifications();
        while (temp)
        {
            cout << temp->getSender() << " - Status: " << temp->getStatus() << endl;
            temp = temp->getNext();
        }
    }

    void showMenu()
    {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        system("color 0b");
        cout << "\n\t\t\t+------------------------------------------------------------------------------------+\n";
        Sleep(300);
        cout << "\t\t\t|                                                                                    |" << endl;
        Sleep(300);
        cout << "\t\t\t|                                                                                    |" << endl;
        Sleep(300);
        cout << "\t\t\t|                                                                                    |" << endl;
        Sleep(300);
        cout << "\t\t\t|                                                                                    |" << endl;
        Sleep(300);
        cout << "\t\t\t|                                                                                    |" << endl;
        Sleep(300);
        cout << "\t\t\t|                                                                                    |" << endl;
        Sleep(300);
        cout << "\t\t\t|                                                                                    |" << endl;
        Sleep(300);
        cout << "\t\t\t|                        Welcome to Mini Instagram!                                  |" << endl;
        Sleep(300);
        cout << "\t\t\t|                                                                                    |" << endl;
        Sleep(300);
        cout << "\t\t\t|                                                                                    |" << endl;
        Sleep(300);
        cout << "\t\t\t|                                                                                    |" << endl;
        Sleep(300);
        cout << "\t\t\t|                                                                                    |" << endl;
        Sleep(300);
        cout << "\t\t\t|                                                                                    |" << endl;
        Sleep(300);
        cout << "\t\t\t|                                                                                    |" << endl;
        Sleep(300);
        cout << "\t\t\t|                                                                                    |" << endl;
        Sleep(300);
        cout << "\t\t\t+-------------------------------------------------------------------------------------+\n";
        Sleep(300);
        cout << "\n\n\t\t\t---------------------------------------------------------------------------------------\n";
        Sleep(300);
        cout << "\t\t\t Presented By : " << endl;
        Sleep(300);
        cout << "\t\t\t\t\t  Muhammad Zaid Hassan  " << endl;
        // Sleep(300);
        Sleep(300);
        cout << "\t\t\t---------------------------------------------------------------------------------------\n";
        cout << endl << endl;
        Sleep(3000);
        system("pause");
        system("CLS");
        int choice;
        do
        {
            system("color 0b");
            cout << "\n\t\t\t\t+----------------------- Menu : -------------------------------+ \n";
            cout << "\t\t\t\t|1. Signup                                                      | \n";
            cout << "\t\t\t\t|2. Login                                                       | \n";
            cout << "\t\t\t\t|3. Send Friend Request                                         | \n";
            /*if (!requests.isEmpty())
            {
                SetConsoleTextAttribute(h, 1);
            }*/
            cout << "\t\t\t\t|4. Accept Friend Request                                       | \n";
            cout << "\t\t\t\t|5. Create Post                                                 | \n";
            cout << "\t\t\t\t|6. View Posts                                                  | \n";
            cout << "\t\t\t\t|7. Newsfeed                                                    | \n";
            cout << "\t\t\t\t|8. Send Message                                                | \n";
            /*if (currentUser->getMessages() != NULL)
            {
                SetConsoleTextAttribute(h, 1);
            }*/
            cout << "\t\t\t\t|9. View Messages                                               | \n";

            cout << "\t\t\t\t|10. Show Notifications                                         | \n";
            cout << "\t\t\t\t|11. Show Followers                                             | \n";
            cout << "\t\t\t\t|12. Show Following                                             | \n";
            cout << "\t\t\t\t|13. Logout                                                     | \n";
            cout << "\t\t\t\t|14. search for a user                                          | \n";
            cout << "\t\t\t\t|15. Exit                                                       | \n";
            cout << "\t\t\t\t+---------------------------------------------------------------+ \n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                system("color 0c");
                system("CLS");
                cout << "------------------------------------- Sing Up--------------------------" << endl;

                string name, password, city, secQ, secA;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter password: ";
                cin >> password;
                cout << "Enter city: ";
                cin >> city;
                cout << "Enter security question: ";
                cin.ignore();
                getline(cin, secQ);
                cout << "Enter security answer: ";
                getline(cin, secA);
                signup(name, password, city, secQ, secA);
                system("pause");
                system("CLS");
                break;
            }
            case 2:
            {
                system("CLS");
                system("color 0A");
                cout << "------------------------------------- Log In --------------------------" << endl;
                string name, password;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter password: ";
                cin >> password;
                login(name, password);
                system("pause");
                system("CLS");
                break;
            }
            case 3:
            {
                system("CLS");
                system("color 0d");
                cout << "--------------- Send request ------------------\n";
                string receiver;
                cout << "Enter receiver's username: ";
                cin >> receiver;
                sendFriendRequest(receiver);
                system("pause");
                system("CLS");
                break;
            }
            case 4:
            {
                system("CLS");
                system("color 0d");
                cout << "--------------- Accept request ------------------\n";
                acceptFriendRequest();
                system("pause");
                system("CLS");
                break;
            }
            case 5:
            {
                system("CLS");
                system("color 0a");
                cout << "--------------- Create Post ------------------\n";
                createPost();
                system("pause");
                system("CLS");
                break;
            }
            case 6:
            {
                system("CLS");
                system("color 71");
                cout << "--------------- View Post ------------------\n";
                viewPosts();
                system("pause");
                system("CLS");
                break;
            }
            case 7:
            {
                system("CLS");
                system("color 07");
                cout << "--------------- News Feed ------------------\n";
                newsFeed();
                system("pause");
                system("CLS");
                break;
            }
            case 8:
            {
                system("CLS");
                system("color 0f");
                cout << "--------------- Send Message ------------------\n";
                sendMessage();
                system("pause");
                system("CLS");
                break;
            }
            case 9:
            {
                system("CLS");
                system("color 12");
                cout << "--------------- View Message ------------------\n";
                viewMessages();
                system("pause");
                system("CLS");
                break;
            }
            case 10:
            {
                system("CLS");
                system("color 03");
                cout << "--------------- Show Notifications ------------------\n";
                showNotifications();
                system("pause");
                system("CLS");
                break;
            }
            case 11:
            {
                system("CLS");
                system("color 01");
                cout << "--------------- Followers ------------------\n";
                showFollowers();
                system("pause");
                system("CLS");
                break;
            }
            case 12:
            {
                system("CLS");
                system("color 05");
                cout << "--------------- Following ------------------\n";
                showFollowing();
                system("pause");
                system("CLS");
                break;
            }
            case 13:
            {
                system("CLS");
                system("color 0a");
                cout << "--------------- Log Out ------------------\n";
                logout();
                system("pause");
                system("CLS");
                break;
            }
            case 14:
            {
                system("CLS");
                system("color 02");
                cout << "--------------- Search A User ------------------\n";
                string username;
                cout << "Enter username to find : ";
                cin >> username;
                User* user = users.findUser(username);
                if (user)
                {
                    cout << "User Found" << endl;
                }
                else
                {
                    cout << "Not Found" << endl;
                }
                system("pause");
                system("CLS");
                break;
            }
            case 15:
                system("CLS");
                cout << "Exiting..." << endl;
                system("pause");
                system("CLS");
                break;
            default:
                cout << "Invalid choice! Try again." << endl;

            }
        } while (choice != 15);
    }
};

int main()
{
    user_networks network;
    network.showMenu();
    return 0;
}

