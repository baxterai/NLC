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
 * File Name: NLCtranslatorCodeBlocksLogicalConditions.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1h2a 27-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR_CODEBLOCKS_LOGICAL_CONDITIONS
#define HEADER_NLC_TRANSLATOR_CODEBLOCKS_LOGICAL_CONDITIONS

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#include "GIAglobalDefs.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"
#include "NLCglobalDefs.h"
#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"
#ifdef NLC_USE_PREPROCESSOR
#include "NLCpreprocessor.h"	//required for NLCsentence
#endif


#ifdef NLC_USE_PREPROCESSOR
void initialiseLogicalConditionLevelRecordArray(bool newUseNLCpreprocessor);
bool getUseNLCpreprocessor();
int getCurrentLogicalConditionLevel();
void setCurrentLogicalConditionLevel(int value);
NLCcodeblock * getCodeBlockAtPreviousLogicalConditionBaseLevelArray(int index);
void setCodeBlockAtPreviousLogicalConditionBaseLevelArray(int index, NLCcodeblock * codeBlockToSet);
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
bool getCurrentSentenceContainsLogicalCondition();
void setCurrentSentenceContainsLogicalCondition(bool value);
int getCurrentLogicalConditionCase(int level);
#endif
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
bool generateCodeBlocksPart2logicalConditions(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName, NLCsentence * currentNLCsentenceInList);
	bool searchForEquivalentSubnetToIfStatement(GIAentityNode * entityCompareConcept, GIAentityNode * entity);
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
	void addNewLogicalCondition(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * currentLogicalConditionObject, int sentenceIndex, int logicalOperation, int * logicalConditionConjunctionIndex, NLClogicalConditionConjunction * logicalConditionConjunctionArray, GIAentityNode * previousLogicalConditionConjunction);
		void checkConditionForLogicalCondition(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * conditionEntity, int sentenceIndex, int logicalOperation, int * logicalConditionConjunctionIndex, NLClogicalConditionConjunction * logicalConditionConjunctionArray);
	#endif
	void tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperation(GIAentityNode * entity, int sentenceIndex, bool tagOrUntag);
#ifdef NLC_USE_PREPROCESSOR
bool setCurrentCodeBlockInTreeToStartOfIfStatement(NLCcodeblock ** currentCodeBlockInTree, NLCcodeblock ** firstCodeBlockAtStartOfIfStatement, NLCcodeblock * firstCodeBlockAtStartOfElseStatement, bool elseIfDetected, bool elseDetected);
bool restoreCurrentCodeBlockInTreeToStartOfElseStatement(NLCcodeblock ** currentCodeBlockInTree, NLCcodeblock * firstCodeBlockAtStartOfIfStatement, NLCcodeblock * firstCodeBlockAtStartOfElseStatement, bool elseIfDetected, bool elseDetected, NLCcodeblock ** previousCodeBlockInTree);
#endif
#endif

#endif