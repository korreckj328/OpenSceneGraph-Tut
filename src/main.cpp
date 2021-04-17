// open scene graph tutorial
// Jeremiah Korreck

#include <osg/Geometry>
#include <osg/Geode>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
#include "DynamicQuadCallback.h"

osg::Geometry* createQuad() {
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
    vertices->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
    colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
    colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
    colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));

    osg::ref_ptr<osg::Geometry> quad = new osg::Geometry;
    quad->setVertexArray(vertices.get());
    quad->setNormalArray(normals.get());
    quad->setNormalBinding(osg::Geometry::BIND_OVERALL);
    quad->setColorArray(colors.get());
    quad->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
    quad->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
    return quad.release();
}

int main() {
    // set the number of multisamples  2,4, or 6
    // rpi 4 only accepts 2, 4
    // apple M1 os 11.2.3 supports 6
    // linux intel 4400HD supports 6
    // this seems to indicate that anything recent and modern will support 6
    
    osg::DisplaySettings::instance()->setNumMultiSamples(6);

    osg::Geometry * quad = createQuad();
    quad->setDataVariance(osg::Object::DYNAMIC);
    quad->setUpdateCallback(new DynamicQuadCallback);

    osg::ref_ptr<osg::Geode> root = new osg::Geode;
    root->addDrawable(quad);

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    viewer.setCameraManipulator(new osgGA::TrackballManipulator);
    while(!viewer.done()) {
        viewer.frame();
    }
    
    return 0;
}
