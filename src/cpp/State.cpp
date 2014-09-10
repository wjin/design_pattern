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
