class Ferrai;

// abstract car state
class CarState
{
public:
    virtual void drive() = 0;
    virtual ~CarState() {}
};

class StartState : public CarState
{
private:
    Ferrai* m_car;

public:
    StartState(Ferrai* car);
    void drive();
};

class NormalState : public CarState
{
private:
    Ferrai* m_car;

public:
    NormalState(Ferrai *car);
    void drive();
};

class BurstState : public CarState
{
private:
    Ferrai* m_car;

public:
    BurstState(Ferrai *car);
    void drive();
};

class AutoState : public CarState
{
private:
    Ferrai* m_car;

public:
    AutoState(Ferrai *car);
    void drive();
};

class Ferrai
{
private:
    // all states
    CarState* m_startState; // start state
    CarState* m_normalState; // normal state
    CarState* m_burstState; // burst state
    CarState* m_autoState; // auto state

    CarState* m_state; // current car state
    int m_speed; // current car speed

    void setState(CarState* m)
    {
        m_state = m;
    }

public:
    void setSpeed(int n)
    {
        m_speed = n;
    }

    Ferrai();
    ~Ferrai();

    void pushStartStateButton();
    void pushNormalStateButton();
    void pushBurstStateButton();
    void pushAutoStateButton();

    void drive();
};

