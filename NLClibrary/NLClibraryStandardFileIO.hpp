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
 * File Name: NLClibraryStandardFileIO.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q12d 22-August-2015
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#ifndef HEADER_NLC_LIBRARY_STANDARD_FILEIO
#define HEADER_NLC_LIBRARY_STANDARD_FILEIO

#include "../NLClibrary/NLClibraryGenericEntityClass.hpp"
#include "../source/XMLparserClass.h"

#define NLC_USE_LIBRARY_FILEIO_FUNCTION_ACTIONOBJECT_FILE_NAME "file"
#define NLC_USE_LIBRARY_FILEIO_FUNCTION_DEFAULT_FILE_NAME_PREPEND "NLCfileIO"
#define NLC_USE_LIBRARY_FILEIO_FUNCTION_DEFAULT_FILE_NAME_APPEND_XML ".xml"
#define NLC_USE_LIBRARY_FILEIO_FUNCTION_DEFAULT_FILE_NAME_APPEND_CSV ".csv"
#define NLC_USE_LIBRARY_FILEIO_FUNCTION_DEFAULT_FILE_NAME_APPEND_TXT ".txt"
#define NLC_USE_LIBRARY_FILEIO_FUNCTION_ACTION_CONDITION_FROM_NAME "from"
#define NLC_USE_LIBRARY_FILEIO_FUNCTION_ACTION_CONDITION_TO_NAME "to"
#define NLC_USE_LIBRARY_FILEIO_XML_ATTRIBUTENAME_CONDITION "condition"
#define NLC_USE_LIBRARY_FILEIO_XML_ATTRIBUTENAME_LISTNAME "name"
#define NLC_USE_LIBRARY_FILEIO_XML_WRITE_PROPERTY_LISTS
//#define NLC_USE_LIBRARY_FILEIO_XML_WRITE_CONDITION_LISTS
//#define NLC_USE_LIBRARY_FILEIO_XML_WRITE_ACTION_LISTS
#define NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
	#define NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_PROPERTY_LIST_ALL "propertyLists"
	#define NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_CONDITION_LIST_ALL "conditionLists"
	#define NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTION_LIST_ALL "actionLists"
	#define NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONINCOMING_LIST_ALL "actionIncomingLists"
	#define NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONOBJECT_LIST_ALL "actionObjectLists"
	#define NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONSUBJECT_LIST_ALL "actionSubjectLists"	
	#define NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_PROPERTY_LIST "propertyList"
	#define NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_CONDITION_LIST "conditionList"
	#define NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTION_LIST "actionList"
	#define NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONINCOMING_LIST "actionIncomingList"
	#define NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONOBJECT_LIST "actionObjectList"
	#define NLC_USE_LIBRARY_FILEIO_XML_TAGNAME_ACTIONSUBJECT_LIST "actionSubjectList"
