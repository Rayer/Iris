/**
 * Project Iris
 */


#ifndef _CONTEXT_H
#define _CONTEXT_H

namespace Iris {
    class Context {
        bool running;
    public:
        bool isRunning() const;

        void setRunning(bool running);
    };
}


#endif //_CONTEXT_H