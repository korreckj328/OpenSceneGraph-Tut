// open scene graph tutorial
// Jeremiah Korreck

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main() {
    // set the number of multisamples  2,4, or 6
    osg::DisplaySettings::instance()->setNumMultiSamples(2);

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("Resources/cessna.osg");
    osgViewer::Viewer viewer;
    viewer.setSceneData(model.get());
    return viewer.run();
}
