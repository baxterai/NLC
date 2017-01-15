/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation. The use of
 * intermediary programs or interfaces including file i/o is considered
 * remote network interaction. This does not imply such arrangements
 * do not constitute derivative works.
 *
 * BAIPROJECT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Affero General Public License
 * version 3 along with BAIPROJECT.  If not, see <http://www.gnu.org/licenses/>
 * for a copy of the AGPLv3 License.
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCprintDefs.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1h3b 28-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_PRINT_DEFS
#define HEADER_NLC_PRINT_DEFS

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#include "NLCglobalDefs.h"

#define NLC_PROGRAMMING_LANGUAGE_CPP (0)
#define NLC_PROGRAMMING_LANGUAGE_JAVA (1)
#define NLC_PROGRAMMING_LANGUAGE_VISUALBASIC (2)
#define NLC_PROGRAMMING_LANGUAGE_CSHARP (3)
#define NLC_PROGRAMMING_LANGUAGE_PHP (4)
#define NLC_PROGRAMMING_LANGUAGE_PERL (5)
#define NLC_PROGRAMMING_LANGUAGE_PYTHON (6)
#define NLC_PROGRAMMING_LANGUAGE_DEFAULT (NLC_PROGRAMMING_LANGUAGE_CPP)
#define NLC_NUMBER_OF_PROGRAMMING_LANGUAGES (7)	//this needs to be moved to NLCglobalDefs.h

#define NLC_ITEM_TYPE_TEMPVAR_APPENDITION "Temp"
#define NLC_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION "PropertyList"
#define NLC_ITEM_TYPE_CONDITIONLISTVAR_APPENDITION "ConditionList"
#define NLC_ITEM_TYPE_DEFINITIONLISTVAR_APPENDITION "DefinitionList"
#define NLC_ITEM_TYPE_CONDITIONPAIRVAR_APPENDITION "ConditionPair"

