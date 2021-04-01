// open scene graph tutorial
// Jeremiah Korreck

#include <osg/MatrixTransform>
#include <osg/PolygonMode>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>


int main() {

    // load the Models
    osg::ref_ptr<osg::Node> glider = osgDB::readNodeFile("Resources/glider.osg");
    
    // create transforms for each of the models I want to render in the scene
    osg::ref_ptr<osg::MatrixTransform> gliderTransformRight = new osg::MatrixTransform;
    osg::ref_ptr<osg::MatrixTransform> gliderTransformLeft = new osg::MatrixTransform;
    
    gliderTransformRight->setMatrix(osg::Matrix::translate(0.5f, 0.0f, 0.0f));
    gliderTransformLeft->setMatrix(osg::Matrix::translate(-0.5f, 0.0f, 0.0f));
    
    gliderTransformRight->addChild(glider.get());
    gliderTransformLeft->addChild(glider.get());

    osg::ref_ptr<osg::PolygonMode> pm = new osg::PolygonMode;
    pm->setMode(osg::PolygonMode::FRONT, osg::PolygonMode::FILL);
    gliderTransformRight->getOrCreateStateSet()->setAttribute(pm.get());

    // add the transforms to the root node of the scene
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(gliderTransformRight.get());
    root->addChild(gliderTransformLeft.get());
    
    // add lighting attributes
    gliderTransformRight->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    gliderTransformLeft->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF|osg::StateAttribute::PROTECTED);
    root->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE );
    
    //create the viewer and then render the root
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    
    return viewer.run();
}
