import qbs
import qbs.Process
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import "../../../libs/openFrameworksCompiled/project/qtcreator/ofApp.qbs" as ofApp

Project{
    property string of_root: '../../..'

    ofApp {
        name: { return FileInfo.baseName(sourceDirectory) }

        files: [
            "src/colorChannel.cpp",
            "src/colorChannel.h",
            "src/colorChannelAlphabet.cpp",
            "src/colorChannelAlphabet.h",
            "src/colorChannelPassthrough.cpp",
            "src/colorChannelPassthrough.h",
            "src/colorChannelPoem.cpp",
            "src/colorChannelPoem.h",
            "src/colorChannelPoemNoRepetitions.cpp",
            "src/colorChannelPoemNoRepetitions.h",
            "src/editable.cpp",
            "src/editable.h",
            "src/keyboardController.cpp",
            "src/keyboardController.h",
            "src/layer.cpp",
            "src/layer.h",
            "src/layout.cpp",
            "src/layout.h",
            "src/layoutGrid.cpp",
            "src/layoutGrid.h",
            "src/layoutGridDynamic.cpp",
            "src/layoutGridDynamic.h",
            "src/layoutGridHorizontalNoisy.cpp",
            "src/layoutGridHorizontalNoisy.h",
            "src/layoutGridVerticalNoisy.cpp",
            "src/layoutGridVerticalNoisy.h",
            "src/layoutHorizontalStripes.cpp",
            "src/layoutHorizontalStripes.h",
            "src/layoutStarryNight.cpp",
            "src/layoutStarryNight.h",
            "src/layoutTelevision.cpp",
            "src/layoutTelevision.h",
            "src/layoutVerticalStripes.cpp",
            "src/layoutVerticalStripes.h",
            "src/ofPooks.cpp",
            "src/ofPooks.h",
            "src/sample.cpp",
            "src/sample.h",
            "src/sampleFactory.cpp",
            "src/sampleFactory.h",
            "src/sampleText.cpp",
            "src/sampleText.h",
            "src/smoothShader.cpp",
            "src/smoothShader.h",
            "src/twinklingStar.cpp",
            "src/twinklingStar.h",
            "src/main.cpp",
        ]

        of.addons: [
            'ofxGui','ofxNetwork','ofxOpenCv','ofxMidi','ofxSvg','ofxVectorGraphics'
        ]

        // additional flags for the project. the of module sets some
        // flags by default to add the core libraries, search paths...
        // this flags can be augmented through the following properties:
        of.pkgConfigs: []       // list of additional system pkgs to include
        of.includePaths: []     // include search paths
        of.cFlags: []           // flags passed to the c compiler
        of.cxxFlags: []         // flags passed to the c++ compiler
        of.linkerFlags: []      // flags passed to the linker
        of.defines: []          // defines are passed as -D to the compiler
        // and can be checked with #ifdef or #if in the code
        of.frameworks: []       // osx only, additional frameworks to link with the project
        of.staticLibraries: []  // static libraries
        of.dynamicLibraries: [] // dynamic libraries

        // create a console window when the application start
        consoleApplication: true

        // other flags can be set through the cpp module: http://doc.qt.io/qbs/cpp-module.html
        // eg: this will enable ccache when compiling
        //
        // cpp.compilerWrapper: 'ccache'

        Depends{
            name: "cpp"
        }

        // common rules that parse the include search paths, core libraries...
        Depends{
            name: "of"
        }

        // dependency with the OF library
        Depends{
            name: "openFrameworks"
        }
    }

    property bool makeOF: true  // use makfiles to compile the OF library
    // will compile OF only once for all your projects
    // otherwise compiled per project with qbs


    property bool precompileOfMain: false  // precompile ofMain.h
    // faster to recompile when including ofMain.h
    // but might use a lot of space per project

    references: [FileInfo.joinPaths(of_root, "/libs/openFrameworksCompiled/project/qtcreator/openFrameworks.qbs")]
}
