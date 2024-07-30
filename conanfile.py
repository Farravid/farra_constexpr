import os

from conan import ConanFile

class CompressorRecipe(ConanFile):
    settings    = "os", "compiler", "build_type", "arch"
    generators  = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("boost/1.85.0") 
        self.requires("benchmark/1.8.4") 
        self.requires("gtest/1.14.0") 

    # def build_requirements(self):

    def layout(self):
        self.folders.build = os.path.join("build", str(self.settings.build_type))
        self.folders.generators = os.path.join("build", str(self.settings.build_type), "generators")

    def validate(self):
        if self.settings.os == "Macos":
            raise ConanInvalidConfiguration("MacOs not supported in Macos")