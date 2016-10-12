   /*******************************************************/
   /*      "C" Language Integrated Production System      */
   /*                                                     */
   /*            CLIPS Version 6.40  10/01/16             */
   /*                                                     */
   /*                  CLASS COMMANDS MODULE              */
   /*******************************************************/

/**************************************************************/
/* Purpose: Kernel Interface Commands for Object System       */
/*                                                            */
/* Principal Programmer(s):                                   */
/*      Brian L. Dantes                                       */
/*                                                            */
/* Contributing Programmer(s):                                */
/*                                                            */
/* Revision History:                                          */
/*                                                            */
/*      6.23: Corrected compilation errors for files          */
/*            generated by constructs-to-c. DR0861            */
/*                                                            */
/*            Changed name of variable log to logName         */
/*            because of Unix compiler warnings of shadowed   */
/*            definitions.                                    */
/*                                                            */
/*      6.24: Renamed BOOLEAN macro type to intBool.          */
/*                                                            */
/*            Added pragmas to remove compilation warnings.   */
/*                                                            */
/*      6.30: Borland C (IBM_TBC) and Metrowerks CodeWarrior  */
/*            (MAC_MCW, IBM_MCW) are no longer supported.     */
/*                                                            */
/*            Added const qualifiers to remove C++            */
/*            deprecation warnings.                           */
/*                                                            */
/*            Converted API macros to function calls.         */
/*                                                            */
/*            Changed find construct functionality so that    */
/*            imported modules are search when locating a     */
/*            named construct.                                */
/*                                                            */
/*      6.40: Pragma once and other inclusion changes.       */
/*                                                           */
/*            Added support for booleans with <stdbool.h>.   */
/*                                                           */
/*            Removed use of void pointers for specific      */
/*            data structures.                               */
/*                                                           */
/*            ALLOW_ENVIRONMENT_GLOBALS no longer supported. */
/*                                                           */
/*            UDF redesign.                                  */
/*                                                           */
/**************************************************************/

/* =========================================
   *****************************************
               EXTERNAL DEFINITIONS
   =========================================
   ***************************************** */

#include <string.h>

#include "setup.h"

#if OBJECT_SYSTEM

#if BLOAD || BLOAD_ONLY || BLOAD_AND_BSAVE
#include "bload.h"
#endif

#include "argacces.h"
#include "classfun.h"
#include "classini.h"
#include "envrnmnt.h"
#include "modulutl.h"
#include "msgcom.h"
#include "router.h"

#include "classcom.h"

/***************************************/
/* LOCAL INTERNAL FUNCTION DEFINITIONS */
/***************************************/

#if (! BLOAD_ONLY) && (! RUN_TIME) && DEBUGGING_FUNCTIONS
   static void                    SaveDefclass(Environment *,struct constructHeader *,void *);
#endif
   static const char             *GetClassDefaultsModeName(unsigned short);

/* =========================================
   *****************************************
          EXTERNALLY VISIBLE FUNCTIONS
   =========================================
   ***************************************** */

/*******************************************************************
  NAME         : EnvFindDefclass
  DESCRIPTION  : Looks up a specified class in the class hash table
                 (Only looks in current or specified module)
  INPUTS       : The name-string of the class (including module)
  RETURNS      : The address of the found class, NULL otherwise
  SIDE EFFECTS : None
  NOTES        : None
 ******************************************************************/
Defclass *EnvFindDefclass( // TBD Needs to look in imported
  Environment *theEnv,
  const char *classAndModuleName)
  {
   CLIPSLexeme *classSymbol = NULL;
   Defclass *cls;
   Defmodule *theModule = NULL;
   const char *className;

   SaveCurrentModule(theEnv);

   className = ExtractModuleAndConstructName(theEnv,classAndModuleName);
   if (className != NULL)
     {
      classSymbol = FindSymbolHN(theEnv,ExtractModuleAndConstructName(theEnv,classAndModuleName),SYMBOL_TYPE);
      theModule = EnvGetCurrentModule(theEnv);
     }

   RestoreCurrentModule(theEnv);

   if (classSymbol == NULL)
     { return NULL; }

   cls = DefclassData(theEnv)->ClassTable[HashClass(classSymbol)];
   while (cls != NULL)
     {
      if (cls->header.name == classSymbol)
        {
         if (cls->system || (cls->header.whichModule->theModule == theModule))
           { return cls->installed ? cls : NULL; }
        }
      cls = cls->nxtHash;
     }

   return NULL;
  }

