// open scene graph tutorial
// Jeremiah Korreck

#include <osg/Geometry>
#include <osg/Geode>
#include <osgUtil/Tessellator>
#include <osg/TriangleFunctor>
#include <osgViewer/Viewer>
#include <iostream>
#include "PrintableVec3.h"

struct FaceCollector
{
    void operator() (const osg::Vec3 v1, const osg::Vec3 v2, 
                     const osg::Vec3 v3, bool treatVertexDataAsTemporary)
    {
        PrintableVec3 pv1 = PrintableVec3(v1.x(), v1.y(), v1.z());
        PrintableVec3 pv2 = PrintableVec3(v2.x(), v2.y(), v2.z());
        PrintableVec3 pv3 = PrintableVec3(v3.x(), v3.y(), v3.z());
        std::cout << "Face vertices: " << pv1 << "; " << pv2 << "; " << pv3 << std::endl;
    }
};

int main() {
    // exploration of osg::Vec3
    osg::Vec3 temp = osg::Vec3(1.0, 2.0, 3.0);
    std::cout << temp.x() << temp.y() << temp.z() << std::endl;


    // create the vertices
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
    vertices->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(1.0f, 0.0f, 1.5f));
    vertices->push_back(osg::Vec3(2.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(2.0f, 0.0f, 1.0f));
    vertices->push_back(osg::Vec3(3.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(3.0f, 0.0f, 1.5f));
    vertices->push_back(osg::Vec3(4.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(4.0f, 0.0f, 1.0f));

    //create the normals
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

    //create geometry

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setVertexArray(vertices.get());
    geom->setNormalArray(normals.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
    geom->addPrimitiveSet(new osg::DrawArrays(GL_QUAD_STRIP, 0, 10));

    osg::TriangleFunctor<FaceCollector> functor;
    geom->accept( functor );

    // add the geometry to a geode and create the scene root
    osg::ref_ptr<osg::Geode> root = new osg::Geode;
    root->addDrawable(geom.get());

    //create the viewer and then render the root
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    
    return viewer.run();
}