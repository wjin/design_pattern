// abstract worker
abstract class Worker {

	// template method, do not modify
	public final void process() {
		// hook for subclass
		hook();

		readRequest();
		analyseRequest();
		executeRequest();
		returnResult();
	}

	public void readRequest() {
		System.out.println("IPC: read request from master process");
	}

	public void analyseRequest() {
		System.out
				.println("Protocol Analysis: analyse request and store result to handle");
	}

	public abstract void executeRequest();

	public void returnResult() {
		System.out.println("Return: return result in buffer to master process");
	}

	public void hook() {
	}
}

// append log worker
class WorkerForLog extends Worker {
	@Override
	public void executeRequest() {
		System.out.println("Execute: open file and append log");
	}
}

// access database worker
class WorkerForDB extends Worker {
	@Override
	public void executeRequest() {
		System.out.println("Execute: open database and read tables");
	}
}

public class Template {
	public static void main(String[] args) {
		Worker log = new WorkerForLog();
		Worker db = new WorkerForDB();

		log.process();
		System.out.println();
		db.process();
	}
}