/*******************************************************************
  NAME         : EnvFindDefclass
  DESCRIPTION  : Looks up a specified class in the class hash table
                 (Only looks in current or specified module)
  INPUTS       : The name-string of the class (including module)
  RETURNS      : The address of the found class, NULL otherwise
  SIDE EFFECTS : None
  NOTES        : None
 ******************************************************************/
Defclass *EnvFindDefclassInModule(
  Environment *theEnv,
  const char *classAndModuleName)
  {
   CLIPSLexeme *classSymbol = NULL;
   Defclass *cls;
   Defmodule *theModule = NULL;
   const char *className;

   SaveCurrentModule(theEnv);
   className = ExtractModuleAndConstructName(theEnv,classAndModuleName);
   if (className != NULL)
     {
      classSymbol = FindSymbolHN(theEnv,ExtractModuleAndConstructName(theEnv,classAndModuleName),SYMBOL_TYPE);
      theModule = EnvGetCurrentModule(theEnv);
     }
   RestoreCurrentModule(theEnv);

   if (classSymbol == NULL)
     { return NULL; }

   cls = DefclassData(theEnv)->ClassTable[HashClass(classSymbol)];
   while (cls != NULL)
     {
      if (cls->header.name == classSymbol)
        {
         if (cls->system || (cls->header.whichModule->theModule == theModule))
           { return cls->installed ? cls : NULL; }
        }
      cls = cls->nxtHash;
     }

   return NULL;
  }

/***************************************************
  NAME         : LookupDefclassByMdlOrScope
  DESCRIPTION  : Finds a class anywhere (if module
                 is specified) or in current or
                 imported modules
  INPUTS       : The class name
  RETURNS      : The class (NULL if not found)
  SIDE EFFECTS : Error message printed on
                  ambiguous references
  NOTES        : Assumes no two classes of the same
                 name are ever in the same scope
 ***************************************************/
Defclass *LookupDefclassByMdlOrScope(
  Environment *theEnv,
  const char *classAndModuleName)
  {
   Defclass *cls;
   const char *className;
   CLIPSLexeme *classSymbol;
   Defmodule *theModule;

   if (FindModuleSeparator(classAndModuleName) == 0)
     { return LookupDefclassInScope(theEnv,classAndModuleName); }

   SaveCurrentModule(theEnv);
   className = ExtractModuleAndConstructName(theEnv,classAndModuleName);
   theModule = EnvGetCurrentModule(theEnv);
   RestoreCurrentModule(theEnv);

   if (className == NULL)
     { return NULL; }

   if ((classSymbol = FindSymbolHN(theEnv,className,SYMBOL_TYPE)) == NULL)
     { return NULL; }

   cls = DefclassData(theEnv)->ClassTable[HashClass(classSymbol)];
   while (cls != NULL)
     {
      if ((cls->header.name == classSymbol) &&
          (cls->header.whichModule->theModule == theModule))
        return(cls->installed ? cls : NULL);
      cls = cls->nxtHash;
     }

   return NULL;
  }

/****************************************************
  NAME         : LookupDefclassInScope
  DESCRIPTION  : Finds a class in current or imported
                   modules (module specifier
                   is not allowed)
  INPUTS       : The class name
  RETURNS      : The class (NULL if not found)
  SIDE EFFECTS : Error message printed on
                  ambiguous references
  NOTES        : Assumes no two classes of the same
                 name are ever in the same scope
 ****************************************************/
Defclass *LookupDefclassInScope(
  Environment *theEnv,
  const char *className)
  {
   Defclass *cls;
   CLIPSLexeme *classSymbol;

   if ((classSymbol = FindSymbolHN(theEnv,className,SYMBOL_TYPE)) == NULL)
     { return NULL; }

   cls = DefclassData(theEnv)->ClassTable[HashClass(classSymbol)];
   while (cls != NULL)
     {
      if ((cls->header.name == classSymbol) && DefclassInScope(theEnv,cls,NULL))
        return cls->installed ? cls : NULL;
      cls = cls->nxtHash;
     }

   return NULL;
  }

/******************************************************
  NAME         : LookupDefclassAnywhere
  DESCRIPTION  : Finds a class in specified
                 (or any) module
  INPUTS       : 1) The module (NULL if don't care)
                 2) The class name (module specifier
                    in name not allowed)
  RETURNS      : The class (NULL if not found)
  SIDE EFFECTS : None
  NOTES        : Does *not* generate an error if
                 multiple classes of the same name
                 exist as do the other lookup functions
 ******************************************************/
