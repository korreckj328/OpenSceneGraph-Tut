// open scene graph tutorial
// Jeremiah Korreck

#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main() {

    // load the Models
    osg::ref_ptr<osg::Node> cessna = osgDB::readNodeFile("Resources/cessna.osg");
    osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile("Resources/cow.osg");
    
    // create transforms for each of the models I want to render in the scene
    osg::ref_ptr<osg::MatrixTransform> cessnaTransform1 = new osg::MatrixTransform;
    osg::ref_ptr<osg::MatrixTransform> cessnaTransform2 = new osg::MatrixTransform;
    osg::ref_ptr<osg::MatrixTransform> cowTransform = new osg::MatrixTransform;
    
    // from the perspective of the camera move the cessnas right and left and the cow backwards
    cessnaTransform1->setMatrix(osg::Matrix::translate(-25.0f, 0.0f, 0.0f));
    cessnaTransform2->setMatrix(osg::Matrix::translate(25.0f, 0.0f, 0.0f));
    cowTransform->setMatrix(osg::Matrix::translate(0.0f, 25.0f, 0.0f));
    
    // add the models to the transforms, note the cessnaTransforms are sharing their leaf node
    cessnaTransform1->addChild(cessna.get());
    cessnaTransform2->addChild(cessna.get());
    cowTransform->addChild(cow.get());
    
    // add the transforms to the root node of the scene
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(cessnaTransform1.get());
    root->addChild(cessnaTransform2.get());
    root->addChild(cowTransform.get());
    
    //create the viewer and then render the root
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    
    return viewer.run();
}
