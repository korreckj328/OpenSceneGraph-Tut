#include "AnimatedSwitch.h"
namespace korreckSoftware {
    void AnimatedSwitch::traverse(osg::NodeVisitor& nv) {
        if (!(++_count % 60)) {
            setValue(0, !getValue(0));
            setValue(1, !getValue(1));
        }
        osg::Switch::traverse(nv);
    }
}