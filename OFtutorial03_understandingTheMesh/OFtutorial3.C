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
    #include "setRootCase.H"

	// These two create the time system (instance called runTime) and fvMesh (instance called mesh).
    #include "createTime.H"
    #include "createMesh.H"
    // ! ============================================== 1 cerateMesh.H就几句话 和 mesh的五要素
    
    // ! (1.1) cerateMesh.H就几句话
    // 
    //   Foam::Info
    //       << "Create mesh for time = "
    //       << runTime.timeName() << Foam::nl << Foam::endl;
    //   
    // ! (1.2) fvMesh类的构造函数
    //   Foam::fvMesh mesh   //! 构造一个名为 mesh 的 fvMesh对象
    //   (
    //       Foam::IOobject  //! 构造mesh时,用到了临时构造的 IOobject
    //       (
    //           Foam::fvMesh::defaultRegion, 
                 //! 默认情况下，OpenFOAM使用名为"defaultRegion"的区域来表示整个网格
                 //! 静态变量defaultRegion的值的类型为 word, 值可能为 region0
                 //! 即, region0 这个word就是这个IOobject的名字了.
    //           runTime.timeName(), //! 文件名
    //           runTime,            //! 注册表(学生处, IOobject是学生, regIOobject是真正带你去注册的工作人员)
    //           Foam::IOobject::MUST_READ //! 读取选项
    //                                     //! 写入选项和是否注册均采用默认值
    //       )
    //   );
    //
    //   static Foam::word Foam::polyMesh::defaultRegion
    //   polyMesh.C中,显示defaultRegion为polyMesh的一个静态的word类型变量
    //   static word defaultRegion;
    
    // ! (1.3) OpenFoam中的Region
    //   在OpenFOAM中，每个网格都可以分为多个区域。
    //   这些区域可以用来定义不同的物理域，例如流体域、固体域等。
    //   默认情况下，OpenFOAM使用名为"defaultRegion"的区域来表示整个网格。
    //   
    //   在Foam::fvMesh::defaultRegion中，defaultRegion是一个静态变量，
    //   它存储了默认区域的名称。当创建一个新的网格对象时，如果没有指定区域名称，
    //   OpenFOAM将自动使用"defaultRegion"。
    //   这个变量可以在其他代码中使用，例如在创建边界条件或初始化场变量时。
    //   在OpenFOAM中，Foam::fvMesh::defaultRegion是一个表示默认区域（region）的对象。
    //   默认区域是指在网格（mesh）中没有被明确定义的区域。

    //   在OpenFOAM中，网格被划分为不同的区域，每个区域可以有不同的物理属性、边界条件等。
    //   defaultRegion对象用于表示没有被明确指定区域的单元格。
    //   在网格划分过程中，如果某个单元格没有被指定区域，则默认被分配到defaultRegion中。
    //   这样，可以在后续的计算过程中对这些单元格应用默认的物理属性和边界条件。
    //
    // ! (1.4) IOobject类的构造函数(之一): IOobject总是对应个文件
    //   IOobject.H中的部分代码:
    //   Foam::IOobject::IOobject
    //   (
    //       const word& name,               //! IOobject的名字
    //       const fileName& instance,       //! IOobject的文件名(包含路径)
    //       const objectRegistry& registry, //! 对象的注册表
    //       readOption r=NO_READ,           //! 读取选项
    //       writeOption w=NO_WRITE,         //! 写入选项
    //       bool registerObject=true        //! 是否注册?
    //   )
    
    // ! (1.5) mesh的五要素: 
    // 
    // 可以发现其实是创建了一个fvMesh对象，叫做mesh。 
    // 创建这个fvMesh对象的时候程序读取了constant/polyMesh/目录下面的
    // points、faces、owner、neighbour和boundary这5个文件。
    // 这5个文件就是OpenFOAM存储网格的文件。
    // 它们可以用blockMesh生成，也可以用前处理工具从其他格式的网格文件
    // 转换得到(比如用fluentMeshtoFoam、gmshToFoam等等)。 
    // 有了这个对象，我们就可以从这个对象获得网格的所有信息（如cell center的坐标、cell的体积等等),
    // 这些信息在创建fvMesh对象时，其构造函数就以自动计算好了。
    

	// runTime and mesh are instances of objects (or classes).
	// If you are not familiar with what a class or object is, it is HIGHLY RECOMMENDED you visit this
	// website and only come back once you've read everything about classes, inheritance and polymorphism:
	// http://www.cplusplus.com/doc/tutorial/classes/
	// Note how the next lines call functions .timeName(), .C() and .Cf() implemented in the objects.
	// It is also important to realise that mesh.C() and .Cf() return vector fields denoting centres of each
    // cell and internal face.
	// Calling the mesh.C().size() method therefore yields the total size of the mesh.

    //! 2. of中很多对象太大,往往采用指向对象的指针,当一个函数实在要返回一个这个对象时,会解引用这个指针
    //
    //!    比如这里的 mesh.C()
    //     fvMeshGeometry.C中的部分代码:
    //     const Foam::volVectorField& Foam::fvMesh::C() const
    //     {
    //         if (!CPtr_)
    //         {
    //             makeC();
    //         }
    //     
    //         return *CPtr_; //! 解引用
    //     }


	Info << "Hello there, the most recent time folder found is " << runTime.timeName() << nl
		 << "The mesh has " << mesh.C().size() << " cells and " << mesh.Cf().size()
         << " internal faces in it. Wubalubadubdub!" << nl << endl;

    // It's possible to iterate over every cell in a standard C++ for loop
    for (label cellI = 0; cellI < mesh.C().size(); cellI++)
        if (cellI%20 == 0) // only show every twentieth cell not to spam the screen too much
            Info << "Cell " << cellI << " with centre at " << mesh.C()[cellI] << endl;
    Info << endl; // spacer

    // Each cell is constructed of faces - these may either be internal or constitute a
    // boundary, or a patch in OpenFOAM terms; internal faces have an owner cell
    // and a neighbour.
    for (label faceI = 0; faceI < mesh.owner().size(); faceI++)
        if (faceI%40 == 0)
            Info << "Internal face " << faceI << " with centre at " << mesh.Cf()[faceI]
                 << " with owner cell " << mesh.owner()[faceI]
                 << " and neighbour " << mesh.neighbour()[faceI] << endl;
    Info << endl;

    // Boundary conditions may be accessed through the boundaryMesh object.
    // In reality, each boundary face is also included in the constant/polyMesh/faces
    // description. But, in that file, the internal faces are defined first.
    // In addition, the constant/polyMesh/boundary file defines the starting faceI
    // indices from which boundary face definitions start.
    // OpenFOAM also provides a macro definition for for loops over all entries
    // in a field or a list, which saves up on the amount of typing.
    forAll(mesh.boundaryMesh(), patchI)
        Info << "Patch " << patchI << ": " << mesh.boundary()[patchI].name() << " with "
             << mesh.boundary()[patchI].Cf().size() << " faces. Starts at total face "
             << mesh.boundary()[patchI].start() << endl;
    Info << endl;

    // Faces adjacent to boundaries may be accessed as follows.
    // Also, a useful thing to know about a face is its normal vector and face area.
    label patchFaceI(0);
    forAll(mesh.boundaryMesh(), patchI)
        Info << "Patch " << patchI << " has its face " << patchFaceI << " adjacent to cell "
             << mesh.boundary()[patchI].patch().faceCells()[patchFaceI]
             << ". It has normal vector " << mesh.boundary()[patchI].Sf()[patchFaceI]
             << " and surface area " << mag(mesh.boundary()[patchI].Sf()[patchFaceI])
             << endl;
    Info << endl;

    // For internal faces, method .Sf() can be called directly on the mesh instance.
    // Moreover, there is a shorthand method .magSf() which returns the surface area
    // as a scalar.
    // For internal faces, the normal vector points from the owner to the neighbour
    // and the owner has a smaller cellI index than the neighbour. For boundary faces,
    // the normals always point outside of the domain (they have "imaginary" neighbours
    // which do not exist).

    // It is possible to look at the points making up each face in more detail.
    // First, we define a few shorthands by getting references to the respective
    // objects in the mesh. These are defined as constants since we do not aim to
    // alter the mesh in any way.
    // NOTE: these lists refer to the physical definition of the mesh and thus
    // include boundary faces. Use can be made of the mesh.boundary()[patchI].Cf().size()
    // and mesh.boundary()[patchI].start() methods to check whether the face is internal
    // or lies on a boundary.
    const faceList& fcs = mesh.faces();
    const List<point>& pts = mesh.points();
    const List<point>& cents = mesh.faceCentres();

    forAll(fcs,faceI)
        if (faceI%80==0)
        {
            if (faceI<mesh.Cf().size())
                Info << "Internal face ";
            else
            {
                forAll(mesh.boundary(),patchI)
                    if ((mesh.boundary()[patchI].start()<= faceI) &&
                        (faceI < mesh.boundary()[patchI].start()+mesh.boundary()[patchI].Cf().size()))
                    {
                        Info << "Face on patch " << patchI << ", faceI ";
                        break; // exit the forAll loop prematurely
                    }
            }

            Info << faceI << " with centre at " << cents[faceI]
                 << " has " << fcs[faceI].size() << " vertices:";
            forAll(fcs[faceI],vertexI)
                // Note how fcs[faceI] holds the indices of points whose coordinates
                // are stored in the pts list.
                Info << " " << pts[fcs[faceI][vertexI]];
            Info << endl;
        }
    Info << endl;

    // In the original cavity tutorial, on which the test case is based,
    // the frontAndBack boundary is defined as and "empty" type. This is a special
    // BC case which may cause unexpected behaviour as its .Cf() field has size of 0.
    // Type of a patch may be checked to avoid running into this problem if there
    // is a substantial risk that an empty patch type will appear
    label patchID(0);
    const polyPatch& pp = mesh.boundaryMesh()[patchID];
    if (isA<emptyPolyPatch>(pp))
    {
        // patch patchID is of type "empty".
        Info << "You will not see this." << endl;
    }

    // Patches may also be retrieved from the mesh using their name. This could be
    // useful if the user were to refer to a particular patch from a dictionary
    // (like when you do when calculating forces on a particular patch).
    word patchName("movingWall");
    patchID = mesh.boundaryMesh().findPatchID(patchName);
    Info << "Retrieved patch " << patchName << " at index " << patchID << " using its name only." << nl << endl;

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
