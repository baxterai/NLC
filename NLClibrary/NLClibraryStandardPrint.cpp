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
 * File Name: NLClibraryStandardPrint.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2f10a 19-April-2018
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#include "NLClibraryStandardPrint.hpp"

void printFunction(vector<NLCgenericEntityClass*>& printClassList, vector<NLCgenericEntityClass*>& printObjectClassList)
{
	for(vector<NLCgenericEntityClass*>::iterator iter1 = printObjectClassList.begin(); iter1 < printObjectClassList.end(); iter1++) 
	{
		NLCgenericEntityClass* printObject = *iter1;
		printEntity(printObject, 0);
	}
}

void printEntity(NLCgenericEntityClass* printObject, int level)
{
	#ifdef NLC_MATH_OBJECTS
	if(printObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL)
	{
		cout << createIndentationBasedOnLevel(level);
		print(printObject->mathObjectNumericalValue);
	}
	#ifdef NLC_MATH_OBJECTS_ADVANCED
	#ifdef NLC_MATH_OBJECTS_STRING
	else if(printObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING)
	{
		cout << createIndentationBasedOnLevel(level);
		print(printObject->mathObjectStringValue);
	}
	#endif
	#ifdef NLC_MATH_OBJECTS_BOOLEAN
	else if(printObject->mathObjectType == NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN)
	{
		cout << createIndentationBasedOnLevel(level);
		print(printObject->mathObjectBooleanValue);
	}
	#endif
	#endif
	else
	{ 
	#endif
		cout << createIndentationBasedOnLevel(level);
		cout << printObject->name << endl;	//print the entity name
		
		for(unordered_map<string, vector<NLCgenericEntityClass*>*>::iterator iter1 = printObject->propertyLists.begin(); iter1 != printObject->propertyLists.end(); iter1++) 
		{
			vector<NLCgenericEntityClass*>* propertyList = iter1->second;
			for(vector<NLCgenericEntityClass*>::iterator iter2 = propertyList->begin(); iter2 < propertyList->end(); iter2++) 
			{
				NLCgenericEntityClass* property = *iter2;
				printEntity(property, level+1);
			}
		}

		#ifdef NLC_LIBRARY_STANDARD_PRINT_CONDITIONS_TEMP
		for(unordered_map<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>::iterator iter1 = printObject->conditionLists.begin(); iter1 != printObject->conditionLists.end(); iter1++) 
		{
			unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList = iter1->second;
			for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter2 = conditionList->begin(); iter2 != conditionList->end(); iter2++) 
			{
				NLCgenericEntityClass* condition = iter2->first;
				NLCgenericEntityClass* conditionObject = iter2->second;	//conditionObject
				#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
				if(!(condition->inverseConditionTwoWay))	//do not write inverse conditions
				{
				#endif
					cout << createIndentationBasedOnLevel(level+1);
					cout << condition->name << endl;	//print the entity name
					printEntity(conditionObject, level+2);
				#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
				}
				#endif				
			}
		}	
		#endif	

	#ifdef NLC_MATH_OBJECTS
	}
	#endif
}

string createIndentationBasedOnLevel(int level)
{
	string indentation = "";
	for(int i=0; i<level; i++)
	{
		indentation = indentation + CHAR_TAB;
	}
	return indentation;
}

//mathText function (macro)
void print(double mathObjectNumericalValue)
{
	cout << mathObjectNumericalValue << endl;	//print the mathText mathObjectNumericalValue
}

#ifdef NLC_MATH_OBJECTS_ADVANCED
#ifdef NLC_MATH_OBJECTS_STRING
void print(string mathObjectStringValue)
{
	cout << mathObjectStringValue << endl;	//print the mathText mathObjectStringValue
}
#endif
#ifdef NLC_MATH_OBJECTS_BOOLEAN
void print(bool boolValue)
{
	//cout << boolValue << endl;	//print the mathText boolValue
	if(boolValue)
	{
		cout << NLC_MATH_OBJECTS_BOOLEAN_VALUE_TRUE << endl;	//print the mathText boolValue
	}
	else
	{
		cout << NLC_MATH_OBJECTS_BOOLEAN_VALUE_FALSE << endl;	//print the mathText boolValue
	}
}
#endif
#endif

