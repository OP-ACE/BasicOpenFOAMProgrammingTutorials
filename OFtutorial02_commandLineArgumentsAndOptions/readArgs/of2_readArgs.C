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
    argList::addNote
    (
        "Demonstrates how to handle command line options.\n"
        "\n"
        "输入参数:\n"
        "----------------\n"
        "  someWord - does stuff\n"
        "  someScalar - does more things\n"
    );
    

    // prepare argument list
    argList::noParallel();
    argList::validArgs.append("someWord");
    argList::validArgs.append("someScalar");

    Foam::argList args(argc, argv);
    // read arguments
    const word someWord = args[1];
    // NOTE: the built-in method for converting strings to other data types
    const scalar someScalar = args.argRead<scalar>(2);

    Info << "Got argument word " << someWord << " and scalar " << someScalar << endl;

    return 0;
}


// ************************************************************************* //
