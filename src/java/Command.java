import java.util.LinkedList;
import java.util.Queue;

// abstract command
interface Command {
	public void execute();
};

// append log command
class AddLog implements Command {
	public void execute() {
		System.out.println("Open file and append log");
	}
};

// access database command
class AccessDatabase implements Command {
	public void execute() {
		System.out.println("Open database and read tables");
	}
};

// macro command
// include a few commands together
class AccessAndLog implements Command {
	private final Command[] cmds;

	public AccessAndLog(Command[] v) {
		cmds = v;
	}

	public void execute() {
		for (Command e : cmds)
			e.execute();
	}
};

// shared queue between Server and Worker
class SharedQueue {
	public static final Queue<Command> workqueue = new LinkedList<Command>();
}

// command invoker
class Server {
	public void addCommand(Command cmd) {
		SharedQueue.workqueue.add(cmd);
	}
}

// command receiver
class Worker {
	public void excuteCommand() {
		while (!SharedQueue.workqueue.isEmpty()) {
			Command c = SharedQueue.workqueue.remove();
			c.execute();
		}
	}
}

public class CommandTest {
	public static void main(String[] args) {
		Server s = new Server();
		Worker w = new Worker();

		Command log = new AddLog();
		Command db = new AccessDatabase();
		Command[] v = { log, db };
		Command macro = new AccessAndLog(v);

		s.addCommand(log);
		s.addCommand(db);
		s.addCommand(macro);

		w.excuteCommand();
	}
}
