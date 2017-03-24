/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is licensed under the GNU Affero General Public License
 * version 3, as published by the Free Software Foundation. The use of
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
 * File Name: NLCtranslatorCodeBlocksLogicalConditionsAdvanced.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2a1f 26-February-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR_CODEBLOCKS_LOGICAL_CONDITIONS_ADVANCED
#define HEADER_NLC_TRANSLATOR_CODEBLOCKS_LOGICAL_CONDITIONS_ADVANCED

#include "GIAentityNodeClass.hpp"
#include "GIAentityConnectionClass.hpp"
#include "NLCglobalDefs.hpp"
#include "NLCcodeBlockClass.hpp"
#include "NLCclassDefinitionClass.hpp"
#ifdef NLC_PREPROCESSOR
#include "NLCpreprocessor.hpp"	//required for NLCpreprocessorSentence
#include "NLCtranslatorCodeBlocksOperations.hpp"
#include "GIAquery.hpp"	//required for testReferencedEntityNodeForExactNameMatch2/traceEntityNode
#include "GIAtranslatorDefs.hpp"
#endif


#ifdef NLC_PREPROCESSOR
class NLCtranslatorCodeBlocksLogicalConditionsAdvancedClass
{
	private: NLCcodeBlockClassClass NLCcodeBlockClass;
	private: SHAREDvarsClass SHAREDvars;
	private: GIAtranslatorOperationsClass GIAtranslatorOperations;
	private: NLCtranslatorCodeBlocksOperationsClass NLCtranslatorCodeBlocksOperations;
	private: GIAqueryClass GIAquery;
	public: void initialiseLogicalConditionLevelRecordArray(const bool newUseNLCpreprocessor);
	public: bool getUseNLCpreprocessor();
	public: NLCcodeblock* getCodeBlockAtPreviousLogicalConditionBaseLevelArray(const int index);
	public: void setCodeBlockAtPreviousLogicalConditionBaseLevelArray(const int index, NLCcodeblock* codeBlockToSet);
	#endif

	#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
	public: bool searchForEquivalentSubnetToIfStatement(GIAentityNode* entityCompareNetworkIndex, GIAentityNode* entity, const bool compareConcepts);
	#endif
};


#endif
