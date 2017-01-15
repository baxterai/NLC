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
 * File Name: NLCtranslator.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1i11p 25-August-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCtranslator.h"
#include "NLCtranslatorCodeBlocks.h"
#include "NLCtranslatorCodeBlocksLogicalConditions.h"	//required for tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperation
#include "NLCtranslatorClassDefinitions.h"
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
#include "GIAtranslatorDefs.h"
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
NLClogicalConditionConjunctionContainer::NLClogicalConditionConjunctionContainer(void)
{
	entity = NULL;
	optimumPathIndex = 0;
}
NLClogicalConditionConjunctionContainer::NLClogicalConditionConjunctionContainer(GIAentityNode * currentEntity)
{
	entity = currentEntity;
	optimumPathIndex = 0;
}
NLClogicalConditionConjunctionContainer::~NLClogicalConditionConjunctionContainer(void)
{
}
#endif

bool translateNetwork(NLCcodeblock * firstCodeBlockInTree, vector<NLCclassDefinition *> * classDefinitionList, vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences, string NLCfunctionName, NLCfunction * currentNLCfunctionInList, bool useNLCpreprocessor)
{
	bool result = true;

	#ifdef NLC_USE_PREPROCESSOR
	initialiseLogicalConditionLevelRecordArray(useNLCpreprocessor);
	#endif

	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
	//NLC translator Part prep A.
	if(!removeRedundantConditionConjunctions(entityNodesActiveListComplete, maxNumberSentences))
	{
		result = false;
	}
	#endif

	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	//NLC translator Part prep B.
	if(!identifyAndTagAllLogicalConditionOperations(entityNodesActiveListComplete, maxNumberSentences))
	{
		result = false;
	}
	#endif

	//NLC translator Part 1.
	if(!generateCodeBlocks(firstCodeBlockInTree, entityNodesActiveListComplete, maxNumberSentences, NLCfunctionName, currentNLCfunctionInList))
	{
		result = false;
	}

	//NLC translator Part 2.
	if(!generateClassHeirarchy(classDefinitionList, entityNodesActiveListComplete, maxNumberSentences))
	{
		result = false;
	}
	return result;
}

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
bool removeRedundantConditionConjunctions(vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences)
{
	bool result = true;
	for(int sentenceIndex=GIA_NLP_START_SENTENCE_INDEX; sentenceIndex <= maxNumberSentences; sentenceIndex++)
	{
		NLClogicalConditionConjunctionContainer * logicalConditionConjunctionContainerFirstInOptimumPath = NULL;
		int maximumNumberOfConjunctions = 0;
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{
			GIAentityNode * conditionEntity = (*entityIter);
			if(conditionEntity->isCondition)
			{
				if(checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, false))
				{
					int conjunctionType = INT_DEFAULT_VALUE;
					bool conjunctionConditionFound = textInTextArray(conditionEntity->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES, &conjunctionType);
					if(conjunctionConditionFound)
					{
						NLClogicalConditionConjunctionContainer * logicalConditionConjunctionContainer = new NLClogicalConditionConjunctionContainer(conditionEntity);
						int numberOfConjunctions = addConjunctionsConnectedToConditionConjunctionObject(conditionEntity, logicalConditionConjunctionContainer, sentenceIndex);
						if(numberOfConjunctions > maximumNumberOfConjunctions)
						{
							logicalConditionConjunctionContainerFirstInOptimumPath = logicalConditionConjunctionContainer;
							maximumNumberOfConjunctions = numberOfConjunctions;
							//cout << "maximumNumberOfConjunctions = " << maximumNumberOfConjunctions << endl;
						}
					}
				}
			}
		}

		#ifdef NLC_DEBUG
		cout << "maximumNumberOfConjunctions = " << maximumNumberOfConjunctions << endl;
		#endif
		if(maximumNumberOfConjunctions > 0)
		{
			for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
			{
				GIAentityNode * conditionEntity = (*entityIter);
				if(conditionEntity->isCondition)
				{
					if(checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, false))
					{
						int conjunctionType = INT_DEFAULT_VALUE;
						bool conjunctionConditionFound = textInTextArray(conditionEntity->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES, &conjunctionType);
						if(conjunctionConditionFound)
						{
							if(!traceConditionConjunctionsOptimiumPathAndSeeIfConditionConjunctionEntityIsOnIt(logicalConditionConjunctionContainerFirstInOptimumPath, conditionEntity))
							{
								GIAentityNode * logicalConditionConjunctionObjectEntity = (conditionEntity->conditionObjectEntity->back())->entity;
								GIAentityNode * logicalConditionConjunctionSubjectEntity = (conditionEntity->conditionSubjectEntity->back())->entity;
								#ifdef NLC_DEBUG
								cout << "disabling conditionEntity: " << conditionEntity->entityName << endl;
								cout << "logicalConditionConjunctionObjectEntity: " << logicalConditionConjunctionObjectEntity->entityName << endl;
								cout << "logicalConditionConjunctionSubjectEntity: " << logicalConditionConjunctionSubjectEntity->entityName << endl;
								#endif

								conditionEntity->disabled = true;
							}
						}
					}
				}
			}
		}
	}
	return result;
}

