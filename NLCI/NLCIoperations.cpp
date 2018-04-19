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
 * File Name: NLCIoperations.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2e4a 15-January-2018
 * Requirements: 
 *
 *******************************************************************************/

#include "NLCIoperations.hpp"
#include "NLCmain.hpp"
#include "GIAmain.hpp"
#include "GIApreprocessor.hpp"

#ifdef GIA_NEURAL_NETWORK
#include "ANNdraw.hpp"
#endif

#include <QTextCodec>

QColor NLCIoperationsClass::generateColourQ(int colourIndex)
{
	colour col;
	LDreferenceClass.convertLdrawColourToDatFileRGB(colourIndex, &col);
	return generateColourQ(&col);
}

QColor NLCIoperationsClass::generateColourQ(colour* col)
{
	return QColor(col->r, col->g, col->b);
}

#ifdef USE_NLCI
bool NLCIoperationsClass::executeNLCwrapper(GIAtranslatorVariablesClass* translatorVariablesTemplate, const bool useNLCinputFileList, const string NLCinputFileListName)
{
	NLCfunction* firstNLCfunctionInList = NULL;
	return executeNLCwrapper(translatorVariablesTemplate, firstNLCfunctionInList, useNLCinputFileList, NLCinputFileListName);
	
}
bool NLCIoperationsClass::executeNLCwrapper(GIAtranslatorVariablesClass* translatorVariablesTemplate, NLCfunction* firstNLCfunctionInList)
{
	bool useNLCinputFileList = false;
	string NLCinputFileListName = "inputFileList.nlcp";
	return executeNLCwrapper(translatorVariablesTemplate, firstNLCfunctionInList, useNLCinputFileList, NLCinputFileListName);
	
}
bool NLCIoperationsClass::executeNLCwrapper(GIAtranslatorVariablesClass* translatorVariablesTemplate, NLCfunction* firstNLCfunctionInList, const bool useNLCinputFileList, const string NLCinputFileListName)
{
	bool result = true;

	string inputFolderLocal = NLCI_NLC_INPUT_FOLDER;
	string outputFolderLocal = NLCI_NLC_OUTPUT_FOLDER;
	
	int NLPfeatureParser = NLCI_NLC_NLP_FEATURE_PARSER;
	int NLPdependencyRelationsParser = NLCI_NLC_NLP_DEPENDENCY_RELATIONS_PARSER;
	bool NLPrelexCompatibilityMode = false;			//(assumes) Relex dependency relations are(/were) generated by Relex parser in Stanford compatibility mode
	bool NLPassumePreCollapsedStanfordRelations = false;	//(assumes) Relex dependency relations are(/were) generated by Relex parser in Stanford compatibility mode / assumes Relex dependency relations were generated by GIA in cff
	#ifdef GIA_NLP_CLIENT_SERVER
	bool NLPclient = NLCI_NLC_NLP_CLIENT;
	#endif

	string NLPexeFolderArray[GIA_NLP_PARSER_NUMBER_OF_TYPES];
	NLPexeFolderArray[GIA_NLP_PARSER_RELEX] = NLCI_NLC_NLP_RELEX_FOLDER;
	NLPexeFolderArray[GIA_NLP_PARSER_STANFORD_CORENLP] = NLCI_NLC_NLP_STANFORD_CORE_NLP_FOLDER;
	NLPexeFolderArray[GIA_NLP_PARSER_STANFORD_PARSER] = NLCI_NLC_NLP_STANFORD_PARSER_FOLDER;

	bool useInputTextPlainTXTFile = false;	//passing data instead
	string inputTextPlainTXTfileName = "inputText.nlc";
	
	string outputTextNLPrelationXMLfileName = "inputNLPrelation.xml";
	string outputTextNLPfeatureXMLfileName = "inputNLPfeature.xml";
	bool useOutputTextCFFFile = false;
	string outputTextCFFFileName = "outputNLP.cff";
	bool useOutputTextXMLFile = false;
	string outputTextXMLFileName = "semanticNet.xml";
	bool useOutputTextCXLFile = false;
	string outputTextCXLFileName = "semanticNet.cxl";
	bool useOutputTextLDRFile = false;
	string outputTextLDRFileName = "semanticNet.ldr";
	bool useOutputTextPPMFile = false;
	string outputTextPPMFileName = "semanticNet.ppm";
	bool useOutputTextSVGFile = false;
	string outputTextSVGFileName = "semanticNet.svg";

	bool useOutputTextAllFile = NLCI_NLC_USE_OUTPUT_TEXT_ALL_FILE;
	string outputTextAllFileName = NLCI_NLC_OUTPUT_TEXT_ALL_FILE_NAME;

	//#ifdef NLC_PREPROCESSOR
	bool useNLCpreprocessor = NLCI_NLC_USE_NLC_PREPROCESSOR;
	//#endif
	#ifdef NLC_API
	bool NLCapi = false;
	string APIsourceFolder = NLC_API_DEFAULT_SOURCE_FOLDER_NAME;
	string APIclassListFileName = NLC_API_DEFAULT_CLASS_LIST_FILE_NAME;
	#endif
	bool printOutput = NLCI_NLC_PRINT_OUTPUT;
	bool displayInOpenGLAndOutputScreenshot = false;

	int rasterImageWidth = 640;
	int rasterImageHeight = 480;


	#ifdef GIA_DATABASE
	bool readFromDatabase = false;
	bool writeToDatabase = false;
	bool useDatabase = false;
	string KBdatabaseFolderName = GIA_DATABASE_FILESYSTEM_DEFAULT_SERVER_OR_MOUNT_NAME_BASE + GIA_DATABASE_FILESYSTEM_DEFAULT_DATABASE_NAME;
	#endif
	#ifdef GIA_SEMANTIC_PARSER
	string semanticParserDatabaseFolderName = GIA_DATABASE_FILESYSTEM_DEFAULT_SERVER_OR_MOUNT_NAME_BASE + GIA_SEMANTIC_PARSER_DATABASE_FILESYSTEM_DEFAULT_DATABASE_NAME;
	#endif
	#ifdef GIA_PREPROCESSOR_POS_TAGGER_DATABASE_PERSISTENT
	string POStaggerDatabaseFolderName = GIA_DATABASE_FILESYSTEM_DEFAULT_SERVER_OR_MOUNT_NAME_BASE + GIA_PREPROCESSOR_POS_TAGGER_DATABASE_FILESYSTEM_DEFAULT_DATABASE_NAME;
	#endif
	
	#ifdef GIA_PREPROCESSOR
	bool useLRP = NLCI_NLC_USE_LRP;
	bool useOutputLRPTextPlainTXTFile = false;
	string outputLRPTextPlainTXTFileName = "inputTextWithLRP.txt";
	string lrpDataFolderName = NLCI_NLC_LRP_FOLDER;
	#endif

	#ifdef USE_WORDNET
	#ifdef GIA_SYNONYMN_DETECTION_DEFAULT_QUERIES_AND_ADVANCED_REFERENCING
	int synonymnDetectionStatus = SYNONYMN_DETECTION_STATUS_QUERIES_AND_ADVANCED_REFERENCING;
	#else
	int synonymnDetectionStatus = SYNONYMN_DETECTION_STATUS_QUERIES_ONLY;
	#endif
	#endif

	//bool train = false;
	//bool form = true;

	//basic execution flow outline; if no dataset or xml inputText file is specified, just form network - do not train network

	string currentFolder = SHAREDvarsClass().getCurrentDirectory();

	translatorVariablesTemplate->isQuery = false;
	translatorVariablesTemplate->entityNodesActiveListComplete = new vector<GIAentityNode*>;	//NOT USED
	translatorVariablesTemplate->entityNodesActiveListNetworkIndexes = new unordered_map<string, GIAentityNode*>;	//NOT USED
	translatorVariablesTemplate->timeConditionNodesActiveList = new unordered_map<long, GIAtimeConditionNode*>;	//NOT USED
	translatorVariablesTemplate->entityNodesActiveListSentences = new map<int, vector<GIAentityNode*>*>;	//NOT USED
	translatorVariablesTemplate->NLPfeatureParser = NLPfeatureParser;
	translatorVariablesTemplate->NLPdependencyRelationsParser = NLPdependencyRelationsParser;
	translatorVariablesTemplate->NLPrelexCompatibilityMode = NLPrelexCompatibilityMode;
	translatorVariablesTemplate->NLPassumePreCollapsedStanfordRelations = NLPassumePreCollapsedStanfordRelations;
	#ifdef GIA_NEURAL_NETWORK
	translatorVariablesTemplate->ANNfirstInputNeuronInNetwork = new ANNneuron();
	#endif
	#ifdef GIA_NLP_CLIENT_SERVER
	translatorVariablesTemplate->NLPclient = NLPclient;
	#endif
	SHAREDvarsClass().copyStringArray(NLPexeFolderArray, translatorVariablesTemplate->NLPexeFolderArray, GIA_NLP_PARSER_NUMBER_OF_TYPES);

	NLCmainClass().executeNLC(

		firstNLCfunctionInList, 
		translatorVariablesTemplate,

		inputFolderLocal,
		outputFolderLocal,

		useInputTextPlainTXTFile,
		inputTextPlainTXTfileName,
		#ifdef NLC_INPUT_FUNCTION_LISTS_EXPLICIT_FROM_DEDICATED_FILE
		useNLCinputFileList,
		NLCinputFileListName,
		#endif
		
		outputTextNLPrelationXMLfileName,
		outputTextNLPfeatureXMLfileName,
		useOutputTextCFFFile,
		outputTextCFFFileName,
		useOutputTextXMLFile,
		outputTextXMLFileName,
		useOutputTextCXLFile,
		outputTextCXLFileName,
		useOutputTextLDRFile,
		outputTextLDRFileName,
		useOutputTextPPMFile,
		outputTextPPMFileName,
		useOutputTextSVGFile,
		outputTextSVGFileName,

		useOutputTextAllFile,
		outputTextAllFileName,
		#ifdef GIA_QUERY_WRITE_ANSWER_TO_FILE
		useOutputTextAnswerPlainTXTFile,
		outputTextAnswerPlainTXTFileName,
		#endif

		//#ifdef NLC_PREPROCESSOR
		useNLCpreprocessor,
		//#endif
		#ifdef NLC_API
		NLCapi,
		APIsourceFolder,
		APIclassListFileName,
		#endif

		printOutput,
		displayInOpenGLAndOutputScreenshot,

		rasterImageWidth,
		rasterImageHeight,

		#ifdef GIA_DATABASE
		readFromDatabase,
		writeToDatabase,
		useDatabase,
		KBdatabaseFolderName,
		#endif
		#ifdef GIA_SEMANTIC_PARSER
		semanticParserDatabaseFolderName,
		#endif
		#ifdef GIA_PREPROCESSOR_POS_TAGGER_DATABASE_PERSISTENT
		POStaggerDatabaseFolderName,
		#endif
		
		#ifdef GIA_PREPROCESSOR
		useLRP,
		useOutputLRPTextPlainTXTFile,
		outputLRPTextPlainTXTFileName,
		lrpDataFolderName,
		#endif

		#ifdef USE_WORDNET
		synonymnDetectionStatus
		#endif
	);
	
	return result;
}

