   /*******************************************************/
   /*      "C" Language Integrated Production System      */
   /*                                                     */
   /*             CLIPS Version 6.40  06/20/16            */
   /*                                                     */
   /*                                                     */
   /*******************************************************/

/*************************************************************/
/* Purpose:                                                  */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Brian L. Dantes                                      */
/*                                                           */
/* Contributing Programmer(s):                               */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.23: Corrected compilation errors for files         */
/*            generated by constructs-to-c. DR0861           */
/*                                                           */
/*      6.24: Renamed BOOLEAN macro type to intBool.         */
/*                                                           */
/*      6.30: Borland C (IBM_TBC) and Metrowerks CodeWarrior */
/*            (MAC_MCW, IBM_MCW) are no longer supported.    */
/*                                                           */
/*            Added const qualifiers to remove C++           */
/*            deprecation warnings.                          */
/*                                                           */
/*            Converted API macros to function calls.        */
/*                                                           */
/*            Changed find construct functionality so that   */
/*            imported modules are search when locating a    */
/*            named construct.                               */
/*                                                           */
/*      6.40: Removed LOCALE definition.                     */
/*                                                           */
/*            Pragma once and other inclusion changes.       */
/*                                                           */
/*************************************************************/

#ifndef _H_classcom

#pragma once

#define _H_classcom

#define CONVENIENCE_MODE  0
#define CONSERVATION_MODE 1

#include "cstrccom.h"
#include "moduldef.h"
#include "object.h"
#include "symbol.h"

   const char             *EnvGetDefclassName(void *,void *);
   const char             *EnvGetDefclassPPForm(void *,void *);
   struct defmoduleItemHeader 
                                 *EnvGetDefclassModule(void *,void *);
   const char             *EnvDefclassModule(void *,void *);
   SYMBOL_HN              *GetDefclassNamePointer(void *);
   void                    SetNextDefclass(void *,void *);
   void                    EnvSetDefclassPPForm(void *,void *,char *);

   void                   *EnvFindDefclass(void *,const char *);
   void                   *EnvFindDefclassInModule(void *,const char *);
   DEFCLASS               *LookupDefclassByMdlOrScope(void *,const char *);
   DEFCLASS               *LookupDefclassInScope(void *,const char *);
   DEFCLASS               *LookupDefclassAnywhere(void *,struct defmodule *,const char *);
   bool                    DefclassInScope(void *,DEFCLASS *,struct defmodule *);
   void                   *EnvGetNextDefclass(void *,void *);
   bool                    EnvIsDefclassDeletable(void *,void *);

   void                    UndefclassCommand(UDFContext *,CLIPSValue *);
   unsigned short          EnvSetClassDefaultsMode(void *,unsigned short);
   unsigned short          EnvGetClassDefaultsMode(void *);
   void                    GetClassDefaultsModeCommand(UDFContext *,CLIPSValue *);
   void                    SetClassDefaultsModeCommand(UDFContext *,CLIPSValue *);

#if DEBUGGING_FUNCTIONS
   void                    PPDefclassCommand(UDFContext *,CLIPSValue *);
   void                    ListDefclassesCommand(UDFContext *,CLIPSValue *);
   void                    EnvListDefclasses(void *,const char *,struct defmodule *);
   bool                    EnvGetDefclassWatchInstances(void *,void *);
   void                    EnvSetDefclassWatchInstances(void *,bool,void *);
   bool                    EnvGetDefclassWatchSlots(void *,void *);
   void                    EnvSetDefclassWatchSlots(void *,bool,void *);
   bool                    DefclassWatchAccess(void *,int,bool,EXPRESSION *);
   bool                    DefclassWatchPrint(void *,const char *,int,EXPRESSION *);
#endif

   void                    GetDefclassListFunction(UDFContext *,CLIPSValue *);
   void                    EnvGetDefclassList(void *,DATA_OBJECT *,struct defmodule *);
   bool                    EnvUndefclass(void *,void *);
   bool                    HasSuperclass(DEFCLASS *,DEFCLASS *);

   SYMBOL_HN              *CheckClassAndSlot(UDFContext *,const char *,DEFCLASS **);

#if (! BLOAD_ONLY) && (! RUN_TIME)
   void                    SaveDefclasses(void *,void *,const char *);
#endif

#endif /* _H_classcom */