int addConjunctionsConnectedToConditionConjunctionObject(GIAentityNode * conditionEntity, NLClogicalConditionConjunctionContainer * logicalConditionConjunctionContainer, int sentenceIndex)
{
	int maximumNumberOfConjunctions = 0;
	GIAentityNode * conditionObjectEntity = NULL;
	GIAentityConnection * conditionConnection = NULL;
	bool conditionHasObject = false;
	if(!(conditionEntity->conditionObjectEntity->empty()))
	{
		conditionHasObject = true;
		conditionConnection = conditionEntity->conditionObjectEntity->back();
		conditionObjectEntity = conditionConnection->entity;
	}
	if(conditionHasObject)
	{
		if(checkSentenceIndexParsingCodeBlocks(conditionObjectEntity, conditionConnection, sentenceIndex, false))
		{
			int conjunctionIndex = 0;
			for(vector<GIAentityConnection*>::iterator connectionIter = conditionObjectEntity->conditionNodeList->begin(); connectionIter != conditionObjectEntity->conditionNodeList->end(); connectionIter++)
			{
				GIAentityConnection * conditionConnection2 = (*connectionIter);
				GIAentityNode * conditionEntity2 = conditionConnection2->entity;
				if(checkSentenceIndexParsingCodeBlocks(conditionEntity2, conditionConnection2, sentenceIndex, false))
				{
					int conjunctionType = INT_DEFAULT_VALUE;
					bool conjunctionConditionFound = textInTextArray(conditionEntity2->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES, &conjunctionType);
					if(conjunctionConditionFound)
					{
						NLClogicalConditionConjunctionContainer * logicalConditionConjunctionContainer2 = new NLClogicalConditionConjunctionContainer(conditionEntity2);
						logicalConditionConjunctionContainer->nextConditionConjunctions.push_back(logicalConditionConjunctionContainer2);
						int numberOfConjunctions = addConjunctionsConnectedToConditionConjunctionObject(conditionEntity2, logicalConditionConjunctionContainer2, sentenceIndex);
						if(numberOfConjunctions > maximumNumberOfConjunctions)
						{
							logicalConditionConjunctionContainer->optimumPathIndex = conjunctionIndex;
							maximumNumberOfConjunctions = numberOfConjunctions;
						}
						conjunctionIndex++;
					}
				}
			}
		}
	}
	else
	{
		cout << "addConjunctionsConnectedToConditionConjunctionObject() error: !conditionHasObject" << endl;
	}
	return maximumNumberOfConjunctions + 1;
}

