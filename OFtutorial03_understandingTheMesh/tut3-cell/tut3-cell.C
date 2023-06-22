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


	// Note how the next lines call functions .timeName(), .C() and .Cf() implemented in the objects.
	// It is also important to realise that mesh.C() and .Cf() return vector fields denoting centres of each
    // cell and internal face.
	// Calling the mesh.C().size() method therefore yields the total size of the mesh.
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

    return 0;
}


// ************************************************************************* //
