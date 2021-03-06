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
 * File Name: NLCIeditorOperations.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2019 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2o2a 08-November-2020
 * Requirements: 
 * /
 *******************************************************************************/


#ifndef NLCI_EDITOR_OPERATIONS
#define NLCI_EDITOR_OPERATIONS

#include "NLCIeditorOperations.hpp"
#include "NLCIoperations.hpp"
#include "GIAtranslatorOperations.hpp"
#include "LRPpreprocessorWordIdentification.hpp"
#include "LRPpreprocessor.hpp"

#include <QTextBlock>

#define NLCI_URL_DELIMITER "/"


class NLCIeditorOperationsClass
{
	//Q_OBJECT
	
private: 
	SHAREDvarsClass SHAREDvars;
	NLCIoperationsClass NLCIoperations;
	LRPpreprocessorClass LRPpreprocessor;
	LRPpreprocessorWordIdentificationClass LRPpreprocessorWordIdentification;
	LRPpreprocessorWordClassClass LRPpreprocessorWordClassObject;
	NLCpreprocessorClass NLCpreprocessor;

public:
	#ifdef USE_NLCI
	bool preprepreprocessTextForNLC(QTextEdit* editor, NLCfunction* firstNLCfunctionInList);
		bool preprepreprocessTextForNLChighlightWrapper(QVector<HighlightingRule>* highlightingRules, NLCfunction* firstNLCfunctionInList);
	#elif defined USE_GIAI
	bool preprepreprocessTextForNLC(QTextEdit* editor, GIAtranslatorVariablesClass* translatorVariablesTemplate);
		bool preprepreprocessTextForNLChighlightWrapper(QVector<HighlightingRule>* highlightingRules, GIAtranslatorVariablesClass* translatorVariablesTemplate);
	#endif
		bool preprepreprocessTextForNLChighlight(QVector<HighlightingRule>* highlightingRules, LRPpreprocessorSentence* firstNLCpreprepreprocessorSentenceInList);
	bool preprepreprocessTextForNLCsingleLine(QTextEdit* editor, QVector<HighlightingRule>* highlightingRules, const int lineIndex);
		bool preprepreprocessTextForNLCsingleLinehighlight(QVector<HighlightingRule>* highlightingRules, LRPpreprocessorSentence* currentNLCpreprepreprocessorSentenceInList, const int lineIndex);		
	bool preprepreprocessTextForNLChighlightSentence(QVector<HighlightingRule>* highlightingRules, vector<LRPpreprocessorPlainTextWord*>* sentence, const bool useOriginalSpacing);

};

#endif
