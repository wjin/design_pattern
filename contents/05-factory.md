# Factory

## Introduction

Factory method is used to encapsulate create behavior so that it **decreases dependencies** between classes and make them loosely decouled. We should **depend on abstraction instead of concrete classes**.

There are three kinds of factory pattern in total: simple factory, factory method and abstract factory.

**Simple Factory** is too simple, it encapsulates creating objects behavior in another class object or just a simple, normally static, function.

**Factory Method** defines an interface for creating an object, but let **subclasses** decide which class to instantiate. Factory Method lets a class **defer instantiation to subclasses**. 

**Abstract factory** includes a series of factory methods to create more than one object once. We can consider factory method as a special case (just create one object) of abstract factory.

Besides, factory method is a special case of template method pattern, and in CPP, there is a technical term for this kind of programming habit: NVI (non-virtual interface).
 
## Example

Again, take Intel SRC as an exmpale. In strategy pattern, it creates SRC object using **new** operator directly. Here I use factory method to encapsulate **create behavoir**.

## Code

### Cpp

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

// Base Audio Control class
class AudioControl
{
public:
    // this is a NVI template method to
    // deal with audio data, do not modify
    void processData()
    {
        // convert all channel's data to the same sample rate
        // and then mix them togegher
        shared_ptr<SRC> resampler = createSRC();
        resampler->convert();
        mixChannel();
        // ...
    }

    void mixChannel()
    {
        cout << "mix data" << endl;
    }

    // factory...
protected:
    virtual shared_ptr<SRC> createSRC() = 0;
};

// Default Audio Control class
class DefaultAudioControl : public AudioControl
{
private:
    virtual shared_ptr<SRC> createSRC()
    {
        cout << "Create Default SRC" << endl;
        return shared_ptr<SRC>(new DefaultSRC());
    }
};

// Specific Intel Audio Control class
class IntelAudioControl : public AudioControl
{
private:
    virtual shared_ptr<SRC> createSRC()
    {
        cout << "Create Intel SRC" << endl;
        return shared_ptr<SRC>(new IntelSRC());
    }
};

int main(int argc, const char* argv[])
{
    shared_ptr<AudioControl> obj(new DefaultAudioControl());
    shared_ptr<AudioControl> iobj(new IntelAudioControl());

    obj->processData();
    iobj->processData();

    return 0;
}
```

### Java

```java
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
```