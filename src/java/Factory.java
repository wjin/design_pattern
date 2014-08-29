interface SRC {
	public void convert();
}

class DefaultSRC implements SRC {
	public void convert() {
		System.out.println("Default Naive SRC");
	}
}

class IntelSRC implements SRC {
	public void convert() {
		System.out.println("Intel High Performance SRC");
	}
}

abstract class AudioControl {
	public void processData() {
		SRC resampler = createSRC();
		resampler.convert();
		mixChannel();
	}

	public void mixChannel() {
		System.out.println("mix data");
	}

	// factory...
	protected abstract SRC createSRC();
}

class DefaultAudioControl extends AudioControl {
	@Override
	protected SRC createSRC() {
		System.out.println("Create Default SRC");
		return new DefaultSRC();
	}
}

class IntelAudioControl extends AudioControl {
	@Override
	protected SRC createSRC() {
		System.out.println("Create Intel SRC");
		return new IntelSRC();
	}
}

public class Factory {
	public static void main(String[] args) {
		AudioControl obj = new DefaultAudioControl();
		AudioControl iobj = new IntelAudioControl();

		obj.processData();
		iobj.processData();
	}
}
