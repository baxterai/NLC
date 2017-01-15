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
 * File Name: NLCprintCodeBlocks.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1k5b 13-October-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCprintCodeBlocks.h"
#include "NLCprintDefs.h"
#include "GIAtranslatorDefs.h"	//required for ENTITY_COORDINATINGCONJUNCTION_ARRAY_INDEX_AND/ENTITY_COORDINATINGCONJUNCTION_ARRAY_INDEX_OR

bool printCodeBlocks(NLCcodeblock * firstCodeBlockInLevel, vector<NLCclassDefinition *> * classDefinitionList, int progLang, string * code, int level)
{
	NLCcodeblock * currentCodeBlockInLevel = firstCodeBlockInLevel;
	while(currentCodeBlockInLevel->next != NULL)
	{
		NLCitem * param1 = currentCodeBlockInLevel->parameters.at(0);
		string contextParam1 = generateStringFromContextVector(&(param1->context), progLang);

		//for logical operations only (NLC_CODEBLOCK_TYPE_IF_HAS_PROPERTY/NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION/NLC_CODEBLOCK_TYPE_WHILE_HAS_PROPERTY/NLC_CODEBLOCK_TYPE_WHILE_HAS_CONDITION);
		string negativeModifierString = "";
		if(param1->negative)
		{
			negativeModifierString = "";
		}
		else
		{
			negativeModifierString = progLangNot[progLang];
		}

		if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION" << endl;
			#endif

			string functionArguments = "";
			generateFunctionExecutionArgumentsWithActionConceptInheritanceString(classDefinitionList, &(currentCodeBlockInLevel->parameters), &functionArguments, progLang);

			string codeBlockText = contextParam1 + param1->functionName + progLangOpenParameterSpace[progLang] + functionArguments + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1.param1(context.param2); 	[param1 = function, context1 = subject, param2 = object]

			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);

			string codeBlockTextCreate = generateTempVariableDeclaration(param2, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + param2->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			printLine(codeBlockTextCreate, level, code);
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + param2->className + NLC_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.push_back(param2);
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_NEW_ENTITY_TO_LOCAL_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_NEW_ENTITY_TO_LOCAL_LIST" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);

			string codeBlockTextCreate = generateTempVariableDeclaration(param2, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + param2->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			printLine(codeBlockTextCreate, level, code);
			string codeBlockText = generateEntityLocalListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instanceList.push_back(param2);
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_NEW_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_NEW_CONDITION" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string codeBlockTextCreate = generateTempVariableDeclaration(param3, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + param3->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			printLine(codeBlockTextCreate, level, code);
			#ifndef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
			string codeBlockTextCreate2 = generateTempVariableDeclaration(param2, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + param2->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			printLine(codeBlockTextCreate2, level, code);
			#endif
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->className, param3->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + generateCodeConditionPairText(param2->name, param2->className, param2->instanceName, param3->className, param3->instanceName, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.insert(pair<param2className, param3className*>(param2, param3));
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_PROPERTY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_PROPERTY" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);

			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + param2->className + NLC_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.push_back(param2);
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_LOCAL_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_LOCAL_LIST" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);

			string codeBlockText = generateEntityLocalListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instanceList.push_back(param2);
			
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_CONDITION" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			#ifndef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
			string codeBlockTextCreate2 = generateTempVariableDeclaration(param2, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + param2->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			printLine(codeBlockTextCreate2, level, code);
			#endif
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->className,  param3->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + generateCodeConditionPairText(param2->name, param2->className, param2->instanceName, param3->className, param3->instanceName, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.insert(pair<param2className, param3className*>(param2, param3));
			printLine(codeBlockText, level, code);

		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST" << endl;
			#endif
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextParam1 + generatePropertyListName(param1->className) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + contextParam1 + generatePropertyListName(param1->className) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = generateTempVariableDeclaration(param1, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMPVAR_APPENDITION
			printLine(tempVarDeclarationText, (level+1), code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_LOCAL_LIST)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_LOCAL_LIST" << endl;
			#endif
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + generateEntityLocalListName(param1) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + generateEntityLocalListName(param1) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = generateTempVariableDeclaration(param1, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMPVAR_APPENDITION
			printLine(tempVarDeclarationText, (level+1), code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_CONDITION_LIST)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_CONDITION_LIST" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeConditionListDefinitionTypeText(param1->className, param2->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextParam1 + generateConditionListName(param1->className, param2->className) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3cMap[progLang] + contextParam1 + generateConditionListName(param1->className, param2->className) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = generateTempVariableDeclaration(param2, progLang) + progLangEquals[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterConditionObjectReference[progLang] + progLangEndLine[progLang];
			printLine(tempVarDeclarationText, (level+1), code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_INTEGER)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_INTEGER" << endl;
			#endif
			string indexName = progLangForIndex[progLang] + iterIndexString;
			string codeBlockText = progLangFor[progLang] + progLangForIndexPart1[progLang] + progLangInteger[progLang] + indexName + progLangForIndexPart2[progLang] + indexName + progLangForIndexPart3[progLang] + param1->name + progLangForIndexPart4[progLang] + indexName + progLangForIndexPart5[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_NEW_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_NEW_FUNCTION" << endl;
			#endif
			string functionArguments = "";
			#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
			generateLocalFunctionArgumentsBasedOnImplicitDeclarationsString(&(currentCodeBlockInLevel->parameters), &functionArguments, progLang);
			#endif
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
			generateFunctionArgumentsBasedOnActionAndActionObjectVars(&(currentCodeBlockInLevel->parameters), &functionArguments, progLang);
			#endif
			string functionOwnerContext = generateFunctionOwnerContext(&(currentCodeBlockInLevel->parameters), progLang);
			string codeBlockText = functionOwnerContext + param1->functionName + progLangOpenParameterSpace[progLang] + functionArguments + progLangCloseParameterSpace[progLang];	//main(){
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);

			string codeBlockTextDeclareAndInitialiseVariable = generateTempVariableDeclaration(param1, progLang) + progLangEquals[progLang] + param2->instanceName + progLangEndLine[progLang];
			printLine(codeBlockTextDeclareAndInitialiseVariable, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE" << endl;
			#endif
			string codeBlockTextDeclareNewVariable = generateTempVariableDeclaration(param1, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + param1->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			printLine(codeBlockTextDeclareNewVariable, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_LOCAL_LIST_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_LOCAL_LIST_VARIABLE" << endl;
			#endif
			string localListDeclarationText = generateCodeEntityListDefinitionTypeText(param1->className, progLang) + generateEntityLocalListName(param1) + progLangEndLine[progLang];	//vector<param1Class*> param1instanceList;
			printLine(localListDeclarationText, level, code);
		}
		#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
		#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_LOGICAL_CONJUNCTION_OF_BOOLS)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_LOGICAL_CONJUNCTION_OF_BOOLS" << endl;
			#endif
			string codeBlockText =  progLangIf[progLang] + progLangOpenParameterSpace[progLang] + generateLogicalConjunctionOfBoolsText(&(currentCodeBlockInLevel->parameters), progLang) + progLangCloseParameterSpace[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ELSE_IF_LOGICAL_CONJUNCTION_OF_BOOLS)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ELSE_IF_LOGICAL_CONJUNCTION_OF_BOOLS" << endl;
			#endif
			string codeBlockText = progLangElseIf[progLang] + progLangOpenParameterSpace[progLang] + generateLogicalConjunctionOfBoolsText(&(currentCodeBlockInLevel->parameters), progLang) + progLangCloseParameterSpace[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_WHILE_LOGICAL_CONJUNCTION_OF_BOOLS)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_WHILE_LOGICAL_CONJUNCTION_OF_BOOLS" << endl;
			#endif
			string codeBlockText = progLangWhile[progLang] + progLangOpenParameterSpace[progLang] + generateLogicalConjunctionOfBoolsText(&(currentCodeBlockInLevel->parameters), progLang) + progLangCloseParameterSpace[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_ARRAY_INITIALISE_TRUE)
		{//CHECK THIS: not used
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_ARRAY_INITIALISE_TRUE" << endl;
			#endif
			string arraySizeString = convertIntToString(NLC_MAXIMUM_NUMBER_OF_CONJUNCTIONS_IN_SENTENCE);	//make this dynamic
			string codeBlockText = progLangBoolean[progLang] + param1->name + progLangArrayOpen[progLang] + arraySizeString + progLangArrayClose[progLang] + progLangEquals[progLang] + progLangArrayInitialisationOpen[progLang] + progLangTrue[progLang] + progLangArrayInitialisationClose[progLang] + progLangEndLine[progLang];
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_ARRAY_INITIALISE_FALSE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_ARRAY_INITIALISE_FALSE" << endl;
			#endif
			string arraySizeString = convertIntToString(NLC_MAXIMUM_NUMBER_OF_CONJUNCTIONS_IN_SENTENCE);	//make this dynamic
			string codeBlockText = progLangBoolean[progLang] + param1->name + progLangArrayOpen[progLang] + arraySizeString + progLangArrayClose[progLang] + progLangEquals[progLang] + progLangArrayInitialisationOpen[progLang] + progLangFalse[progLang] + progLangArrayInitialisationClose[progLang] + progLangEndLine[progLang];
			printLine(codeBlockText, level, code);
		}
		#else
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_PROPERTY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_PROPERTY" << endl;
			#endif

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + contextParam1 + generatePropertyListName(param1->className) + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//if(!(context1->param1PropertyList.empty())){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION" << endl;
			#endif

			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + contextParam1 + generateConditionListName(param1->className, param2->className) + progLangObjectReferenceDelimiter2[progLang] + progLangHasCondition[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//if(!(context1->param1param2ConditionList.empty())){
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_WHILE_HAS_PROPERTY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_WHILE_HAS_PROPERTY" << endl;
			#endif

			string codeBlockText = progLangWhile[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + contextParam1 + generatePropertyListName(param1->className) + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//while(!(context1->param1PropertyList.empty())){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_WHILE_HAS_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_WHILE_HAS_CONDITION" << endl;
			#endif

			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);

			string codeBlockText = progLangWhile[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + contextParam1 + generateConditionListName(param1->className, param2->className) + progLangObjectReferenceDelimiter2[progLang] + progLangHasCondition[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//while(!(context1->param1param2ConditionList.empty())){
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		#endif
		#endif
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ELSE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ELSE" << endl;
			#endif
			string codeBlockText = progLangElse[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_WHILE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_WHILE" << endl;
			#endif
			string codeBlockText = progLangWhile[progLang] + progLangOpenParameterSpace[progLang] + param1->name + progLangCloseParameterSpace[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_VARIABLE_INITIALISE_TRUE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_VARIABLE_INITIALISE_TRUE" << endl;
			#endif
			string codeBlockText = progLangBoolean[progLang] + param1->name + progLangEquals[progLang] + progLangTrue[progLang] + progLangEndLine[progLang];
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_VARIABLE_INITIALISE_FALSE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_VARIABLE_INITIALISE_FALSE" << endl;
			#endif
			string codeBlockText = progLangBoolean[progLang] + param1->name + progLangEquals[progLang] + progLangFalse[progLang] + progLangEndLine[progLang];
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_BOOL_VARIABLE_TRUE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_SET_BOOL_VARIABLE_TRUE" << endl;
			#endif
			string codeBlockText = param1->name + progLangEquals[progLang] + progLangTrue[progLang] + progLangEndLine[progLang];
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_BOOL_VARIABLE_FALSE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_SET_BOOL_VARIABLE_FALSE" << endl;
			#endif
			string codeBlockText = param1->name + progLangEquals[progLang] + progLangFalse[progLang] + progLangEndLine[progLang];
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DEBUG)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DEBUG" << endl;
			#endif
			string codeBlockText = param1->name;
			printLine(codeBlockText, level, code);
		}
		#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REMOVE_PROPERTIES)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_REMOVE_PROPERTIES" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);

			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + param2->className + NLC_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveProperties[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.clear();
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REMOVE_ENTITIES_FROM_LOCAL_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_REMOVE_ENTITIES_FROM_LOCAL_LIST" << endl;
			#endif

			string codeBlockText = generateEntityLocalListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveProperties[progLang] + progLangEndLine[progLang];		//param1instanceList.clear();
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REMOVE_CONDITIONS)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_REMOVE_CONDITIONS" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->className,  param3->className) + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveConditions[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.clear();
			printLine(codeBlockText, level, code);

		}
		#endif
		#ifdef NLC_PREPROCESSOR_MATH
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_MATHTEXT_LINE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_MATHTEXT_LINE" << endl;
			#endif
			string codeBlockText = param1->name + progLangEndLine[progLang];
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_MATHTEXT_WITH_LOGICAL_OPERATOR)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_MATHTEXT_WITH_LOGICAL_OPERATOR" << endl;
			#endif
			string codeBlockText = param1->name;
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}		
		#endif
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_INT_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_INT_VARIABLE" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string codeBlockText = progLangInteger[progLang] + param1->name + progLangEquals[progLang] + param2->name + progLangEndLine[progLang];
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_INCREMENT_INT_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_INCREMENT_INT_VARIABLE" << endl;
			#endif
			string codeBlockText = param1->name + progLangEquals[progLang] + param1->name + progLangMathPlus[progLang] + string("1") + progLangEndLine[progLang];
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_COMMENT_SINGLE_LINE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_COMMENT_SINGLE_LINE" << endl;
			#endif
			string codeBlockText = progLangOpenSingleLineComment[progLang] + param1->name;
			printLine(codeBlockText, level, code);
		}
		#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REASSIGN_ITER)
		{
			string iterIndexString = convertIntToString(level-1);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_REASSIGN_ITER" << endl;
			#endif
			string tempVarDeclarationText = param1->instanceName + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];
			printLine(tempVarDeclarationText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;
	
			string localListDeclarationText = generateCodeEntityListDefinitionTypeText(param1->className, progLang) + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangEndLine[progLang];	//vector<param1Class*> param1instanceCategoryList;
			printLine(localListDeclarationText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string genericListAppendName = param3->name;

			string codeBlockText = generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instanceCategoryList.push_back(param2);
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;
			
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = generateTempVariableDeclaration(param1, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMPVAR_APPENDITION
			printLine(tempVarDeclarationText, (level+1), code);
		}
		#ifdef NLC_CATEGORIES_TEST_PLURALITY
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_GENERIC_ENTITY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_GENERIC_ENTITY" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//if(!(param1instanceCategoryList.empty())){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_PRINT_WARNING)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_PRINT_WARNING" << endl;
			#endif
			string codeBlockText = progLangPrintTextOpen[progLang] + param1->name + progLangPrintTextClose[progLang]  + progLangEndLine[progLang];	//cout << "warning" << endl;
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_NUM_GENERIC_ENTITY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_NUM_GENERIC_ENTITY" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string valueString = param3->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangGreaterThan[progLang] + valueString + progLangCloseParameterSpace[progLang];		//if(param1instanceCategoryList.size() > 0){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		#endif
		#ifdef NLC_USE_ADVANCED_REFERENCING
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_GET_BACK_GENERIC_ENTITY_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_GET_BACK_GENERIC_ENTITY_LIST" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			string tempVarDeclarationText = generateTempVariableDeclaration(param1, progLang) + progLangEquals[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangEndLine[progLang];

			printLine(tempVarDeclarationText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_EXECUTE_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_EXECUTE_FUNCTION" << endl;
			#endif

			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string genericListAppendName = param3->name;
			
			string codeBlockText = "";
			string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + STRING_SPACE + param2->className + progLangTemplateUsePart2[progLang] + STRING_SPACE; 	//<param2> 
			codeBlockText = codeBlockText + NLC_USE_ADVANCED_REFERENCING_SINGULAR_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addToCategoryIfPassSingularDefinitePluralityTests<param1class, param2class> (param1instanceCategoryList, param2instanceName);				
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_NEW_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_NEW_FUNCTION" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string genericListAppendName = param3->name;
			
			string templateName1 = "E1";
			string templateName2 = "E2";
			string codeBlockTextTemplateHeader = progLangTemplateHeaderPart1[progLang] + progLangTemplateHeaderClassType[progLang] + templateName1 + progLangTemplateUseClassSeparator[progLang] + STRING_SPACE + progLangTemplateHeaderClassType[progLang] + templateName2 + progLangTemplateHeaderPart2[progLang];  //template <class E1, class E2>
			string codeBlockTextFunctionHeader = progLangClassMemberFunctionType[progLang] + NLC_USE_ADVANCED_REFERENCING_SINGULAR_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeEntityListDefinitionTypeText(templateName1, progLang) + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangClassMemberFunctionParametersNext[progLang] + templateName2 + progLangPointer[progLang] + STRING_SPACE + param2->instanceName + progLangCloseParameterSpace[progLang];	//void addToCategoryIfPassSingularDefinitePluralityTests(vector<E1*> param1instanceCategoryList, E2* param2instanceName)

			string codeBlockText6 = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//if(!(param2->lastSentenceReferenced.empty())){
			
			string codeBlockText4 = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//if(!(param1instanceCategoryList.empty())){
				//NB this code could be generated using existing codeblock (NLC_CODEBLOCK_TYPE_IF_HAS_GENERIC_ENTITY)
			string codeBlockText5 = progLangElse[progLang];
			 
			#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
			string codeBlockText1 = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackGetLast[progLang] + progLangGreaterThan[progLang] + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangCloseParameterSpace[progLang] + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackGetLast[progLang] + progLangCloseParameterSpace[progLang];		//if(param2->lastSentenceReferenced.top() > param1instanceCategoryList.back()->lastSentenceReferenced.top())
			string codeBlockText2 = progLangElseIf[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackGetLast[progLang] + progLangEqualsTest[progLang] + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangCloseParameterSpace[progLang] + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackGetLast[progLang] + progLangCloseParameterSpace[progLang];		//if(param2->lastSentenceReferenced.top() == param1instanceCategoryList.back()->lastSentenceReferenced.top())
			#else
			string codeBlockText1 = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangGreaterThan[progLang] + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangCloseParameterSpace[progLang] + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangCloseParameterSpace[progLang];		//if(param2->lastSentenceReferenced > param1instanceCategoryList.back()->lastSentenceReferenced)
			string codeBlockText2 = progLangElseIf[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangEqualsTest[progLang] + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangCloseParameterSpace[progLang] + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangCloseParameterSpace[progLang];		//if(param2->lastSentenceReferenced == param1instanceCategoryList.back()->lastSentenceReferenced)			
			#endif
			string codeBlockText3 = progLangElse[progLang];
			
			string removeCategoryListItemsText = generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveProperties[progLang] + progLangEndLine[progLang];		//param1instanceCategoryList.clear();
				//NB this code could be moved to a new codeblock (NLC_CODEBLOCK_TYPE_REMOVE_PROPERTIES_GENERIC_LIST)
				
			string addCategoryItemText = generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instanceCategoryList.push_back(param2);
				//NB this code could be generated using existing codeblock (NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST)

			#ifdef NLC_USE_ADVANCED_REFERENCING_DO_NOT_ADD_DUPLICATES
			string negativeModifierStringFind = progLangNot[progLang];	//if not found (negative find)
			string findCategoryItemText = progLangFindPart1[progLang] + negativeModifierStringFind + progLangFindPart2[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangFindPart3[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangFindPart4[progLang] + param2->instanceName + progLangFindPart5[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangFindPart6[progLang];	//if(!find(param1instanceCategoryList.begin(), param1instanceCategoryList.end(), param2) != param1instanceCategoryList.end()) 
				//NB this code could be moved to a new codeblock  (NLC_CODEBLOCK_TYPE_FIND_PROPERTY_IN_GENERIC_LIST)
			#endif
			
			int q = 0;
			printLine("", level, code);
			printLine(codeBlockTextTemplateHeader, level, code);
			printLine(codeBlockTextFunctionHeader, level, code);
			printLine(progLangOpenBlock[progLang], level, code);

				#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
				q++;
				printLine(codeBlockText6, level+q, code);
				printLine(progLangOpenBlock[progLang], level+q, code);
				#endif
							
					q++;
					printLine(codeBlockText4, level+q, code);
					printLine(progLangOpenBlock[progLang], level+q, code);
					printLine(addCategoryItemText, level+q+1, code);
					printLine(progLangCloseBlock[progLang], level+q, code);
					printLine(codeBlockText5, level+q, code);
					printLine(progLangOpenBlock[progLang], level+q, code);

						q++;
						printLine(codeBlockText1, level+q, code);
						printLine(progLangOpenBlock[progLang], level+q, code);
						printLine(removeCategoryListItemsText, level+q+1, code);
						printLine(addCategoryItemText, level+q+1, code);
						printLine(progLangCloseBlock[progLang], level+q, code);

						printLine(codeBlockText2, level+q, code);
						printLine(progLangOpenBlock[progLang], level+q, code);
						#ifdef NLC_USE_ADVANCED_REFERENCING_DO_NOT_ADD_DUPLICATES
						printLine(findCategoryItemText, level+q+1, code);
						printLine(progLangOpenBlock[progLang], level+q+1, code);
						printLine(addCategoryItemText, level+q+2, code);
						printLine(progLangCloseBlock[progLang], level+q+1, code);
						#else
						printLine(addCategoryItemText, level+q+1, code);
						#endif
						printLine(progLangCloseBlock[progLang], level+q, code);

						printLine(codeBlockText3, level+q, code);
						printLine(progLangOpenBlock[progLang], level+q, code);
						printLine(progLangCloseBlock[progLang], level+q, code);		

					q--;
					printLine(progLangCloseBlock[progLang], level+q, code);

					/*
					if(!(param1instanceCategoryList.empty()))
					{
						param1instanceCategoryList.push_back(param2);
					}
					else
					{	
						if(param1->lastSentenceReferenced > param1instanceCategoryList.back()->lastSentenceReferenced)
						{
							param1instanceCategoryList.clear();
							param1instanceCategoryList.push_back(param2);
						}
						else if(param1->lastSentenceReferenced == param1instanceCategoryList.back()->lastSentenceReferenced)
						{
							if(!find(param1instanceCategoryList.begin(), param1instanceCategoryList.end(), param2) != param1instanceCategoryList.end()) 
							{
								param1instanceCategoryList.push_back(param2);
							}
						}
						else
						{	

						}
					}
					*/
					
				#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
				q--;							
				printLine(progLangCloseBlock[progLang], level+q, code);
				#endif	
			
			q--;							
			printLine(progLangCloseBlock[progLang], level+q, code);						
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_EXECUTE_FUNCTION)
		{//finish coding this
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_EXECUTE_FUNCTION" << endl;
			#endif

			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string genericListAppendName = param3->name;
			
			string codeBlockText = "";
			string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + STRING_SPACE + param2->className + progLangTemplateUsePart2[progLang] + STRING_SPACE; 	//<param2> 
			codeBlockText = codeBlockText + NLC_USE_ADVANCED_REFERENCING_PLURAL_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addToCategoryIfPassSingularDefinitePluralityTests<param1class, param2class> (param1instanceCategoryList, param2instanceName);				
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_NEW_FUNCTION)
		{//finish coding this
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_NEW_FUNCTION" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string genericListAppendName = param3->name;
			
			string templateName1 = "E1";
			string templateName2 = "E2";
			string codeBlockTextTemplateHeader = progLangTemplateHeaderPart1[progLang] + progLangTemplateHeaderClassType[progLang] + templateName1 + progLangTemplateUseClassSeparator[progLang] + STRING_SPACE + progLangTemplateHeaderClassType[progLang] + templateName2 + progLangTemplateHeaderPart2[progLang];  //template <class E1, class E2>
			string codeBlockTextFunctionHeader = progLangClassMemberFunctionType[progLang] + NLC_USE_ADVANCED_REFERENCING_PLURAL_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeEntityListDefinitionTypeText(templateName1, progLang) + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangClassMemberFunctionParametersNext[progLang] + templateName2 + progLangPointer[progLang] + STRING_SPACE + param2->instanceName + progLangCloseParameterSpace[progLang];	//void addToCategoryIfPassSingularDefinitePluralityTests(vector<E1*> param1instanceCategoryList, E2* param2instanceName)

			string codeBlockText6 = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//if(!(param2->lastSentenceReferenced.empty())){

			string addCategoryItemText = generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instanceCategoryList.push_back(param2);
				//NB this code could be generated using existing codeblock (NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST)

			#ifdef NLC_USE_ADVANCED_REFERENCING_DO_NOT_ADD_DUPLICATES
			string negativeModifierStringFind = progLangNot[progLang];	//if not found (negative find)
			string findCategoryItemText = progLangFindPart1[progLang] + negativeModifierStringFind + progLangFindPart2[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangFindPart3[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangFindPart4[progLang] + param2->instanceName + progLangFindPart5[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangFindPart6[progLang];	//if(!find(param1instanceCategoryList.begin(), param1instanceCategoryList.end(), param2) != param1instanceCategoryList.end()) 
				//NB this code could be moved to a new codeblock  (NLC_CODEBLOCK_TYPE_FIND_PROPERTY_IN_GENERIC_LIST)
			#endif

			int q = 0;
			printLine("", level+q, code);
			printLine(codeBlockTextTemplateHeader, level+q, code);
			printLine(codeBlockTextFunctionHeader, level+q, code);
			printLine(progLangOpenBlock[progLang], level+q, code);
				
				/*
				#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
				q++;
				printLine(codeBlockText6, level+q, code);
				printLine(progLangOpenBlock[progLang], level+q, code);
				#endif
				*/
				
					q++;		
					#ifdef NLC_USE_ADVANCED_REFERENCING_DO_NOT_ADD_DUPLICATES
					printLine(findCategoryItemText, level+q, code);
					printLine(progLangOpenBlock[progLang], level+q, code);
					printLine(addCategoryItemText, level+q+1, code);
					printLine(progLangCloseBlock[progLang], level+q, code);
					#else
					printLine(addCategoryItemText, level+q, code);
					#endif	

					/*
					if(!find(param1instanceCategoryList.begin(), param1instanceCategoryList.end(), param2) != param1instanceCategoryList.end()) 
					{
						param1instanceCategoryList.push_back(param2);
					}
					*/
				
				/*
				#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
				q--;							
				printLine(progLangCloseBlock[progLang], level+q, code);	
				#endif
				*/
				
			q--;
			printLine(progLangCloseBlock[progLang], level+q, code);	
		}		
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_UPDATE_LAST_SENTENCE_REFERENCED)	//execute for all new/undeclared/indefinite entities and accessed category items
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_UPDATE_LAST_SENTENCE_REFERENCED" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string lastSentenceReferenced = param2->name;

			#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
			string codeBlockText = param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackGetLast[progLang] + progLangEquals[progLang] + lastSentenceReferenced + progLangEndLine[progLang];		//param1->lastSentenceReferenced.top() = x;		
			#else
			string codeBlockText = param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangEquals[progLang] + lastSentenceReferenced + progLangEndLine[progLang];		//param1->lastSentenceReferenced = x;
			#endif
			printLine(codeBlockText, level, code);
		}
		#endif
		#endif	
		#ifdef NLC_GENERATE_TYPE_LISTS
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE2)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE2" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;
	
			string localListDeclarationText = generateCodeEntityListDefinitionTypeText2(param1->className, progLang) + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangEndLine[progLang];	//vector<vector<param1Class*>> param1instanceTypeList;
			printLine(localListDeclarationText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST2)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST2" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			NLCitem * param4 = currentCodeBlockInLevel->parameters.at(3);
			string genericListAppendName = param3->name;
			string genericListAppendName2 = param4->name;

			string codeBlockText = generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + generateGenericListName(param2->instanceName, genericListAppendName2) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instanceTypeList.push_back(param2);
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST2)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST2" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;
			
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeText2(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = generateCodeEntityListDefinitionTypeText(param1->className, progLang) + generatePropertyListName(param1->className) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMPVAR_APPENDITION
				//check use of generatePropertyListName(); should really be generateTempListName()
			printLine(tempVarDeclarationText, (level+1), code);
		}
		#endif
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_OR_EQUAL_TO_NUM_GENERIC_ENTITY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_OR_EQUAL_TO_NUM_GENERIC_ENTITY" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string valueString = param3->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangGreaterThanOrEqualTo[progLang] + valueString + progLangCloseParameterSpace[progLang];		//if(param1instanceCategoryList.size() > 0){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_TEST_INT_VARIABLE_GREATER_THAN_OR_EQUAL_TO_NUM)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_TEST_INT_VARIABLE_GREATER_THAN_OR_EQUAL_TO_NUM" << endl;
			#endif

			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string valueString = param2->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + param1->name + progLangGreaterThanOrEqualTo[progLang] + valueString + progLangCloseParameterSpace[progLang];		//if(variable > x){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		#endif
		/*	
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_PROPERTY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_PROPERTY" << endl;
			#endif

			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string valueString = param2->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + generatePropertyListName(param1->className) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangGreaterThan[progLang] + valueString + progLangCloseParameterSpace[progLang];		//if(context1->param1PropertyList.size() > x){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_CONDITION" << endl;
			#endif

			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);			
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string valueString = param3->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + generateConditionListName(param1->className, param2->className) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangGreaterThan[progLang] + valueString + progLangCloseParameterSpace[progLang];		//if(context1->param1param2ConditionList.size() > x){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		#endif
		*/
		#endif
		#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_CONTEXT_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_CONTEXT_LIST" << endl;
			#endif
			string contextLevelString = param1->name;
			
			string  genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
			string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLISTVAR_APPENDITION) + contextLevelString;
			string contextListDeclarationText = generateCodeEntityListDefinitionTypeText(genericEntityClassName, progLang) + contextListName + progLangEndLine[progLang];	//vector<genericEntityClass*> contextListX;
			printLine(contextListDeclarationText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_NEW_FUNCTION)
		{//finish coding this
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_NEW_FUNCTION" << endl;
			#endif

			string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
			string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLISTVAR_APPENDITION);
			string entityToAddName = NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE;
			
			string codeBlockTextFunctionHeader = progLangClassMemberFunctionType[progLang] + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_ADD_ENTITY_TO_CONTEXT_LIST_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeEntityListDefinitionTypeText(genericEntityClassName, progLang) + contextListName + progLangClassMemberFunctionParametersNext[progLang] + generateTempVariableDeclaration(genericEntityClassName, entityToAddName, progLang) + progLangClassMemberFunctionParametersNext[progLang] + progLangClassLastSentenceIndexVariableType[progLang] + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_SENTENCE_INDEX_VARIABLE_NAME + progLangCloseParameterSpace[progLang];	//void addVariableToContextList(vector<genericEntityClass*> contextList, genericEntityClass* genericEntity, int sentenceIndex)

			printLine("", level, code);
			printLine(codeBlockTextFunctionHeader, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
				string pushLastSentenceReferencedText = contextListName + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + entityToAddName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//contextList.push_back(genericEntity);
				printLine(pushLastSentenceReferencedText, (level+1), code);
				string codeBlockUpdateLastSentenceReferencedText = entityToAddName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackAdd[progLang] + progLangOpenParameterSpace[progLang] + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_SENTENCE_INDEX_VARIABLE_NAME + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//genericEntity->lastSentenceReferenced.push(sentenceIndex);		
				printLine(codeBlockUpdateLastSentenceReferencedText, (level+1), code);
			printLine(progLangCloseBlock[progLang], level, code);	
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_EXECUTE_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_EXECUTE_FUNCTION" << endl;
			#endif
			
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_PRINT_LEVEL_USED_INSTEAD_OF_CONTEXT_LEVEL
			string contextLevelString = convertIntToString(level);
			#else
			string contextLevelString = param1->name;
			#endif
			string entityToAddName = param2->instanceName;
			string sentenceIndexString = param3->name;

			string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
			string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLISTVAR_APPENDITION) + contextLevelString;
			string tempVariableName = string(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
			
			string codeBlockText = "";
			codeBlockText = codeBlockText + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_ADD_ENTITY_TO_CONTEXT_LIST_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + contextListName + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangClassMemberFunctionParametersNext[progLang] + sentenceIndexString + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addVariableToContextList(contextListX, entityName, sentenceIndex);			
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_NEW_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_NEW_FUNCTION" << endl;
			#endif
			
			string iterIndexString = convertIntToString(level);
			string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
			string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLISTVAR_APPENDITION);
			string tempVariableName = string(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
				
			string codeBlockTextFunctionHeader = progLangClassMemberFunctionType[progLang] + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_CLEAR_CONTEXT_LIST_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeEntityListDefinitionTypeText(genericEntityClassName, progLang) + contextListName + progLangCloseParameterSpace[progLang];	//void clearContextList(vector<genericEntityClass*> contextList)

			printLine("", level, code);
			printLine(codeBlockTextFunctionHeader, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
				string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeText(genericEntityClassName, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextListName + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + contextListName + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];	//for(vector<genericEntityClass*> ::iterator iterX = contextList.begin(); iterX < contextList.end(); iterX++)
				printLine(codeBlockText, (level+1), code);
					printLine(progLangOpenBlock[progLang], (level+1), code);	//{
					string tempVarDeclarationText = generateTempVariableDeclaration(genericEntityClassName, tempVariableName, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//genericEntityClass* genericEntity = *iter2;
					printLine(tempVarDeclarationText, (level+2), code);
					string popLastSentenceReferencedText = tempVariableName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackRemove[progLang] + progLangEndLine[progLang];	//genericEntity->lastSentenceReferenced.pop();
					printLine(popLastSentenceReferencedText, (level+2), code);
				printLine(progLangCloseBlock[progLang], (level+1), code);
				string clearContextListText = contextListName + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveProperties[progLang] + progLangEndLine[progLang];		//contextList.clear();
				printLine(clearContextListText, (level+1), code);
			printLine(progLangCloseBlock[progLang], level, code);	
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_EXECUTE_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_EXECUTE_FUNCTION" << endl;
			#endif
			
			#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_PRINT_LEVEL_USED_INSTEAD_OF_CONTEXT_LEVEL
			string contextLevelString = convertIntToString(level);
			#else
			string contextLevelString = param1->name;
			#endif

			string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLISTVAR_APPENDITION) + contextLevelString;

			string codeBlockExecuteFunctionText = "";
			codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_CLEAR_CONTEXT_LIST_FUNCTION_NAME +  progLangOpenParameterSpace[progLang] + contextListName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//clearContextLevelList(contextListX);
			printLine(codeBlockExecuteFunctionText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CONTEXT_BLOCK)
		{
			printLine(progLangOpenBlock[progLang], level, code);		
		}
		#endif
		/*
		else if(currentCodeBlockInLevel->codeBlockType == ...)
		{

		}
		...
		*/
		else
		{
			cout << "printCodeBlocks: error: currentCodeBlockInLevel->codeBlockType = " << currentCodeBlockInLevel->codeBlockType << endl;
		}

		if(currentCodeBlockInLevel->lowerLevel != NULL)
		{
			printCodeBlocks(currentCodeBlockInLevel->lowerLevel, classDefinitionList, progLang, code, (level+1));
			printLine(progLangCloseBlock[progLang], level, code);
			#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
			if(currentCodeBlockInLevel->isLogicalCondition)
			{
				//createCodeBlocksClearContextListVariableExecuteFunction:
				#ifdef NLC_DEBUG
				cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_EXECUTE_FUNCTION" << endl;
				#endif

				string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
				#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_PRINT_LEVEL_USED_INSTEAD_OF_CONTEXT_LEVEL
				string contextLevelString = convertIntToString(level + 1);
				#else
				string contextLevelString = convertIntToString(currentCodeBlockInLevel->contextLevel);
				#endif
				string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLISTVAR_APPENDITION) + contextLevelString;
			
				string codeBlockExecuteFunctionText = "";
				codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_CLEAR_CONTEXT_LIST_FUNCTION_NAME +  progLangOpenParameterSpace[progLang] + contextListName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//clearContextLevelList(contextListX);
				printLine(codeBlockExecuteFunctionText, level, code);
			}
			#endif
		}

		currentCodeBlockInLevel = currentCodeBlockInLevel->next;
	}
	return true;
}



void generateFunctionExecutionArgumentsWithActionConceptInheritanceString(vector<NLCclassDefinition *> * classDefinitionList, vector<NLCitem*> * codeBlockParameters, string * functionArguments, int progLang)
{
	vector<NLCitem*> * parameters;
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	NLCitem * param1 = codeBlockParameters->at(0);
	//get function arguments from class definition list (in case they have been dynamically updated based on implicit declarations within the function definition)
	bool foundLocalClassDefinition = false;
	NLCclassDefinition * localClassDefinition = findClassDefinition(classDefinitionList, param1->instanceName, &foundLocalClassDefinition);	//see if class definition already exists
	if(foundLocalClassDefinition)
	{
		parameters = &(localClassDefinition->parameters);
	}
	else
	{
		//#ifdef NLC_DEBUG5
		cout << "warning: !foundLocalClassDefinition: param1->instanceName = " << param1->instanceName << endl;
		cout << "(action probably has no subject)." << endl;
		//#endif
		parameters = codeBlockParameters;
	}
	#else
	parameters = codeBlockParameters;
	#endif
	//parameters = codeBlockParameters;

	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;

		cout << "at1" << endl;
		cout << "currentItem->itemType = " << currentItem->itemType << endl;
		if((currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_INSTANCE_OR_CLASS_LIST) || (currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_INSTANCE_OR_CLASS_LIST))	//not currently used
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodePluralReferenceText(currentItem, progLang);
			//*functionArguments = *functionArguments + generateCodeSingularReferenceText(currentItem, progLang);	//OLD
		}
		#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
		else if((currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION) || (currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION))
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
			*functionArguments = *functionArguments + generateCodePluralReferenceText(currentItem, progLang);
			#else
			*functionArguments = *functionArguments + generateCodeSingularReferenceText(currentItem, progLang);
			#endif
		}
		else if((currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT) || (currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OBJECT))
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
			*functionArguments = *functionArguments + generateCodePluralReferenceText(currentItem, progLang);
			#else
			*functionArguments = *functionArguments + generateCodeSingularReferenceText(currentItem, progLang);
			#endif
		}
		#endif
		/*
		#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_CONDITION)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeConditionPairReferenceText(currentItem, progLang);
		}
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_PROPERTY)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeSingularReferenceText(currentItem, progLang);
		}
		#endif
		*/
	}
}


string generateCodePluralReferenceText(NLCitem * functionArgumentItem, int progLang)
{
	string codePropertyTypeText = generateEntityLocalListName(functionArgumentItem);
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	if(functionArgumentItem->functionArgumentPassCastRequired)
	{	
		cout << "generateCodePluralReferenceText() error: functionArgumentItem->functionArgumentPassCastRequired not yet coded" << endl;
		//CHECKTHIS	//v2.assign(v1.begin(), v1.end());
	}
	#endif
	return codePropertyTypeText;
}

string generateCodeSingularReferenceText(NLCitem * functionArgumentItem, int progLang)
{
	string codePropertyTypeText = functionArgumentItem->instanceName;
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	if(functionArgumentItem->functionArgumentPassCastRequired)
	{
		codePropertyTypeText = progLangDynamicCastStart[progLang] + functionArgumentItem->functionArgumentPassCastClassName + progLangDynamicCastEnd[progLang] + progLangOpenParameterSpace[progLang] + functionArgumentItem->instanceName + progLangCloseParameterSpace[progLang];	//dynamic_cast<parentClass*>(childClassInstance);
	}
	#endif
	return codePropertyTypeText;
}

#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
string generateCodeConditionPairReferenceText(NLCitem * functionArgumentConditionItem, int progLang)
{
	//do: ADD dynamic_cast<functionArgumentPassCastClassName> if functionArgumentPassCastClassName != ""
	string codeConditionPairTypeText = generateCodeConditionPairTextWithContext(functionArgumentConditionItem->name, functionArgumentConditionItem->className, functionArgumentConditionItem->instanceName, functionArgumentConditionItem->className2, functionArgumentConditionItem->instanceName2, &(functionArgumentConditionItem->context), progLang);
	return codeConditionPairTypeText;
}
#endif


#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
void generateLocalFunctionArgumentsBasedOnImplicitDeclarationsString(vector<NLCitem*> * parameters, string * functionArguments, int progLang)
{
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeEntityListDefinitionText(currentItem, progLang);
		}
	}
}
#endif

#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
void generateFunctionArgumentsBasedOnActionAndActionObjectVars(vector<NLCitem*> * parameters, string * functionArguments, int progLang)
{
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;
		cout << "\tcurrentItem->itemType = " << currentItem->itemType << endl;
		cout << "currentItem->instanceName = " << currentItem->instanceName << endl;
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION)
		{
			cout << "NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION" << endl;
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
			*functionArguments = *functionArguments + generateCodeEntityListDefinitionText(currentItem, progLang);
			#else
			*functionArguments = *functionArguments + currentItem->className + progLangPointer[progLang] + STRING_SPACE + generateEntityLocalListName(currentItem);
			#endif
		}
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT)
		{
			cout << "NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT" << endl;
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
			*functionArguments = *functionArguments + generateCodeEntityListDefinitionText(currentItem, progLang);
			#else
			*functionArguments = *functionArguments + currentItem->className + progLangPointer[progLang] + STRING_SPACE + generateEntityLocalListName(currentItem);
			#endif			
		}
	}
}
#endif





string generateFunctionOwnerContext(vector<NLCitem*> * parameters, int progLang)
{
	bool foundFunctionOwner = false;
	string functionOwnerContext = "";
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER)
		{
			functionOwnerContext = progLangClassMemberFunctionType[progLang] + currentItem->className + progLangFunctionOwnerClassDelimiter[progLang];
			foundFunctionOwner = true;
		}
	}
	#endif
	if(!foundFunctionOwner)
	{
		functionOwnerContext = progLangClassMemberFunctionType[progLang];
	}
	return functionOwnerContext;
}

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
string generateLogicalConjunctionOfBoolsText(vector<NLCitem*> * parameters, int progLang)
{
	string logicalConjunctionOfBoolsText = "";
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;
		if(currentItem->conjunctionType == ENTITY_COORDINATINGCONJUNCTION_ARRAY_INDEX_AND)
		{
			logicalConjunctionOfBoolsText = logicalConjunctionOfBoolsText + STRING_SPACE + progLangAnd[progLang] + STRING_SPACE;
		}
		else if(currentItem->conjunctionType == ENTITY_COORDINATINGCONJUNCTION_ARRAY_INDEX_OR)
		{
			logicalConjunctionOfBoolsText = logicalConjunctionOfBoolsText + STRING_SPACE + progLangOr[progLang] + STRING_SPACE;
		}

		if(currentItem->negative)
		{
			logicalConjunctionOfBoolsText = logicalConjunctionOfBoolsText + progLangNot[progLang];
		}

		logicalConjunctionOfBoolsText = logicalConjunctionOfBoolsText + currentItem->name;	//should create a new currentItem variable called variableName for non-objects
	}
	return logicalConjunctionOfBoolsText;
}
#endif

