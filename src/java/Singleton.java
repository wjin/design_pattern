// do not consider multithread
public class Singleton {
	private static Singleton instance; // static

	private Singleton() { // private
	}

	public static Singleton getInstance() { // static
		if (instance == null) {
			instance = new Singleton();
		}
		return instance;
	}

	public static void main(String[] args) {
		Singleton obj1 = getInstance();
		Singleton obj2 = getInstance();

		if (obj1 != obj2) {
			System.out.println("Wrong");
		} else {
			System.out.println("Right");
		}
	}
}


// synchronized method
public class Singleton {
	private static Singleton instance; // static

	private Singleton() { // private
	}

	public static synchronized Singleton getInstance() { // static
		if (instance == null) {
			instance = new Singleton();
		}
		return instance;
	}
	// ...
}


// double-checked locking
public class Singleton {
	private volatile static Singleton instance; // volatile static

	private Singleton() { // private
	}

	public static Singleton getInstance() { // static
		if (instance == null) {
			synchronized (Singleton.class) {
				if (instance == null) {
					instance = new Singleton();
				}
			}
		}
		return instance;
	}
    // ...
}


// early create object
public class Singleton {
	private final static Singleton instance = new Singleton(); // static

	private Singleton() { // private
	}

	public static Singleton getInstance() { // static
		return instance;
	}
	// ...
}


// static code block
public class Singleton {
	private final static Singleton instance; // static

	private Singleton() { // private
	}

	static {
		instance = new Singleton();
	}

	public static Singleton getInstance() { // static
		return instance;
	}
	// ...
}
