// open scene graph tutorial
// Jeremiah Korreck

#include <osg/Program>
#include <osg/LineWidth>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main() {
    // even though this program is for a geometry shader, a vertex shader is always required.
    static const char* vertSource = {"#version 120\n"
                                     "#extension GL_EXT_geometry_shader4 : enable\n"
                                     "void main()\n"
                                     "{gl_Position = ftransform(); }\n"
    };
    
    // geometry shader
    static const char* geomSource = {"#version 120\n"
                                     "#extension GL_EXT_geometry_shader4 : enable\n"
                                     "uniform int segments;\n"
                                     "void main()\n"
                                     "{\n"
                                     "  float delta = 1.0 / float(segments);\n"
                                     "  vec4 v;\n"
                                     "  for (int i=0; i<=segments; ++i)\n"
                                     "  {\n"
                                     "      float t = delta * float(i);\n"
                                     "      float t2 = t * t;\n"
                                     "      float one_minus_t = 1.0 - t;\n"
                                     "      float one_minus_t2 = one_minus_t * one_minus_t;\n"
                                     "      v = gl_PositionIn[0] * one_minus_t2 * one_minus_t + gl_PositionIn[1] * 3.0 * t * one_minus_t2 + gl_PositionIn[2] * 3.0 * t2 * one_minus_t + gl_PositionIn[3] * t2 * t;\n"
                                     "      gl_Position = v;\n"
                                     "      EmitVertex();\n"
                                     "  }\n"
                                     "  EndPrimitive();\n"
                                     "}\n"
    };
    
    //create input primitive
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(1.0f, 1.0f, 1.0f));
    vertices->push_back(osg::Vec3(2.0f, 1.0f, -1.0f));
    vertices->push_back(osg::Vec3(3.0f, 0.0f, 0.0f));
    
    osg::ref_ptr<osg::Geometry> controlPoints = new osg::Geometry;
    controlPoints->setVertexArray(vertices.get());
    controlPoints->addPrimitiveSet(new osg::DrawArrays(GL_LINES_ADJACENCY_EXT, 0, 4));
    
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(controlPoints.get());
    
    // set the parameters of the shader
    int segments = 100;
    
    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(new osg::Shader(osg::Shader::VERTEX, vertSource));
    program->addShader(new osg::Shader(osg::Shader::GEOMETRY, geomSource));
    
    program->setParameter(GL_GEOMETRY_VERTICES_OUT_EXT, segments + 1);
    program->setParameter(GL_GEOMETRY_INPUT_TYPE_EXT, GL_LINES_ADJACENCY_EXT);
    program->setParameter(GL_GEOMETRY_OUTPUT_TYPE_EXT, GL_LINE_STRIP);
    
    // set the line width,  default is 1.0
    osg::ref_ptr<osg::LineWidth> lineWidth = new osg::LineWidth;
    lineWidth->setWidth(2.0f);
    
    // set the rendering attributes to the state set and add uniform for the shader
    osg::StateSet *stateset = geode->getOrCreateStateSet();
    stateset->setAttributeAndModes(program.get());
    stateset->setAttribute(lineWidth.get());
    stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    stateset->addUniform(new osg::Uniform("segments", segments));
    
    //create the viewer and then render the root
    osgViewer::Viewer viewer;
    viewer.setSceneData(geode.get());
    
    return viewer.run();
}
