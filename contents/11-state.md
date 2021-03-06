# State

## Introduction

The state pattern allows an object to **alter its behavior when its internal state changes**. The object will appear to change its class. And the UML graph is similar to Strategy pattern.

## Example

Last weekend, I watched a F1 match. And noticed that Hamilton ran into an issue when starting because the car's start mode button did not work. A conspiracy?

Also I noticed that there is a burst mode of the engine that driveres can use to get much more power with a little more fuel.

So here I take car as an example as I always take the things I am familar with. Normally, a car has three modes: start mode, normal mode and burst mode. As a state pattern, it is easy to add other modes, so auto mode is added to my fancy car because of Google's advanced unmaned technology. I wish there is a fly mode in the near future :(

## Code

### Cpp

As there are two classes referenced with each other, to pass build we need to split header file and cpp file.

```cpp
// File State.h
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


// File State.cpp

#include <iostream>
#include "State.h"

using namespace std;

StartState::StartState(Ferrai* car)
{
    m_car = car;
}

void StartState::drive()
{
    m_car->setSpeed(10);
    cout << "Start State: help start smoothly" << endl;
}

NormalState::NormalState(Ferrai *car)
{
    m_car = car;
}

void NormalState::drive()
{
    m_car->setSpeed(50);
    cout << "Normal State: have fun" << endl;
}

BurstState::BurstState(Ferrai *car)
{
    m_car = car;
}

void BurstState::drive()
{
    m_car->setSpeed(100);
    cout << "Burst State: please concentrate" << endl;
}

AutoState::AutoState(Ferrai *car)
{
    m_car = car;
}

void AutoState::drive()
{
    m_car->setSpeed(30);
    cout << "Auto State: relax, just enjoy" << endl;
}

Ferrai::Ferrai()
    : m_startState(new StartState(this)),
      m_normalState(new NormalState(this)),
      m_burstState(new BurstState(this)),
      m_autoState(new AutoState(this))
{
    setState(m_normalState);
    setSpeed(0);
}

Ferrai::~Ferrai()
{
    delete m_startState;
    delete m_normalState;
    delete m_burstState;
    delete m_autoState;
}

void Ferrai::pushStartStateButton()
{
    setState(m_startState);
}

void Ferrai::pushNormalStateButton()
{
    setState(m_normalState);
}

void Ferrai::pushBurstStateButton()
{
    // security check
    if (typeid(*m_state) != typeid(NormalState)) {
        cout << "Warnning: cannot enter burst state" << endl;
        return;
    }

    setState(m_burstState);
}

void Ferrai::pushAutoStateButton()
{
    setState(m_autoState);
}

void Ferrai::drive()
{
    m_state->drive();
    cout << "Current Speed:" << m_speed << endl;
}

int main(int argc, char *argv[])
{
    Ferrai car;

    car.pushStartStateButton();
    car.drive();

    car.pushNormalStateButton();
    car.drive();

    car.pushBurstStateButton();
    car.drive();

    car.pushAutoStateButton();
    car.drive();

    car.pushBurstStateButton();
    car.drive();

    car.pushNormalStateButton();
    car.drive();

    return 0;
}
```

### Java
```java
// abstract car state
interface CarState {
	public void drive();
}

class StartState implements CarState {
	private final Ferrai car;

	public StartState(Ferrai car) {
		this.car = car;
	}

	public void drive() {
		car.setSpeed(10);
		System.out.println("Start State: help start smoothly");
	}
}

class NormalState implements CarState {
	private final Ferrai car;

	public NormalState(Ferrai car) {
		this.car = car;
	}

	public void drive() {
		car.setSpeed(50);
		System.out.println("Normal State: have fun");
	}
}

class BurstState implements CarState {
	private final Ferrai car;

	public BurstState(Ferrai car) {
		this.car = car;
	}

	public void drive() {
		car.setSpeed(100);
		System.out.println("Burst State: please concentrate");
	}
}

class AutoState implements CarState {
	private final Ferrai car;

	public AutoState(Ferrai car) {
		this.car = car;
	}

	public void drive() {
		car.setSpeed(30);
		System.out.println("Auto State: relax, just enjoy");
	}
}

class Ferrai {
	// all states
	private final CarState m_startState; // start state
	private final CarState m_normalState; // normal state
	private final CarState m_burstState; // burst state
	private final CarState m_autoState; // auto state

	private CarState m_state; // current car state
	private int m_speed; // current car speed

	private void setState(CarState state) {
		m_state = state;
	}

	void setSpeed(int speed) {
		m_speed = speed;
	}

	public Ferrai() {
		m_startState = new StartState(this);
		m_normalState = new NormalState(this);
		m_burstState = new BurstState(this);
		m_autoState = new AutoState(this);

		setState(m_normalState);
		setSpeed(0);
	}

	public void pushStartStateButton() {
		setState(m_startState);
	}

	public void pushNormalStateButton() {
		setState(m_normalState);
	}

	public void pushBurstStateButton() {
		// security check
		if (!(m_state instanceof NormalState)) {
			System.out.println("Warnning: cannot enter burst state");
			return;
		}

		setState(m_burstState);
	}

	public void pushAutoStateButton() {
		setState(m_autoState);
	}

	public void drive() {
		m_state.drive();
		System.out.println("Current Speed:" + m_speed);
	}
}

public class State {
	public static void main(String[] args) {
		Ferrai car = new Ferrai();

		car.pushStartStateButton();
		car.drive();

		car.pushNormalStateButton();
		car.drive();

		car.pushBurstStateButton();
		car.drive();

		car.pushAutoStateButton();
		car.drive();

		car.pushBurstStateButton();
		car.drive();

		car.pushNormalStateButton();
		car.drive();

	}
}
```
