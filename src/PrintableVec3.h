#ifndef PRINTABLE_VEC3_H
#define PRINTABLE_VEC3_H

class PrintableVec3: public osg::Vec3 {
    public:
    PrintableVec3(float x, float y, float z) {
        osg::Vec3(x, y, z);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const PrintableVec3& v) {
        os << v.x() << ' ' << v.y() << ' ' << v.z();
        return os;
    }
};

#endif