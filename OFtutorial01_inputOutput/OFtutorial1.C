/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2015 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

int main(int argc, char *argv[])
{
    // Initialise OF case
    // 初始化一个OF实例（case）
    #include "setRootCase.H"
    //! setRootCase.H中创建了 args, 所以下面没有定义但是可以直接拿来用, 它是一个 argList 对象
    //! Foam::argList args(argc, argv);
    //! argList类有成员数据: executable_, rootPath_ 等
    //! argList类有成员函数: executable()
    //! //- Name of executable without the path
    //!     inline const word& executable() const;
    //! 返回程序名称(word类型)


    // These two create the time system (instance called runTime) and fvMesh (instance called mesh).
    // 创建 runTime 和 fvMesh
    #include "createTime.H"
    #include "createMesh.H"

    /* 
    * *****************************************************************************
    * 预先存在于testcase中的文件: customProperties
    * 路径: BasicOpenFOAMProgrammingTutorials/OFtutorial01_inputOutput/testCase/constant/customProperties
    * 内容:
    * FoamFile
    * {
    *     version     2.0;
    *     format      ascii;
    *     class       dictionary;
    *     location    "constant";
    *     object      transportProperties;
    * }
    * 
    * someWord myWord;
    * 
    * someScalar 0.01;
    * 
    * someBool on;
    * 
    * someList
    * (
    *     0
    *     1
    *     2
    * );
    * 
    * someHashTable
    * (
    *     key0 (0 0 0)
    *     key1 (1 0 0)
    * );
    * *****************************************************************************
    */

    // Get access to a custom dictionary
    dictionary customDict;
    const word dictName("customProperties");

    // Create and input-output object - this holds the path to the dict and its name
    IOobject dictIO
    (
        dictName, // name of the file
        mesh.time().constant(), // path to where the file is
        mesh, // reference to the mesh needed by the constructor
        IOobject::MUST_READ // indicate that reading this dictionary is compulsory
    );

    Info << "******" << (args.executable()) << "*******";
    // Check the if the dictionary is present and follows the OF format
    if (!dictIO.typeHeaderOk<dictionary>(true))
        FatalErrorIn(args.executable()) << "Cannot open specified refinement dictionary "
            << dictName << exit(FatalError);
    /* 
    ! args.executable(): 用于获取程序名称
    ! 一些无参函数的调用,用意不在执行了什么动作,而是在于返回的结果
    ! args.executable()的用于在于 args.executable_
    ! 通过打印可知 args.executable() 的值为 ofTutorial1

    */

    /*
    ! FatalErrorIn(args.executable()), FatalErrorIn 是个宏.看到括号,不要只想到函数,可以是宏

    * FatalErrorIn的定义:
    * #define FatalErrorIn ( functionName ) ::Foam::FatalError((functionName), __FILE__, __LINE__)

    * 用途:
    * Report an error message using Foam::FatalError.
    * for functionName in file __FILE__ at line __LINE__
    */


    /*
    * 这段代码做了以下几件事:*
    * 1. 调用dictIO.typeHeaderOk<dictionary>(true)检查指定的字典文件: (1)是否存在 且 (2)格式正确
    ! 我.找(必须存在): 按必须存在的要求查找我. 
    ! 这就是OOP的特点:按照一般的函数的习惯,我是主语,我在找东西, 其实我是宾语, 有点到装的意思.
    * 
    typeHeaderOk 是OpenFOAM中用于检查字典文件头部是否正确的模板函数。


    * dictIO.typeHeaderOk<字典类型>(是否必须存在)
    * 
    * 其中:
    * 
    * dictIO: 表示字典IO对象,用于读取字典文件。
    * 
    * 字典类型: 表示要读取的字典的类型,如dictionary、fvMesh等。
    * 
    * 是否必须存在: 是一个布尔值,true表示字典文件必须存在,false表示字典文件可以不存在。
    * 
    * 所以上面代码中的dictIO.typeHeaderOk<dictionary>(true)表示:
    * 
    * 1. 要读取的字典类型是dictionary,即普通的OpenFOAM字典。
    * 
    * 2. 该字典文件必须存在(布尔值为true)。
    * 
    * 3. 如果字典文件存在但是头部格式不正确,或者不存在而布尔值指定必须存在,则typeHeaderOk会返回false。
    * 
    * 4. 只有当字典文件存在且头部格式正确时,typeHeaderOk才会返回true。
    */

    

    // Initialise the dictionary object
    customDict = IOdictionary(dictIO);

    // ---
    // Read various pieces of information from the main part of the dictionary

    // Lookup which does not need to be told what type of variable we're looking for and
    // uses the standard C++ stringstream syntax
    word someWord;
    customDict.lookup("someWord") >> someWord;

    // This template method needs to know the type of the variable and can provide
    // a default value if the entry is not found in the dictionary
    //! scalar 不能像word那样用 >> 赋值.以下代码错误!
    //! scalar someScalar;
    //! customDict.lookupOrDefault<scalar>("someScalar", 1.0) >> someScalar;

    scalar someScalar{ customDict.lookupOrDefault<scalar>("someScalar", 1.0) };

    // A switch is a neat feature allowing boolean values to be read from a dict,
    // it supports the OpenFOAM yes/on/true/1 and no/off/false/0 values automatically.
    bool someBool ( customDict.lookupOrDefault<Switch>("someBool",true) );

    // Lists of values may also be read in the same way
    List<scalar> someList ( customDict.lookup("someList") );

    // This type of container is particularly interesting - it associates entries with
    // given key values (here of word type but can be anything); useful when
    // associating things by indices in a list is less handy
    HashTable<vector,word> someHashTable ( customDict.lookup("someHashTable") );

    // Summarise what's been read and print in the console
    Info << nl << "Read the following:" << nl << nl
         << "someWord " << someWord << nl << nl
         << "someScalar " << someScalar << nl << nl
         << "someList " << someList << nl << nl
         << "someHashTable " << someHashTable << nl << nl
         << "someBool " << someBool << nl << nl
         << endl;

    // ---
    // Create a custom directory and write an output file

    // Create the output path directory
    fileName outputDir = mesh.time().path()/"postProcessing";
    // Creathe the directory
    mkDir(outputDir);

    // File pointer to direct the output to
	autoPtr<OFstream> outputFilePtr;
    // Open the file in the newly created directory
    outputFilePtr.reset(new OFstream(outputDir/"customOutputFile.dat"));
    //! OF的fileName类 重载了 /
    //! Foam::fileName Foam::operator/(const Foam::string &, const Foam::string &)

    // Write stuff
    outputFilePtr() << "# This is a header" << endl;
    outputFilePtr() << "0 1 2 3 4 5" << endl;
    /* 
    ! OF的 autotr重载了()算符,实现的是 指针的解引用
    ! template<class T>
    ! inline T& Foam::autoPtr<T>::operator()()
    ! {
    !     if (!ptr_)
    !     {
    !         FatalErrorInFunction
    !             << "object of type " << typeid(T).name()
    !             << " is not allocated"
    !             << abort(FatalError);
    !     }
    !     
    !     return *ptr_;
    ! }
    */

    // Append to the imported hash table and wirte it too
    someHashTable.insert("newKey", vector(1., 0., 0.));
    outputFilePtr() << someHashTable << endl;

    Info<< "End\n" << endl;
    return 0;

    /* 
    * 生成的文件 customOutputFile.dat 及其写入的内容
    * 路径: /BasicOpenFOAMProgrammingTutorials/OFtutorial01_inputOutput/testCase/postProcessing/customOutputFile.dat
    * 内容: 
    * # This is a header
    * 0 1 2 3 4 5
    * 
    * 3
    * (
    * key0 (0 0 0)
    * newKey (1 0 0)
    * key1 (1 0 0)
    * )
    */
}


// ************************************************************************* //