#else

bool NLCIoperationsClass::executeGIAwrapper(GIAtranslatorVariablesClass* translatorVariablesTemplate, GIAtranslatorVariablesClass* translatorVariablesQuery, const bool query)
{
	bool result = true;

	string inputFolderLocal = NLCI_GIA_INPUT_FOLDER;
	string outputFolderLocal = NLCI_GIA_OUTPUT_FOLDER;

	#ifdef GIA_NLP_CLIENT_SERVER
	bool NLPclient = NLCI_GIA_NLP_CLIENT;
	#endif
	
	int NLPfeatureParser = NLCI_GIA_NLP_FEATURE_PARSER;
	int NLPdependencyRelationsParser = NLCI_GIA_NLP_DEPENDENCY_RELATIONS_PARSER;
	bool NLPrelexCompatibilityMode = false;			//(assumes) Relex dependency relations are(/were) generated by Relex parser in Stanford compatibility mode
	bool NLPassumePreCollapsedStanfordRelations = false;	//(assumes) Relex dependency relations are(/were) generated by Relex parser in Stanford compatibility mode / assumes Relex dependency relations were generated by GIA in cff
	
	int queryNLPfeatureParser = NLCI_GIA_NLP_FEATURE_PARSER_QUERY;
	int queryNLPdependencyRelationsParser = NLCI_GIA_NLP_FEATURE_PARSER_QUERY;
	bool queryNLPrelexCompatibilityMode = false;			//(assumes) Relex dependency relations are(/were) generated by Relex parser in Stanford compatibility mode
	bool queryNLPassumePreCollapsedStanfordRelations = false;	//(assumes) Relex dependency relations are(/were) generated by Relex parser in Stanford compatibility mode / assumes Relex dependency relations were generated by GIA in cff

	string NLPexeFolderArray[GIA_NLP_PARSER_NUMBER_OF_TYPES];
	NLPexeFolderArray[GIA_NLP_PARSER_RELEX] = NLCI_GIA_NLP_RELEX_FOLDER;
	NLPexeFolderArray[GIA_NLP_PARSER_STANFORD_CORENLP] = NLCI_GIA_NLP_STANFORD_CORE_NLP_FOLDER;
	NLPexeFolderArray[GIA_NLP_PARSER_STANFORD_PARSER] = NLCI_GIA_NLP_STANFORD_PARSER_FOLDER;
	
	bool useInputTextPlainTXTFile = false;
	string inputTextPlainTXTfileName = string(GIA_TEXT_BASE_FILE_NAME) + GIA_TEXT_FILE_EXTENSION;			//"inputText.txt";

	#ifdef USE_CE
	bool useInputTextCodeextensionsTXTFileName = false;
	string inputTextCodeextensionsTXTFileName = "codeextensionsEnumerated.txt";
	#endif

	bool useInputTextNLPrelationXMLFile = false;
	string inputTextNLPrelationXMLfileName = string(GIA_NLP_RELATION_BASE_FILE_NAME) + GIA_NLP_XML_FILE_EXTENSION;	//"inputNLPrelation.xml";
	bool useInputTextNLPfeatureXMLFile = false;
	string inputTextNLPfeatureXMLfileName = string(GIA_NLP_FEATURE_BASE_FILE_NAME) + GIA_NLP_XML_FILE_EXTENSION;	//"inputNLPfeature.xml";
	bool useOutputTextCFFFile = false;
	string outputTextCFFFileName = string(GIA_SEMANTIC_NET_BASE_FILE_NAME) + GIA_SEMANTIC_NET_CFF_FILE_EXTENSION;
	bool useInputTextXMLFile = false;
	string inputTextXMLFileName = string(GIA_SEMANTIC_NET_BASE_FILE_NAME) + GIA_SEMANTIC_NET_XML_FILE_EXTENSION;
	bool useOutputTextXMLFile = false;
	string outputTextXMLFileName = string(GIA_SEMANTIC_NET_BASE_FILE_NAME) + GIA_SEMANTIC_NET_XML_FILE_EXTENSION;
	bool useOutputTextCXLFile = false;
	string outputTextCXLFileName = string(GIA_SEMANTIC_NET_BASE_FILE_NAME) + GIA_SEMANTIC_NET_CXL_FILE_EXTENSION;
	bool useOutputTextLDRFile = false;
	string outputTextLDRFileName = string(GIA_SEMANTIC_NET_BASE_FILE_NAME) + GIA_SEMANTIC_NET_LDR_FILE_EXTENSION;
	bool useOutputTextPPMFile = false;
	string outputTextPPMFileName = string(GIA_SEMANTIC_NET_BASE_FILE_NAME) + GIA_SEMANTIC_NET_PPM_FILE_EXTENSION;
	bool useOutputTextSVGFile = false;
	string outputTextSVGFileName = string(GIA_SEMANTIC_NET_BASE_FILE_NAME) + GIA_SEMANTIC_NET_SVG_FILE_EXTENSION;
	bool useInputQueryPlainTXTFile = false;
	string inputQueryPlainTXTFileName = string(GIA_TEXT_BASE_FILE_NAME) + GIA_QUERY_FILE_PREPEND + GIA_TEXT_FILE_EXTENSION;				//"inputTextQuery.txt";
	bool useInputQueryNLPrelationXMLFile = false;
	string inputQueryNLPrelationXMLFileName = string(GIA_NLP_RELATION_BASE_FILE_NAME) + GIA_QUERY_FILE_PREPEND + GIA_NLP_XML_FILE_EXTENSION;	//"inputNLPrelationQuery.xml";
	bool useInputQueryNLPfeatureXMLFile = false;
	string inputQueryNLPfeatureXMLFileName = string(GIA_NLP_FEATURE_BASE_FILE_NAME) + GIA_QUERY_FILE_PREPEND + GIA_NLP_XML_FILE_EXTENSION;		//"inputNLPfeatureQuery.xml";
	bool useOutputQueryCFFFile = false;
	string outputQueryCFFFileName = string(GIA_SEMANTIC_NET_BASE_QUERY_FILE_NAME) + GIA_SEMANTIC_NET_CFF_FILE_EXTENSION;
	bool useInputQueryXMLFile = false;
	string inputQueryXMLFileName = string(GIA_SEMANTIC_NET_BASE_QUERY_FILE_NAME) + GIA_SEMANTIC_NET_XML_FILE_EXTENSION;
	bool useOutputQueryXMLFile = false;
	string outputQueryXMLFileName = string(GIA_SEMANTIC_NET_BASE_QUERY_FILE_NAME) + GIA_SEMANTIC_NET_XML_FILE_EXTENSION;
	bool useOutputQueryCXLFile = false;
	string outputQueryCXLFileName = string(GIA_SEMANTIC_NET_BASE_QUERY_FILE_NAME) + GIA_SEMANTIC_NET_CXL_FILE_EXTENSION;
	bool useOutputQueryLDRFile = false;
	string outputQueryLDRFileName = string(GIA_SEMANTIC_NET_BASE_QUERY_FILE_NAME) + GIA_SEMANTIC_NET_LDR_FILE_EXTENSION;
	bool useOutputQueryPPMFile = false;
	string outputQueryPPMFileName = string(GIA_SEMANTIC_NET_BASE_QUERY_FILE_NAME) + GIA_SEMANTIC_NET_PPM_FILE_EXTENSION;
	bool useOutputQuerySVGFile = false;
	string outputQuerySVGFileName = string(GIA_SEMANTIC_NET_BASE_QUERY_FILE_NAME) + GIA_SEMANTIC_NET_SVG_FILE_EXTENSION;
	bool useOutputTextAllFile = NLCI_GIA_USE_OUTPUT_TEXT_ALL_FILE;
	string outputTextAllFileName = NLCI_GIA_OUTPUT_TEXT_ALL_FILE_NAME;
	
	#ifdef GIA_NEURAL_NETWORK
	bool ANNuseInputXMLFile = false;
	string ANNinputXMLFileName = string(NEURAL_NETWORK_VISUALISATION_BASE_FILE_NAME) + NEURAL_NETWORK_VISUALISATION_XML_FILE_EXTENSION;
	bool ANNuseOutputXMLFile = false;
	string ANNoutputXMLFileName = string(NEURAL_NETWORK_VISUALISATION_BASE_FILE_NAME) + NEURAL_NETWORK_VISUALISATION_XML_FILE_EXTENSION;
	bool ANNuseOutputLDRFile = false;
	string ANNoutputLDRFileName = string(NEURAL_NETWORK_VISUALISATION_BASE_FILE_NAME) + NEURAL_NETWORK_VISUALISATION_LDR_FILE_EXTENSION;
	bool ANNuseOutputSVGFile = false;
	string ANNoutputSVGFileName = string(NEURAL_NETWORK_VISUALISATION_BASE_FILE_NAME) + NEURAL_NETWORK_VISUALISATION_SVG_FILE_EXTENSION;
	bool ANNuseOutputPPMFile = false;
	string ANNoutputPPMFileName = string(NEURAL_NETWORK_VISUALISATION_BASE_FILE_NAME) + NEURAL_NETWORK_VISUALISATION_PPM_FILE_EXTENSION;
	bool ANNuseOutputPPMFileRaytraced = false;
	string ANNoutputPPMFileNameRaytraced = string(NEURAL_NETWORK_VISUALISATION_BASE_FILE_NAME) + NEURAL_NETWORK_VISUALISATION_PPM_RAYTRACED_FILE_EXTENSION;
	string ANNoutputTALFileName = string(NEURAL_NETWORK_VISUALISATION_BASE_FILE_NAME) + NEURAL_NETWORK_VISUALISATION_TAL_FILE_EXTENSION;
	bool ANNuseOutputAllFile = false;
	string ANNoutputAllFileName = NEURAL_NETWORK_VISUALISATION_BASE_FILE_NAME;
	bool ANNuseSprites = true;
	#endif
	
	#ifdef GIA_QUERY_WRITE_ANSWER_TO_FILE
	bool useOutputTextAnswerPlainTXTFile = false;
	string outputTextAnswerPlainTXTFileName = GIA_ANSWER_FILE_NAME;
	#endif
	
	#ifdef GIA_INPUT_FILE_LISTS
	bool inputFileList = false;
	#endif
	bool printOutput = NLCI_GIA_PRINT_OUTPUT;
	bool printOutputQuery = NLCI_GIA_PRINT_OUTPUT_QUERY;
	bool displayInOpenGLAndOutputScreenshot = false;

	int rasterImageWidth = 640;
	int rasterImageHeight = 480;

	bool useInputQuery = false;
	if(query)
	{
		useInputQuery = true;
	}

	#ifdef GIA_DATABASE
	bool readFromDatabase = false;
	bool writeToDatabase = false;
	bool useDatabase = false;
	string KBdatabaseFolderName = GIA_DATABASE_FILESYSTEM_DEFAULT_SERVER_OR_MOUNT_NAME_BASE + GIA_DATABASE_FILESYSTEM_DEFAULT_DATABASE_NAME;
	#endif
	#ifdef GIA_SEMANTIC_PARSER
	string semanticParserDatabaseFolderName = GIA_DATABASE_FILESYSTEM_DEFAULT_SERVER_OR_MOUNT_NAME_BASE + GIA_SEMANTIC_PARSER_DATABASE_FILESYSTEM_DEFAULT_DATABASE_NAME;
	#endif
	#ifdef GIA_PREPROCESSOR_POS_TAGGER_DATABASE_PERSISTENT
	string POStaggerDatabaseFolderName = GIA_DATABASE_FILESYSTEM_DEFAULT_SERVER_OR_MOUNT_NAME_BASE + GIA_PREPROCESSOR_POS_TAGGER_DATABASE_FILESYSTEM_DEFAULT_DATABASE_NAME;
	#endif
	
	#ifdef GIA_PREPROCESSOR
	bool useLRP = NLCI_GIA_USE_LRP;
	bool useOutputLRPTextPlainTXTFile = false;
	string outputLRPTextPlainTXTFileName = string(GIA_TEXT_BASE_FILE_NAME) + GIA_TEXT_FILE_WITH_LRP_PREPEND + GIA_TEXT_FILE_EXTENSION;	//"inputTextWithLRP.txt";
	bool useOutputQueryLRPTextPlainTXTFile = false;
	string outputQueryLRPTextPlainTXTFileName = string(GIA_TEXT_BASE_FILE_NAME) + GIA_TEXT_FILE_WITH_LRP_PREPEND + GIA_QUERY_FILE_PREPEND + GIA_TEXT_FILE_EXTENSION;	//"inputTextWithLRPQuery.txt";
	string lrpDataFolderName = NLCI_GIA_LRP_FOLDER;
	#endif

	#ifdef USE_WORDNET
	#ifdef GIA_SYNONYMN_DETECTION_DEFAULT_QUERIES_AND_ADVANCED_REFERENCING
	int synonymnDetectionStatus = SYNONYMN_DETECTION_STATUS_QUERIES_AND_ADVANCED_REFERENCING;
	#else
	int synonymnDetectionStatus = SYNONYMN_DETECTION_STATUS_QUERIES_ONLY;
	#endif
	#endif
	


	string currentFolder = SHAREDvarsClass().getCurrentDirectory();

	translatorVariablesTemplate->isQuery = false;
	translatorVariablesTemplate->entityNodesActiveListComplete = new vector<GIAentityNode*>;	//NOT USED
	translatorVariablesTemplate->entityNodesActiveListNetworkIndexes = new unordered_map<string, GIAentityNode*>;	//NOT USED
	translatorVariablesTemplate->timeConditionNodesActiveList = new unordered_map<long, GIAtimeConditionNode*>;	//NOT USED
	translatorVariablesTemplate->entityNodesActiveListSentences = new map<int, vector<GIAentityNode*>*>;	//NOT USED
	translatorVariablesTemplate->NLPfeatureParser = NLPfeatureParser;
	translatorVariablesTemplate->NLPdependencyRelationsParser = NLPdependencyRelationsParser;
	translatorVariablesTemplate->NLPrelexCompatibilityMode = NLPrelexCompatibilityMode;
	translatorVariablesTemplate->NLPassumePreCollapsedStanfordRelations = NLPassumePreCollapsedStanfordRelations;
	#ifdef GIA_NLP_CLIENT_SERVER
	translatorVariablesTemplate->NLPclient = NLPclient;
	#endif
	SHAREDvarsClass().copyStringArray(NLPexeFolderArray, translatorVariablesTemplate->NLPexeFolderArray, GIA_NLP_PARSER_NUMBER_OF_TYPES);
	
	if(query)
	{
		translatorVariablesQuery->isQuery = true;
		translatorVariablesQuery->entityNodesActiveListComplete = new vector<GIAentityNode*>;
		translatorVariablesQuery->entityNodesActiveListNetworkIndexes = new unordered_map<string, GIAentityNode*>;
		translatorVariablesQuery->timeConditionNodesActiveList = new unordered_map<long, GIAtimeConditionNode*>;
		translatorVariablesQuery->entityNodesActiveListSentences = new map<int, vector<GIAentityNode*>*>;
		translatorVariablesQuery->NLPfeatureParser = queryNLPfeatureParser;
		translatorVariablesQuery->NLPdependencyRelationsParser = queryNLPdependencyRelationsParser;
		translatorVariablesQuery->NLPrelexCompatibilityMode = queryNLPrelexCompatibilityMode;
		translatorVariablesQuery->NLPassumePreCollapsedStanfordRelations = queryNLPassumePreCollapsedStanfordRelations;
		#ifdef GIA_NLP_CLIENT_SERVER
		translatorVariablesQuery->NLPclient = NLPclient;
		#endif
		SHAREDvarsClass().copyStringArray(NLPexeFolderArray, translatorVariablesQuery->NLPexeFolderArray, GIA_NLP_PARSER_NUMBER_OF_TYPES);
	}
	

	GIAmainClass().executeGIA(

		translatorVariablesTemplate,
		translatorVariablesQuery,

		inputFolderLocal,
		outputFolderLocal,

		useInputTextPlainTXTFile,
		inputTextPlainTXTfileName,
		#ifdef USE_CE
		useInputTextCodeextensionsTXTFileName,
		inputTextCodeextensionsTXTFileName,
		#endif
		useInputTextNLPrelationXMLFile,
		inputTextNLPrelationXMLfileName,
		useInputTextNLPfeatureXMLFile,
		inputTextNLPfeatureXMLfileName,
		useInputTextXMLFile,
		inputTextXMLFileName,		
		
		useOutputTextCFFFile,
		outputTextCFFFileName,
		useOutputTextXMLFile,
		outputTextXMLFileName,
		useOutputTextCXLFile,
		outputTextCXLFileName,
		useOutputTextLDRFile,
		outputTextLDRFileName,
		useOutputTextPPMFile,
		outputTextPPMFileName,
		useOutputTextSVGFile,
		outputTextSVGFileName,
		useInputQueryPlainTXTFile,
		inputQueryPlainTXTFileName,
		useInputQueryNLPrelationXMLFile,
		inputQueryNLPrelationXMLFileName,
		useInputQueryNLPfeatureXMLFile,
		inputQueryNLPfeatureXMLFileName,
		useOutputQueryCFFFile,
		outputQueryCFFFileName,
		useInputQueryXMLFile,
		inputQueryXMLFileName,
		useOutputQueryXMLFile,
		outputQueryXMLFileName,
		useOutputQueryCXLFile,
		outputQueryCXLFileName,
		useOutputQueryLDRFile,
		outputQueryLDRFileName,
		useOutputQueryPPMFile,
		outputQueryPPMFileName,
		useOutputQuerySVGFile,
		outputQuerySVGFileName,
		useOutputTextAllFile,
		outputTextAllFileName,
		
		#ifdef GIA_NEURAL_NETWORK
		ANNuseInputXMLFile,
		ANNinputXMLFileName,	
		ANNuseOutputXMLFile,
		ANNoutputXMLFileName,
		ANNuseOutputLDRFile,
		ANNoutputLDRFileName,
		ANNuseOutputSVGFile,
		ANNoutputSVGFileName,
		ANNuseOutputPPMFile,
		ANNoutputPPMFileName,
		ANNuseOutputPPMFileRaytraced,
		ANNoutputPPMFileNameRaytraced,				
		ANNuseOutputAllFile,
		ANNoutputAllFileName,
		ANNuseSprites,
		#endif
		
		#ifdef GIA_QUERY_WRITE_ANSWER_TO_FILE
		useOutputTextAnswerPlainTXTFile,
		outputTextAnswerPlainTXTFileName,
		#endif

		#ifdef GIA_INPUT_FILE_LISTS
		inputFileList,
		#endif
		printOutput,
		printOutputQuery,
		displayInOpenGLAndOutputScreenshot,

		rasterImageWidth,
		rasterImageHeight,

		useInputQuery,

		#ifdef GIA_DATABASE
		readFromDatabase,
		writeToDatabase,
		useDatabase,
		KBdatabaseFolderName,
		#endif
		#ifdef GIA_SEMANTIC_PARSER
		semanticParserDatabaseFolderName,
		#endif
		#ifdef GIA_PREPROCESSOR_POS_TAGGER_DATABASE_PERSISTENT
		POStaggerDatabaseFolderName,
		#endif
		
		#ifdef GIA_PREPROCESSOR
		useLRP,
		useOutputLRPTextPlainTXTFile,
		outputLRPTextPlainTXTFileName,
		useOutputQueryLRPTextPlainTXTFile,
		outputQueryLRPTextPlainTXTFileName,
		lrpDataFolderName,
		#endif

		#ifdef USE_WORDNET
		synonymnDetectionStatus
		#endif

	);
	
	return result;
}

