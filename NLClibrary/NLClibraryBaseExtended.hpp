/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryBaseExtended.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2f3a 10-April-2018
 * Requirements: requires C++ code to be generated by NLC
 * Description: Base NLC library Functions (no generic property and condition lists) 
 * Note: These extended functions are not generally hard coded
 *
 *******************************************************************************/
 
#ifndef HEADER_NLC_LIBRARY_BASE_EXTENDED
#define HEADER_NLC_LIBRARY_BASE_EXTENDED

#include "NLClibraryGenericEntityClass.hpp"

#ifdef NLC_LIBRARY_BASE_EXTENDED
template <class E1, class E2>
void addProperty(E1* E1Instance, vector<E2*>* E2propertyList, E2* E2Instance);
template <class E1, class E2, class E3>
#ifdef NLC_CONDITION_LISTS_VECTOR
void addCondition(E1* E1Instance, vector<pair<E2*, E3*>*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant as it can be generated from new E2()
#else
void addCondition(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant as it can be generated from new E2()
#endif
#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
template <class E1, class E2, class E3>
#ifdef NLC_CONDITION_LISTS_VECTOR
void addConditionInverse(E1* E1Instance, vector<pair<E2*, E3*>*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant as it can be generated from new E2()
#else
void addConditionInverse(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant as it can be generated from new E2()
#endif
#endif
template <class E1, class E2>
void addActionSubject(E1* E1action, E2* E2actionSubject, vector<E1*>* E1actionList, vector<E2*>* E2actionSubjectList);
template <class E1, class E2>
void addActionObject(E1* E1action, E2* E2actionObject, vector<E1*>* E1actionIncomingList, vector<E2*>* E2actionObjectList);

template <class E1, class E2>
void removeProperty(E1* E1Instance, vector<E2*>* E2propertyList, E2* E2Instance);
template <class E1, class E2, class E3>
#ifdef NLC_CONDITION_LISTS_VECTOR
void removeCondition(E1* E1Instance, vector<pair<E2*, E3*>*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant as it can be generated from new E2()
#else
void removeCondition(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant as it can be generated from new E2()
#endif
template <class E1, class E2>
void removeProperties(E1* E1Instance, vector<E2*>* E2propertyList, E2* E2Instance);
template <class E1, class E2, class E3>
#ifdef NLC_CONDITION_LISTS_VECTOR
void removeConditions(E1* E1Instance, vector<pair<E2*, E3*>*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant as it can be generated from new E2()
#else
void removeConditions(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant as it can be generated from new E2()
#endif

#ifdef NLC_ENUM_LISTS
#ifdef NLC_ENUM_LISTS_PROPERTIES
template <class E1, class E2>
void addEnumProperty(E1* E1Instance, E2* E2Instance, vector<NLCgenericEntityClass*>* propertyList);
template <class E1, class E2>
void clearExistingEnumProperty(E1* E1Instance, E2* E2Instance);
#endif
#ifdef NLC_ENUM_LISTS_CONDITIONS
template <class E1, class E2, class E3>
#ifdef NLC_CONDITION_LISTS_VECTOR
void addEnumCondition(E1* E1Instance, E2* E2Instance, E3* E3Instance, vector<pair<NLCgenericEntityClass*, NLCgenericEntityClass*>*>* conditionList);
#else
void addEnumCondition(E1* E1Instance, E2* E2Instance, E3* E3Instance, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList);
#endif
template <class E1, class E2, class E3>
void clearExistingEnumCondition(E1* E1Instance, string E2className, E3* E3Instance);
#endif
#endif

template <class E1>
E1* addNewEntityToLocalList(vector<E1*>* E1classList);
template <class E1>
void addEntityToLocalList(vector<E1*>* E1classList, E1* E1Instance);

template <class E1>
bool removeItemFromVectorList(vector<E1*>* vectorList, E1* itemToRemove);
template <class E1, class E2>
#ifdef NLC_CONDITION_LISTS_VECTOR
bool removeItemFromConditionList(vector<pair<E1*, E2*>*>* unorderedMap, string conditionName, pair<E1*, E2*>*itemToRemove);
#else
bool removeItemFromConditionList(unordered_map<E1*, E2*>* unorderedMap, string conditionName, pair<E1*, E2*>*itemToRemove);
/*
template <class E1, class E2>
bool removeObjectFromConditionList(unordered_map<E1*, E2*>* unorderedMap, E2 *objectToRemove);
*/
#endif

#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_MERGERS
template <class E1>
void findAndRemoveEntityFromLocalList(vector<E1*>* E1instanceList, E1* E1Instance);
template <class E1, class E2>
void findAndReplaceEntityInLocalList(vector<E1*>* E1instanceList, E1* E1Instance, E2* E2Instance);
template <class E1, class E2>
void mergeEntity1AttributesIntoEntity2(E1* E1Instance, E2* E2Instance);
#endif

#endif

#include "NLClibraryBaseExtended.cpp"

#endif