Defclass *LookupDefclassAnywhere(
  Environment *theEnv,
  Defmodule *theModule,
  const char *className)
  {
   Defclass *cls;
   CLIPSLexeme *classSymbol;

   if ((classSymbol = FindSymbolHN(theEnv,className,SYMBOL_TYPE)) == NULL)
     { return NULL; }

   cls = DefclassData(theEnv)->ClassTable[HashClass(classSymbol)];
   while (cls != NULL)
     {
      if ((cls->header.name == classSymbol) &&
          ((theModule == NULL) ||
           (cls->header.whichModule->theModule == theModule)))
        { return cls->installed ? cls : NULL; }
      cls = cls->nxtHash;
     }

   return NULL;
  }

/***************************************************
  NAME         : DefclassInScope
  DESCRIPTION  : Determines if a defclass is in
                 scope of the given module
  INPUTS       : 1) The defclass
                 2) The module (NULL for current
                    module)
  RETURNS      : True if in scope,
                 false otherwise
  SIDE EFFECTS : None
  NOTES        : None
 ***************************************************/
bool DefclassInScope(
  Environment *theEnv,
  Defclass *theDefclass,
  Defmodule *theModule)
  {
#if DEFMODULE_CONSTRUCT
   int moduleID;
   char *scopeMap;

   scopeMap = (char *) theDefclass->scopeMap->contents;
   if (theModule == NULL)
     { theModule = EnvGetCurrentModule(theEnv); }
   moduleID = (int) theModule->header.bsaveID;

   return TestBitMap(scopeMap,moduleID) ? true : false;
#else
#if MAC_XCD
#pragma unused(theEnv,theDefclass,theModule)
#endif
   return true;
#endif
  }

/***********************************************************
  NAME         : EnvGetNextDefclass
  DESCRIPTION  : Finds first or next defclass
  INPUTS       : The address of the current defclass
  RETURNS      : The address of the next defclass
                   (NULL if none)
  SIDE EFFECTS : None
  NOTES        : If ptr == NULL, the first defclass
                    is returned.
 ***********************************************************/
Defclass *EnvGetNextDefclass(
  Environment *theEnv,
  Defclass *theDefclass)
  {
   return (Defclass *) GetNextConstructItem(theEnv,(struct constructHeader *) theDefclass,
                                            DefclassData(theEnv)->DefclassModuleIndex);
  }

/***************************************************
  NAME         : EnvIsDefclassDeletable
  DESCRIPTION  : Determines if a defclass
                   can be deleted
  INPUTS       : Address of the defclass
  RETURNS      : True if deletable,
                 false otherwise
  SIDE EFFECTS : None
  NOTES        : None
 ***************************************************/
bool EnvIsDefclassDeletable(
  Environment *theEnv,
  Defclass *theDefclass)
  {
   if (! ConstructsDeletable(theEnv))
     { return false; }

   if (theDefclass->system == 1)
     { return false; }

#if (! BLOAD_ONLY) && (! RUN_TIME)
   return (IsClassBeingUsed(theDefclass) == false) ? true : false;
#else
   return false;
#endif
  }

/*************************************************************
  NAME         : UndefclassCommand
  DESCRIPTION  : Deletes a class and its subclasses, as
                 well as their associated instances
  INPUTS       : None
  RETURNS      : Nothing useful
  SIDE EFFECTS : None
  NOTES        : Syntax : (undefclass <class-name> | *)
 *************************************************************/
void UndefclassCommand(
  Environment *theEnv,
  UDFContext *context,
  UDFValue *returnValue)
  {
   UndefconstructCommand(context,"undefclass",DefclassData(theEnv)->DefclassConstruct);
  }

/********************************************************
  NAME         : EnvUndefclass
  DESCRIPTION  : Deletes the named defclass
  INPUTS       : None
  RETURNS      : True if deleted, or false
  SIDE EFFECTS : Defclass and handlers removed
  NOTES        : Interface for AddConstruct()
 ********************************************************/
