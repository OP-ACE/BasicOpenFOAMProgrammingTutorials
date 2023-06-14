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
    
    argList::noParallel();

    argList::validArgs.append("someWord");
    argList::validArgs.append("someScalar");
  

    // prepare options
    // addOption函数
    // static void Foam::argList::addOption(const Foam::word   &opt, 
    //                                      const Foam::string &param = "", 
    //                                      const Foam::string &usage = "")
    // - Add to an option to validOptions with usage information
    //   An option with an empty param is a bool option
    //
    argList::addOption // string variable
    (
        "dict",           //选项的名字
        "某个word类型的值", //选项值的类型, 这个信息 帮助 optionReadIfPresent 把读如的字符串转为正确的类型
        "提示信息:字典路径"
    );

    argList::addBoolOption // on/off depending on whether option is given or not
    (
        "someSwitch",
        "提示:someSwitch, bool类型之默认0,即,false"
        // 如果终端运行程序输入该选项则该选项为true/1,否则为false/0,即:
        // 如果运行 ./readOptions abc 123 -someSwitch 则 someSwitch的值为1
        // 如果运行 ./readOptions abc 123             则 someSwitch的值为0
    );

    argList::addOption // integer variable
    (
        "someInt",
        "某个label类型的值",
        "提示:选项someInt要求输入一个label类型的值"
    );

    // ========================================================  生存 argList对象 argListObj
    // create argument list
    // This is normally defined inside setRootCase.H
    // #include "setRootCase.H"

    Foam::argList argListObj(argc, argv);
    if (!argListObj.checkRootCase())
    {
        Foam::FatalError.exit();
    }



    // 读取必选参数(2个)
    const word someWord = argListObj[1];
    // NOTE: the built-in method for converting strings to other data types
    const scalar someScalar = argListObj.argRead<scalar>(2);
    
    // 输出读取到的必选参数
    Info << "\n--必选项:\n";
    Info << "Got argument word: " << someWord << " and scalar: " << someScalar << endl;

    // 读取可选参数(共3个:字典路径,bool值,整数)
    // default path to some dictionary
    Info << "\n--可选项:\n";
    fileName dictPath("./system/defaultDict");

    // conditional execution based on an option being passed
    if (argListObj.optionFound("dict"))
    {
        argListObj.optionReadIfPresent("dict", dictPath);
        Info << "Got an override flag for dictionary path" << endl;
    }
    Info << "可选项    dict    的值(dict的路径): " << dictPath << endl;

    // switch option
    const bool someConstBool = argListObj.optionFound("someSwitch");
    Info << "可选项 someSwitch 的值(0/1)       : " << someConstBool << endl;

    // numeric value option - same as string variables really
    label someInt(0);
    argListObj.optionReadIfPresent("someInt", someInt);
    Info << "可选项   someInt  的值            : " << someInt << endl;
    
    Info<< "\n----------- End of readOptions ---------\n" << endl;

    return 0;
}


// ************************************************************************* //
