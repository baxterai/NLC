/*******************************************************************************
 *
 * This file is part of NLC.
 *
 * NLC is commercially licensed software. It may not be redistributed,
 * and may only be used by a registered licensee.
 *
 * NLC is sold in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * BAI Commercial License for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You will have received a copy of the BAI Commercial License
 * along with NLC. For more information, visit <http://www.baxterai.com>
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryBaseExtended.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q1e 11-August-2015
 * Requirements: requires C++ code to be generated by NLC
 * Description: Base NLC library Functions (no generic property and condition lists) 
 * Note: These extended functions are not generally hard coded (unlike those in NLClibraryBase) but are still dual licensed under AGPL
 *
 *******************************************************************************/
 
#ifndef HEADER_NLC_LIBRARY_BASE_EXTENDED
#define HEADER_NLC_LIBRARY_BASE_EXTENDED

#include "NLClibraryGenericEntityClass.hpp"

#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
template <class E1, class E2>
void addProperty(E1* E1Instance, vector<E2*>* E2propertyList, E2* E2Instance);
template <class E1, class E2, class E3>
void addCondition(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant
template <class E1, class E2>
void addActionSubject(E1* E1action, E2* E2actionSubject, vector<E1*>* E1actionList, vector<E2*>* E2actionSubjectList);
template <class E1, class E2>
void addActionObject(E1* E1action, E2* E2actionObject, vector<E1*>* E1actionIncomingList, vector<E2*>* E2actionObjectList);

template <class E1, class E2>
void removeProperty(E1* E1Instance, vector<E2*>* E2propertyList, E2* E2Instance);
template <class E1, class E2, class E3>
void removeCondition(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant
template <class E1, class E2>
void removeProperties(E1* E1Instance, vector<E2*>* E2propertyList, E2* E2Instance);
template <class E1, class E2, class E3>
void removeConditions(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant

#ifdef NLC_USE_ENUM_LISTS
#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
template <class E1, class E2>
void addEnumProperty(E1* E1Instance, E2* E2Instance, vector<NLCgenericEntityClass*>* propertyList);
template <class E1, class E2>
void clearExistingEnumProperty(E1* E1Instance, E2* E2Instance);
#endif
#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
template <class E1, class E2, class E3>
void addEnumCondition(E1* E1Instance, E2* E2Instance, E3* E3Instance, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList);
template <class E1, class E2, class E3>
void clearExistingEnumCondition(E1* E1Instance, string E2className, E3* E3Instance);
#endif
#endif

template <class E1>
E1* addNewEntityToLocalList(vector<E1*>* E1classList);
template <class E1>
void addNewEntityToLocalList(vector<E1*>* E1classList, E1* E1Instance);

template <class E1>
bool removeItemFromVectorList(vector<E1*>* vectorList, E1* itemToRemove);
template <class E1, class E2>
bool removeItemFromUnorderedMap(unordered_map<E1*, E2*>* unorderedMap, string conditionName, pair<E1*, E2*>*itemToRemove);
/*
template <class E1, class E2>
bool removeObjectFromUnorderedMap(unordered_map<E1*, E2*>* unorderedMap, E2 *objectToRemove);
*/

#endif

#include "NLClibraryBaseExtended.cpp"

#endif
