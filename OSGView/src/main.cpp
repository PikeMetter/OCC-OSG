#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

int main(int argc, char** argv)
{
    osgViewer::Viewer viewer;
    viewer.setSceneData(osgDB::readNodeFile("cow.osg"));
    return viewer.run();
}