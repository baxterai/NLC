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
 * File Name: NLClibraryBase.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1u15d 03-October-2016
 * Requirements: requires C++ code to be generated by NLC
 * Description: Base NLC library Functions (no generic property and condition lists) 
 * Note: These functions are hard coded and dual licensed under AGPLv3 and BAI Commercial
 *
 *******************************************************************************/
 
//Base NLC library Functions (no generic property and condition lists)

#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
template <class E1, class E2>
void addToCategoryIfPassPluralDefiniteReferencingTests(vector<E1*>& entityCategoryList, E2* entity0)
{
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_ADD_DUPLICATES
	if(!(find(entityCategoryList.begin(), entityCategoryList.end(), entity0) != entityCategoryList.end()))
	{
	#endif
		entityCategoryList.push_back(entity0);
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_ADD_DUPLICATES
	}
	#endif
}
#endif

#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
template <class E1, class E2>
vector<E2*>& castVector(vector<E1*>& E1List)
{
	vector<E2*>& E2List = reinterpret_cast<vector<E2*>&>(E1List);
	return E2List;
}

//not currently used
#ifdef NLC_CONDITION_LISTS_VECTOR
template <class E1, class E2, class E3, class E4>
vector<pair<E3*, E4*>*>& castVectorPair(vector<pair<E1*, E2*>*>& E1E2List)
{
	vector<pair<E3*, E4*>*>& E3E4List = reinterpret_cast<vector<pair<E3*, E4*>*>&>(E1E2List);
	return E3E4List;
}
#else
template <class E1, class E2, class E3, class E4>
unordered_map<E3*, E4*>& castUnorderedMap(unordered_map<E1*, E2*>& E1E2List)
{
	unordered_map<E3*, E4*>& E3E4List = reinterpret_cast<unordered_map<E3*, E4*>&>(E1E2List);
	return E3E4List;
}
#endif
#endif




#ifdef NLC_USE_ADVANCED_REFERENCING
#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
template <class E1, class E2>
void addToCategoryIfPassSingularDefiniteReferencingTests(vector<E1*>& entityCategoryList, E2* entity0)
{
	#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
	if(!(entity0->lastSentenceReferenced.empty()))
	{
	#endif
		if(entityCategoryList.empty())
		{
			entityCategoryList.push_back(entity0);
		}
		else
		{
			#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
			if(entity0->lastSentenceReferenced.top() > (entityCategoryList.back())->lastSentenceReferenced.top())
			#else
			if(entity0->lastSentenceReferenced > (entityCategoryList.back())->lastSentenceReferenced)			
			#endif
			{
				entityCategoryList.clear();
				entityCategoryList.push_back(entity0);
			}
			#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
			else if(entity0->lastSentenceReferenced.top() == (entityCategoryList.back())->lastSentenceReferenced.top())
			#else
			else if(entity0->lastSentenceReferenced == (entityCategoryList.back())->lastSentenceReferenced)			
			#endif
			{
				#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_ADD_DUPLICATES
				if(!(find(entityCategoryList.begin(), entityCategoryList.end(), entity0) != entityCategoryList.end()))
				{
				#endif
					entityCategoryList.push_back(entity0);
				#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_ADD_DUPLICATES
				}
				#endif
			}
			else
			{
			}
		}
	#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
	}
	#endif
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_WARNING
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_WARNING_PLACE_IN_NLC_PREDEFINED_FUNCTION_ADDTOCATEGORYIFPASSSINGULARDEFINITEREFERENCINGTESTS
	//Singular definite plurality tests
	if(entityCategoryList.size() > 1)
	{
		cout << "Execution warning: multiple objects have been added to a singular definite variable (category) - should the entity have been defined as plural instead?" << endl;
	}
	#endif
	#endif
}
#endif

#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
template <class E1>
void findAliasAndAddToCategoryList(vector<E1*>& E1List, string aliasName, vector<E1*>& E1CategoryList)
{
	for(typename vector<E1*>::iterator iter1 = E1List.begin(); iter1 < E1List.end(); iter1++) 
	{
		E1* NLCgenericEntity = *iter1;
		if((find(NLCgenericEntity->aliasList.begin(), NLCgenericEntity->aliasList.end(), aliasName) != NLCgenericEntity->aliasList.end()))
		{
			E1CategoryList.push_back(NLCgenericEntity);
		}
	}
}

template <class E1>
bool findAlias(E1* E1Instance, string aliasName)
{
	bool result = false;
	if((find(E1Instance->aliasList.begin(), E1Instance->aliasList.end(), aliasName) != E1Instance->aliasList.end()))
	{
		result = true;
	}
	return result;
}
#endif


#endif



