//
// Created by Jeremiah Korreck on 4/17/21.
//

#include <osg/Geometry>
#include "DynamicQuadCallback.h"

void DynamicQuadCallback::update(osg::NodeVisitor *, osg::Drawable *drawable) {
    osg::Geometry* quad = dynamic_cast<osg::Geometry*>(drawable);
    if(!quad) {
        return;
    }
    osg::Vec3Array * vertices = dynamic_cast<osg::Vec3Array*>(quad->getVertexArray());
    if(!vertices) {
        return;
    }
    osg::Quat quat(osg::PI * 0.01, osg::X_AXIS);
    vertices->back() = quat * vertices->back();
    quad->dirtyDisplayList();
    quad->dirtyBound();
}
