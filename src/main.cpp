// open scene graph tutorial
// Jeremiah Korreck

#include <osg/MatrixTransform>
#include <osg/PolygonMode>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>


int main() {

    // load the Models
    osg::ref_ptr<osg::Node> cessna = osgDB::readNodeFile("Resources/cessna.osg");
    
    // create transforms for each of the models I want to render in the scene
    osg::ref_ptr<osg::MatrixTransform> cessnaTransformRight = new osg::MatrixTransform;
    osg::ref_ptr<osg::MatrixTransform> cessnaTransformLeft = new osg::MatrixTransform;
    
    cessnaTransformRight->setMatrix(osg::Matrix::translate(25.0f, 0.0f, 0.0f));
    cessnaTransformLeft->setMatrix(osg::Matrix::translate(-25.0f, 0.0f, 0.0f));
    
    cessnaTransformRight->addChild(cessna.get());
    cessnaTransformLeft->addChild(cessna.get());

    osg::ref_ptr<osg::PolygonMode> pm = new osg::PolygonMode;
    pm->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
    cessnaTransformRight->getOrCreateStateSet()->setAttribute(pm.get());

    // add the transforms to the root node of the scene
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(cessnaTransformRight.get());
    root->addChild(cessnaTransformLeft.get());
    
    //create the viewer and then render the root
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    
    return viewer.run();
}
