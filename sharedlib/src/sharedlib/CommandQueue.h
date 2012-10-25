#ifndef COMMANDQUEUE_H
#define	COMMANDQUEUE_H

#include <deque>
#include <functional>
#include <yaxl.h>
#include "CompileConfig.h"

using std::deque;

class LIBEXPORT CommandQueue {
public:
    typedef std::function<void(void)> Command;

    CommandQueue(void);
    virtual ~CommandQueue(void);

    void run(void);
    void add(Command command);

private:
    deque<Command> _commands;
    yaxl::concurrency::Mutex _mutex;
};

#endif	/* COMMANDQUEUE_H */

