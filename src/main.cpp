// open scene graph tutorial
// Jeremiah Korreck

#include <osg/MatrixTransform>
#include <osg/Switch>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include "SwitchingCallback.h"

int main() {
    // set the number of multisamples  2,4, or 6
    // rpi 4 only accepts 2, 4
    
    osg::DisplaySettings::instance()->setNumMultiSamples(4);

    osg::ref_ptr<osg::Node> cessna = osgDB::readNodeFile("Resources/cessna.osg");
    osg::ref_ptr<osg::Node> cessnaFire = osgDB::readNodeFile("Resources/cessnaFire.osg");

    osg::ref_ptr<osg::Switch> cessnaSwitch = new osg::Switch;
    cessnaSwitch->addChild(cessna.get(), false);
    cessnaSwitch->addChild(cessnaFire.get(), true);
    
    cessnaSwitch->setUpdateCallback(new SwitchingCallback);
    
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(cessnaSwitch);

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    viewer.setCameraManipulator(new osgGA::TrackballManipulator);
    while(!viewer.done()) {
        viewer.frame();
    }
    
    return 0;
}