bool EnvUndefclass(
  Environment *theEnv,
  Defclass *theDefclass)
  {
#if RUN_TIME || BLOAD_ONLY
   return false;
#else

#if BLOAD || BLOAD_AND_BSAVE
   if (Bloaded(theEnv))
     return false;
#endif
   if (theDefclass == NULL)
     { return RemoveAllUserClasses(theEnv); }

   return DeleteClassUAG(theEnv,theDefclass);
#endif
  }


#if DEBUGGING_FUNCTIONS

/*********************************************************
  NAME         : PPDefclassCommand
  DESCRIPTION  : Displays the pretty print form of
                 a class to the wdialog router.
  INPUTS       : None
  RETURNS      : Nothing useful
  SIDE EFFECTS : None
  NOTES        : Syntax : (ppdefclass <class-name>)
 *********************************************************/
void PPDefclassCommand(
  Environment *theEnv,
  UDFContext *context,
  UDFValue *returnValue)
  {
   PPConstructCommand(context,"ppdefclass",DefclassData(theEnv)->DefclassConstruct);
  }

/***************************************************
  NAME         : ListDefclassesCommand
  DESCRIPTION  : Displays all defclass names
  INPUTS       : None
  RETURNS      : Nothing useful
  SIDE EFFECTS : Defclass names printed
  NOTES        : H/L Interface
 ***************************************************/
void ListDefclassesCommand(
  Environment *theEnv,
  UDFContext *context,
  UDFValue *returnValue)
  {
   ListConstructCommand(context,DefclassData(theEnv)->DefclassConstruct);
  }

/***************************************************
  NAME         : EnvListDefclasses
  DESCRIPTION  : Displays all defclass names
  INPUTS       : 1) The logical name of the output
                 2) The module
  RETURNS      : Nothing useful
  SIDE EFFECTS : Defclass names printed
  NOTES        : C Interface
 ***************************************************/
void EnvListDefclasses(
  Environment *theEnv,
  const char *logicalName,
  Defmodule *theModule)
  {
   ListConstruct(theEnv,DefclassData(theEnv)->DefclassConstruct,logicalName,theModule);
  }

/*********************************************************
  NAME         : EnvGetDefclassWatchInstances
  DESCRIPTION  : Determines if deletions/creations of
                 instances of this class will generate
                 trace messages or not
  INPUTS       : A pointer to the class
  RETURNS      : True if a trace is active,
                 false otherwise
  SIDE EFFECTS : None
  NOTES        : None
 *********************************************************/
bool EnvGetDefclassWatchInstances(
  Environment *theEnv,
  Defclass *theDefclass)
  {
#if MAC_XCD
#pragma unused(theEnv)
#endif

   return theDefclass->traceInstances;
  }

/*********************************************************
  NAME         : EnvSetDefclassWatchInstances
  DESCRIPTION  : Sets the trace to ON/OFF for the
                 creation/deletion of instances
                 of the class
  INPUTS       : 1) true to set the trace on,
                    false to set it off
                 2) A pointer to the class
  RETURNS      : Nothing useful
  SIDE EFFECTS : Watch flag for the class set
  NOTES        : None
 *********************************************************/
void EnvSetDefclassWatchInstances(
  Environment *theEnv,
  bool newState,
  Defclass *theDefclass)
  {
#if MAC_XCD
#pragma unused(theEnv)
#endif

   if (theDefclass->abstract)
     { return; }

   theDefclass->traceInstances = newState;
  }

/*********************************************************
  NAME         : EnvGetDefclassWatchSlots
  DESCRIPTION  : Determines if changes to slots of
                 instances of this class will generate
                 trace messages or not
  INPUTS       : A pointer to the class
  RETURNS      : True if a trace is active,
                 false otherwise
  SIDE EFFECTS : None
  NOTES        : None
 *********************************************************/
bool EnvGetDefclassWatchSlots(
  Environment *theEnv,
  Defclass *theDefclass)
  {
#if MAC_XCD
#pragma unused(theEnv)
#endif

   return theDefclass->traceSlots;
  }

/**********************************************************
  NAME         : EnvSetDefclassWatchSlots
  DESCRIPTION  : Sets the trace to ON/OFF for the
                 changes to slots of instances of the class
  INPUTS       : 1) true to set the trace on,
                    false to set it off
                 2) A pointer to the class
  RETURNS      : Nothing useful
  SIDE EFFECTS : Watch flag for the class set
  NOTES        : None
 **********************************************************/
void EnvSetDefclassWatchSlots(
  Environment *theEnv,
  bool newState,
  Defclass *theDefclass)
  {
#if MAC_XCD
#pragma unused(theEnv)
#endif

   theDefclass->traceSlots = newState;
  }

