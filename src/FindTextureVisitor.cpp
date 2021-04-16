#include "FindTextureVisitor.h"

void FindTextureVisitor::apply(osg::Node& node) {
    replaceTexture(node.getStateSet());
    traverse(node);
}

void FindTextureVisitor::apply(osg::Geode& geode) {
    replaceTexture(geode.getStateSet());
    for (unsigned int i = 0; i < geode.getNumDrawables(); ++i) {
        replaceTexture(geode.getDrawable(i)->getStateSet());
    }
    traverse(geode);
}

void FindTextureVisitor::replaceTexture(osg::StateSet* stateset) {
    if(stateset) {
        osg::Texture* oldTexture = dynamic_cast<osg::Texture*>(stateset->getTextureAttribute(
            0, osg::StateAttribute::TEXTURE));
        if(oldTexture) {
            stateset->setTextureAttribute(0, _texture.get());
        }
    }
}