bool traceConditionConjunctionsOptimiumPathAndSeeIfConditionConjunctionEntityIsOnIt(NLClogicalConditionConjunctionContainer * logicalConditionConjunctionContainer, GIAentityNode * logicalConditionConjunctionToTest)
{
	bool foundLogicalConditionConjunctionOnOptimumPath = false;
	if(logicalConditionConjunctionToTest == logicalConditionConjunctionContainer->entity)
	{
		foundLogicalConditionConjunctionOnOptimumPath = true;
	}
	else
	{
		if(!(logicalConditionConjunctionContainer->nextConditionConjunctions.empty()))
		{
			if(traceConditionConjunctionsOptimiumPathAndSeeIfConditionConjunctionEntityIsOnIt(logicalConditionConjunctionContainer->nextConditionConjunctions[logicalConditionConjunctionContainer->optimumPathIndex], logicalConditionConjunctionToTest))
			{
				foundLogicalConditionConjunctionOnOptimumPath = true;
			}
		}
	}
	return foundLogicalConditionConjunctionOnOptimumPath;
	/*
	for(vector<NLClogicalConditionConjunctionContainer*>::iterator iter = logicalConditionConjunctionContainer->nextConditionConjunctions->begin(); iter != logicalConditionConjunctionContainer->nextConditionConjunctions->end(); iter++)
	{

	}
	*/
}
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
bool identifyAndTagAllLogicalConditionOperations(vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences)
{
	for(int sentenceIndex=GIA_NLP_START_SENTENCE_INDEX; sentenceIndex <= maxNumberSentences; sentenceIndex++)
	{
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{
			GIAentityNode * conditionEntity = (*entityIter);
			if(checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, true))	//could be set to false instead
			{
				bool foundLogicalConditionOperation = false;
				int logicalOperation;
				bool foundLogicalConditionOperationBasic = textInTextArray(conditionEntity->entityName, logicalConditionOperationsArray, NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES, &logicalOperation);
				if(foundLogicalConditionOperationBasic && (logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_FOR))
				{
					//FUTURE: NB this implementation must be made compatible with GIAdatabase.cpp and GIAxmlConversion.cpp (eg store entityIndex and sentenceIndexTemp). NB sentenceIndexTemp is necessary for other NLC functions also.
					#ifdef NLC_ONLY_SUPPORT_LOGICAL_CONJUNCTION_FOR_AT_START_OF_SENTENCE
					if(conditionEntity->entityIndexTemp == 1)
					{
						foundLogicalConditionOperation = true;
					}
					#else
					//because GIA Sentence objects are unavailable to NLC, must parse all entities including disabled entites and locate matching entities (in same sentence and with entityIndex+1 of "for" condition):
					for(vector<GIAentityNode*>::iterator entityIter2 = entityNodesActiveListComplete->begin(); entityIter2 != entityNodesActiveListComplete->end(); entityIter2++)
					{
						GIAentityNode * entity2 = (*entityIter);
						if(entity2->sentenceIndexTemp == sentenceIndex)
						{
							if(entity2->entityIndexTemp = conditionEntity->entityIndex+1)
							{
								bool wordImmediatelySucceedingForFound = textInTextArray(entity2->entityName, logicalConditionOperationsWordImmediatelySucceedingForArray, NLC_LOGICAL_CONDITION_OPERATIONS_WORD_IMMEDIATELY_SUCCEEDING_FOR_NUMBER_OF_TYPES);
								foundLogicalConditionOperation = true;
							}
						}
					}
					#endif
				}
				else if(foundLogicalConditionOperationBasic)
				{
					foundLogicalConditionOperation = true;
				}
				if(foundLogicalConditionOperation)
				{
					//concepts must be tagged as NLClogicalConditionOperation to prevent generateClassHeirarchy from creating class definitions for logical conditions
					#ifdef NLC_DEBUG
					cout << "foundLogicalConditionOperation: " << conditionEntity->entityName << endl;
					#endif
					conditionEntity->NLClogicalConditionOperation = true;

					if(conditionEntity->isCondition)
					{//ignore concepts

						GIAentityNode * conditionSubject = NULL;
						GIAentityNode * conditionObject = NULL;
						bool foundConditionSubject = false;
						bool foundConditionObject = false;
						if(!(conditionEntity->conditionSubjectEntity->empty()))
						{
							conditionSubject = (conditionEntity->conditionSubjectEntity->back())->entity;
							foundConditionSubject = true;
						}
						if(!(conditionEntity->conditionObjectEntity->empty()))
						{
							conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
							foundConditionObject = true;
						}
						if(foundConditionSubject && foundConditionObject)
						{
							conditionEntity->NLCparsedForlogicalConditionOperations = true;
							//cout << "tagged: conditionEntity->entityName = " << conditionEntity->entityName << endl;

							if(conditionObject->isConcept)
							{
								cout << "identifyAndTagAllLogicalConditionOperations() error: NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS only handles substance concepts. GIA_CREATE_SUBSTANCE_CONCEPTS_FOR_ALL_SENTENCES_WITH_CONCEPTS must be enabled." << endl;
								cout << "conditionObject = " << conditionObject->entityName;
							}
							else
							{
								tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperation(conditionObject, sentenceIndex, true);
							}
							if(conditionSubject->isConcept)
							{
								cout << "identifyAndTagAllLogicalConditionOperations() error: NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS only handles substance concepts. GIA_CREATE_SUBSTANCE_CONCEPTS_FOR_ALL_SENTENCES_WITH_CONCEPTS must be enabled." << endl;
								cout << "conditionSubject = " << conditionSubject->entityName;
							}
							else
							{
								tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperation(conditionSubject, sentenceIndex, true);
							}
						}
					}
				}
			}
		}
	}
	return true;
}
#endif


