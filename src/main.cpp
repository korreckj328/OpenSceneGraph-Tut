// open scene graph tutorial
// Jeremiah Korreck

#include <osg/Camera>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
#include "FindTextureVisitor.h"

int main() {
    // set the number of multisamples  2,4, or 6
    osg::DisplaySettings::instance()->setNumMultiSamples(2);

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("Resources/lz.osg");
    osg::ref_ptr<osg::Node> subModel = osgDB::readNodeFile("Resources/glider.osg");

    int texWidth = 1024;
    int texHeight = 1024;

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setTextureSize(texWidth, texHeight);
    texture->setInternalFormat(GL_RGBA);
    texture->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
    texture->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);

    FindTextureVisitor ftv(texture.get());

    if(model.valid()) {
        model->accept(ftv);
    }

    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setViewport(0, 0, texWidth, texHeight);
    camera->setClearColor(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera->setRenderOrder(osg::Camera::PRE_RENDER);
    camera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
    camera->attach(osg::Camera::COLOR_BUFFER, texture.get());

    camera->setReferenceFrame(osg::Camera::ABSOLUTE_RF);
    camera->addChild(subModel.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(model.get());
    viewer.setCameraManipulator(new osgGA::TrackballManipulator);

    float delta = 0.1f;
    float bias = 0.0f;
    osg::Vec3 eye(0.0f, -5.0f, 5.0f);
    while(!viewer.done()) {
        if (bias < -1.0f) {
            delta = 0.1f;
        } else if (bias > 1.0f) {
            delta = -0.1f;
        }
        bias += delta;
        camera->setViewMatrixAsLookAt(eye, osg::Vec3(), osg::Vec3(bias, 1.0f, 1.0f));
        viewer.frame();
    }
    return 0;
}
