// open scene graph tutorial
// Jeremiah Korreck

#include <osg/MatrixTransform>
#include <osg/LOD>
#include <osg/Switch>
#include <osgUtil/Simplifier>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include "AnimatedSwitch.h"

int main() {

    // load the Models
    osg::ref_ptr<osg::Node> cessnaL3 = osgDB::readNodeFile("Resources/cessna.osg");
    osg::ref_ptr<osg::Node> cessnaL2 = dynamic_cast<osg::Node*>(cessnaL3->clone(osg::CopyOp::DEEP_COPY_ALL));
    osg::ref_ptr<osg::Node> cessnaL1 = dynamic_cast<osg::Node*>(cessnaL3->clone(osg::CopyOp::DEEP_COPY_ALL));

    osg::ref_ptr<osg::Node> cessnafireL3 = osgDB::readNodeFile("Resources/cessnafire.osg");
    osg::ref_ptr<osg::Node> cessnafireL2 = dynamic_cast<osg::Node*>(cessnafireL3->clone(osg::CopyOp::DEEP_COPY_ALL));
    osg::ref_ptr<osg::Node> cessnafireL1 = dynamic_cast<osg::Node*>(cessnafireL3->clone(osg::CopyOp::DEEP_COPY_ALL));
    
    // create transforms for each of the models I want to render in the scene
    osg::ref_ptr<osg::MatrixTransform> cessnaTransform = new osg::MatrixTransform;
    
    // create simplifier
    osgUtil::Simplifier simplifier;
    simplifier.setSampleRatio(0.5);

    // run the second model thru the simplifier
    cessnaL2->accept(simplifier);
    cessnafireL2->accept(simplifier);

    // set the simplifier to a smaller ratio and run L1
    simplifier.setSampleRatio(0.1);
    cessnaL1->accept(simplifier);
    cessnafireL1->accept(simplifier);

    // create the LOD node
    osg::ref_ptr<osg::LOD> cessnaLOD = new osg::LOD;
    cessnaLOD->addChild(cessnaL1.get(), 200.0f, FLT_MAX);
    cessnaLOD->addChild(cessnaL2.get(), 50.0f, 200.0f);
    cessnaLOD->addChild(cessnaL3.get(), 0.0f, 50.0f);

    osg::ref_ptr<osg::LOD> cessnafireLOD = new osg::LOD;
    cessnafireLOD->addChild(cessnafireL1.get(), 200.0f, FLT_MAX);
    cessnafireLOD->addChild(cessnafireL2.get(), 50.0f, 200.0f);
    cessnafireLOD->addChild(cessnafireL3.get(), 0.0f, 50.0f);

    osg::ref_ptr<korreckSoftware::AnimatedSwitch> cessnaAnimatedSwitch = new korreckSoftware::AnimatedSwitch;
    cessnaAnimatedSwitch->addChild(cessnaLOD.get(), true);
    cessnaAnimatedSwitch->addChild(cessnafireLOD.get(), false);

    // add the Animated Switch node to the models transform
    cessnaTransform->addChild(cessnaAnimatedSwitch.get());

    // add the transforms to the root node of the scene
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(cessnaTransform.get());
    
    //create the viewer and then render the root
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    
    return viewer.run();
}
