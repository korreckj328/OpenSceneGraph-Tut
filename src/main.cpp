// open scene graph tutorial
// Jeremiah Korreck

#include <osg/MatrixTransform>
#include <osg/LightSource>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

osg::Node* createLightSource(unsigned int num, const osg::Vec3& trans, const osg::Vec4& color) {
    osg::ref_ptr<osg::Light> light = new osg::Light;
    light->setLightNum(num);
    light->setDiffuse(color);
    light->setPosition(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));

    osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource;
    lightSource->setLight(light);
    osg::ref_ptr<osg::MatrixTransform> sourceTrans = new osg::MatrixTransform;
    sourceTrans->setMatrix(osg::Matrix::translate(trans));
    sourceTrans->addChild(lightSource.get());
    return sourceTrans.release();
}


int main() {
    // load the Models
    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("Resources/cessna.osg");
    
    // create transforms for each of the models I want to render in the scene
    osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform;
    
    transform->addChild(model.get());
    
    // add the transforms to the root node of the scene
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(transform.get());
    
    osg::Node * light0 = createLightSource(0, osg::Vec3(-20.0f, 0.0f, 0.0f), osg::Vec4(1.0f,1.0f,0.0f,1.0f));
    osg::Node * light1 = createLightSource(1, osg::Vec3(0.0f, -20.0f, 0.0f), osg::Vec4(0.0f,1.0f,1.0f,1.0f));
    osg::Node * light2 = createLightSource(2, osg::Vec3(0.0f, 20.0f, -20.0f), osg::Vec4(1.0f,0.0f,0.0f,1.0f));

    root->getOrCreateStateSet()->setMode(GL_LIGHT0, osg::StateAttribute::ON);
    root->getOrCreateStateSet()->setMode(GL_LIGHT1, osg::StateAttribute::ON);
    root->getOrCreateStateSet()->setMode(GL_LIGHT2, osg::StateAttribute::ON);

    root->addChild(light0);
    root->addChild(light1);
    root->addChild(light2);
    
    //create the viewer and then render the root
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    
    return viewer.run();
}
