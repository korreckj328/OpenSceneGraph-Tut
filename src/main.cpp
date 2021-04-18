// open scene graph tutorial
// Jeremiah Korreck

#include <osg/AnimationPath>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
#include "DynamicQuadCallback.h"

osg::AnimationPath* createAnimationPath(float radius, float time) {
    osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
    path->setLoopMode(osg::AnimationPath::LOOP);

    unsigned int numSamples = 32;
    float delta_yaw = 2.0f * osg::PI / ((float)numSamples - 1.0f);
    float delta_time = time / (float)numSamples;
    for (unsigned int i = 0; i < numSamples; ++i) {
        float yaw = delta_yaw * (float)i;
        osg::Vec3 pos(sinf(yaw) * radius, cosf(yaw) * radius, 0.0f);
        osg::Quat rot(-yaw, osg::Z_AXIS);
        path->insert(delta_time * (float)i, osg::AnimationPath::ControlPoint(pos, rot));
    }
    return path.release();
}

int main() {
    // set the number of multisamples  2,4, or 6
    // rpi 4 only accepts 2, 4
    // apple M1 os 11.2.3 supports 6
    // linux intel 4400HD supports 6
    // this seems to indicate that anything recent and modern will support 6
    
    osg::DisplaySettings::instance()->setNumMultiSamples(6);

    osg::ref_ptr<osg::Node> cessna = osgDB::readNodeFile("Resources/cessna.osg.0,0,90.rot");
    osg::ref_ptr<osg::MatrixTransform> root = new osg::MatrixTransform;
    root->addChild(cessna.get());

    osg::ref_ptr<osg::AnimationPathCallback> animationPathCallback = new osg::AnimationPathCallback;
    animationPathCallback->setAnimationPath(createAnimationPath(50.0f, 6.0f));
    root->setUpdateCallback(animationPathCallback.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    viewer.setCameraManipulator(new osgGA::TrackballManipulator);
    while(!viewer.done()) {
        viewer.frame();
    }
    
    return 0;
}