#ifdef NLC_SUPPORT_INPUT_FILE_LISTS

void reconcileClassDefinitionListFunctionArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition(NLCcodeblock * firstCodeBlockInTree, vector<NLCclassDefinition *> * classDefinitionList, string NLCfunctionName)
{
	//reconcile function arguments (both class function header and code function reference)
	string functionName = "";
	string functionOwnerName = "";
	bool foundFunctionOwnerClass = false;
	parseFunctionNameFromNLCfunctionName(NLCfunctionName, &functionName, &functionOwnerName, &foundFunctionOwnerClass);	//gets "fight" from "dog::fight"

	NLCclassDefinition * classDefinitionFound = NULL;
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition * currentClassDef = *classDefinitionIter;
		if((currentClassDef->name == generateClassName(functionOwnerName)) || !foundFunctionOwnerClass)
		{
			//cout << "currentClassDef->name = " << currentClassDef->name << endl;
			for(vector<NLCclassDefinition*>::iterator localListIter = currentClassDef->functionList.begin(); localListIter != currentClassDef->functionList.end(); localListIter++)
			{
				NLCclassDefinition * functionClassDefinition = *localListIter;
				//cout << "functionClassDefinition->functionNameSpecial = " << functionClassDefinition->functionNameSpecial << endl;
				//cout << "functionName = " << functionName << endl;
				if(functionClassDefinition->functionNameSpecial == generateFunctionName(functionName))
				{
					#ifdef NLC_DEBUG
					cout << "reconcileClassDefinitionListFunctionArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition() functionName = " << functionName << endl;
					#endif
					//contrast and compare function class arguments vs

					findFormalFunctionArgumentCorrelateInExistingList(functionClassDefinition, &(firstCodeBlockInTree->parameters), classDefinitionList);
				}
			}
		}
	}
}

