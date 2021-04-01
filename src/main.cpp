// open scene graph tutorial
// Jeremiah Korreck

#include <osg/MatrixTransform>
#include <osg/LOD>
#include <osgUtil/Simplifier>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main() {

    // load the Models
    osg::ref_ptr<osg::Node> cessnaL3 = osgDB::readNodeFile("Resources/cessna.osg");
    osg::ref_ptr<osg::Node> cessnaL2 = dynamic_cast<osg::Node*>(cessnaL3->clone(osg::CopyOp::DEEP_COPY_ALL));
    osg::ref_ptr<osg::Node> cessnaL1 = dynamic_cast<osg::Node*>(cessnaL3->clone(osg::CopyOp::DEEP_COPY_ALL));
    
    // create transforms for each of the models I want to render in the scene
    osg::ref_ptr<osg::MatrixTransform> cessnaTransform1 = new osg::MatrixTransform;
    
    // create simplifier
    osgUtil::Simplifier simplifier;
    simplifier.setSampleRatio(0.5);

    // run the second model thru the simplifier
    cessnaL2->accept(simplifier);

    // set the simplifier to a smaller ratio and run L1
    simplifier.setSampleRatio(0.1);
    cessnaL1->accept(simplifier);

    // create the LOD node
    osg::ref_ptr<osg::LOD> cessnaLOD = new osg::LOD;
    cessnaLOD->addChild(cessnaL1.get(), 200.0f, FLT_MAX);
    cessnaLOD->addChild(cessnaL2.get(), 50.0f, 200.0f);
    cessnaLOD->addChild(cessnaL3.get(), 0.0f, 50.0f);

    // add the LOD node to the models transform
    cessnaTransform1->addChild(cessnaLOD.get());

    // add the transforms to the root node of the scene
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(cessnaTransform1.get());
    
    //create the viewer and then render the root
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    
    return viewer.run();
}
