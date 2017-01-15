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
 * File Name: NLClibraryGenericClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1p13b 03-August-2015
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#include "NLClibraryGenericClass.h"

NLCgenericEntityClass::NLCgenericEntityClass(void)
{
	name = "NLCgenericEntity";
	#ifdef NLC_USE_MATH_OBJECTS
	value = 0.0;
	#endif
	
	#ifdef NLC_USE_ENUM_LISTS 
	enumType = NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM;
	#endif
};

#ifdef NLC_USE_ENUM_LISTS
#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
unordered_map<string, string> enumTypeTableProperties;	//generated from NLCrules.xml (used for quick determination of enumType based on entity name)
#endif
#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
unordered_map<string, string> enumTypeTableConditions;	//generated from NLCrules.xml (used for quick determination of enumType based on entity name)
#endif
#ifdef NLC_USE_ENUM_LISTS_ACTIONS
unordered_map<string, string> enumTypeTableActions;	//generated from NLCrules.xml (used for quick determination of enumType based on entity name)
#endif
#endif

