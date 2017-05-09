
#include "CLIPSNET_Environment.h"

using namespace System;
using namespace System::Text;
using namespace System::Reflection;
using namespace System::IO;
using namespace CLIPS;

namespace CLIPSNET
  {	 
   DelegatePeriodicCallback::DelegatePeriodicCallback() 
     {
     
     }

   void DelegatePeriodicCallback::Callback()
     {
      CallbackEvents();
     }

   /***************/
   /* Environment */
   /***************/
   Environment::Environment() : m_Env( new CLIPSCPPEnv ) 
     {
     
     }
   
   /****************/
   /* ~Environment */
   /****************/
   Environment::~Environment()
     {
      this->!Environment(); 
     }
     
   /****************/
   /* !Environment */
   /****************/
   Environment::!Environment()
     {
      delete m_Env; 
     }
 
   /************/
   /* ToString */
   /************/
   String ^ Environment::ToString()
     {
      long long envLong = (long long) m_Env;

      return gcnew String("<Environment-" + envLong + ">");
     }
    
   /***************/
   /* CommandLoop */
   /***************/
   void Environment::CommandLoop()
     { return m_Env->CommandLoop(); }

   /****************************/
   /* CommandLoopOnceThenBatch */
   /****************************/
   void Environment::CommandLoopOnceThenBatch()
     { 
      return m_Env->CommandLoopOnceThenBatch(); 
     }

   /***************/
   /* PrintBanner */
   /***************/
   void Environment::PrintBanner()
     { return m_Env->PrintBanner(); }

   /***************/
   /* PrintPrompt */
   /****************/
   void Environment::PrintPrompt()
     { return m_Env->PrintPrompt(); }

   /*******/
   /* Run */
   /*******/
   long long Environment::Run()
     { return m_Env->Run(-1LL); }

   /*******/
   /* Run */
   /*******/
   long long Environment::Run(
     long long runLimit)
     { return m_Env->Run(runLimit); }

   /*********/
   /* Reset */
   /*********/
   void Environment::Reset()
     { return m_Env->Reset(); }

   /********/
   /* Load */
   /********/
   int Environment::Load(
     String ^ fileName)
     {
      array<Byte>^ ebFileName = Encoding::UTF8->GetBytes(fileName);
      if (ebFileName->Length)
        {
         pin_ptr<Byte> pbFileName = &ebFileName[0];
         return m_Env->Load((char *) pbFileName);
        }
      else
        { return m_Env->Load(""); }
     }
     
   /******************/
   /* LoadFromString */
   /******************/
   void Environment::LoadFromString(
     String ^ loadString)
     {
      array<Byte>^ ebLoadString = Encoding::UTF8->GetBytes(loadString);
      if (ebLoadString->Length)
        {
         pin_ptr<Byte> pbLoadString = &ebLoadString[0];
         m_Env->LoadFromString((char *) pbLoadString);
        }
      else 
        { m_Env->LoadFromString(""); }
     }

   /********************/
   /* LoadFromResource */
   /********************/
   bool Environment::LoadFromResource(
     String ^ assemblyName,
     String ^ resourceName)
     {
      Assembly ^ assembly = System::Reflection::Assembly::Load(assemblyName);
      Stream ^ stream = assembly->GetManifestResourceStream(resourceName);
      if (stream == nullptr) return false;
      StreamReader ^ reader = gcnew StreamReader(stream);
      String ^ resourceContent = reader->ReadToEnd();

      this->LoadFromString(resourceContent);
      return true;
     }
     
   /*********/
   /* Build */
   /*********/
   bool Environment::Build(
     String ^ buildString)
     {
      array<Byte>^ ebBuildString = Encoding::UTF8->GetBytes(buildString);
      if (ebBuildString->Length)
        {
         pin_ptr<Byte> pbBuildString = &ebBuildString[0];
         return m_Env->Build((char *) pbBuildString);
        }
      else
        { return m_Env->Build(""); }
     }
     
   /********/
   /* Eval */
   /********/
   PrimitiveValue ^ Environment::Eval(
     String ^ evalString)
     {
      PrimitiveValue ^ rv;
      array<Byte>^ ebEvalString = Encoding::UTF8->GetBytes(evalString);
      if (ebEvalString->Length)
        {
         pin_ptr<Byte> pbEvalString = &ebEvalString[0];
         rv = DataObjectToPrimitiveValue(m_Env->Eval((char *) pbEvalString));
        }
      else
        {  rv = DataObjectToPrimitiveValue(m_Env->Eval("")); }

      return rv;
     }
     
   /****************/
   /* AssertString */
   /****************/
   FactAddressValue ^ Environment::AssertString(
     String ^ factString)
     {
      CLIPS::FactAddressValue *frv;
      array<Byte>^ ebFactString = Encoding::UTF8->GetBytes(factString);
      if (ebFactString->Length)
        {
         pin_ptr<Byte> pbFactString = &ebFactString[0];
         frv = m_Env->AssertString((char *) pbFactString);
        }
      else
        { frv = m_Env->AssertString(""); }

      if (frv == NULL) return (nullptr);
      
      return gcnew FactAddressValue(frv);
     }
     
   /*************/
   /* AddRouter */
   /*************/
   void Environment::AddRouter(
	  String ^ routerName,
	  int priority,
	  Router ^ theRouter)
     { 
      array<Byte>^ ebRouterName = Encoding::UTF8->GetBytes(routerName);
      if (ebRouterName->Length)
        {
         pin_ptr<Byte> pbRouterName = &ebRouterName[0];
         m_Env->AddRouter((char *) pbRouterName,priority,(CLIPS::CLIPSCPPRouter *) theRouter->RouterBridge());
        }
      else
        { m_Env->AddRouter("",priority,(CLIPS::CLIPSCPPRouter *) theRouter->RouterBridge()); }
     }

   /****************/
   /* DeleteRouter */
   /****************/
   void Environment::DeleteRouter(
	  String ^ routerName)
     { 
      array<Byte>^ ebRouterName = Encoding::UTF8->GetBytes(routerName);
      if (ebRouterName->Length)
        {
         pin_ptr<Byte> pbRouterName = &ebRouterName[0];
         m_Env->DeleteRouter((char *) pbRouterName);
        }
      else
        { m_Env->DeleteRouter(""); }
     }
  
   /***********************/
   /* AddPeriodicCallback */
   /***********************/
   void Environment::AddPeriodicCallback(
	  String ^ callbackName,
	  int priority,
	  PeriodicCallback ^ theCallback)
     { 
      array<Byte>^ ebCallbackName = Encoding::UTF8->GetBytes(callbackName);
      if (ebCallbackName->Length)
        {
         pin_ptr<Byte> pbCallbackName = &ebCallbackName[0];
         m_Env->AddPeriodicFunction((char *) pbCallbackName,priority,(CLIPS::CLIPSCPPPeriodicFunction *) theCallback->PeriodicCallbackBridge());
        }
      else
        { m_Env->AddPeriodicFunction("",priority,(CLIPS::CLIPSCPPPeriodicFunction *) theCallback->PeriodicCallbackBridge()); }
     }

   /**************************/
   /* RemovePeriodicCallback */
   /**************************/
   void Environment::RemovePeriodicCallback(
	  String ^ callbackName)
     { 
      array<Byte>^ ebCallbackName = Encoding::UTF8->GetBytes(callbackName);
      if (ebCallbackName->Length)
        {
         pin_ptr<Byte> pbCallbackName = &ebCallbackName[0];
         m_Env->DeleteRouter((char *) pbCallbackName);
        }
      else
        { m_Env->RemovePeriodicFunction(""); }
     }

   /***************************/
   /* EnablePeriodicFunctions */
   /***************************/
   bool Environment::EnablePeriodicFunctions(
     bool value)
     {
      return m_Env->EnablePeriodicFunctions(value);
     }

   /********************/
   /* InputBufferCount */
   /********************/
   size_t Environment::InputBufferCount()
     { 
      return m_Env->InputBufferCount();
     }   
   
   /*******************/
   /* getInputBuffer: */
   /*******************/
   String ^ Environment::GetInputBuffer()
     {
      const char *inputBuffer;

      inputBuffer = m_Env->GetInputBuffer();
      if (inputBuffer == NULL)
        { return gcnew String(""); }
      
      return gcnew String(inputBuffer,0, (int) strlen(inputBuffer), UTF8Encoding::UTF8);
     }

   /*******************/
   /* setInputBuffer: */
   /*******************/
   void Environment::SetInputBuffer(
     String ^ commandString)
     {
      array<Byte>^ ebCommandString = Encoding::UTF8->GetBytes(commandString);    

      if (ebCommandString->Length)
        {  
         pin_ptr<Byte> pbCommandString = &ebCommandString[0];
         m_Env->SetInputBuffer((char *) pbCommandString);
        }
      else
        { m_Env->SetInputBuffer(""); }   
     }

   /*******************************/
   /* InputBufferContainsCommand: */
   /*******************************/
   bool Environment::InputBufferContainsCommand()
     {
      return m_Env->InputBufferContainsCommand();
     }
   
   /********************/
   /* AppendToDribble: */
   /********************/
   void Environment::AppendToDribble(
     String ^ commandString)
     {
      array<Byte>^ ebCommandString = Encoding::UTF8->GetBytes(commandString);    

      if (ebCommandString->Length)
        {  
         pin_ptr<Byte> pbCommandString = &ebCommandString[0];
         m_Env->AppendToDribble((char *) pbCommandString);
        }
     }

   /********************/
   /* GetHaltExecution */
   /********************/
   bool Environment::GetHaltExecution()
     { 
      if (m_Env->GetHaltExecution() == 0)
        { return false; }
      else
        { return true; }
     }

   /********************/
   /* SetHaltExecution */
   /********************/
   void Environment::SetHaltExecution(bool value)
     { m_Env->SetHaltExecution(value); }


   /***************************/
   /* SetHaltCommandLoopBatch */
   /***************************/
   void Environment::SetHaltCommandLoopBatch(bool value)
     { m_Env->SetHaltCommandLoopBatch(value); }

   /**********************/
   /* GetEvaluationError */
   /**********************/
   bool Environment::GetEvaluationError()
     {
      if (m_Env->GetEvaluationError() == 0)
        { return false; }
      else
        { return true; }
     }
     
   /**********************/
   /* SetEvaluationError */
   /**********************/
   void Environment::SetEvaluationError(bool value)
     {
      m_Env->SetEvaluationError(value);
     }

   /****************/
   /* GetHaltRules */
   /****************/
   bool Environment::GetHaltRules()
     {
      if (m_Env->GetHaltRules() == 0)
        { return false; }
      else
       { return true; }
     }
     
   /****************/
   /* SetHaltRules */
   /****************/
   void Environment::SetHaltRules(bool value)
     {
      m_Env->SetHaltRules(value);
     }

   /********************/
   /* ChangeDirectory: */
   /********************/
   bool Environment::ChangeDirectory(
     String ^ directoryString)
     {
      array<Byte>^ ebDirectoryString = Encoding::UTF8->GetBytes(directoryString);    
      int rv;

      if (ebDirectoryString->Length)
        {  
         pin_ptr<Byte> pbDirectoryString = &ebDirectoryString[0];
         rv = m_Env->ChangeDirectory((char *) pbDirectoryString);
        }
      else
        { rv =  m_Env->ChangeDirectory(""); }   

      if (rv == 0) return false;
      else return true;
     }

   /*****************/
   /* GetFocusStack */
   /*****************/
   FocusStack ^ Environment::GetFocusStack()
     {
      CLIPSCPPFocusStack *theCPPStack = m_Env->GetFocusStack();
      CLIPSCPPFocus *theCPPFocus;
      FocusStack ^ theStack;
      size_t i;
      std::vector<CLIPSCPPFocus *> *v;
      std::string *theCPPString;
	   const char *theCString;
	   List<Focus ^> ^ theList;

      v = theCPPStack->GetStack();

      theList = gcnew List<Focus ^>;

      for (i = 0; i < v->size(); i++)
        {
         theCPPFocus = v->at(i);
         theCPPString = theCPPFocus->GetModuleName();
		   theCString = theCPPString->c_str();
         theList->Add(gcnew Focus(gcnew String(theCString)));
        }

      theStack = gcnew FocusStack(theList);

      delete theCPPStack;

      return theStack;
     }

   /*************/
   /* GetAgenda */
   /*************/
   Agenda ^ Environment::GetAgenda(
     String ^ moduleName)
     {
      array<Byte>^ ebModuleNameString = Encoding::UTF8->GetBytes(moduleName);
      pin_ptr<Byte> pbModuleNameString;
      CLIPSCPPActivation *theCPPActivation;
      CLIPSCPPAgenda *theCPPAgenda;
      Agenda ^ theAgenda;
      size_t i;
      std::vector<CLIPSCPPActivation *> *v;
      std::string *theCPPRuleName, *theCPPBasis;
	   const char *theCRuleName, *theCBasis;
	   List<Activation ^> ^ theList;

      if (ebModuleNameString->Length == 0) return nullptr;
      pbModuleNameString = &ebModuleNameString[0];

      theCPPAgenda = m_Env->GetAgenda((char *) pbModuleNameString);

      v = theCPPAgenda->GetActivations();

      theList = gcnew List<Activation ^>;

      for (i = 0; i < v->size(); i++)
        {
         theCPPActivation = v->at(i);
         theCPPRuleName = theCPPActivation->GetRuleName();
		   theCRuleName = theCPPRuleName->c_str();
         theCPPBasis = theCPPActivation->GetBasis();
		   theCBasis = theCPPBasis->c_str();
         theList->Add(gcnew Activation(gcnew String(theCRuleName),theCPPActivation->GetSalience(),gcnew String(theCBasis)));
        }

      theAgenda = gcnew Agenda(theList);

      delete theCPPAgenda;

      return theAgenda;    
     }

   Agenda ^ Environment::GetAgenda(
     Focus ^ theFocus)
     {
      return GetAgenda(theFocus->ModuleName);
     }
 
   bool Environment::GetAgendaChanged()
     {
      return m_Env->GetAgendaChanged();
     }

   void Environment::SetAgendaChanged(
     bool newValue)
     {
      m_Env->SetAgendaChanged(newValue);
     }

   bool Environment::GetFocusChanged()
     {
      return m_Env->GetFocusChanged();
     }

   void Environment::SetFocusChanged(
     bool newValue)
     {
      m_Env->SetFocusChanged(newValue);
     }
  };



  	  