//from NLCclassDefinitionClass.h
static string progLangClassTitlePrepend[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"class ", "class ", "class ", "class ", "class ", "class ", "class "};
static string progLangOpenClass[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"{", "{", "{", "{", "{", "{", "{"};
static string progLangCloseClass[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"};", "};", "};", "};", "};", "};", "};"};
static string progLangClassIntro[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"public:", "public:", "public:", "public:", "public:", "public:", "public:"};
static string progLangClassConstructorDestructorAppend[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(void)", "(void)", "(void)", "(void)", "(void)", "(void)", "(void)"};
static string progLangClassDestructorPrepend[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"~", "~", "~", "~", "~", "~", "~"};
static string progLangClassListTypeStart[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"vector<", "vector<", "vector<", "vector<", "vector<", "vector<", "vector<"};
static string progLangClassListTypeEnd[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"> ", "> ", "> ", "> ", "> ", "> ", "> "};
static string progLangClassList2DTypeStart[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"unordered_map<", "unordered_map<", "unordered_map<", "unordered_map<", "unordered_map<", "unordered_map<", "unordered_map<"};
static string progLangClassList2DTypeMiddle[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {", ", ", ", ", ", ", ", ", ", ", ", ", "};
static string progLangClassList2DTypeConditionTypeVar[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"string", "string", "string", "string", "string", "string", "string"};
static string progLangClassPairTypeStart[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"pair<", "pair<", "pair<", "pair<", "pair<", "pair<", "pair<"};
static string progLangClassPairTypeEnd[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {">", ">", ">", ">", ">", ">", ">"};

static string progLangDependenciesStandardLibaries[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"#include <string>\n#include <vector>\n#include <unordered_map>\n#include <utility>\nusing namespace std;\n", "", "", "", "", "", ""};
static string progLangClassConstructorParameters[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"void", "void", "void", "void", "void", "void", "void"};

static string progLangClassNameVariableType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"string ", "string ", "string ", "string ", "string ", "string ", "string "};
static string progLangClassNameVariableName[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"name", "name", "name", "name", "name", "name", "name"};
static string progLangClassNameVariableEquals[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" = ", " = ", " = ", " = ", " = ", " = ", " = "};
static string progLangClassMemberFunctionType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"void ", "void ", "void ", "void ", "void ", "void ", "void "};
static string progLangClassMemberFunctionParameters[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"()", "()", "()", "()", "()", "()", "()"};
static string progLangClassMemberFunctionParametersOpen[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(", "(", "(", "(", "(", "(", "("};
static string progLangClassMemberFunctionParametersClose[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {")", ")", ")", ")", ")", ")", ")"};
static string progLangClassMemberFunctionParametersNext[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {", ", ", ", ", ", ", ", ", ", ", ", ", "};
static string progLangClassInheritanceHeader[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"public ", "public ", "public ", "public ", "public ", "public ", "public "};
static string progLangStringOpenClose[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"\"", "\"", "\"", "\"", "\"", "\"", "\""};

static string progLangDynamicCastStart[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"dynamic_cast<", "dynamic_cast<", "dynamic_cast<", "dynamic_cast<", "dynamic_cast<", "dynamic_cast<", "dynamic_cast<"};
static string progLangDynamicCastEnd[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"*>", "*>", "*>", "*>", "*>", "*>", "*>"};
static string progLangFunctionOwnerClassDelimiter[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"::", "::", "::", "::", "::", "::", "::"};

//from NLCcodeBlockClass.h
static string progLangOpenBlock[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"{", "{", "{", "{", "{", "{", "{"};
static string progLangCloseBlock[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"}", "}", "}", "}", "}", "}", "}"};
static string progLangObjectReferenceDelimiter[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"->", "->", "->", "->", "->", "->", "->"};
static string progLangFunctionReferenceDelimiter[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".", ".", ".", ".", ".", ".", "."};
static string progLangOpenParameterSpace[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(", "(", "(", "(", "(", "(", "("};
static string progLangCloseParameterSpace[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {")", ")", ")", ")", ")", ")", ")"};
static string progLangEndLine[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {";", ";", ";", ";", ";", ";", ";"};
static string progLangFor[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"for", "for", "for", "for", "for", "for", "for"};
static string progLangIf[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"if", "if", "if", "if", "if", "if", "if"};
static string progLangElseIf[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"else if", "else if", "else if", "else if", "else if", "else if", "else if"};
static string progLangElse[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"else", "else", "else", "else", "else", "else", "else"};
static string progLangWhile[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"while", "while", "while", "while", "while", "while", "while"};
static string progLangObjectCheckHasPropertyFunction[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass"};
static string progLangParameterSpaceNextParam[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {",", ",", ",", ",", ",", ",", ","};
static string progLangPointer[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"*", "*", "*", "*", "*", "*", "*"};
static string progLangNot[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"!", "!", "!", "!", "!", "!", "!"};
static string progLangEquals[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" = ", " = ", " = ", " = ", " = ", " = ", " = "};
static string progLangForIterPart1[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(", "(", "(", "(", "(", "(", "("};
static string progLangForIterPart2a[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"::iterator ", "::iterator ", "::iterator ", "::iterator ", "::iterator ", "::iterator ", "::iterator "};
static string progLangForIterPart2c[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" = ", " = ", " = ", " = ", " = ", " = ", " = "};
static string progLangForIterPart3a[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".begin()", ".begin()", ".begin()", ".begin()", ".begin()", ".begin()", ".begin()"};
static string progLangForIterPart3b[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"; ", "; ", "; ", "; ", "; ", "; ", "; "};
static string progLangForIterPart3c[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" < ", " < ", " < ", " < ", " < ", " < ", " < "};
static string progLangForIterPart3cMap[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" != ", " != ", " != ", " != ", " != ", " != ", " != "};
static string progLangForIterPart4a[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".end()", ".end()", ".end()", ".end()", ".end()", ".end()", ".end()"};
static string progLangForIterPart4b[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"; ", "; ", "; ", "; ", "; ", "; ", "; "};
static string progLangForIterPart4c[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"++) ", "++) ", "++)", "++)", "++)", "++)", "++)"};
static string progLangForIterName[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"iter", "iter", "iter", "iter", "iter", "iter", "iter"};
static string progLangForIterConditionObjectReference[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"->second", "->second", "->second", "->second", "->second", "->second", "->second"};

static string progLangForIndexPart1[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(", "(", "(", "(", "(", "(", "("};
static string progLangForIndexPart2[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" = 0; ", " = 0; ", " = 0; ", " = 0; ", " = 0; ", " = 0; ", " = 0; "};
static string progLangForIndexPart3[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" < ", " < ", " < ", " < ", " < ", " < ", " < "};
static string progLangForIndexPart4[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"; ", "; ", "; ", "; ", "; ", "; ", "; "};
static string progLangForIndexPart5[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"++) ", "++) ", "++)", "++)", "++)", "++)", "++)"};


static string progLangNewObject[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"new ", "new ", "new ", "new ", "new ", "new ", "new "};
static string progLangAddProperty[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"push_back", "push_back", "push_back", "push_back", "push_back", "push_back", "push_back"};
static string progLangAddCondition[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"insert", "insert", "insert", "insert", "insert", "insert", "insert"};
static string progLangFindProperty[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"empty()", "empty()", "empty()", "empty()", "empty()", "empty()", "empty()"};
static string progLangFindCondition[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"empty()", "empty()", "empty()", "empty()", "empty()", "empty()", "empty()"};

static string progLangMainEntryPointFunctionName[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"main", "main", "main", "main", "main", "main", "main"};

static string progLangBoolean[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"bool ", "bool ", "bool ", "bool ", "bool ", "bool ", "bool "};
static string progLangFalse[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"false", "false", "false", "false", "false", "false", "false"};
static string progLangTrue[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"true", "true", "true", "true", "true", "true", "true"};
static string progLangInteger[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"int ", "int ", "int ", "int ", "int ", "int ", "int "};
static string progLangForIndex[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"index", "index", "index", "index", "index", "index", "index"};

static string progLangAnd[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"&&", "&&", "&&", "&&", "&&", "&&", "&&"};
static string progLangOr[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"||", "||", "||", "||", "||", "||", "||"};
static string progLangArrayOpen[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"[", "[", "[", "[", "[", "[", "["};
static string progLangArrayClose[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"]", "]", "]", "]", "]", "]", "]"};
static string progLangArrayInitialisationOpen[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"{", "{", "{", "{", "{", "{", "{"};
static string progLangArrayInitialisationClose[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"}", "}", "}", "}", "}", "}", "}"};



static string progLangMathPlus[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" + ", " + ", " + ", " + ", " + ", " + ", " + "};
static string progLangMathMinus[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" - ", " - ", " - ", " - ", " - ", " - ", " - "};
static string progLangMathMultiply[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" * ", " * ", " * ", " * ", " * ", " * ", " * "};
static string progLangMathDivide[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" / ", " / ", " / ", " / ", " / ", " / ", " / "};

#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
static string progLangRemoveProperties[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"clear", "clear", "clear", "clear", "clear", "clear", "clear"};
static string progLangRemoveConditions[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"clear", "clear", "clear", "clear", "clear", "clear", "clear"};
#endif


void printLine(string command, int level, string * code);
string generatePropertyListName(string propertyClassName);
string generateConditionListName(string conditionClassName, string conditionObjectClassName);
string generateConditionPairName(string conditionClassName, string conditionObjectClassName);
string generateCodePropertyListDefinitionText(string propertyClassName, int progLang);
	string generateCodePropertyListDefinitionTypeText(string propertyClassName, int progLang);
string generateCodeConditionListDefinitionText(string conditionClassName, string conditionObjectClassName, int progLang);
	string generateCodeConditionListDefinitionTypeText(string conditionClassName, string conditionObjectClassName, int progLang);


#endif
