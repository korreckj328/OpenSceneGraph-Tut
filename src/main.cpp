// open scene graph tutorial
// Jeremiah Korreck

#include <osg/MatrixTransform>
#include <osg/Fog>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>


int main() {
    // create the fog
    osg::ref_ptr<osg::Fog> fog = new osg::Fog;
    fog->setMode(osg::Fog::LINEAR);
    fog->setStart(500.0f);
    fog->setEnd(2500.0f);
    fog->setColor(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    
    // load the Models
    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("Resources/lz.osg");
    
    // create transforms for each of the models I want to render in the scene
    osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform;
    
    transform->addChild(model.get());
   
    transform->getOrCreateStateSet()->setAttributeAndModes(fog.get());
    
    // add the transforms to the root node of the scene
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(transform.get());
    
    
    //create the viewer and then render the root
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    
    return viewer.run();
}
