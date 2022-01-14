# KV Cache
C++ Implementation of a Key-Value cache.

The cache is composed by a primary cache (RAM Cache) and a secondary cache (Storage Cache).

The RAM Cache has a maximum size. When the maximum capacity has been reached, KV Pairs will be evicted based on the selected cache eviction strategies to make place to new elements. Evicted elements will then be moved to the secondary cache.


## Tools and Required Software
Before the project can be used, you should check that all the necessary softwares and tools are installed.
Mandatory are the following:

#### - C++ compiler compatible with C++20

* [gcc 7+](https://gcc.gnu.org/)
	<details>
	<summary>Install command</summary>

	- Debian/Ubuntu:

			sudo apt install build-essential

	- Windows:

			choco install mingw -y

	- MacOS:

			brew install gcc
	</details>

* [clang 6+](https://clang.llvm.org/)
	<details>
	<summary>Install command</summary>

	- Debian/Ubuntu:

			bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"

	- Windows:

		Visual Studio 2019 ships with LLVM (see the Visual Studio section). However, to install LLVM separately:

			choco install llvm -y

		llvm-utils for using external LLVM with Visual Studio generator:

			git clone https://github.com/zufuliu/llvm-utils.git
			cd llvm-utils/VS2017
			.\install.bat

	- MacOS:

			brew install llvm
	</details>

* [Visual Studio 2019 or higher](https://visualstudio.microsoft.com/)
	<details>
	<summary>Install command + Environment setup</summary>

	On Windows, you need to install Visual Studio 2019 because of the SDK and libraries that ship with it.

	Visual Studio IDE - 2019 Community (installs Clang too):

		choco install -y visualstudio2019community --package-parameters "add Microsoft.VisualStudio.Workload.NativeDesktop --includeRecommended --includeOptional --passive --locale en-US"

	Put MSVC compiler, Clang compiler, and vcvarsall.bat on the path:

			choco install vswhere -y
			refreshenv

			# change to x86 for 32bit
			$clpath = vswhere -products * -latest -prerelease -find **/Hostx64/x64/*
			$clangpath = vswhere -products * -latest -prerelease -find **/Llvm/bin/*
			$vcvarsallpath =  vswhere -products * -latest -prerelease -find **/Auxiliary/Build/*

			$path = [System.Environment]::GetEnvironmentVariable("PATH", "User")
			[Environment]::SetEnvironmentVariable("Path", $path + ";$clpath" + ";$clangpath" + ";$vcvarsallpath", "User")
			refreshenv

	</details>

#### - [CMake](https://cmake.org/) at least version 3.15 or higher
<details>
<summary>Install Command</summary>

- Debian/Ubuntu:

		sudo apt-get install cmake

- Windows:

		choco install cmake -y

- MacOS:

		brew install cmake

</details>

#### - [Conan](https://conan.io/) (Also Vcpkg could be used but isn't tested)
<details>
<summary>Install Command</summary>

- Via pip - https://docs.conan.io/en/latest/installation.html#install-with-pip-recommended

		pip install --user conan

Note: Check that pip is installed with python3, otherwise there will be errors when configuring the cmake project

- Windows:

		choco install conan -y

- MacOS:

		brew install conan

</details>
<br/><br/>

C++20 is required since the following features are used in the library or in the client:
- Concepts
- Designated Initializer
- Map.contains
- Using enum construct

To setup the environment on linux ubuntu, there are two scripts that can be used:

1. For installing conan
```Bash
scripts/conan_install.sh
```

2. For Installing the required Cpp tools
```Bash
scripts/required_cpp_tools_install.sh
```

## Optional Tools

This project may also run with other software for static code analysis, documentation and related things. These are optional but they are strongly suggested for development since they improve code quality.

Furthermore, a clang-format file is present the root folder to have a standard formatting for the codebase.

  * [Doxygen](http://doxygen.nl/)
	<details>
	<summary>Install Command</summary>

	- Debian/Ubuntu:

			sudo apt-get install doxygen
			sudo apt-get install graphviz

	- Windows:

			choco install doxygen.install -y
			choco install graphviz -y

	- MacOS:

			brew install doxygen
	 		brew install graphviz

	</details>


  * [ccache](https://ccache.dev/)
	<details>
	<summary>Install Command</summary>

	- Debian/Ubuntu:

			sudo apt-get install ccache

	- Windows:

			choco install ccache -y

	- MacOS:

			brew install ccache

	</details>


  * [Cppcheck](http://cppcheck.sourceforge.net/)
	<details>
	<summary>Install Command</summary>

	- Debian/Ubuntu:

			sudo apt-get install cppcheck

	- Windows:

			choco install cppcheck -y

	- MacOS:

			brew install cppcheck

	</details>


  * [include-what-you-use](https://include-what-you-use.org/)
	<details>
	<summary>Install Command</summary>

	Follow instructions here:
	https://github.com/include-what-you-use/include-what-you-use#how-to-install
	</details>


To install these optional tools environment on linux ubuntu the following script can be run:

For Installing the required Cpp tools
```Bash
scripts/optional_cpp_tools_install.sh
```

## Build
This software uses cmake for generating the build system configuration.

In particular, starting from the root directory, the command to generate the build configuration is:

* <details>
	<summary>Single Configuration Builders (Make, Ninja)</summary>
		
		Single configuration builders won't know about configurations, so cmake has to create different build directories for each one of them.

		- Release
		```Bash
		cmake -S . -B ./build/Release -DCMAKE_BUILD_TYPE:STRING=Release
		```

		- Debug
		```Bash
		cmake -S . -B ./build/Debug -DCMAKE_BUILD_TYPE:STRING=Debug
		```

		- Release with Debug Symbols
		```Bash
		cmake -S . -B ./build/RelWithDebInfo
		```

		- Release with Minimum Size
		```Bash
		cmake -S . -B ./build/MinSizeRel
		```
</details>

* <details>
	<summary>Multiconfiguration Builders (Visual Studio, Ninja Multi-Configuration)</summary>

		Multiconfiguration builders will work directly in a single build folder and the actual configuration has to be specified at compile time.
		```Bash
		cmake -S . -B ./build
		```
</details>

Then, to actually compile the code, you can use directly cmake via the following commands launched from the root directory:

* <details>
	<summary>Single Configuration Builders (Make, Ninja)</summary>
		
	Single configuration builders won't know about configurations, so the build process has to be launched separately from each build folder.

	- Release
		```Bash
		cmake --build ./build/Release
		```

	- Debug
		```Bash
		cmake --build ./build/Debug
		```

	- Release with Debug Symbols
		```Bash
		cmake --build ./build/RelWithDebInfo
		```

	- Release with Minimum Size
		```Bash
		cmake --build ./build/MinSizeRel
		```
	</details>

* <details>
	<summary>Multiconfiguration Builders (Visual Studio, Ninja Multi-Configuration)</summary>

	Multiconfiguration builders will work directly in a single build folder and the actual configuration has to be specified at build time.

	- Release
		```Bash
		cmake --build ./build -- /p:configuration=release
		```

	- Debug
		```Bash
		cmake --build ./build -- /p:configuration=Debug
		```

	- Release with Debug Symbols
		```Bash
		cmake --build ./build -- /p:configuration=RelWithDebInfo
		```

	- Release with Minimum Size
		```Bash
		cmake --build ./build -- /p:configuration=MinSizeRel
		```
	</details>

CMake will automatically pick the predefined C++ compiler. On Linux systems you can change it via the "CXX" system variable.

Automatic Tests can be run from the build directly via CMake. 

* <details>
	<summary>Single Configuration Builders (Make, Ninja)</summary>
		```Bash
		cd build/Debug
		ctest -C Debug
		```
  </details>

* <details>
	<summary>Multiconfiguration Builders (Visual Studio, Ninja Multi-Configuration)</summary>
		```Bash
		cd build
		ctest -C Debug
		```
  </details>

This library uses the [Catch2](https://github.com/catchorg/Catch2) framework for automatic testing.

## Continuous Integration

This project uses [appveyor](https://ci.appveyor.com) for running continuous integration. After every commit, the source code is compiled and tested on the following environments:
- Linux Ubuntu 20.04 with GCC 9.3.0
- Windows Server 2022 with MSBuild VC142

## Static Code Analysis and Sanitizers

The cmake configuration supports various tools to be run automatically post build
- What You See is What You Get
- Clang-Tidy
- Cppcheck

To add them to the build process, uncomment the relative options in the root's cmake file from line 22 to 43.
These tools must be installed on the develompent system and cmake must be able to find them on the current system path.
See the section on optional tools for installation instructions.

# Library Documentation

The library supports doxygen for automatically generating code documentation.
See the section on optional tools for instructions on installing doxigen on your system.
The "doxygen-docs" target will be automatically generated by cmake if the option is uncommented in the root's cmake file on line 33.
For example, if you generate a make configuration, the command to create the documentation after the build has been completed would be
```Bash
cd build/Release
make doxygen-docs
```
If the process is successfull, the produced documentation will be found in the following directory:
```
build/Release/html
```