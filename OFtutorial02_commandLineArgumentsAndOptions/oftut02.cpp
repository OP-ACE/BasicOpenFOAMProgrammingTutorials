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
    // ===================  001 =====================
    //
    // (001) 给 (由本源程序编译生存的)可执行程序(应用) 添加说明
    // 
    // Define the help message for this application
    //
    // (002)
    // 这里没有声明就直接就用argist. 因为fvCFD中包含了这句: #include "argList.H"
    argList::addNote
    (
        "Demonstrates how to handle command line options.\n"
        "\n"
        "输入参数:\n"
        "----------------\n"
        "  someWord - does stuff\n"
        "  someScalar - does more things\n"
    );
    //
    // (003)效果:
    //
    // dyfluid @ testCase $ ofTutorial2
    // 
    // Usage: ofTutorial2 [OPTIONS] <someWord> <someScalar>
    // options:
    //   -case <dir>       specify alternate case directory, default is the cwd
    //   -dict <word>      Path to an additional dictionary (not really used now)
    //   -fileHandler <handler>
    //                     override the fileHandler
    //   -libs <(lib1 .. libN)>
    //                     pre-load libraries
    //   -noFunctionObjects
    //                     do not execute functionObjects
    //   -someInt <label>  Optional integer
    //   -someSwitch       Switches from A to B
    //   -srcDoc           display source code in browser
    //   -doc              display application documentation in browser
    //   -help             print the usage
    // 
    // Demonstrates how to handle command line options.
    // 
    // Input arguments:
    // ----------------
    //   someWord - does stuff
    //   someScalar - does more things
    // 

    

    // ===================  002 =======================
    // prepare argument list
    argList::noParallel();
    argList::validArgs.append("someWord");
    // argList::validArgs返回一个链表LList,见argist.C文件.
    // alidArgs的签名: 
    // SLList<Foam::string>  argList::validArgs;
    // append是链表LList.H的函数,签名为:
    // void append(const T& a)
    argList::validArgs.append("someScalar");


    // prepare options
    argList::addOption // string variable
    (
        "dict",
        "word",
        "Path to an additional dictionary (not really used now)"
    );

    argList::addBoolOption // on/off depending on whether option is given or not
    (
        "someSwitch",
        "Switches from A to B"
    );

    argList::addOption // integer variable
    (
        "someInt",
        "label",
        "Optional integer"
    );

    // ===
    // create argument list
    // This is normally defined inside setRootCase.H
    // #include "setRootCase.H"
    Foam::argList args(argc, argv);

    return 0;
}


// ************************************************************************* //
