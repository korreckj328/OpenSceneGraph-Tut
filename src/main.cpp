// open scene graph tutorial
// Jeremiah Korreck

#include <osg/Geometry>
#include <osg/Geode>
#include <osgUtil/Tessellator>
#include <osgViewer/Viewer>

int main() {
    // create the vertices
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(2.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(2.0f, 0.0f, 1.0f));
    vertices->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
    vertices->push_back(osg::Vec3(1.0f, 0.0f, 2.0f));
    vertices->push_back(osg::Vec3(2.0f, 0.0f, 2.0f));
    vertices->push_back(osg::Vec3(2.0f, 0.0f, 3.0f));
    vertices->push_back(osg::Vec3(0.0f, 0.0f, 3.0f));

    //create the normals
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

    //create geometry

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setVertexArray(vertices.get());
    geom->setNormalArray(normals.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
    geom->addPrimitiveSet(new osg::DrawArrays(GL_POLYGON, 0, 8));

    // tessellate the geometry
    osgUtil::Tessellator tessellator;
    tessellator.retessellatePolygons(*geom);
    
    // add the geometry to a geode and create the scene root
    osg::ref_ptr<osg::Geode> root = new osg::Geode;
    root->addDrawable(geom.get());

    //create the viewer and then render the root
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    
    return viewer.run();
}