//
// Created by Jeremiah Korreck on 4/17/21.
//

#ifndef OPENSCENEGRAPH_TUT_DYNAMICQUADCALLBACK_H
#define OPENSCENEGRAPH_TUT_DYNAMICQUADCALLBACK_H


#include <osg/Drawable>

class DynamicQuadCallback : public osg::Drawable::UpdateCallback {
public:
    virtual void update(osg::NodeVisitor*, osg::Drawable* drawable);
};


#endif //OPENSCENEGRAPH_TUT_DYNAMICQUADCALLBACK_H
