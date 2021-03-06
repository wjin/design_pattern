# Observer

## Introduction

The observer pattern defines a **one-to-many** dependency between objects so that when one object changes state, all of its dependents are **notified and updated** automatically.

**Key Point**

* Subject and observers are loosely coupled

* Do not rely on notification order

* Pull/push

## Example

Nowadays, many people use scoial network sites or media, such as facebook, twitter and linkedin, to make friends and have fun. If you post a new message, all your friends who are following you will get it instantly. This is an observer pattern or publish/subscribe model in terms of IT guys :(

Another example is about Redis NoSql database. Redis has a feature called pub/sub. Client can subscribe any channels that it is interested in and then gets notification from those channels. This is also a **one-to-many** relationship and redis uses a list to record clients for each channel. In my opinion, observer pattern is an abstract concept that can be found in many softwares and its implementation depends on you.

## Code

Demo code shows all followers (Beauties) will get notification when subject(HandsomeEric) has a new post. And they are loosely coupled.

### Cpp

```cpp
class Observer;

// abstract subject
class Subject
{
public:
    virtual void registerObserver(Observer *) = 0;
    virtual void removeObserver(Observer *) = 0;
    virtual void notifyObservers() = 0;
};

// abstract observer
class Observer
{
public:
    virtual void update(const string &) = 0;
};

// concrete observer
class Beauty1 : Observer
{
public:
    virtual void update(const string &s)
    {
        cout << "Beauty1 got message: " << s << endl;
    }

    void follow(Subject *sub)
    {
        sub->registerObserver(this);
    }

    void unfollow(Subject *sub)
    {
        sub->removeObserver(this);
    }
};

// another concrete observer
class Beauty2 : Observer
{
public:
    virtual void update(const string &s)
    {
        cout << "Beauty2 got message: " << s << endl;
    }

    void follow(Subject *sub)
    {
        sub->registerObserver(this);
    }

    void unfollow(Subject *sub)
    {
        sub->removeObserver(this);
    }
};

// concrete subject
class HandsomeEric : public Subject
{
private:
    list<Observer*> followers;
    string latestPost;

public:
    virtual void registerObserver(Observer *obj)
    {
        followers.push_back(obj);
    }

    virtual void removeObserver(Observer *obj)
    {
        for (auto ite = followers.begin(); ite != followers.end(); ++ite) {
            if (*ite == obj) {
                followers.erase(ite);
            }
        }
    }

    virtual void notifyObservers()
    {
        for (auto e : followers) {
            e->update(latestPost);
        }
    }

    void newPost(const string &s)
    {
        latestPost = s;
        notifyObservers();
    }
};

int main(int argc, const char* argv[])
{
    HandsomeEric eric;
    Beauty1 b1;
    Beauty2 b2;

    b1.follow(&eric);
    b2.follow(&eric);
    eric.newPost("anyone wants to have a dinner with me?");

    b1.unfollow(&eric);
    eric.newPost("anyone wants to watch football match tonight?");

    return 0;
}
```

### Java

```java
import java.util.LinkedList;

// abstract Subject
interface Subject {
	public void registerObserver(Observer obj);

	public void removeObserver(Observer obj);

	public void notifyObservers();
};

// abstract Observer
interface Observer {
	public void update(String s);
};

// concrete Observer
class Beauty1 implements Observer {
	public void update(String s) {
		System.out.println("Beauty1 got message: " + s);
	}

	public void follow(Subject sub) {
		sub.registerObserver(this);
	}

	public void unfollow(Subject sub) {
		sub.removeObserver(this);
	}
};

// another concrete Observer
class Beauty2 implements Observer {
	public void update(String s) {
		System.out.println("Beauty2 got message: " + s);
	}

	public void follow(Subject sub) {
		sub.registerObserver(this);
	}

	public void unfollow(Subject sub) {
		sub.removeObserver(this);
	}
};

// concrete Subject
class HandsomeEric implements Subject {
	private final LinkedList<Observer> followers;
	private String latestPost;

	HandsomeEric() {
		followers = new LinkedList<Observer>();
	}

	public void registerObserver(Observer obj) {
		followers.add(obj);
	}

	public void removeObserver(Observer obj) {
		for (Observer e : followers) {
			if (e == obj) {
				followers.remove(e);
			}
		}
	}

	public void notifyObservers() {
		for (Observer e : followers) {
			e.update(latestPost); // push
		}
	}

	public void newPost(String s) {
		latestPost = s;
		notifyObservers();
	}
}

public class Observe {
	public static void main(String[] args) {
		HandsomeEric eric = new HandsomeEric();
		Beauty1 b1 = new Beauty1();
		Beauty2 b2 = new Beauty2();

		b1.follow(eric);
		b2.follow(eric);
		eric.newPost("anyone wants to have a dinner with me?");

		b1.unfollow(eric);
		eric.newPost("anyone wants to watch football match tonight?");
	}
}
```