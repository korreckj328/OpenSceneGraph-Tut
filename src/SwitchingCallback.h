#ifndef SWITCHINGCALLBACK_H
#define SWITCHINGCALLBACK_H

#include <osg/Switch>

class SwitchingCallback : public osg::NodeCallback {
public:
    SwitchingCallback() : _count(0) {}
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

protected:
    unsigned int _count;
};
#endif