#endif
#define NLC_USE_LIBRARY_FILEIO_FILETYPE_XML (1)	//xml file
#define NLC_USE_LIBRARY_FILEIO_FILETYPE_FLAT (2)	//flat file (text/csv file)
#define NLC_USE_LIBRARY_FILEIO_FILETYPE_DEFAULT (NLC_USE_LIBRARY_FILEIO_FILETYPE_XML)
#define NLC_USE_LIBRARY_GENERATE_OBJECT_BY_NAME_FUNCTION_NAME "generateObjectByName"	
#define NLC_USE_LIBRARY_FILEIO_FLAT_DELIMITER_COMMA ","
#define NLC_USE_LIBRARY_FILEIO_FLAT_DELIMITER_TAB "\t"
#define NLC_USE_LIBRARY_FILEIO_FLAT_DELIMITER_DEFAULT (NLC_USE_LIBRARY_FILEIO_FLAT_DELIMITER_TAB)
#define NLC_USE_LIBRARY_FILEIO_FLAT_NUMBER_OF_DELIMITERS (2)
static string nlcLibraryFileIOflatFileDelimiters[NLC_USE_LIBRARY_FILEIO_FLAT_NUMBER_OF_DELIMITERS] = {NLC_USE_LIBRARY_FILEIO_FLAT_DELIMITER_COMMA, NLC_USE_LIBRARY_FILEIO_FLAT_DELIMITER_TAB};
#define NLC_USE_LIBRARY_FILEIO_FLAT_NUMBER_OF_NUMERICAL_CHARACTERS (10)
static char nlcLibraryFileIOflatFileNumericalCharacters[NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_NUMERICAL_CHARACTERS_NUMBER_OF_TYPES] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
#define NLC_USE_LIBRARY_FILEIO_FLAT_NUMBER_OF_ALPHABETIC_CHARACTERS (53)
static char nlcLibraryFileIOflatFileAlphabeticCharacters[NLC_USE_LIBRARY_FILEIO_FLAT_NUMBER_OF_ALPHABETIC_CHARACTERS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_'};
#define NLC_ALLOW_ALPHANUMERIC_CLASS_NAMES
#define NLC_USE_LIBRARY_FILEIO_FLAT_NULL_PROPERTY_VALUE "0"


//writeFunction() limitation: only supports NLC_USE_ADVANCED_REFERENCING
void writeFunction(vector<NLCgenericEntityClass*>& writeClassList, vector<NLCgenericEntityClass*>& writeObjectClassList);
#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_PROPERTY_LISTS
void writeXMLfilePropertyList(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList);
	void writeXMLfileVectorList(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList, string listName);
		#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
		XMLparserTag* createVectorListTagWithLowerLevel(XMLparserTag* currentTagInList, string tagName, vector<NLCgenericEntityClass*>* vectorClassList);
		#endif
#endif
#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_CONDITION_LISTS
void writeXMLfileConditionListRecurse(XMLparserTag* firstTagInList, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* writeObjectClassMapList);
	void writeXMLfileMapList(XMLparserTag* firstTagInList, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* writeObjectClassMapList, string listName);
		#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
		XMLparserTag* createMapListTagWithLowerLevel(XMLparserTag* currentTagInList, string tagName, NLCgenericEntityClass*>* writeObjectClassMapList);
		#endif
#endif
#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_ACTION_LISTS
void writeXMLfileActionListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList);
void writeXMLfileActionIncomingListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList);
void writeXMLfileActionSubjectListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList);
void writeXMLfileActionObjectListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList);
#endif
void writeXMLfileObject(XMLparserTag* firstTagInList, NLCgenericEntityClass* writeObject);
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
	XMLparserTag* createAllListTagWithLowerLevel(XMLparserTag* currentTagInList, string tagName);
	#endif

void readFunction(vector<NLCgenericEntityClass*>& readClassList, vector<NLCgenericEntityClass*>& readObjectClassList);
bool readXMLfileToNLCpropertyLists(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList);
#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_PROPERTY_LISTS
bool readXMLfilePropertyList(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList);
	bool readXMLfileVectorList(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList, string listName);
#endif
#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_CONDITION_LISTS
bool readXMLfileConditionListRecurse(XMLparserTag* firstTagInList, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* readObjectClassMapList);
	bool readXMLfileMapList(XMLparserTag* firstTagInList, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* readObjectClassMapList, string listName);
#endif
#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_ACTION_LISTS
void readXMLfileActionListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList);
void readXMLfileActionIncomingListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList);
void readXMLfileActionSubjectListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList);
void readXMLfileActionObjectListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList);
#endif
void readXMLfileObject(XMLparserTag* firstTagInList, NLCgenericEntityClass* readObject);
	bool readFileObjectVectorListAll(XMLparserTag* currentTagInList, NLCgenericEntityClass* readObject, string vectorListAllTagName, string vectorListTagName);
	#ifdef NLC_USE_LIBRARY_FILEIO_XML_WRITE_CONDITION_LISTS
	bool readFileObjectMapListAll(XMLparserTag* currentTagInList, NLCgenericEntityClass* readObject, string vectorListAllTagName, string vectorListTagName);
	#endif

bool writeNLCflatFilePropertyLists(string fileName, vector<NLCgenericEntityClass*>* writeObjectClassList, string delimiter);
bool readNLCflatfilePropertyLists(string fileName, vector<NLCgenericEntityClass*>* readObjectClassList, string delimiter);
bool variableNameIsAcceptableNLCclassName(string currentVariableName);	
	bool stringContainsNumbers(string s);		
	bool stringContainsAlphabetic(string s);

#endif

