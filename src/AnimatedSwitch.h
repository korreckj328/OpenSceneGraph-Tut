// Animated Switch
#ifndef ANIMATED_SWITCH_H
#define ANIMATED_SWITCH_H
#include <osg/Switch>
namespace korreckSoftware {
    class AnimatedSwitch: public osg::Switch {
    public:
        AnimatedSwitch() : osg::Switch(), _count(0){}
        AnimatedSwitch(const AnimatedSwitch& copy, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY): osg::Switch(copy, copyop), _count(copy._count) {}
        META_Node(osg, AnimatedSwitch);

        virtual void traverse(osg::NodeVisitor& nv);
    protected:
        unsigned int _count;
    };
};

#endif