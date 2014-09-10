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
