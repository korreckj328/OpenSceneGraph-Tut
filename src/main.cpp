// open scene graph tutorial
// Jeremiah Korreck

#include <osg/Camera>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main() {
    // lz.osg is a demo terrain and the glider.osg will be rendered to the hud
    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("Resources/lz.osg");
    osg::ref_ptr<osg::Node> hudModel = osgDB::readNodeFile("Resources/glider.osg");

    // regular camera
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    camera->setRenderOrder(osg::Camera::POST_RENDER);

    camera->setReferenceFrame(osg::Camera::ABSOLUTE_RF);
    camera->setViewMatrixAsLookAt(osg::Vec3(0.0f,-5.0f, 5.0f),
                                    osg::Vec3(),
                                    osg::Vec3(0.0f, 1.0f, 1.0f));
    camera->addChild(hudModel.get());

    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(model.get());
    root->addChild(camera.get());
    //create the viewer and then render the root
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    
    return viewer.run();
}
