#include <iostream>
#include <memory>
#include <queue>
#include <vector>

using namespace std;

// abstract command
class Command
{
public:
    virtual void execute() = 0;
};

// append log command
class AddLog : public Command
{
public:
    void execute()
    {
        cout << "Open file and append log" << endl;
    }
};

// access database command
class AccessDatabase : public Command
{
public:
    void execute()
    {
        cout << "Open database and read tables" << endl;
    }
};

// macro command
// include a few commands together
class AccessAndLog : public Command
{
private:
    vector<shared_ptr<Command>> cmds;

public:
    AccessAndLog(vector<shared_ptr<Command>> &v) : cmds(v) {}
    void execute()
    {
        for (auto e : cmds)
            e->execute();
    }
};

// shared queue between server and worker
queue<shared_ptr<Command>> workqueue;

// command invoker
class Server
{
public:
    void addCommand(shared_ptr<Command> cmd)
    {
        workqueue.push(cmd);
    }
};

// command receiver
class Worker
{
public:
    void excuteCommand()
    {
        while (!workqueue.empty()) {
            shared_ptr<Command> cmd = workqueue.front();
            workqueue.pop();
            cmd->execute();
        }
    }
};

int main(int argc, const char* argv[])
{
    Server s;
    Worker w;

    shared_ptr<Command> log(new AddLog());
    shared_ptr<Command> db(new AccessDatabase());
    vector<shared_ptr<Command>> v = { log, db };
    shared_ptr<Command> macro(new AccessAndLog(v));

    s.addCommand(log);
    s.addCommand(db);
    s.addCommand(macro);

    w.excuteCommand();

    return 0;
}