/******************************************************************
  NAME         : DefclassWatchAccess
  DESCRIPTION  : Parses a list of class names passed by
                 AddWatchItem() and sets the traces accordingly
  INPUTS       : 1) A code indicating which trace flag is to be set
                    0 - Watch instance creation/deletion
                    1 - Watch slot changes to instances
                 2) The value to which to set the trace flags
                 3) A list of expressions containing the names
                    of the classes for which to set traces
  RETURNS      : True if all OK, false otherwise
  SIDE EFFECTS : Watch flags set in specified classes
  NOTES        : Accessory function for AddWatchItem()
 ******************************************************************/
bool DefclassWatchAccess(
  Environment *theEnv,
  int code,
  bool newState,
  EXPRESSION *argExprs)
  {
   if (code)
     return(ConstructSetWatchAccess(theEnv,DefclassData(theEnv)->DefclassConstruct,newState,argExprs,
                                    (ConstructGetWatchFunction *) EnvGetDefclassWatchSlots,
                                    (ConstructSetWatchFunction *) EnvSetDefclassWatchSlots));
   else
     return(ConstructSetWatchAccess(theEnv,DefclassData(theEnv)->DefclassConstruct,newState,argExprs,
                                    (ConstructGetWatchFunction *) EnvGetDefclassWatchInstances,
                                    (ConstructSetWatchFunction *) EnvSetDefclassWatchInstances));
  }

/***********************************************************************
  NAME         : DefclassWatchPrint
  DESCRIPTION  : Parses a list of class names passed by
                 AddWatchItem() and displays the traces accordingly
  INPUTS       : 1) The logical name of the output
                 2) A code indicating which trace flag is to be examined
                    0 - Watch instance creation/deletion
                    1 - Watch slot changes to instances
                 3) A list of expressions containing the names
                    of the classes for which to examine traces
  RETURNS      : True if all OK, false otherwise
  SIDE EFFECTS : Watch flags displayed for specified classes
  NOTES        : Accessory function for AddWatchItem()
 ***********************************************************************/
bool DefclassWatchPrint(
  Environment *theEnv,
  const char *logName,
  int code,
  EXPRESSION *argExprs)
  {
   if (code)
     return(ConstructPrintWatchAccess(theEnv,DefclassData(theEnv)->DefclassConstruct,logName,argExprs,
                                      (ConstructGetWatchFunction *) EnvGetDefclassWatchSlots,
                                      (ConstructSetWatchFunction *) EnvSetDefclassWatchSlots));
   else
     return(ConstructPrintWatchAccess(theEnv,DefclassData(theEnv)->DefclassConstruct,logName,argExprs,
                                      (ConstructGetWatchFunction *) EnvGetDefclassWatchInstances,
                                      (ConstructSetWatchFunction *) EnvSetDefclassWatchInstances));
  }

#endif /* DEBUGGING_FUNCTIONS */

/*********************************************************
  NAME         : GetDefclassListFunction
  DESCRIPTION  : Groups names of all defclasses into
                   a multifield variable
  INPUTS       : A data object buffer
  RETURNS      : Nothing useful
  SIDE EFFECTS : Multifield set to list of classes
  NOTES        : None
 *********************************************************/
void GetDefclassListFunction(
  Environment *theEnv,
  UDFContext *context,
  UDFValue *returnValue)
  {
   GetConstructListFunction(context,returnValue,DefclassData(theEnv)->DefclassConstruct);
  }

/***************************************************************
  NAME         : EnvGetDefclassList
  DESCRIPTION  : Groups all defclass names into
                 a multifield list
  INPUTS       : 1) A data object buffer to hold
                    the multifield result
                 2) The module from which to obtain defclasses
  RETURNS      : Nothing useful
  SIDE EFFECTS : Multifield allocated and filled
  NOTES        : External C access
 ***************************************************************/
void EnvGetDefclassList(
  Environment *theEnv,
  UDFValue *returnValue,
  Defmodule *theModule)
  {
   GetConstructList(theEnv,returnValue,DefclassData(theEnv)->DefclassConstruct,theModule);
  }

/*****************************************************
  NAME         : HasSuperclass
  DESCRIPTION  : Determines if class-2 is a superclass
                   of class-1
  INPUTS       : 1) Class-1
                 2) Class-2
  RETURNS      : True if class-2 is a superclass of
                   class-1, false otherwise
  SIDE EFFECTS : None
  NOTES        : None
 *****************************************************/
