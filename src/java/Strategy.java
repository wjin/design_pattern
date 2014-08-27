interface SRC {
	public void convert();
}

class DefaultSRC implements SRC {
	public void convert()
	{
		System.out.println("Default Naive SRC");
	}
}

class IntelSRC implements SRC {
	public void convert()
	{
		System.out.println("Intel High Performance SRC");
	}
}

class AudioControl {
	private SRC m_resampler;
	
	public AudioControl()
	{
		m_resampler = new DefaultSRC();
	}
	
    public void processData()
    {
        m_resampler.convert();
        mixChannel();
    }

    public void mixChannel()
    {
    	System.out.println("mix data");
    }

    public void swithSRC()
    {
        m_resampler = new IntelSRC();
    }
}

public class Strategy {
	public static void main(String[] args) {
		AudioControl obj = new AudioControl();
		obj.processData();
		obj.swithSRC();
		obj.processData();
	}
}

