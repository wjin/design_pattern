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