bool HasSuperclass(
  Defclass *c1,
  Defclass *c2)
  {
   long i;

   for (i = 1 ; i < c1->allSuperclasses.classCount ; i++)
     if (c1->allSuperclasses.classArray[i] == c2)
       return true;
   return false;
  }

/********************************************************************
  NAME         : CheckClassAndSlot
  DESCRIPTION  : Checks class and slot argument for various functions
  INPUTS       : 1) Name of the calling function
                 2) Buffer for class address
  RETURNS      : Slot symbol, NULL on errors
  SIDE EFFECTS : None
  NOTES        : None
 ********************************************************************/
CLIPSLexeme *CheckClassAndSlot(
   UDFContext *context,
   const char *func,
   Defclass **cls)
  {
   UDFValue theArg;
   Environment *theEnv = context->environment;

   if (! UDFFirstArgument(context,SYMBOL_TYPE,&theArg))
     return NULL;

   *cls = LookupDefclassByMdlOrScope(theEnv,theArg.lexemeValue->contents);
   if (*cls == NULL)
     {
      ClassExistError(theEnv,func,theArg.lexemeValue->contents);
      return NULL;
     }

   if (! UDFNextArgument(context,SYMBOL_TYPE,&theArg))
     return NULL;

   return theArg.lexemeValue;
  }

#if (! BLOAD_ONLY) && (! RUN_TIME)

/***************************************************
  NAME         : SaveDefclasses
  DESCRIPTION  : Prints pretty print form of
                   defclasses to specified output
  INPUTS       : The  logical name of the output
  RETURNS      : Nothing useful
  SIDE EFFECTS : None
  NOTES        : None
 ***************************************************/
void SaveDefclasses(
  Environment *theEnv,
  Defmodule *theModule,
  const char *logName)
  {
#if DEBUGGING_FUNCTIONS
   DoForAllConstructsInModule(theEnv,theModule,SaveDefclass,
                              DefclassData(theEnv)->DefclassModuleIndex,
                              false,(void *) logName);
#else
#if MAC_XCD
#pragma unused(theEnv,theModule,logName)
#endif
#endif
  }

#endif

/* =========================================
   *****************************************
          INTERNALLY VISIBLE FUNCTIONS
   =========================================
   ***************************************** */

#if (! BLOAD_ONLY) && (! RUN_TIME) && DEBUGGING_FUNCTIONS

/***************************************************
  NAME         : SaveDefclass
  DESCRIPTION  : Writes out the pretty-print forms
                 of a class and all its handlers
  INPUTS       : 1) The class
                 2) The logical name of the output
  RETURNS      : Nothing useful
  SIDE EFFECTS : Class and handlers written
  NOTES        : None
 ***************************************************/
static void SaveDefclass(
  Environment *theEnv,
  struct constructHeader *theConstruct,
  void *userBuffer)
  {
   const char *logName = (const char *) userBuffer;
   Defclass *theDefclass = (Defclass *) theConstruct;
   unsigned hnd;
   const char *ppForm;

   ppForm = EnvGetDefclassPPForm(theEnv,theDefclass);
   if (ppForm != NULL)
     {
      PrintInChunks(theEnv,logName,ppForm);
      EnvPrintRouter(theEnv,logName,"\n");
      hnd = EnvGetNextDefmessageHandler(theEnv,theDefclass,0);
      while (hnd != 0)
        {
         ppForm = EnvGetDefmessageHandlerPPForm(theEnv,theDefclass,hnd);
         if (ppForm != NULL)
           {
            PrintInChunks(theEnv,logName,ppForm);
            EnvPrintRouter(theEnv,logName,"\n");
           }
         hnd = EnvGetNextDefmessageHandler(theEnv,theDefclass,hnd);
        }
     }
  }

#endif

/***********************************************/
/* EnvSetClassDefaultsMode: Allows the setting */
/*    of the class defaults mode.              */
/***********************************************/
unsigned short EnvSetClassDefaultsMode(
  Environment *theEnv,
  unsigned short value)
  {
   unsigned short ov;

   ov = DefclassData(theEnv)->ClassDefaultsMode;
   DefclassData(theEnv)->ClassDefaultsMode = value;
   return(ov);
  }

