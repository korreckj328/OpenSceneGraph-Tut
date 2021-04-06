// open scene graph tutorial
// Jeremiah Korreck

#include <osg/Texture2D>
#include <osg/Geometry>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <iostream>

int main() {
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back(osg::Vec3(-0.5f, 0.0f, -0.5f));
    vertices->push_back(osg::Vec3(0.5f, 0.0f, -0.5f));
    vertices->push_back(osg::Vec3(0.5f, 0.0f, 0.5f));
    vertices->push_back(osg::Vec3(-0.5f, 0.0f, 0.5f));
    
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
    
    osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array;
    texcoords->push_back(osg::Vec2(0.0f, 0.0f));
    texcoords->push_back(osg::Vec2(0.0f, 1.0f));
    texcoords->push_back(osg::Vec2(1.0f, 1.0f));
    texcoords->push_back(osg::Vec2(1.0f, 0.0f));
    
    osg::ref_ptr<osg::Geometry> quad = new osg::Geometry;
    quad->setVertexArray(vertices.get());
    quad->setNormalArray(normals.get());
    quad->setNormalBinding(osg::Geometry::BIND_OVERALL);
    quad->setTexCoordArray(0, texcoords.get());
    quad->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
    
    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    osg::ref_ptr<osg::Image> image = osgDB::readImageFile("Resources/Images/lz.rgb");
    
    if (image == nullptr) {
        std::cout << "image is null" << std::endl;
    } else {
        std::cout << "image was loaded" << std::endl;
    }
    
    texture->setImage(image.get());
    
    osg::ref_ptr<osg::Geode> root = new osg::Geode;
    root->addDrawable(quad.get());
    root->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());
    
    //create the viewer and then render the root
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    
    return viewer.run();
}