bool findFormalFunctionArgumentCorrelateInExistingList(NLCclassDefinition * functionClassDefinition, vector<NLCitem*> * formalFunctionArgumentList, vector<NLCclassDefinition *> * classDefinitionList)
{
	vector<NLCitem*> * existingFunctionArgumentList = &(functionClassDefinition->parameters);

	for(vector<NLCitem*>::iterator parametersIterator = formalFunctionArgumentList->begin(); parametersIterator < formalFunctionArgumentList->end(); parametersIterator++)
	{
		NLCitem * formalFunctionArgument = *parametersIterator;
		NLCclassDefinition * classDefinitionCorrespondingToExistingFunctionArgument = NULL;
		NLCclassDefinition * classDefinitionCorrespondingToFormalFunctionArgument = NULL;	//not used
		NLCitem * existingFunctionArgument = NULL;
		bool foundFormalFunctionArgumentCorrelateForExistingArgument = false;
		int foundFormalFunctionArgumentCorrelateForExistingArgumentInheritanceLevel = NLC_SUPPORT_INPUT_FILE_LISTS_MAX_INHERITANCE_DEPTH_FOR_CLASS_CASTING;
		if(formalFunctionArgument->itemType == NLC_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL)
		{
			#ifdef NLC_DEBUG
			cout << "formalFunctionArgument->className = " << formalFunctionArgument->className << endl;
			#endif
			for(vector<NLCitem*>::iterator parametersIterator = existingFunctionArgumentList->begin(); parametersIterator < existingFunctionArgumentList->end(); parametersIterator++)
			{
				NLCitem * currentExistingFunctionArgument = *parametersIterator;

				bool foundClassDefinitionCorrespondingToExistingFunctionArgument = false;
				for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
				{
					NLCclassDefinition * currentClassDef = *classDefinitionIter;
					if(currentClassDef->name == currentExistingFunctionArgument->className)
					{
						classDefinitionCorrespondingToExistingFunctionArgument = currentClassDef;
						foundClassDefinitionCorrespondingToExistingFunctionArgument = true;
					}
				}

				if(foundClassDefinitionCorrespondingToExistingFunctionArgument)
				{
					#ifdef NLC_DEBUG
					cout << "foundClassDefinitionCorrespondingToExistingFunctionArgument: " << classDefinitionCorrespondingToExistingFunctionArgument->name << endl;
					#endif
					if(formalFunctionArgument->itemType == NLC_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL)
					{//CHECKTHIS; do not currently distinguish between plural and singular variables - this will need to be updated in future
						int inheritanceLevel = 0;
						NLCclassDefinition * tempClassDef = NULL;
						//cout << "classDefinitionCorrespondingToExistingFunctionArgument->name = " << classDefinitionCorrespondingToExistingFunctionArgument->name << endl;
						//cout << "formalFunctionArgument->className = " << formalFunctionArgument->className << endl;
						if(findParentClass(classDefinitionCorrespondingToExistingFunctionArgument, formalFunctionArgument->className, 0, &inheritanceLevel, &tempClassDef))
						{
							if(inheritanceLevel < foundFormalFunctionArgumentCorrelateForExistingArgumentInheritanceLevel)
							{
								//cout << "foundFormalFunctionArgumentCorrelateForExistingArgument" << endl;
								foundFormalFunctionArgumentCorrelateForExistingArgument = true;
								foundFormalFunctionArgumentCorrelateForExistingArgumentInheritanceLevel = inheritanceLevel;
								classDefinitionCorrespondingToFormalFunctionArgument = tempClassDef;
								existingFunctionArgument = currentExistingFunctionArgument;
							}
						}
					}
					else
					{
						//cout << "unsupported function argument: formalFunctionArgument->itemType = " << formalFunctionArgument->itemType << endl;
					}
				}
				else
				{
					cout << "findFormalFunctionArgumentCorrelateInExistingList() error: !foundClassDefinitionCorrespondingToExistingFunctionArgument: " << currentExistingFunctionArgument->className << endl;
				}
			}
			if(foundFormalFunctionArgumentCorrelateForExistingArgument)
			{
				existingFunctionArgument->functionArgumentCertified = true;

				//store cast information for more generic class type passed as function argument
				if(existingFunctionArgument->className != formalFunctionArgument->className)
				{
					existingFunctionArgument->functionArgumentPassCastClassName = formalFunctionArgument->className;
					existingFunctionArgument->functionArgumentPassCastRequired = true;
				}
			}
			else
			{
				#ifdef NLC_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
				bool foundFunctionArgumentInActionSubjectContents = false;
				GIAentityNode * actionEntity = functionClassDefinition->actionOrConditionInstance;
				if(!(actionEntity->actionSubjectEntity->empty()))
				{
					GIAentityNode * actionSubject = (actionEntity->actionSubjectEntity->back())->entity;
					//cout << "actionSubject = " << actionSubject->entityName << endl;
					//cout << "formalFunctionArgument->className = " << formalFunctionArgument->className << endl;
					if(formalFunctionArgument->className == generateClassName(actionSubject))
					{
						foundFunctionArgumentInActionSubjectContents = true;
						#ifdef NLC_DEBUG
						cout << "foundFunctionArgumentInActionSubjectContents: " << formalFunctionArgument->className << endl;
						#endif
						//formalFunctionArgument->formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = true;	//not done; this is now handled by generateContextBlocks()
					}
					/*//ignore conditions of actionSubject; they will need to be explicitly referenced by the function
					for(vector<GIAentityConnection*>::iterator entityIter = actionSubject->conditionNodeList->begin(); entityIter != actionSubject->conditionNodeList->end(); entityIter++)
					{
						GIAentityNode * actionCondition = (*entityIter)->entity;
					}
					*/
					for(vector<GIAentityConnection*>::iterator entityIter = actionSubject->propertyNodeList->begin(); entityIter != actionSubject->propertyNodeList->end(); entityIter++)
					{
						GIAentityNode * actionProperty = (*entityIter)->entity;
						if(formalFunctionArgument->className == generateClassName(actionProperty))
						{//NB these implicitly declared parameters in the function definition will be referenced as plural (lists) not singular entities
								//NO: check this is the case; eg the dog eats the pie; 'the dog' should be extracted from dogList if it was not passed as a parameter
								//1dXy: all parameters should be passed as lists (temporary lists should be created if specific variables require passing)
							foundFunctionArgumentInActionSubjectContents = true;
						}
					}
				}

				if(!foundFunctionArgumentInActionSubjectContents)
				{
					cout << "NLC compiler warning: !foundFormalFunctionArgumentCorrelateForExistingArgument && !foundFunctionArgumentInActionSubjectContents (function arguments will not map): " << formalFunctionArgument->className << endl;
				#else
					cout << "NLC compiler warning: !foundFormalFunctionArgumentCorrelateForExistingArgument (function arguments will not map): " << formalFunctionArgument->className << endl;
				#endif
					//add a new function argument to the existing function argument list
					NLCitem * formalFunctionArgumentToAddExistingFunctionArgumentList = new NLCitem(formalFunctionArgument);	//NLC by default uses plural (lists) not singular entities
					existingFunctionArgumentList->push_back(formalFunctionArgumentToAddExistingFunctionArgumentList);
				#ifdef NLC_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
				}
				#endif
			}
		}
	}
	return true;
}

