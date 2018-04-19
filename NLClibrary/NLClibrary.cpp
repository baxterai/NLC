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
 * File Name: NLClibrary.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2f10a 19-April-2018
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/

#include "NLClibrary.hpp"

void initialiseNLClibrary()
{
 	XMLparserTag* NLCfirstTagInXMLfile = new XMLparserTag();
	if(!parseNLCrulesXMLfile(NLCfirstTagInXMLfile))
	{
		cout << "error: NLCrules.xml file not detected" << endl;
		exit(0);
	}

	#ifdef NLC_ENUM_LISTS
	initiateEnumTypeTables(NLCfirstTagInXMLfile);
	#endif
}


//copied from XMLrulesClass.cpp
bool parseNLCrulesXMLfile(XMLparserTag* NLCfirstTagInXMLfile)
{
	bool result = true;

	if(!XMLparserClassClass().readXMLfile(NLC_RULES_XML_FILE_NAME, NLCfirstTagInXMLfile))
 	{
		result = false;
	}
	
	return result;
}

#ifdef NLC_ENUM_LISTS
void initiateEnumTypeTables(XMLparserTag* NLCfirstTagInXMLfile)
{
	unordered_map<string, string>* enumTypeTableCurrent = NULL;
	
	bool result = true;
	XMLparserTag* firstTagInRulesTag = XMLparserClassClass().parseTagDownALevel(NLCfirstTagInXMLfile, RULES_XML_TAG_rules2, &result);
	if(result)
	{
		XMLparserTag* currentTag = firstTagInRulesTag;
		bool foundEnumTag = false;
		XMLparserTag* firstTagInEnumTag = NULL;
		while((currentTag->nextTag != NULL) && !foundEnumTag)
		{
			if(currentTag->name == RULES_XML_TAG_enum)
			{
				foundEnumTag = true;
				firstTagInEnumTag = XMLparserClassClass().parseTagDownALevel(currentTag, RULES_XML_TAG_enum, &result);
			}
			currentTag = currentTag->nextTag;
		}
		if(foundEnumTag)
		{
			XMLparserTag* currentEntityTag = firstTagInEnumTag;
			while(currentEntityTag->nextTag != NULL)
			{
				if(currentEntityTag->name == RULES_XML_TAG_entity)
				{
					string currentEntity = "";
					if(currentEntityTag->firstAttribute->name == RULES_XML_ATTRIBUTE_name)
					{
						currentEntity = currentEntityTag->firstAttribute->value;
						#ifdef NLC_ENUM_LISTS_PROPERTIES
						if(currentEntity == NLC_ENUM_LIST_ENTITY_NAME_PROPERTY)
						{
							enumTypeTableCurrent = &enumTypeTableProperties;
						}
						#endif
						#ifdef NLC_ENUM_LISTS_CONDITIONS
						else if(currentEntity == NLC_ENUM_LIST_ENTITY_NAME_CONDITION)
						{
							enumTypeTableCurrent = &enumTypeTableConditions;
						}
						#endif
						#ifdef NLC_ENUM_LISTS_ACTIONS
						else if(currentEntity == NLC_ENUM_LIST_ENTITY_NAME_ACTION)
						{
							enumTypeTableCurrent = &enumTypeTableActions;
						}
						#endif
						else
						{
							cout << "initiateEnumTypeTables{} error: entity attribute name illegal value found in NLCrules.xml: " << currentEntityTag->firstAttribute->value << endl;
						}
					}
					else
					{
						cout << "initiateEnumTypeTables{} error: entity attribute name not found in NLCrules.xml" << endl;
					}
					
					XMLparserTag* firstTagInEntityTag = XMLparserClassClass().parseTagDownALevel(currentEntityTag, RULES_XML_TAG_entity, &result);
					XMLparserTag* currentTypeTag = firstTagInEntityTag;
					while(currentTypeTag->nextTag != NULL)
					{
						if(currentTypeTag->name == RULES_XML_TAG_type)
						{	
							string currentType = "";
							if(currentTypeTag->firstAttribute->name == RULES_XML_ATTRIBUTE_name)
							{
								currentType = currentTypeTag->firstAttribute->value;
							}
							else
							{
								cout << "initiateEnumTypeTables{} error: type attribute name not found in NLCrules.xml" << endl;
							}	
							
							XMLparserTag* firstTagInTypeTag = XMLparserClassClass().parseTagDownALevel(currentTypeTag, RULES_XML_TAG_type, &result);
							XMLparserTag* currentInstanceTag = firstTagInTypeTag;
							while(currentInstanceTag->nextTag != NULL)
							{
								if(currentTypeTag->name == RULES_XML_TAG_type)
								{	
									string currentInstance = "";
									if(currentInstanceTag->firstAttribute->name == RULES_XML_ATTRIBUTE_name)
									{
										currentInstance = currentInstanceTag->firstAttribute->value;
									}
									else
									{
										cout << "initiateEnumTypeTables{} error: type attribute name not found in NLCrules.xml" << endl;
									}

									//#ifdef DEBUG_NLC_ENUM_LISTS
									cout << "currentEntity = " << currentEntity << endl;
									cout << "currentType = " << currentType << endl;
									cout << "currentInstance = " << currentInstance << endl; 
									//#endif
									enumTypeTableCurrent->insert(pair<string, string>(currentInstance, currentType));
								}
								else
								{
									cout << "initiateEnumTypeTables{} error: type tag not found in NLCrules.xml" << endl;
								}	
								currentInstanceTag = currentInstanceTag->nextTag;					
							}
						}
						else
						{
							cout << "initiateEnumTypeTables{} error: type tag not found in NLCrules.xml" << endl;
						}		
						currentTypeTag = currentTypeTag->nextTag;				
					}				
				}
				else
				{
					cout << "initiateEnumTypeTables{} error: entity tag not found in NLCrules.xml" << endl;
				}
				currentEntityTag = currentEntityTag->nextTag;
			}
		}
	}
}
#endif
	
