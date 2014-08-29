#include <iostream>
#include <memory>

using namespace std;

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
