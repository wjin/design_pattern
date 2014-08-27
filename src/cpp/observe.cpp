#include <iostream>
#include <memory>
#include <list>
#include <string>

using namespace std;

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
