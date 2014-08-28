#include <iostream>
#include <memory>

using namespace std;

// abstract component
class Character
{
public:
    virtual void attack() = 0;
};

// concrete component
class Warrior : public Character
{
public:
    void attack()
    {
        cout << "Warrior is attacking" << endl;
    }
};

// another concrete component
class Wizard : public Character
{
public:
    void attack()
    {
        cout << "Wizard is attacking" << endl;
    }
};

// abstract decorator
// decorator has the same type of the object
// that it will decoreate
class Weapon : public Character
{
};

// concrete decorator
class Sword : public Weapon
{
private:
    shared_ptr<Character> person;

public:
    Sword(shared_ptr<Character> ptr) : person(ptr) {}
    void attack()
    {
        cout << "Begin...";
        person->attack();
        cout << "with Sword";
        cout << "...End" << endl;
    }
};

// another concrete decorator
class Wand : public Weapon
{
private:
    shared_ptr<Character> person;

public:
    Wand(shared_ptr<Character> ptr) : person(ptr) {}
    void attack()
    {
        cout << "Begin...";
        person->attack();
        cout << "with Wand";
        cout << "...End" << endl;
    }
};

int main(int argc, const char* argv[])
{
    shared_ptr<Character> war(new Warrior());
    shared_ptr<Character> wiz(new Wizard());

    war->attack();
    wiz->attack();

    shared_ptr<Character> warWithSword(new Sword(war));
    shared_ptr<Character> warWithWand(new Wand(war));
    shared_ptr<Character> wizWithSword(new Sword(wiz));
    shared_ptr<Character> wizWithWand(new Wand(wiz));

    warWithSword->attack();
    warWithWand->attack();
    wizWithSword->attack();
    wizWithWand->attack();

    // crazy warrior with sword and wand :(
    shared_ptr<Character> warWithSwordAndWand(new Wand(warWithSword));
    warWithSwordAndWand->attack();

    return 0;
}