bool findParentClass(NLCclassDefinition * classDefinition, string variableName, int inheritanceLevel, int * maxInheritanceLevel, NLCclassDefinition ** parentClass)
{
	bool foundVariable = false;
	if(classDefinition->name == variableName)
	{
		foundVariable = true;
		*maxInheritanceLevel = inheritanceLevel;
		*parentClass = classDefinition;
	}
	else
	{
		for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->definitionList.begin(); localListIter != classDefinition->definitionList.end(); localListIter++)
		{
			NLCclassDefinition * targetClassDefinition = *localListIter;
			if(findParentClass(targetClassDefinition, variableName, (inheritanceLevel+1), maxInheritanceLevel, parentClass))
			{
				foundVariable = true;
			}
		}
	}
	return foundVariable;
}

bool getFilesFromFileList2(string inputListFileName, vector<string> * inputTextFileNameList, int * numberOfInputFilesInList)
{
	bool result = true;
	*numberOfInputFilesInList = 0;
	ifstream parseFileObject(inputListFileName.c_str());
	if(!parseFileObject.rdbuf( )->is_open())
	{
		//txt file does not exist in current directory.
		cout << "Error: input list file does not exist in current directory: " << inputListFileName << endl;
		result = false;
	}
	else
	{
		char currentToken;
		int fileNameIndex = 0;
		int charCount = 0;
		string currentFileName = "";
		while(parseFileObject.get(currentToken))
		{
			if(currentToken == CHAR_NEWLINE)
			{
				inputTextFileNameList->push_back(currentFileName);
				#ifdef GIA_MAIN_DEBUG
				//cout << "currentFileName = " << currentFileName << endl;
				#endif
				currentFileName = "";
				fileNameIndex++;
			}
			else
			{
				currentFileName = currentFileName + currentToken;
			}
			charCount++;
		}
		*numberOfInputFilesInList = fileNameIndex;
	}
	#ifdef GIA_MAIN_DEBUG
	//cout << "*numberOfInputFilesInList = " << *numberOfInputFilesInList << endl;
	#endif
	return result;
}

#endif