#endif

int NLCIoperationsClass::preprepreprocessTextForNLChighlightWordDetermineColourIndex(const string* word)
{
	int colourIndex = NLCI_EDITOR_DEFAULT_FONT_COLOUR;
	int grammaticalBaseTenseForm = INT_DEFAULT_VALUE;
	string baseNameFoundNOTUSED = "";
	if(GIApreprocessorMultiwordReduction.determineVerbCaseStandardWithAdditional(*word, &baseNameFoundNOTUSED, &grammaticalBaseTenseForm))
	{
		colourIndex = GIA_DRAW_VERB_NODE_COLOUR;
	}
	else if(GIApreprocessorMultiwordReduction.determineIsPreposition(*word))
	{
		colourIndex = GIA_DRAW_PREPOSITION_NODE_COLOUR;
	}
	else if(GIApreprocessorMultiwordReduction.determineIsAdverb(*word))
	{
		colourIndex = GIA_DRAW_ADVERB_NODE_COLOUR;
	}
	else if(GIApreprocessorMultiwordReduction.determineIsAdjective(*word))
	{
		colourIndex = GIA_DRAW_ADJECTIVE_NODE_COLOUR;
	}
	else if(GIApreprocessorMultiwordReduction.determineIsNoun(*word))
	{
		colourIndex = GIA_DRAW_NOUN_NODE_COLOUR;
	}
	else
	{

	}
	return colourIndex;
}

