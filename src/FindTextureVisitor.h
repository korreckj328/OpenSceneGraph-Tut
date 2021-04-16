#ifndef FINDTEXTUREVISITOR_H
#define FINDTEXTUREVISITOR_H

// #include <osg/Texture2D>
// #include <osg/Camera>
// #include <osgDB/ReadFile>
// #include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>

class FindTextureVisitor : public osg::NodeVisitor {
public:
    FindTextureVisitor(osg::Texture* texture) : _texture(texture) {
        setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);
    }

    virtual void apply(osg::Node& node);
    virtual void apply(osg::Geode& geode);
    void replaceTexture(osg::StateSet* stateSet);
protected:
    osg::ref_ptr<osg::Texture> _texture;
};


#endif