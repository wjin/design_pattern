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