int NLCIoperationsClass::processTextForNLChighlightWordDetermineColourIndex(GIAentityNode* entity)
{
	int colourIndex = NLCI_EDITOR_DEFAULT_FONT_COLOUR;
	if(entity != NULL)
	{
		//cout << "entity->entityType = " << entity->entityType << endl;
		if(entity->entityType == GIA_ENTITY_TYPE_NETWORK_INDEX)
		{
			//colourIndex = GIA_DRAW_NETWORK_INDEX_NODE_COLOUR;	//no entity instance created; leave colour as default (e.g. black)
		}
		else if(entity->entityType == GIA_ENTITY_TYPE_SUBSTANCE)
		{
			colourIndex = GIA_DRAW_SUBSTANCE_NODE_COLOUR;
		}
		else if(entity->entityType == GIA_ENTITY_TYPE_CONCEPT)
		{
			colourIndex = GIA_DRAW_CONCEPT_NODE_COLOUR;
		}
		else if(entity->entityType == GIA_ENTITY_TYPE_ACTION)
		{
			colourIndex = GIA_DRAW_ACTION_NODE_COLOUR;
		}
		else if(entity->entityType == GIA_ENTITY_TYPE_CONDITION)
		{
			colourIndex = GIA_DRAW_CONDITION_NODE_COLOUR;
		}
		else if(entity->entityType == GIA_ENTITY_TYPE_DEFINITION)
		{
			colourIndex = GIA_DRAW_DEFINITION_NODE_COLOUR;
		}
		else if(entity->entityType == GIA_ENTITY_TYPE_QUALITY)
		{
			colourIndex = GIA_DRAW_SUBSTANCE_QUALITY_NODE_COLOUR;
		}
		else if(entity->entityType == GIA_ENTITY_TYPE_PROPERTY)
		{
			colourIndex = GIA_DRAW_PROPERTY_NODE_COLOUR;
		}
	}
	return colourIndex;		
}

QString convertStringToQString(const string str)
{
	return QString::fromStdString(str);
}

string convertQStringToString(const QString qstr)
{
	return qstr.toStdString();
}

QString convertByteArrayToQString(const QByteArray& ba)
{
	return QTextCodec::codecForMib(1015)->toUnicode(ba);	//1015 = UTF-16
}










