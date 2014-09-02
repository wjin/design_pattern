#include <iostream>
#include <memory>

using namespace std;

// abstract worker
class Worker
{
public:
    // template method, do not modify
    virtual void process() final {
        // hook for subclass
        hook();

        readRequest();
        analyseRequest();
        executeRequest();
        returnResult();
    }

    void readRequest()
    {
        cout << "IPC: read request from master process" << endl;
    }

    void analyseRequest()
    {
        cout << "Protocol Analysis: analyse request and store result to handle" << endl;
    }

    virtual void executeRequest() = 0;

    void returnResult()
    {
        cout << "Return: return result in buffer to master process" << endl;
    }

    virtual void hook() {}
};

// append log worker
class WorkerForLog : public Worker
{
public:
    void executeRequest()
    {
        cout << "Execute: open file and append log" << endl;
    }
};

// access database worker
class WorkerForDB : public Worker
{
public:
    void executeRequest()
    {
        cout << "Execute: open database and read tables" << endl;
    }
};

int main(int argc, const char* argv[])
{
    shared_ptr<Worker> log(new WorkerForLog());
    shared_ptr<Worker> db(new WorkerForDB());

    log->process();
    cout << endl;
    db->process();

    return 0;
}
