# Strategy

## Introduction

The strategy pattern defines **a family of algorithms**, encapsulates each one, and makes them **interchangeable**. Strategy lets the algorithm **vary independently from clients** that use it.

## Example

In my previous work about Android audio framework, I was responsible for integrating Intel SRC(sample rate conversion) into Android audio framework as Intel SRC has better performance than the default SRC on x86 platform.

The default design is pretty good and easy to understand and extend because of Strategy Pattern. I implemented a new derived class, which encapsulates Intel SRC algorithm (a family of algorithms).

Also, we can dynamically switch back to default SRC when Intel SRC does not support some specific kind of conversions (interchangaeble).

The client, audio control (AudioFlinger in android), does not care about which algorithm it is using, it just delegates resampler to do conversion for it (vary independently from clients).

## Code

### CPP

```cpp
// Base class
class SRC
{
public:
    // interface, ignore arguments :(
    // convert data from input to output buffer
    virtual void convert() = 0;
};

// Default SRC
class DefaultSRC : public SRC
{
public:
    void convert()
    {
        cout << "Default Naive SRC" << endl;
    }
};

// Intel SRC
class IntelSRC : public SRC
{
public:
    void convert()
    {
        cout << "Intel High Performance SRC" << endl;
    }
};

// Audio Control class
class AudioControl
{
private:
    shared_ptr<SRC> m_resampler; // encapsulate SRC algorithm

public:
    AudioControl() : m_resampler(new DefaultSRC()) {}

    void processData()
    {
        // convert all channel's data to the same sample rate
        // and then mix them togegher
        m_resampler->convert();
        mixChannel();
        // ...
    }

    void mixChannel()
    {
        cout << "mix data" << endl;
    }

    // dynamic switch SRC
    void swithSRC()
    {
        m_resampler.reset(new IntelSRC());
    }
};

int main(int argc, const char* argv[])
{
    AudioControl obj;

    obj.processData();
    obj.swithSRC();
    obj.processData();

    return 0;
}
```

### Java

```java
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
```