/****************************************/
/* EnvGetClassDefaultsMode: Returns the */
/*    value of the class defaults mode. */
/****************************************/
unsigned short EnvGetClassDefaultsMode(
  Environment *theEnv)
  {
   return DefclassData(theEnv)->ClassDefaultsMode;
  }

/***************************************************/
/* GetClassDefaultsModeCommand: H/L access routine */
/*   for the get-class-defaults-mode command.      */
/***************************************************/
void GetClassDefaultsModeCommand(
  Environment *theEnv,
  UDFContext *context,
  UDFValue *returnValue)
  {
   returnValue->lexemeValue = EnvCreateSymbol(theEnv,GetClassDefaultsModeName(EnvGetClassDefaultsMode(theEnv)));
  }

/***************************************************/
/* SetClassDefaultsModeCommand: H/L access routine */
/*   for the set-class-defaults-mode command.      */
/***************************************************/
void SetClassDefaultsModeCommand(
  Environment *theEnv,
  UDFContext *context,
  UDFValue *returnValue)
  {
   UDFValue theArg;
   const char *argument;
   unsigned short oldMode;

   oldMode = DefclassData(theEnv)->ClassDefaultsMode;

   /*=====================================================*/
   /* Check for the correct number and type of arguments. */
   /*=====================================================*/

   if (! UDFFirstArgument(context,SYMBOL_TYPE,&theArg))
     { return; }

   argument = theArg.lexemeValue->contents;

   /*=============================================*/
   /* Set the strategy to the specified strategy. */
   /*=============================================*/

   if (strcmp(argument,"conservation") == 0)
     { EnvSetClassDefaultsMode(theEnv,CONSERVATION_MODE); }
   else if (strcmp(argument,"convenience") == 0)
     { EnvSetClassDefaultsMode(theEnv,CONVENIENCE_MODE); }
   else
     {
      UDFInvalidArgumentMessage(context,"symbol with value conservation or convenience");
      returnValue->lexemeValue = EnvCreateSymbol(theEnv,GetClassDefaultsModeName(EnvGetClassDefaultsMode(theEnv)));
      return;
     }

   /*===================================*/
   /* Return the old value of the mode. */
   /*===================================*/

   returnValue->lexemeValue = EnvCreateSymbol(theEnv,GetClassDefaultsModeName(oldMode));
  }

/*******************************************************************/
/* GetClassDefaultsModeName: Given the integer value corresponding */
/*   to a specified class defaults mode, return a character string */
/*   of the class defaults mode's name.                            */
/*******************************************************************/
static const char *GetClassDefaultsModeName(
  unsigned short mode)
  {
   const char *sname;

   switch (mode)
     {
      case CONSERVATION_MODE:
        sname = "conservation";
        break;
      case CONVENIENCE_MODE:
        sname = "convenience";
        break;
      default:
        sname = "unknown";
        break;
     }

   return(sname);
  }

/*#############################*/
/* Additional Access Functions */
/*#############################*/

CLIPSLexeme *GetDefclassNamePointer(
  Defclass *theClass)
  {
   return GetConstructNamePointer((struct constructHeader *) theClass);
  }

void SetNextDefclass(
  Defclass *theClass,
  Defclass *targetClass)
  {
   SetNextConstruct((struct constructHeader *) theClass,
                    (struct constructHeader *) targetClass);
  }

/*##################################*/
/* Additional Environment Functions */
/*##################################*/

const char *EnvGetDefclassName(
  Environment *theEnv,
  Defclass *theClass)
  {
   return EnvGetConstructNameString(theEnv,(struct constructHeader *) theClass);
  }

const char *EnvGetDefclassPPForm(
  Environment *theEnv,
  Defclass *theClass)
  {
   return GetConstructPPForm(theEnv,(struct constructHeader *) theClass);
  }

struct defmoduleItemHeader *EnvGetDefclassModule(
  Environment *theEnv,
  Defclass *theClass)
  {
   return GetConstructModuleItem((struct constructHeader *) theClass);
  }

const char *EnvDefclassModule(
  Environment *theEnv,
  Defclass *theClass)
  {
   return GetConstructModuleName((struct constructHeader *) theClass);
  }

void EnvSetDefclassPPForm(
  Environment *theEnv,
  Defclass *theClass,
  char *thePPForm)
  {
   SetConstructPPForm(theEnv,(struct constructHeader *) theClass,thePPForm);
  }

#endif /* OBJECT_SYSTEM */