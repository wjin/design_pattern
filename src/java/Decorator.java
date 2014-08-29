// abstract component
abstract class Character {
	public void attack() {
	}
}

// concrete component
class Warrior extends Character {
	@Override
	public void attack() {
		System.out.println("Warrior is attacking");
	}
}

// another concrete component
class Wizard extends Character {
	@Override
	public void attack() {
		System.out.println("Wizard is attacking");
	}
}

// abstract decorator
// decorator has the same type of the object
// that it will decorate
class Weapon extends Character {
}

// concrete decorator
class Sword extends Weapon {
	private final Character person;

	public Sword(Character ptr) {
		person = ptr;
	}

	@Override
	public void attack() {
		System.out.print("Begin...");
		person.attack();
		System.out.print("with Sword");
		System.out.println("...End");
	}
}

// concrete decorator
class Wand extends Weapon {
	private final Character person;

	public Wand(Character ptr) {
		person = ptr;
	}

	@Override
	public void attack() {
		System.out.print("Begin...");
		person.attack();
		System.out.print("with Wand");
		System.out.println("...End");
	}
}

public class Decorator {
	public static void main(String[] args) {
		Character war = new Warrior();
		Character wiz = new Wizard();

		war.attack();
		wiz.attack();

		Character warWithSword = new Sword(war);
		Character warWithWand = new Wand(war);
		Character wizWithSword = new Sword(wiz);
		Character wizWithWand = new Wand(wiz);

		warWithSword.attack();
		warWithWand.attack();
		wizWithSword.attack();
		wizWithWand.attack();
	}
}
