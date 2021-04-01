// open scene graph tutorial
// Jeremiah Korreck

#include <osg/MatrixTransform>
#include <osg/Switch>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main() {

    // load the Models
    osg::ref_ptr<osg::Node> cessna = osgDB::readNodeFile("Resources/cessna.osg");
    osg::ref_ptr<osg::Node> cessna_onfire = osgDB::readNodeFile("Resources/cessnafire.osg");
    
    // create transforms for each of the models I want to render in the scene
    osg::ref_ptr<osg::MatrixTransform> cessnaTransform1 = new osg::MatrixTransform;
    
    // create a switch node
    osg::ref_ptr<osg::Switch> cessnaModelSwitch = new osg::Switch;
    cessnaModelSwitch->addChild(cessna.get(), false);
    cessnaModelSwitch->addChild(cessna_onfire.get(), true);
    
    // add the models to the transforms, note the cessnaTransforms are sharing their leaf node
    cessnaTransform1->addChild(cessnaModelSwitch.get());
    
    // add the transforms to the root node of the scene
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(cessnaTransform1.get());
    
    // switchnode set value
    cessnaModelSwitch->setValue(0, true);
    cessnaModelSwitch->setValue(1, false);
    
    //create the viewer and then render the root
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    
    return viewer.run();
}
