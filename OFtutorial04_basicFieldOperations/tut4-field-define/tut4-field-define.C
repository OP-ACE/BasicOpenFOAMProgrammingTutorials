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

// This is a function declaration; this method will calculate some scalar value
// given the current time, location in space x, and a reference point x0. The
// function also accepts a scaling factor, scale.
// The actual implementation, or definition, is below.
scalar calculatePressure(scalar t, vector x, vector x0, scalar scale);

int main(int argc, char *argv[])
{
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"

	// These read the fields p and U from the time folders, as specified in system/controlDict (i.e. latestTime, startTime, etc.)
	Info<< "Reading field p\n" << endl;
	volScalarField p // note that pressure is a scalar field
	(
		IOobject
		(
		    "p", // name of the field
		    runTime.timeName(), // name of the current time, i.e. the time folder to read from
		    mesh,
		    IOobject::MUST_READ, // always gets imported, will throw an error if the field is missing
		    IOobject::AUTO_WRITE // will get saved automatically when the controlDict parameters will request it
		),
		mesh // initialises the field to match the size of the mesh with default (0) values
	);

	Info<< "Reading field U\n" << endl;
	volVectorField U // note that velocity is a vector field
	(
		IOobject
		(
		    "U",
		    runTime.timeName(),
		    mesh,
		    IOobject::MUST_READ,
		    IOobject::AUTO_WRITE
		),
		mesh
	);


    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
